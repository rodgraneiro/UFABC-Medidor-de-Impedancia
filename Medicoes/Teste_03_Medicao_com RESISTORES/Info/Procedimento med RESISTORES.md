## Medição da impedânia dos RESISTORES com o MIE.

O arquivo /Dados/SoResistores.txt contém 16 pontos de medição de
resistência - de resistores comerciais 5% de tolerância variando de zero à 2350 Ohms - 
medidos com um multímetro digital e dos valores de impedância Z e fase medidas com o MIE conforme figura.
OBs.: Foram efetuadas algumas assossiações em parlelo com os resistores para atingir o valor 
de resistência desejado. 

Os valores dos resistores medidos com o multímetro são de: 1.1R, 5.1R, 9.8R, 14.8R, 27.5R,
54.8R, 99.5R. 219.8R, 295.8R, 497R, 667R, 987R, 1630R, 1934R, 2350R e zero (curto-circuito dos 
terminais de excitação de corrente).

![Circuito eletrônico do teste](Circuito_eletronico.jpg)

Cada ponto da curva é a média trimada de mil medições efetuadas pelo MIE onde foram eliminadas
o quarcentil superior e inferior das amostras. Os cálculos foram efetuados no Matlab através do código 
/Codigo/SortMatlab_tst_new.m onde cada arquivo "TRIMPOT_r_XXXXXX_2021jul12.txt" foi substituido nas
linhas de código 2 e 3.

![Exemplo de medição de resistividade de 100 Ohms on trimpot](ExemploMedTrimpot.jpg)

A curva de Impedância Multímetro vs Impedância MIE (/Info/Curva_Z_Fase_TRIMPOT) foi efetuada através 
do código em Matlab no arquivo /Codigo/Somente_TRIMPOT.m e pode ser vista a seguir.

![Impedância Multímetro vs Impedância MIE](Curva_Z_Fase_TRIMPOT.jpg) 


Trimpot utilizado:


![TRIMPOT 3006P 103](trimpot3006P.jpg)


