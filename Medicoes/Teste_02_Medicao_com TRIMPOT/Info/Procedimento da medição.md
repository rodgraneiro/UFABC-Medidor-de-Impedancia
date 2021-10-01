## Medição da impedânia de um trimpot tipo 3006P 103 (1K)com o MIE.
O arquivo /Dados/SoTRIMPOT.txt contém 26 pontos de medição de
resistência do trimpot com valores de zero à 2500 Ohms variando em passos de 100 Ohms
medidos com um multímetro digital e dos valores de impedância Z e fase medidas com o MIE.

Cada ponto de medição é a media trimada de mil medições efetuadas pelo MIE onde foram eliminadas
o quarcentil superior e inferor das amostras. Os cálculos foram efetuados no Matlab através do código 
/Codigo/SortMatlab_tst_new.m.

A curva de Impedância Multímetro vs Impedância MIE (/Info/Curva_Z_Fase_TRIMPOT) foi efetuada atraves 
do código em Matlab no arquivo /Codigo/Somente_TRIMPOT.m e pode ser vista a seguir.

![Impedância Multímetro vs Impedância MIE](Curva_Z_Fase_TRIMPOT.jpg) 

