close all;clear all;


RESISTOR = [1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350
            1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350];
       
        

CAPACITOR = [1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09
             1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09];


XC_calculado = [4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03
                4.98, 10.84, 15.13, 22.54, 50.3, 107.22, 265.12, 493.98, 1349.25, 1686.41, 1806.01, 2013.03];
        
         
TRANScap = CAPACITOR';
TRANS_XC_calculado = XC_calculado';


MODULO_Z = zeros(12,15);
MODULO_fase = zeros(12,15);
REAL_Z = zeros(12,15);
IMAGINARIO_Z = zeros(13,16);

RESISTORzero_XC = [39.3,	37.86,	38.55,	38.86,	41.11,	83.56,	171.01,	320.25,	768.29,	865.94,	908.05,	1035.11];
RESISTOR1_1_XC = [40.52, 46.6, 40.74, 40.75, 40.86, 40.46, 40.76, 40.7, 40.99, 40.69, 40.67, 40.67];
RESISTOR9_8_XC = [41.82,	44.10, 45.07, 45.89, 46.62, 46.74, 46.86, 46.83, 46.84, 46.83, 46.83, 44.88];
RESISTOR5_1_XC = [41.70, 42.72, 42.97, 43.04, 42.95, 42.77, 42.82, 42.74, 42.88, 43.04, 42.94, 42.97];
RESISTOR14_8_XC = [40.99, 43.72, 45.31, 47.48, 49.45, 50.12, 49.91, 50.34, 50.34, 50.56, 50.46, 50.48];
RESISTOR27_5_XC = [40.25, 42.72, 44.66, 48.19, 54.77, 57.84, 58.59, 58.87, 58.99, 59.04, 58.85, 58.81];
RESISTOR54_8_XC = [39.82, 41.69, 46.36, 47.10, 60.01, 71.92, 75.93, 78.02, 78.46, 78.32, 78.41, 77.76];
RESISTOR99_5_XC = [39.79, 40.93, 42.07, 45.37, 59.89, 84.25, 95.65, 107.32, 109.16, 109.77, 109.89, 109.85];
RESISTOR219_8_XC = [39.69, 40.73, 41.74, 44.17, 57.61, 92.87, 134.11 , 176.54, 187.74, 189.10, 189.44, 190.03];
RESISTOR296_XC = [40.18,	40.72,	42.31,	44.5,	56.87,	94.68,	171.26,	212.06,	238.53,	238.42,	239.26,	239.91];

RESISTOR497_XC = [39.43, 39.92, 40.86, 42.93, 54.50, 90.90, 157.61, 261.91, 329.91, 336.14, 339.27, 342.04];
RESISTOR667_XC = [39.62, 40.34, 40.91, 42.67, 54.23, 90.24, 143.34, 289.99, 393.39, 409.60, 415.11, 419.73];
RESISTOR990_XC = [39.74,	40.4,	41.17,	43.11,	53.86,	90.3,	134.6,	309.69,	490.99,	513.76,	539.43,	539.43];

RESISTOR1630_XC = [39.47, 40.12, 40.83,	42.69, 53.49, 88.29, 132.20, 323.96, 592.69, 663.12, 696.77, 730.10];
RESISTOR1941_XC = [39.16, 39.86, 40.63,	42.44, 52.96, 87.57, 139.14, 323.02, 633.90, 704.64, 751.29,	800.58];
RESISTOR2350_XC = [39.26, 39.92, 40.53, 42.75, 53.14, 87.87, 142.27, 328.57, 607.09, 756.94, 812.66, 873.74];
 

%MODULO_Z(:,1)=RESISTORzero_XC';
MODULO_Z(:,1)=RESISTOR1_1_XC';
MODULO_Z(:,2)=RESISTOR5_1_XC';
MODULO_Z(:,3)=RESISTOR9_8_XC';
MODULO_Z(:,4)=RESISTOR14_8_XC';
MODULO_Z(:,5)=RESISTOR27_5_XC';
MODULO_Z(:,6)=RESISTOR54_8_XC';
MODULO_Z(:,7)=RESISTOR99_5_XC';
MODULO_Z(:,8)=RESISTOR219_8_XC';
MODULO_Z(:,9)=RESISTOR296_XC';

MODULO_Z(:,10)=RESISTOR497_XC';
MODULO_Z(:,11)=RESISTOR667_XC';
MODULO_Z(:,12)=RESISTOR990_XC';
MODULO_Z(:,13)=RESISTOR1630_XC';
MODULO_Z(:,14)=RESISTOR1941_XC';

MODULO_Z(:,15)=RESISTOR2350_XC';

figure
%figure('units', 'normalized', 'outerposition', [0 0 1 1]);
mesh(RESISTOR,TRANScap,MODULO_Z);
set(gca, 'YScale', 'log')
set(gca, 'XScale', 'log')
title('SUPERFÍCIE RESISTÊNCIA x CAPACITÂNCIA x MÓDULO Z');
ylabel('CAPACITÂNCIA [F]');
xlabel('RESISTÊNCIA [OHM]');
zlabel('AMPLITUDE [OHM]');
colormap 'winter';

RESISTORzero_fase = [-11.09,	-17.79,	-21.58,	-28.65,	-47.95,	-68.94,	-83.51,	-87.98,	-86.03,	-86.58,	-85.34,	-84.78];
RESISTOR1_1_fase = [-7.97, -7.84, -8.28, -8.82, -9.02, -8.43, -8.8, -7.88, -7.79, -7.78, -8.69, -8.74];
RESISTOR9_8_fase = [-11.56,	-13.39, -12.89, -11.58, -9.4, -9.12, -8.14, -8.56, -8.44, -8.10, -8.57, -7.88];
RESISTOR5_1_fase = [-11.03,	-10.80, -9.21, -9.34, -9.14, -8.18, -8.17, -9.14, -8.02, -8.04, -8.04, -8.53];
RESISTOR14_8_fase = [-13.54,	-14.51, -14.24, -13.32, -12.34, -10.21, -9.37, -8.6, -8.92, -7.93, -7.48, -7.29];
RESISTOR27_5_fase = [-12.84,	-18.09, -18.88, -18.61, -16.43, -12.56, -10.41, -9.49, -8.31, -8.82, -8.97, -9.29];
RESISTOR54_8_fase = [-13.59,	-18.95, -21.76, -25.16, -26.27, -21.41, -16.65, -11.20, -9.04, -9.42, -9.83, -9.61];
RESISTOR99_5_fase = [ -12.84,	-18.75, -22.65, -28.03, -37.05, -32.31, -27.34, -16.02, -11.46, -10.35, -10.62, -10.56];
RESISTOR219_8_fase = [-13.7,	-20.17, -22.31, -29.75, -43.79, -49.24, -43.45, -27.49, -15.73, -13.65, -13.87, -11.71];
RESISTOR296_fase = [-13.36,	-18.87,	-22.44,	-28.7,	-43.84,	-54.44,	-45.15,	-32.64,	-16,	-15.51,	-14.5,	-14.38];

RESISTOR497_fase = [-14.00,	-20.48, -23.19, -29.92, -47.72, -60.62, -61.13, -45.81, -24.60, -21.13, -19.44, -17.51];
RESISTOR667_fase = [-13.29,	-19.84, -23.66, -29.10, -48.27, -62.98, -67.56, -54.06, -30.52, -26.11, -23.14, -20.70];
RESISTOR990_fase = [-12.81,	-18.83,	-23.6,	-29.47,	-47.9,	-65.14,	-71.02,	-63.94,	-36.9,	-31.88,	-25.09,	-25.09];

RESISTOR1630_fase = [-13.64, -20.18, -22.43, -30.95, -49.90, -68.28, -75.01, -73.01, -49.90, -42.94, -37.95, -34.68];
RESISTOR1941_fase = [-12.99, -19.58, -22.89, -29.51, -49.71, -67.44, -75.68, -76.55, -52.07, -45.96, -42.98, -38.08];

RESISTOR2350_fase = [-13.99, -19.66, -24.09, -30.40, -49.40, -69.52, -77.37, -78.36, -60.78, -50.72, -46.81, -42.81];

%MODULO_fase(:,1)=RESISTORzero_fase';
MODULO_fase(:,1)=RESISTOR1_1_fase';
MODULO_fase(:,2)=RESISTOR5_1_fase';
MODULO_fase(:,3)=RESISTOR9_8_fase';
MODULO_fase(:,4)=RESISTOR14_8_fase';
MODULO_fase(:,5)=RESISTOR27_5_fase';
MODULO_fase(:,6)=RESISTOR54_8_fase';
MODULO_fase(:,7)=RESISTOR99_5_fase';
MODULO_fase(:,8)=RESISTOR219_8_fase';
MODULO_fase(:,9)=RESISTOR296_fase';

MODULO_fase(:,10)=RESISTOR497_fase';
MODULO_fase(:,11)=RESISTOR667_fase';
MODULO_fase(:,12)=RESISTOR990_fase';
MODULO_fase(:,13)=RESISTOR1630_fase';
MODULO_fase(:,14)=RESISTOR1941_fase';
MODULO_fase(:,15)=RESISTOR2350_fase';

figure
%figure('units', 'normalized', 'outerposition', [0 0 1 1]);
mesh(RESISTOR,TRANScap,MODULO_fase);
set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('SUPERFÍCIE RESISTÊNCIA x CAPACITÂNCIA x FASE');
ylabel('CAPACITÂNCIA [F]');
xlabel('RESISTÊNCIA [OHM]');
zlabel('FASE [°]');
colormap 'winter';



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


figure;
mesh(RESISTOR,TRANS_XC_calculado,MODULO_Z);
set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('SUPERFÍCIE RESISTÊNCIA x REATÂNCIA x MÓDULO Z');
ylabel('REATÂNCIA [F]');
xlabel('RESISTÊNCIA [OHM]');
zlabel('AMPLITUDE [OHM]');
colormap 'winter';

figure;
mesh(RESISTOR,TRANS_XC_calculado,MODULO_fase);
set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('SUPERFÍCIE RESISTÊNCIA x REATÂNCIA x FASE');
ylabel('REATÂNCIA [F]');
xlabel('RESISTÊNCIA [OHM]');
zlabel('FASE [°]');
colormap 'winter';

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

tMODULO_Z = MODULO_Z';
tMODULO_fase = MODULO_fase'; 
save('tMODULO_Z.mat','tMODULO_Z')
save('tMODULO_fase.mat','tMODULO_fase')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

RESISTORpadrao = [1.1, 5.1, 9.8, 14.8, 27.5, 54.8, 99.5, 219.8, 296.1, 497, 667, 990, 1630, 1934, 2350];

figure
%figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(2,1,1);
plot(RESISTORpadrao,MODULO_Z(1,:),  '-o');
hold on;
plot(RESISTORpadrao,MODULO_Z(2,:),  '-+');
hold on;
plot(RESISTORpadrao,MODULO_Z(3,:),  '-*');
hold on;
plot(RESISTORpadrao,MODULO_Z(4,:),  '-');
hold on;
plot(RESISTORpadrao,MODULO_Z(5,:),  '-x');
hold on;
plot(RESISTORpadrao,MODULO_Z(6,:),  '-s');
hold on;
plot(RESISTORpadrao,MODULO_Z(7,:),  '-d');
hold on;
plot(RESISTORpadrao,MODULO_Z(8,:),  '-^');
hold on;
plot(RESISTORpadrao,MODULO_Z(9,:),  '-v');
hold on;
plot(RESISTORpadrao,MODULO_Z(10,:),  '->');
hold on;
plot(RESISTORpadrao,MODULO_Z(11,:),  '-<');
hold on;
plot(RESISTORpadrao,MODULO_Z(12,:),  '-p');

%set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('RESISTÊNCIA x MÓDULO Z -  RC PARALELO - 31,25KhZ');
ylabel('MÓDULO DE Z [OHM]');
xlabel('RESISTÊNCIA [OHM]');
%zlabel('AMPLITUDE [OHM]');
%colormap 'winter';
axis([0 10000 0 900]);
legend('1023nF','470nF', '336,6nF', '226nF', '101nF', '47,5nF', '10,3nF', '20,4nF', '4,2nF', '3,2nF','2,82nF', '2,53nF');
grid on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(2,1,2);
plot(RESISTORpadrao,MODULO_fase(1,:),  '-o');
hold on;
plot(RESISTORpadrao,MODULO_fase(2,:),  '-+');
hold on;
plot(RESISTORpadrao,MODULO_fase(3,:),  '-*');
hold on;
plot(RESISTORpadrao,MODULO_fase(4,:),  '-');
hold on;
plot(RESISTORpadrao,MODULO_fase(5,:),  '-x');
hold on;
plot(RESISTORpadrao,MODULO_fase(6,:),  '-s');
hold on;
plot(RESISTORpadrao,MODULO_fase(7,:),  '-d');
hold on;
plot(RESISTORpadrao,MODULO_fase(8,:),  '-^');
hold on;
plot(RESISTORpadrao,MODULO_fase(9,:),  '-v');
hold on;
plot(RESISTORpadrao,MODULO_fase(10,:),  '->');
hold on;
plot(RESISTORpadrao,MODULO_fase(11,:),  '-<');
hold on;
plot(RESISTORpadrao,MODULO_fase(12,:),  '-p');

%set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('RESISTÊNCIA x FASE -  RC PARALELO - 31,25KhZ');
ylabel('FASE [°]');
xlabel('RESISTÊNCIA [OHM]');
%zlabel('AMPLITUDE [OHM]');
%colormap 'winter';
%axis([0 10000 30 1000]);
legend('1023nF','470nF', '336,6nF', '226nF', '101nF', '47,5nF', '10,3nF', '20,4nF', '4,2nF', '3,2nF','2,82nF', '2,53nF');
grid on;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Capacitância vs Módulo Z
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

CAPACITORpadrao = [1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09];

figure
%figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(2,1,1);
plot(CAPACITORpadrao,MODULO_Z(:,1),  '-o');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,2),  '-+');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,3),  '-*');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,4),  '-');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,5),  '-x');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,6),  '-s');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,7),  '-d');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,8),  '-^');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,9),  '-v');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,10),  '->');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,11),  '-<');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,12),  '-p');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,13),  ':o');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,14),  ':+');
hold on;
plot(CAPACITORpadrao,MODULO_Z(:,15),  ':*');
hold on;
%set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('CAPACITÂNCIA x MÓDULO Z -  RC PARALELO - 31,25KhZ');
ylabel('MÓDULO DE Z [OHM]');
xlabel('CAPACITÂNCIA [F]');
%zlabel('AMPLITUDE [OHM]');
colormap 'winter';
axis([1e-9 2e-6 0 900]);
legend('1,1\Omega','5,1\Omega', '9,8\Omega', '14,8\Omega', '27,5\Omega', '54,8\Omega', '99,5\Omega', '219,8', '296,1\Omega', '497\Omega','667\Omega', '990\Omega', '1630\Omega','1934\Omega', '2350\Omega','Location','southwest');
grid on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Capacitância vs Módulo Z
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

CAPACITORpadrao = [1.02E-06, 4.70E-07, 3.37E-07, 2.26E-07, 1.01E-07, 4.75E-08, 1.92E-08, 1.03E-08, 3.80E-09, 3.029E-09,	2.82E-09, 2.53E-09];

%figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(2,1,2);
plot(CAPACITORpadrao,MODULO_fase(:,1),  '-o');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,2),  '-+');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,3),  '-*');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,4),  '-');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,5),  '-x');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,6),  '-s');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,7),  '-d');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,8),  '-^');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,9),  '-v');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,10),  '->');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,11),  '-<');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,12),  '-p');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,13),  ':o');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,14),  ':+');
hold on;
plot(CAPACITORpadrao,MODULO_fase(:,15),  ':*');
hold on;
%set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
title('CAPACITÂNCIA x MÓDULO Z -  RC PARALELO - 31,25KhZ');
ylabel('FASE [°]');
xlabel('CAPACITÂNCIA [F]');
%zlabel('AMPLITUDE [OHM]');
colormap 'winter';
axis([1e-9 2e-6 -80 0]);
legend('1,1\Omega','5,1\Omega', '9,8\Omega', '14,8\Omega', '27,5\Omega', '54,8\Omega', '99,5\Omega', '219,8', '296,1\Omega', '497\Omega','667\Omega', '990\Omega', '1630\Omega','1934\Omega', '2350\Omega','Location','southwest');
grid on;