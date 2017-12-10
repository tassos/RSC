/**
 * \file	ecuAppl_TCPHandler.c
 * \brief	TCP Handler functions
 * \details	Implements the functions for TCP Handler module
 * \author	Cosmin Marcu
 * \date	18.11.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuAppl_TCPHandler.h"
#include "ecuAppl_Pot.h"
#include "lwip/inet.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/api.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"

/**
 * \ingroup  ecuAppl_TCP
 * \defgroup tcp_defines TCP Handler Defines
 *  Preprocessor defines for TCP Handler module
 *  @{
 */
/* Defines */
#define TCPHANDLER_FUNC_MEMALLOC(x)			mem_malloc(x)			//!< LWIP mem_alloc
#define TCPHANDLER_FUNC_MEMFREE(x)			mem_free(x)				//!< LWIP mem_free
#define TCPHANDLER_FUNC_TCP_SETPRIO(x,y)	tcp_setprio(x,y)		//!< LWIP tcp_setprio
#define TCPHANDLER_FUNC_TCP_ARG(x,y) 		tcp_arg(x,y)			//!< LWIP tcp_arg
#define TCPHANDLER_FUNC_TCP_SENT(x,y) 		tcp_sent(x,y)			//!< LWIP tcp_sent
#define TCPHANDLER_FUNC_TCP_RECV(x,y) 		tcp_recv(x,y)			//!< LWIP tcp_recv
#define TCPHANDLER_FUNC_TCP_RECVED(x,y) 	tcp_recved(x,y)			//!< LWIP tcp_recved
#define TCPHANDLER_FUNC_TCP_ERR(x,y) 		tcp_err(x,y)			//!< LWIP tcp_err
#define TCPHANDLER_FUNC_TCP_POLL(x,y,z) 	tcp_poll(x,y,z)			//!< LWIP tcp_poll
#define TCPHANDLER_FUNC_TCP_CLOSE(x) 		tcp_close(x)			//!< LWIP tcp_close
#define TCPHANDLER_FUNC_TCP_NEW(x) 			tcp_new()				//!< LWIP tcp_new
#define TCPHANDLER_FUNC_TCP_BIND(x,y,z)		tcp_bind(x,y,z)			//!< LWIP tcp_bind
#define TCPHANDLER_FUNC_TCP_LISTEN(x) 		tcp_listen(x)			//!< LWIP tcp_listen
#define TCPHANDLER_FUNC_TCP_ACCEPT(x,y) 	tcp_accept(x,y)			//!< LWIP tcp_accept
#define TCPHANDLER_FUNC_PBUF_REF(x) 		pbuf_ref(x)				//!< LWIP pbuf_ref
#define TCPHANDLER_FUNC_PBUF_FREE(x) 		pbuf_free(x)			//!< LWIP pbuf_free
#define TCPHANDLER_FUNC_PBUF_CHAIN(x,y) 	pbuf_chain(x,y)			//!< LWIP pbuf_chain
/**@} end of group tcp_defines */

/**
 * \ingroup  ecuAppl_TCP
 * \defgroup tcp_typedefs TCP Handler Types
 *  Types definition for TCP Handler module
 *  @{
 */
#define T_S_TCPHANDLER_PCB 					struct tcp_pcb			//!< TCP PCB structure
#define T_S_TCPHANDLER_PBUF					struct pbuf				//!< TCP PBUF structure
#define	T_E_TCPHANDLER_ERROR 				err_t					//!< TCP error

/**
 * @brief	Defines TCP RX states
 */
typedef enum E_TCPHANDLER_RX_STATE {
  E_TCPHANDLER_RX_STATE_NONE = 0,				//!< Rx Idle state
  E_TCPHANDLER_RX_STATE_ACCEPTED,				//!< Rx Accepted state
  E_TCPHANDLER_RX_STATE_RECEIVED,				//!< Rx Receiving state
  E_TCPHANDLER_RX_STATE_CLOSING					//!< Rx Closing state
} T_E_TCPHANDLER_RX_STATE;

/**
 * @brief	TCP RX structure
 */
typedef struct {
  T_UBYTE ub_State;						//!< Connection state
  T_UBYTE ub_Retries;					//!< Number of retries
  T_S_TCPHANDLER_PCB *ps_PCB;			//!< PCB pointer
  T_S_TCPHANDLER_PBUF *ps_PBUF;			//!< PBUF pointer
} T_S_TCPHANDLER_CONNECTION;
/**@} end of group tcp_typedefs */

/**
 * \ingroup  ecuAppl_TCP
 * \defgroup tcp_variables TCP Handler Variables
 *  Global/shared TCP Handler module variables
 *  @{
 */
/* Private variables */
PRIVATE_DATA T_S_TCPHANDLER_PCB *prs_PCB;			//!< Global PCB structure
/**@} end of group tcp_variables */
double raub_buf[4];
/**
 * \ingroup  ecuAppl_TCP
 * \defgroup tcp_functions TCP Handler Functions
 *  Functions definitions for TCP Handler module
 *  @{
 */
/* Private functions definition */
PRIVATE_FCT T_E_TCPHANDLER_ERROR ecuAppl_TCPHandler_Accept(void *pv_arg, T_S_TCPHANDLER_PCB *lps_NewPCB, T_E_TCPHANDLER_ERROR le_Error);
PRIVATE_FCT T_E_TCPHANDLER_ERROR ecuAppl_TCPHandler_Receive(void *pv_arg, T_S_TCPHANDLER_PCB *lps_PCB, T_S_TCPHANDLER_PBUF *lps_PBUF, T_E_TCPHANDLER_ERROR le_Error);
PRIVATE_FCT void ecuAppl_TCPHandler_Error(void *pv_arg, T_E_TCPHANDLER_ERROR le_Error);
PRIVATE_FCT T_E_TCPHANDLER_ERROR ecuAppl_TCPHandler_Sent(void *pv_arg, T_S_TCPHANDLER_PCB *lps_PCB, T_UWORD luw_Length);
PRIVATE_FCT void ecuAppl_TCPHandler_Send(T_S_TCPHANDLER_PCB *lps_PCB, T_S_TCPHANDLER_CONNECTION *lps_Conn);
PRIVATE_FCT void ecuAppl_TCPHandler_Close(T_S_TCPHANDLER_PCB *lps_PCB, T_S_TCPHANDLER_CONNECTION *lps_Conn);

static void udpecho_raw_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port);
void udpecho_raw_server_init(u16_t port);

/**
 * \brief	Callback for TCP accept connections
 * \param	pv_arg	Pointer to arguments
 * \param	lps_NewPCB New PCB structure
 * \param	le_Error TCP error
 * \return 	ERR_OK if memory allocated successfully
 * 			ERR_MEM otherwise
 */
PRIVATE_FCT T_E_TCPHANDLER_ERROR ecuAppl_TCPHandler_Accept(void *pv_arg, T_S_TCPHANDLER_PCB *lps_NewPCB, T_E_TCPHANDLER_ERROR le_Error)
{
	T_E_TCPHANDLER_ERROR le_Return;
	T_S_TCPHANDLER_CONNECTION *lps_Connection;

	LWIP_UNUSED_ARG(pv_arg);
	LWIP_UNUSED_ARG(le_Error);

	/* commonly observed practice to call tcp_setprio(), why? */
	TCPHANDLER_FUNC_TCP_SETPRIO(lps_NewPCB, TCP_PRIO_MIN);

	lps_Connection = (T_S_TCPHANDLER_CONNECTION *)TCPHANDLER_FUNC_MEMALLOC(sizeof(T_S_TCPHANDLER_CONNECTION));
	if (lps_Connection != NULL)
	{
		lps_Connection->ub_State = E_TCPHANDLER_RX_STATE_ACCEPTED;
		lps_Connection->ps_PCB = lps_NewPCB;
		lps_Connection->ub_Retries = 0;
		lps_Connection->ps_PBUF = NULL;
		/* pass newly allocated lps_Connection to our callbacks */
		TCPHANDLER_FUNC_TCP_ARG(lps_NewPCB, lps_Connection);
		TCPHANDLER_FUNC_TCP_RECV(lps_NewPCB, ecuAppl_TCPHandler_Receive);
		TCPHANDLER_FUNC_TCP_ERR(lps_NewPCB, ecuAppl_TCPHandler_Error);
		//    TCPHANDLER_FUNC_TCP_POLL(newpcb, echo_poll, 0);
		le_Return = ERR_OK;
	}
	else
	{
		le_Return = ERR_MEM;
	}
	return le_Return;
}

/**
 * \brief	Callback for TCP receive
 * \param	pv_arg	Pointer to arguments
 * \param	lps_PCB PCB structure
 * \param	lps_PBUF PBUF structure
 * \param	le_Error TCP error
 * \return 	ERR_OK if packet received successfully
 * 			ERR_MEM otherwise
 */
PRIVATE_FCT T_E_TCPHANDLER_ERROR ecuAppl_TCPHandler_Receive(void *pv_arg, T_S_TCPHANDLER_PCB *lps_PCB, T_S_TCPHANDLER_PBUF *lps_PBUF, T_E_TCPHANDLER_ERROR le_Error)
{
	T_S_TCPHANDLER_CONNECTION *lps_Connection;
	T_E_TCPHANDLER_ERROR le_Return;
	T_S_TCPHANDLER_PBUF *lps_LocalPBUF;
	T_UBYTE laub_buf[9] = {'R', 'E', 'C', 'V',' ','o','k','\n','\r'};

	lps_Connection = (T_S_TCPHANDLER_CONNECTION *)pv_arg;
	if (lps_PBUF == NULL)
	{
		/* remote host closed connection */
		lps_Connection->ub_State = E_TCPHANDLER_RX_STATE_CLOSING;
		if(lps_Connection->ps_PBUF == NULL)
		{
			/* we're done sending, close it */
			ecuAppl_TCPHandler_Close(lps_PCB, lps_Connection);
		}
		else
		{
			/* we're not done yet */
			//TODO: add send data
			TCPHANDLER_FUNC_TCP_SENT(lps_PCB, ecuAppl_TCPHandler_Sent);
			ecuAppl_TCPHandler_Send(lps_PCB, lps_Connection);
		}
		le_Return = ERR_OK;
	}
	else if(le_Error != ERR_OK)
	{
		/* cleanup, for unknown reason */
		if (lps_PBUF != NULL)
		{
		  lps_Connection->ps_PBUF = NULL;
		  TCPHANDLER_FUNC_PBUF_FREE(lps_PBUF);
		}
		le_Return = le_Error;
	}
	else if(lps_Connection->ub_State == E_TCPHANDLER_RX_STATE_ACCEPTED)
	{
		/* first data chunk in p->payload */
		lps_Connection->ub_State = E_TCPHANDLER_RX_STATE_RECEIVED;
		/* store reference to incoming pbuf (chain) */
		lps_Connection->ps_PBUF = lps_PBUF;
		lps_Connection->ps_PBUF->payload = laub_buf;
		lps_Connection->ps_PBUF->len = 9u;
		lps_Connection->ps_PBUF->tot_len = 9u;
		/* install send completion notifier */
		//TODO: add send data
		TCPHANDLER_FUNC_TCP_SENT(lps_PCB, ecuAppl_TCPHandler_Sent);
		ecuAppl_TCPHandler_Send(lps_PCB, lps_Connection);
		le_Return = ERR_OK;
	}
	else if (lps_Connection->ub_State == E_TCPHANDLER_RX_STATE_RECEIVED)
	{
		/* read some more data */
		if(lps_Connection->ps_PBUF == NULL)
		{
			lps_Connection->ps_PBUF = lps_PBUF;
			//TODO: add send data
			lps_Connection->ps_PBUF->payload = laub_buf;
			lps_Connection->ps_PBUF->len = 9u;
			lps_Connection->ps_PBUF->tot_len = 9u;
			TCPHANDLER_FUNC_TCP_SENT(lps_PCB, ecuAppl_TCPHandler_Sent);
			ecuAppl_TCPHandler_Send(lps_PCB, lps_Connection);
		}
		else
		{
			/* chain pbufs to the end of what we recv'ed previously  */
			lps_LocalPBUF = lps_Connection->ps_PBUF;
			TCPHANDLER_FUNC_PBUF_CHAIN(lps_LocalPBUF,lps_PBUF);
		}
		le_Return = ERR_OK;
	}
	else if(lps_Connection->ub_State == E_TCPHANDLER_RX_STATE_CLOSING)
	{
		/* odd case, remote side closing twice */
		TCPHANDLER_FUNC_TCP_RECVED(lps_PCB, lps_PBUF->tot_len);
		lps_Connection->ps_PBUF = NULL;
		TCPHANDLER_FUNC_PBUF_FREE(lps_PBUF);
		le_Return = ERR_OK;
	}
	else
	{
		/* unknown lps_Connection->state */
		TCPHANDLER_FUNC_TCP_RECVED(lps_PCB, lps_PBUF->tot_len);
		lps_Connection->ps_PBUF = NULL;
		TCPHANDLER_FUNC_PBUF_FREE(lps_PBUF);
		le_Return = ERR_OK;
	}
	return le_Return;
}

/**
 * \brief	Callback for TCP error
 * \param	pv_arg	Pointer to arguments
 * \param	le_Error TCP error
 * \return 	None
 */
PRIVATE_FCT void ecuAppl_TCPHandler_Error(void *pv_arg, T_E_TCPHANDLER_ERROR le_Error)
{
	T_S_TCPHANDLER_CONNECTION *lps_Connection;

	LWIP_UNUSED_ARG(le_Error);

	lps_Connection = (T_S_TCPHANDLER_CONNECTION *)pv_arg;
	if (lps_Connection != NULL)
	{
		/* Free connection memory */
		TCPHANDLER_FUNC_MEMFREE(lps_Connection);
	}
}

/**
 * \brief	Callback for TCP sent
 * \param	pv_arg	Pointer to arguments
 * \param	lps_PCB	PCB structure
 * \param	luw_Length Packet length (unused)
 * \return 	ERR_OK if packet received successfully
 * 			ERR_MEM otherwise
 */
PRIVATE_FCT T_E_TCPHANDLER_ERROR ecuAppl_TCPHandler_Sent(void *pv_arg, T_S_TCPHANDLER_PCB *lps_PCB, T_UWORD luw_Length)
{
	T_S_TCPHANDLER_CONNECTION *lps_Connection;

	LWIP_UNUSED_ARG(luw_Length);

	lps_Connection = (T_S_TCPHANDLER_CONNECTION *)pv_arg;
	lps_Connection->ub_Retries = 0;

	if(lps_Connection->ps_PBUF != NULL)
	{
		/* still got pbufs to send */
		TCPHANDLER_FUNC_TCP_SENT(lps_PCB, ecuAppl_TCPHandler_Sent);
		ecuAppl_TCPHandler_Send(lps_PCB, lps_Connection);
	}
	else
	{
		/* no more pbufs to send */
		if(lps_Connection->ub_State == E_TCPHANDLER_RX_STATE_CLOSING)
		{
			ecuAppl_TCPHandler_Close(lps_PCB, lps_Connection);
		}
	}
	return ERR_OK;
}

/**
 * \brief	Callback for TCP sent
 * \param	lps_PCB	PCB strucure
 * \param	lps_Conn Connection handler
 * \return 	None
 */
PRIVATE_FCT void ecuAppl_TCPHandler_Send(T_S_TCPHANDLER_PCB *lps_PCB, T_S_TCPHANDLER_CONNECTION *lps_Conn)
{
	T_S_TCPHANDLER_PBUF *lps_PBUF;
	T_E_TCPHANDLER_ERROR le_WriteError = ERR_OK;
	T_UWORD luw_Len = 0u;
	T_UBYTE lub_isFree = FALSE;

	while ((le_WriteError == ERR_OK) && (lps_Conn->ps_PBUF != NULL) &&  (lps_Conn->ps_PBUF->len <= tcp_sndbuf(lps_PCB)))
	{
		lps_PBUF = lps_Conn->ps_PBUF;
		/* enqueue data for transmission */
		le_WriteError = tcp_write(lps_PCB, lps_PBUF->payload, lps_PBUF->len, 1);
		if (le_WriteError == ERR_OK)
		{
			luw_Len = lps_PBUF->len;
			/* continue with next pbuf in chain (if any) */
			lps_Conn->ps_PBUF = lps_PBUF->next;
			if(lps_Conn->ps_PBUF != NULL)
			{
			  /* new reference! */
			  TCPHANDLER_FUNC_PBUF_REF(lps_Conn->ps_PBUF);
			}
			/* chop first pbuf from chain */
			do
			{
			  /* try hard to free pbuf */
				lub_isFree = TCPHANDLER_FUNC_PBUF_FREE(lps_PBUF);
			}
			while(lub_isFree == FALSE);
			/* we can read more data now */
			TCPHANDLER_FUNC_TCP_RECVED(lps_PCB, luw_Len);
		}
		else if(le_WriteError == ERR_MEM)
		{
			/* we are low on memory, try later / harder, defer to poll */
			lps_Conn->ps_PBUF = lps_PBUF;
		}
		else
		{
			/* other problem ?? */
		}
	}
}

/**
 * \brief	Callback for TCP sent
 * \param	lps_PCB	PCB strucure
 * \param	lps_Conn Connection handler
 * \return 	None
 */
PRIVATE_FCT void ecuAppl_TCPHandler_Close(T_S_TCPHANDLER_PCB *lps_PCB, T_S_TCPHANDLER_CONNECTION *lps_Conn)
{
	TCPHANDLER_FUNC_TCP_ARG(lps_PCB, NULL);
	TCPHANDLER_FUNC_TCP_SENT(lps_PCB, NULL);
	TCPHANDLER_FUNC_TCP_RECV(lps_PCB, NULL);
	TCPHANDLER_FUNC_TCP_ERR(lps_PCB, NULL);
	TCPHANDLER_FUNC_TCP_POLL(lps_PCB, NULL, 0);

	if (lps_Conn != NULL)
	{
		/* Free connection memory */
		TCPHANDLER_FUNC_MEMFREE(lps_Conn);
	}
	TCPHANDLER_FUNC_TCP_CLOSE(lps_PCB);
}

union u_t {
	T_UBYTE buffer[8];
	double d;
};

static T_UBYTE global_state = 0;

void rcpot_SetState (T_UBYTE state)
{
	global_state = state;
}

static void udpecho_raw_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port)
{
	struct pbuf pl;
	double tau1;
	double tau2;
	double luw_PotValue;
	static double setpoint = 0;

	setpoint = (double)(ecuAppl_Pot_GetPotValue());

	LWIP_UNUSED_ARG(arg);
	if(p == NULL)
		return;

	union u_t q1;
	union u_t q2;
	union u_t time;

	T_UBYTE *bigBuffer;
	bigBuffer = p->payload;

	memcpy(q1.buffer,&bigBuffer[0],8);
	memcpy(q2.buffer,&bigBuffer[8],8);
	memcpy(time.buffer,&bigBuffer[16],8);

	raub_buf[0] = tau1;
	raub_buf[1] = tau2;
	raub_buf[2] = setpoint;
	raub_buf[3] = setpoint;

	pl.flags = p->flags;
	pl.len = 32;
	pl.next = NULL;
	pl.payload = &raub_buf[0];
	pl.ref = p->ref;
	pl.tot_len = 32u;
	pl.len = 32u;
//	p->payload = raub_buf;
//	p->len = 8u;
//	p->tot_len = 8u;
//	T_UBYTE *lub_byte = p->payload;
//	T_UBYTE lub_size = p->len;
	udp_sendto(pcb, &pl, addr, 4000);
	pbuf_free(p);
}

/*-----------------------------------------------------------------------------------*/
void udpecho_raw_server_init(u16_t port)
{
	struct udp_pcb *pcb;

	pcb = udp_new();
	udp_bind(pcb, IP_ADDR_ANY, port);

	/* no need to loop forever */
	udp_recv(pcb , udpecho_raw_recv, pcb);
}

/**
 * \brief	Initializes TCP Handler module
 * \return 	none
 */
void ecuAppl_TCPHandler_Init(T_UWORD luw_Port)
{
	T_E_TCPHANDLER_ERROR le_Error;

	udpecho_raw_server_init(4000);
	prs_PCB = TCPHANDLER_FUNC_TCP_NEW();
	if (prs_PCB != NULL)
	{


		le_Error = TCPHANDLER_FUNC_TCP_BIND(prs_PCB, IP_ADDR_ANY, luw_Port);
		if (le_Error == ERR_OK)
		{
		  prs_PCB = TCPHANDLER_FUNC_TCP_LISTEN(prs_PCB);
		  TCPHANDLER_FUNC_TCP_ACCEPT(prs_PCB, ecuAppl_TCPHandler_Accept);
		}
		else
		{
		  /* abort? output diagnostic? */
		}
	}
	else
	{
	/* abort? output diagnostic? */
	}
}
/**@} end of group tcp_functions */
