function output = my_robot(input)
    tau1=input(1);
    tau2=input(2);
    q1=input(3);
    q2=input(4);
    q1p=input(5);
    q2p=input(6);


    D=[0.003515*cos(q2) + 0.000925*cos(q2)^2 + 0.026254,        0;
         0, 0.023625];

    C=[0.24 - 0.0017575*q2p*sin(q2) - 0.0004625*q2p*sin(2.0*q2), - 0.0004625*q1p*sin(2.0*q2) - 0.0017575*q1p*sin(q2);
       0.0004625*q1p*sin(2.0*q2) + 0.0017575*q1p*sin(q2),                                                0.16];

    G = [ -1.7764e-20*sin(q1)*(1.0217e19*cos(q2) + 7.4761e18);
                                    -0.18149*cos(q1)*sin(q2)];

    output=D\(-C*[q1p;q2p]-G+[tau1;tau2]);
end