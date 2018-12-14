function dd = dronemodel( u1,u2,u3,u4, theta, phi, csi, dtheta, dphi, dcsi)

m=0.4;
Ix=0.002;
Iy=0.0016;
Iz=0.0035;
b=192.32*10^(-7);
d=1*10^(-7);
l=0.1778;
g=9.8;
c=1.9712;

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
 
 Utheta=u3;
 Uphi=u2; 
 Ucsi=u4;
 Ucoll=u1+m*g;
 
 %Ucoll=m*g+delta_Ucoll;
 
 %F1=b*c^2*u1^2;F2=b*c^2*u2^2;F3=b*c^2*u3^2;F4=b*c^2*u4^2;
 %tau1=d*c^2*u1^2;tau2=d*c^2*u2^2;tau3=d*c^2*u3^2;tau4=d*c^2*u4^2;
 
 %Ucol=F1+F2+F3+F4;
 %Uphi=l*(F1-F3);
 %Utheta=l*(-F4+F2);
 %Ucsi=tau1+tau3-tau2-tau4;
 
 ddx=(cos(phi)*sin(theta)*cos(csi)+sin(phi)*sin(csi))*Ucoll/m;
 ddy=(cos(phi)*sin(theta)*sin(csi)-sin(phi)*cos(csi))*Ucoll/m;
 ddz=-g+cos(phi)*cos(theta)*Ucoll/m;
 ddangle=Jinv*([Uphi;Utheta;Ucsi]-C*[dphi;dtheta;dcsi]);
 ddphi=ddangle(1);
 ddtheta=ddangle(2);
 ddcsi=ddangle(3);
  
 dd=[ddx;ddy;ddz;ddphi;ddtheta;ddcsi];
