clear all; close all; clc; more off;


nomes_medidas;


for n = 1:20
    [modulo_mean, fase_mean, modulo1, fase1, modulo_teorico, fase_teorico, Z] = ...
             pega_dado(medidas(n).nome, medidas(n).R, medidas(n).C);
    Zampl_med(n) = modulo_mean;
    Zfase_med(n) = fase_mean;
    Zampl_teo(n) = modulo_teorico;
    Zfase_teo(n) = fase_teorico;
  
endfor

correcao_fase = mean(Zfase_med-Zfase_teo);
Zfase_med = Zfase_med - correcao_fase;

figure(1);
subplot(2,2,1);
plot(Zampl_teo, Zampl_med, 'o');
grid on;
title("Amplitude");
ylabel("|Z| medido [ohm]");
xlabel("|Z| teorico [ohm]");
hold on; plot([0 1000], [0 1000], ':r');
set(gca, "linewidth", 4, "fontsize", 20)
subplot(2,2,2);
plot(Zampl_teo, Zampl_med-Zampl_teo, 'o');
grid on;
title("Erro Amplitude");
ylabel("|Z| medido - |Z| teorico [ohm]");
xlabel("|Z| teorico [ohm]");
set(gca, "linewidth", 4, "fontsize", 20)
subplot(2,2,3);
plot(Zfase_teo, Zfase_med, 'o');
grid on;
title("Fase");
ylabel("<Z medido [graus]");
xlabel("<Z teorico [graus]");
hold on; plot([0 -50], [0 -50], ':r');
set(gca, "linewidth", 4, "fontsize", 20)
subplot(2,2,4);
plot(Zfase_teo, Zfase_med-Zfase_teo, 'o');
grid on;
title(["Erro Fase; correcao: " num2str(correcao_fase) " graus"]);
ylabel("<Z medido - <Z teorico [graus]");
xlabel("<Z teorico [graus]");
set(gca, "linewidth", 4, "fontsize", 20)
