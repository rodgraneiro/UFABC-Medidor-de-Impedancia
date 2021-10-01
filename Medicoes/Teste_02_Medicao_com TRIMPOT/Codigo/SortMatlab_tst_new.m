clear;
file_impedancia = importdata('TRIMPOT_r_104_4R_2021jul12.txt');
file_nome = ('TRIMPOT_r_104_4R_2021jul12.txt')
z = file_impedancia(:, 2);
fase = file_impedancia(:, 3);
banana = 0;
new_r = 0;
AngulosErrados = 0;
percentERROR = 0;
nrows = length(z);
x = 1 : nrows;


zSort = sort(z);
faseSort = sort(fase);
impedancia = [[zSort] [faseSort]];
% 
for r =size( impedancia, 1 ) : -1 : 1
    teste = impedancia(r,2);
         if teste < -29;  
         AngulosErrados  = AngulosErrados +1;     
         end    
end

for r =size( impedancia, 1 ) : -1 : 1
    teste = impedancia(r,2);
         if teste > 29;  
         AngulosErrados  = AngulosErrados +1;      
         end    
end


percentERROR = (AngulosErrados/nrows)*100;
%zeSort = sort(ze,2);

impedanciaSortFase = sortrows(impedancia,2);

quartil =  floor(length(impedanciaSortFase)/4);
new_M_size = (length(impedanciaSortFase)- quartil);

 impedanciaSortFase = impedanciaSortFase(1:new_M_size,:);
 impedanciaSortFase = impedanciaSortFase(quartil:end,:);
 
 Nr_amostra_filt = length(impedanciaSortFase);
 xTrim = 1 : Nr_amostra_filt;
 zTrim = impedanciaSortFase(:, 1);
 faseTrim = impedanciaSortFase(:, 2);
 
 impe_fase = mean(impedanciaSortFase);
 impedanciaZ = impe_fase(:, 1);
 faseZ = impe_fase(:, 2);
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3,3,1);
     plotyy(x, z, x, fase);
     title({'Impedância e fase originais';file_nome},'Interpreter', 'none')
     hold on;
     grid on;
 
subplot(3,3,2);
     histogram(z);
     title('Histograma Impedância original');
 
subplot(3,3,3);
        histogram(fase);
        title('Histograma fase original');
    
 subplot(3,3,[4, 5]);
         plotyy(x, zSort, x, faseSort);
         title('Impedância e fase classificados');
         hold on;

         grid on;
     
 subplot(3,3,7);
         plotyy(xTrim, zTrim, xTrim, faseTrim);
         title('Impedância e fase trimados');
         hold on;
         grid on;
 
 subplot(3,3,8);
         histogram(zTrim);
         title('Histograma Impedância trimado');
         subplot(3,3,9);
         histogram(faseTrim);
         title('Histograma fase trimado');
 %%%%%%%%%%%%%%%%%%%

%plot(1:10)
dim = [.7 .6 .01 .01];
str = num2str(impedanciaZ);
d = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
d.Color = 'red';
d.FontSize = 20;

dim = [.65 .6 .01 .01];
str = 'Z = ';
c = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
c.Color = 'red';
c.FontSize = 20;

dim = [.9 .6 .01 .01];
str = num2str(faseZ);
b = annotation('textbox',dim, 'String',num2str(faseZ),'FitBoxToText','on');
b.Color = 'red';
b.FontSize = 20;

dim = [.83 .6 .01 .01];
str = 'Fase = ';
a = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
a.Color = 'red';
a.FontSize = 20;


dim = [.75 .5 .01 .01];
str = num2str(AngulosErrados);
d = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
d.Color = 'red';
d.FontSize = 20;

dim = [.65 .5 .01 .01];
str = 'AngErrs';
c = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
c.Color = 'red';
c.FontSize = 20;


dim = [.9 .5 .01 .01];
str = num2str(percentERROR);
b = annotation('textbox',dim, 'String',num2str(percentERROR),'FitBoxToText','on');
b.Color = 'red';
b.FontSize = 20;

dim = [.83 .5 .01 .01];
str = ' % ';
a = annotation('textbox',dim, 'String',str,'FitBoxToText','on');
a.Color = 'red';
a.FontSize = 20;