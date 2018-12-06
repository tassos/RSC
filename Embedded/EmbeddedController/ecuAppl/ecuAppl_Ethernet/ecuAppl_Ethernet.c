/**
 * \file	ecuAppl_Ethernet.c
 * \brief	Ethernet functions
 * \details	Implements the functions for Ethernet controller and LWIP connections
 * \author	Cosmin Marcu
 * \date	18.11.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuAppl_Ethernet.h"
#include "lpc17xx_pinsel.h"

#include "ecuDrv_gpio.h"
#include "lpc17xx_emac.h"
#include "lwip/inet.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/api.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

err_t ethernetif_init(struct netif *netif);
void ethernetif_poll(void);

/**
 * \ingroup  ecuAppl_Ethernet
 * \defgroup eth_variables Ethernet Variables
 *  Global/shared Ethernet module variables
 *  @{
 */
/* Private variables */
PRIVATE_DATA struct netif rs_NetIf;									//!< Ethernet interface
PRIVATE_DATA T_UBYTE raub_IP[4u] = { 192u, 168u, 2u, 239u };		//!< IP address
PRIVATE_DATA T_UBYTE raub_GW[4u] = { 192u, 168u, 2u, 1u };			//!< Gateway address
PRIVATE_DATA T_UBYTE raub_NetMask[4u] = { 255u, 255u, 255u, 0u };	//!< Subnet mask
/**@} end of group eth_variables */

/* Private functions definition */
PRIVATE_FCT void ecuAppl_Ethernet_EmacConfig(void);

/**
 * \ingroup  ecuAppl_Ethernet
 * \defgroup eth_functions Ethernet Functions
 *  Functions definitions for Ethernet module
 *  @{
 */
/* Private functions implementation */
/**
 * \brief	Ethernet controller pin configuration
 * \return 	none
 */
PRIVATE_FCT void ecuAppl_Ethernet_EmacConfig(void)
{
  /* pin configuration */
  PINSEL_CFG_Type PinCfg;

  /*
   * Enable P1 Ethernet Pins:
   * P1.0 - ENET_TXD0
   * P1.1 - ENET_TXD1
   * P1.4 - ENET_TX_EN
   * P1.8 - ENET_CRS
   * P1.9 - ENET_RXD0
   * P1.10 - ENET_RXD1
   * P1.14 - ENET_RX_ER
   * P1.15 - ENET_REF_CLK
   * P1.16 - ENET_MDC
   * P1.17 - ENET_MDIO
   */
  PinCfg.Funcnum = 1;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Portnum = 1;

  PinCfg.Pinnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 1;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 4;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 8;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 9;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 10;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 14;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 15;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 16;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 17;
  PINSEL_ConfigPin(&PinCfg);
}

/**
 * \brief	Initializes Ethernet module
 * \return 	none
 */
T_E_ERROR ecuAppl_Ethernet_Init(void)
{
	  struct ip_addr ipaddr, netmask, gw;

	  ecuAppl_Ethernet_EmacConfig();

	  lwip_init();

	  IP4_ADDR(&ipaddr, raub_IP[0], raub_IP[1], raub_IP[2], raub_IP[3]);
	  IP4_ADDR(&gw, raub_GW[0], raub_GW[1], raub_GW[2], raub_GW[3]);
	  IP4_ADDR(&netmask, raub_NetMask[0], raub_NetMask[1], raub_NetMask[2], raub_NetMask[3]);

	  if (netif_add(&rs_NetIf, &ipaddr, &netmask, &gw, NULL, ethernetif_init, ip_input) == NULL)
	  {
		  return E_ERROR;
	  }

	  netif_set_default(&rs_NetIf);
	  netif_set_up(&rs_NetIf);

	  return E_SUCCESS;
}
/**@} end of group nfc_functions */

/**
 * \ingroup  ecu_tasks
 * \defgroup eth_tasks Ethernet Tasks
 *  Tasks definitions for Ethernet module
 *  @{
 */
/**
 * \brief	Periodic 2s Ethernet task
 * \return 	none
 */
void ecuAppl_Ethernet_Task_2s(void)
{
	ethernetif_poll();
}
/**@} end of group eth_tasks */
