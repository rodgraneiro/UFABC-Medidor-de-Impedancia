%clear all; close all; clc; more off;

ma = 0;
nomes_Erick_medidas_copia;



for n = 1:21
    [Zmean, modulo_mean, fase_mean, modulo1, fase1, modulo_teorico, fase_teorico, Z] = ...
                pega_dado(medidas(n).nome, medidas(n).R, medidas(n).C);
    Zampl_med(n) = modulo_mean;
    Zfase_med(n) = fase_mean;
    Zampl_teo(n) = modulo_teorico;
    Zfase_teo(n) = fase_teorico;
    Z_med(n) = Zmean;
    Z_teo(n) = Z;
    real_teo(n) = real(Z);
    imag_teo(n) = imag(Z);
    real_med(n) = real(Zmean);
    imag_med(n) = imag(Zmean);
%     plot(Zmedido(n), 'ok','LineWidth',2)
%     hold on;
      
  end
   
correcao_fase = mean(Zfase_med-Zfase_teo);
Zfase_med = Zfase_med - correcao_fase;

figure(1);
subplot(2,2,1);
plot(Zampl_teo, Zampl_med, 'ob','LineWidth',2);
hold on;
pZ = polyfit(Zampl_teo,Zampl_med,1);
Ax_eq_line_Z = (pZ(1,1)*Zampl_teo)+ pZ(1,2);
plot(Zampl_teo, Ax_eq_line_Z, '-r','LineWidth',1);
grid on;
title('A)          |Z| AMPLITUDE IMPEDANCE [\Omega]');
ylabel('|Z| MEASURED [\Omega]');
xlabel('|Z| THEORETICAL [\Omega]');
%hold on; plot([0 1000], [0 1000], ':r');
%plot([0 1000], [-28 1000-28], ':g');
set(gca, 'linewidth', 2, 'fontsize', 20)

subplot(2,2,2);
plot(Zampl_teo, Zampl_med-Zampl_teo, 'ob', 'LineWidth',2);
grid on;
title('B)             |Z| AMPLITUDE ERROR [\Omega]');
ylabel('|Z| MEAS.D - |Z| THEO. [\Omega]','LineWidth',2);
xlabel('|Z| THEORETICAL [\Omega]');
set(gca, 'linewidth', 2, 'fontsize', 20)

subplot(2,2,3);
plot(Zfase_teo, Zfase_med, 'ob','LineWidth',2);
hold on;
pF = polyfit(Zfase_teo,Zfase_med,1);
Ax_eq_line_F = (pF(1,1)*Zfase_teo)+ pF(1,2);
plot(Zfase_teo, Ax_eq_line_F, '-r','LineWidth',1);
grid on;
title('C)                           PHASE [°]');
ylabel('PHASE MEASURED [°]');
xlabel('PHASE THEORETICAL [°]');
%hold on; plot([0 -50], [0 -50], ':r');
set(gca, 'linewidth', 2, 'fontsize', 20)

subplot(2,2,4);
plot(Zfase_teo, Zfase_med-Zfase_teo, 'ob','LineWidth',2);
grid on;
title('D)                     PHASE ERROR [°]');
ylabel('PHASE MEAS-PHASE THEO [°]');
xlabel('PHASE THEORETICAL [°]');
set(gca, 'linewidth', 2, 'fontsize', 20)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2);
subplot(2,2,1);
plot(real_teo, real_med, 'ob','LineWidth',2);
hold on;
pR = polyfit(real_teo,real_med,1);
Ax_eq_line_R = (pR(1,1)*real_teo)+ pR(1,2);
plot(real_teo, Ax_eq_line_R, '-r','LineWidth',1);
grid on;
title('A)                         REAL PART');
ylabel('REAL MEASURED [\Omega]');
xlabel('REAL THEORETICAL [\Omega]');
%hold on; plot([0 1000], [0 1000], ':r');
%plot([0 1000], [-28 1000-28], ':g');
%plot([0 1000], [0 1000], ':g');
set(gca, 'linewidth', 2, 'fontsize', 20);

subplot(2,2,2);
plot(real_teo, real_med-real_teo, 'ob','LineWidth',2);
grid on;
title('B)                  REAL PART ERROR');
ylabel('REAL  Meas. - REAL Theo [\Omega]');
xlabel('REAL THEORETICAL [\Omega]');
set(gca, 'linewidth', 2, 'fontsize', 20);


subplot(2,2,3);
plot(imag_teo, imag_med, 'ob','LineWidth',2);
hold on;
pI = polyfit(imag_teo,imag_med,1);
Ax_eq_line_I = (pR(1,1)*imag_teo)+ pI(1,2);
plot(imag_teo, Ax_eq_line_I, '-r','LineWidth',1);
grid on;
title('C)                    IMAGINARY PART ');
ylabel('IMAGINARY MEASURED  [\Omega]');
xlabel('IMAGINARY THEORETICAL [\Omega]');
%hold on; plot([0 -500], [0 -500], ':r');
set(gca, 'linewidth', 2, 'fontsize', 20);

subplot(2,2,4);
plot(imag_teo, imag_med-imag_teo, 'ob','LineWidth',2);
grid on;
%title(['Erro Fase; correcao: ' num2str(correcao_fase) ' graus']);
title('D)              IMAGINARY PART ERROR');


ylabel('IMAG Meas. - IMAG Theo. [\Omega]');
xlabel('IMAGINARY THEORETICAL [\Omega]');
set(gca, 'linewidth', 2, 'fontsize', 20);

% [R] = corr(Z_med',Z_teo','Type','pearson');
% 
% 
% des_std_Z_polar=std(abs(Z_med'-Z_teo'));
% des_std_Ph_polar=std(angle(Z_med'-Z_teo'));
% 
% des_std_retangular=std(Z_med'-Z_teo');
% 
% stderror = std (Z_med-Z_teo) / sqrt (length (Z_med))
% stderrorb = std (Zampl_med-Zampl_teo) / sqrt (length (Z_teo))
% stderrorc = std (Zfase_med-Zfase_teo) / sqrt (length (Z_teo))
