% drone quadcopter - linear control

%% parameters

m=0.4472;
Ix=0.002;
Iy=0.0016;
Iz=0.0035;
b=192.32*10^(-7);
d=1*10^(-7);
l=0.1778;
g=9.8;
c=1.9712;


%% model
 syms theta phi csi dtheta dphi dcsi x y z dx dy dz
 
 J=[Ix 0 -Ix*sin(theta);
     0  Iy*(cos(phi))^2+Iz*(sin(phi))^2     (Iy-Iz)*cos(phi)*sin(phi)*cos(theta);
     -Ix*sin(theta)  (Iy-Iz)*cos(phi)*sin(phi)*cos(theta)   Ix*(sin(theta))^2+Iy*(sin(phi))^2*(cos(theta))^2+Iz*(cos(phi))^2*(cos(theta))^2];
 
 c11=0;
 c12=(Iy-Iz)*(dtheta*cos(phi)*sin(phi)+dphi*(sin(phi))^2*cos(theta))+(Iz-Iy)*dcsi*(cos(phi))^2*cos(theta)-Ix*dcsi*cos(theta);
 c13=(Iz-Iy)*dcsi*(cos(theta))^2*sin(phi)*cos(phi);
 c21=(Iz-Iy)*(dtheta*sin(phi)*cos(phi)+dphi*(sin(phi))^2*cos(theta))+(Iy-Iz)*dcsi*(cos(phi))^2*cos(theta)+Ix*dcsi*cos(theta);
 c22=(Iz-Iy)*dphi*cos(phi)*sin(phi);
 c23=-Ix*dcsi*sin(theta)*cos(theta)+Iy*dcsi*(sin(phi))^2*sin(theta)*cos(theta)+Iz*dcsi*(cos(phi))^2*sin(theta)*cos(theta);
 c31=(Iy-Iz)*dcsi*(cos(theta))^2*sin(phi)*cos(phi)-Ix*dtheta*cos(theta);
 c32=(Iz-Iy)*(dtheta*cos(phi)*sin(phi)*sin(theta)+dphi*(sin(phi))^2*cos(theta))+(Iy-Iz)*dphi*(cos(phi))^2*cos(theta)+Ix*dcsi*sin(theta)*cos(theta)-Iy*dcsi*(sin(phi))^2*sin(theta)*cos(theta)-Iz*dcsi*(cos(phi))^2*sin(theta)*cos(theta);
 c33=(Iy-Iz)*dphi*(cos(theta))^2*sin(phi)*cos(phi)-Iy*dtheta*(sin(phi))^2*sin(theta)*cos(theta)-Iz*dtheta*(cos(phi))^2*sin(theta)*cos(theta)+Ix*dtheta*sin(theta)*cos(theta);
 
 C=[c11 c12 c13;c21 c22 c23; c31 c32 c33];
 
 Jinv=inv(J);
 
 syms Utheta Uphi Ucsi delta_Ucoll
 
 Ucoll=m*g+delta_Ucoll;

 ddx=(cos(phi)*sin(theta)*cos(csi)+sin(phi)*sin(csi))*Ucoll/m;
 ddy=(cos(phi)*sin(theta)*sin(csi)-sin(phi)*cos(csi))*Ucoll/m;
 ddz=-g+cos(phi)*cos(theta)*Ucoll/m;
 ddangle=Jinv*([Uphi;Utheta;Ucsi]-C*[dphi;dtheta;dcsi]);
 ddphi=ddangle(1);
 ddtheta=ddangle(2);
 ddcsi=ddangle(3);
 
 %% linearization in hovering mode
 
 x=[x;y;z;phi;theta;csi;dx;dy;dz;dphi;dtheta;dcsi];
 
 x1=[dx;dy;dz;dphi;dtheta;dcsi];
 x2=[ddx;ddy;ddz;ddphi;ddtheta;ddcsi];
 x1=vpa(simplify(x1),5);
 x2=vpa(simplify(x2),5);
 f=[x1;x2];
 A=jacobian(f,x);
 dphi=0;
 dcsi=0;
 dtheta=0;
 theta=0;
 csi=0;
 phi=0;
 dx=0;
 dy=0;
 dz=0;
 
 B=jacobian(f,[delta_Ucoll;Uphi;Utheta;Ucsi]);
 B=eval(B);
  
 
 Utheta=0;
 Uphi=0;
 Ucsi=0;
 delta_Ucoll=0;
 A=eval(A);
 
 %% pole placement

 K=place(A,B,[-40 -41 -42 -4.1 -4.2 -4.3 -43 -44 -45 -4.4 -4.5 -4.6]*0.5)
 
