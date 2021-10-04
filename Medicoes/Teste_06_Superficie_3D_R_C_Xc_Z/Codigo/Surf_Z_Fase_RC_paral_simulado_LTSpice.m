close all;clear;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CÁLCULO IMPEDÂNCIA (Zload) REAL -  Resistor em paralelo com Capacitor
% Zload = Resistor // Capacitor
% Zload = 1/R + (-1/Xc)
% Xc = 1/2.PI.31250.Capacitor
% ModuloZ = raiz(R^2 + Xc^2) Ohms
% faseZ = arctan(Xc/R) rad/s
% autor Edson
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
freq = 31250;
omega = 2*pi()*freq;

Rload = [1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350 ];
Cload = [1.023e-6, 470e-9, 336.6e-9, 226e-9, 101.2e-9, 45.5e-9, 19.21e-9, 10.31e-9, 3.8e-9, 3.29e-9, 2.82e-9, 2.53e-9];


% C1 = 1.023e-6;
% C2 = 470e-9;

%InversoR = [ 1/R1 1/R2];
%InversoXc = [1/(omega*C1)^-1 1/(omega*C2)^-1];

%ModuloZ = sqrt(InversoR(1,1)^2 + InversoXc(1,1)^2);
ModuloZ = ones(15,12);

for r =1:1:size( Rload, 1 );
        InversoR = 1./Rload(r,:);   
end

for c =1:1:size( Cload, 1 );
        InversoXc = -((omega.*Cload(c,:)));       
end
        InversoXc = InversoXc';

    for Rc =1:15;
        for Phz = 1:12;
            ModuloZ(Rc, Phz) =  1/sqrt(InversoR(1,Rc).^2 + InversoXc(Phz,1).^2);
        end
        Phz = 0;
    end
% for Rc =1:16;
%            ModuloZ(1, 12) =  sqrt(InversoR(1,12).^2 + InversoXc(1,:).^2);
%     end
% for Phz =1:1:size( Cload, 1 );
%         %ModuloZ =  sqrt(InversoXc(1,:).^2 + InversoXc(1,:).^2);
%         PhaseZ = (180/pi())*(atan2(InversoXc(1,:)',InversoR(1,Phz)));
% end



for Rc =1:15;
        for Phz = 1:12;
            PhaseZ(Rc, Phz) = (180/pi())*(atan2(InversoXc(Phz,1)',InversoR(1, Rc)));
        end
        Phz = 0;
end
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

xRESISTOR = [1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350
            1.1 5.1 9.8 14.8 27.5 54.8 99.5 219.8 295.8 497 667 990 1630 1934 2350];




CAPACITOR = [1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9
              1.023e-6 470e-9 336.6e-9 226e-9 101.2e-9 45.5e-9 19.21e-9 10.31e-9 3.8e-9 3.29e-9 2.82e-9 2.53e-9];
          
yCAPACITOR = CAPACITOR';
Transp_ModuloZ =  ModuloZ';
Transp_PhaseZ = PhaseZ';
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MESH SUPERFÍCIE MÓDULO Z E FASE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
mesh(xRESISTOR,yCAPACITOR,Transp_ModuloZ);
set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('SUPERFÍCIE RESISTÊNCIA x REATÂNCIA x MÓDULO Z');
ylabel('CAPACITÂNCIA [F]');
xlabel('RESISTÊNCIA [OHM]');
zlabel('AMPLITUDE [OHM]');
colormap(winter(1))




figure;
mesh(xRESISTOR,yCAPACITOR,Transp_PhaseZ);
set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('SUPERFÍCIE RESISTÊNCIA x REATÂNCIA x FASE Z');
ylabel('CAPACITÂNCIA [F]');
xlabel('RESISTÊNCIA [OHM]');
zlabel('FASE [°]');
colormap(winter(1))
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

load('tMODULO_Z.mat')
load('tMODULO_fase.mat')

%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% RESISTOR 1.1 Ohm EM PARALELO COM CAPACITORES: 1023nF, 470nF,336.6nF, 226nF,
% 101.2nF, 45.5nF, 19.21nF, 10.31nF, 3.8nF, 3.29nF, 2.82nF e 2.53nF
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Z_real_1_1R_Xc = ModuloZ(1,:);
Z_MIE_1_1R_Xc = tMODULO_Z(1,:);

% figure('units','normalized','outerposition',[0 0 1 1]);
% 
% Fase_real_1_1R_Xc = PhaseZ(1,:);
% Fase_MIE_1_1R_Xc = tMODULO_fase(1,:);


% subplot(2,1,1);
% plot(Z_real_1_1R_Xc, Z_real_1_1R_Xc,  ':*r');
% hold on;
% plot(Z_real_1_1R_Xc, Z_MIE_1_1R_Xc,  ':ob');
% 
% grid on;
% 
% title('IMPEDÂNCIA MEDIDA  vs IMPEDÂNCIA CALCULADA - R[\Omega] = 1.1 [\Omega] // C [F] para 31250 [Hz]');
% ylabel('IMPEDÂNCIA Z MEDIDA [\Omega]');
% xlabel('IMPEDÂNCIA Z CALCULADA [\Omega]');
% grid on;
% legend('Z [\Omega] CALCULADA', 'Z [\Omega] MEDIDA','Location','northwest');
% 
% subplot(2,1,2);
% plot(Fase_real_1_1R_Xc, Fase_real_1_1R_Xc,  ':*r');
% hold on;
% plot(Fase_real_1_1R_Xc, Fase_MIE_1_1R_Xc,  ':ob');
% 
% grid on;
% 
% title('FASE MEDIDA  x FASE CALCULADA');
% ylabel('FASE MEDIDA [°]');
% xlabel('FASE CALCULADA [°]');
% 
% 
% legend('FASE CALCULADA[°]', 'FASE MEDIDA[°]','Location','northwest' );
% %%%%%%%%%%%%%%%%%%5
% 
% 
