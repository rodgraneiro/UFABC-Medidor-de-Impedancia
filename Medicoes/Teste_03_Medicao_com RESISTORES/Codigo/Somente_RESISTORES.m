clear;
file_RESISTOR = importdata('SoResistores.txt');
file_nome_RESISTOR = ('SoResistores.txt');

RESISTORvalue = file_RESISTOR(:, 1);
RESISTORfase = file_RESISTOR(:, 3);
Z_RESISTOR_MIE = file_RESISTOR(:, 2);


nrows = length(file_RESISTOR);
subplot(2,1,1);
plot(RESISTORvalue, Z_RESISTOR_MIE, ':ob');

grid on;
%legend('IMPEDÂNCIA TRIMPOT','IMPEDÂNCIA RESISTORES')
title('MEDIÇÃO DE IMPEDÂNCIA - RESISTORES');
xlabel('RESISTÊNCIA [\Omega] - MEDIDA COM MULTÍMETRO')
ylabel('IMPEDÂNCIA DO RESISTOR [\Omega] - MEDIDA COM MIE')
%axis equal

[p,S] = polyfit(RESISTORvalue,Z_RESISTOR_MIE,1);
[y_fit,delta] = polyval(p,RESISTORvalue,S);
hold on;
plot(RESISTORvalue,y_fit,'k-');


legend('RESISTOR','Equação da reta (Z)');
a = p(:,1);
b = p(:,2);

subplot(2,1,2);
plot(RESISTORvalue, RESISTORfase, ':ob');
%axis equal
grid on;
%legend('FASE TRIMPOT','FASE RESISTORES');
title('MEDIÇÕES DE FASE - TRIMPOTs');
xlabel('RESISTÊNCIA [\Omega] - MEDIDA COM MULTÍMETRO');
ylabel('FASE DO RESISTOR[°] - MEDIDA COM MIE')
[r,W] = polyfit(RESISTORvalue,RESISTORfase,1);
[y_fit_fase_RESISTOR,delta] = polyval(r,RESISTORvalue,W);
hold on;
plot(RESISTORvalue,y_fit_fase_RESISTOR,'k-');



f = r(:,1);
g = r(:,2);

legend('FASE MEDIÇÃO RESISTOR', 'Equação da reta (fase)');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

dim = [.7 .75 .01 .01];
s0 = 'y1 = ';
s = num2str(a);
s1 = 'x+';
s2 = num2str(b);
str = strcat(s0,s,s1,s2);
d = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
d.Color = 'black';
d.FontSize = 16;



dim = [.7 .35 .01 .01];
s0 = 'y1 = ';
sf = num2str(f);
s1 = 'x';
sf2 = num2str(g);
str = strcat(s0,sf,s1,sf2);
d = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
d.Color = 'black';
d.FontSize = 16;

% dim = [.7 .3 .01 .01];
% v0 = 'y2 = ';
% vf = num2str(i);
% v1 = 'x';
% vf2 = num2str(j);
% str = strcat(v0,vf,v1,vf2);
% d = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
% d.Color = 'green';
% d.FontSize = 16;
