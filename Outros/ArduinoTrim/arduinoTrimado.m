clear all; close all; clc; more off; 
raw = importdata('arduinoTrimado_edit.txt'); %load(casaTeste_R_220_1_4dez2021_edit.txt);

unSort_modulo = raw(2:101 ,1);
unSort_fase = raw(2:101, 2);

sort_quartil_1 = raw(103:178 ,1);
sort_quartil_2 = raw(103:178 ,2);

sort_quartil2_1 = raw(180:231 ,1);
sort_quartil2_2 = raw(180:231 ,2);

Sort_modulo = raw(233:332 ,1);
Sort_fase = raw(233:332 ,2);

mean_retangular = [raw(334 ,1);raw(334 ,2)]
mean_polar = [raw(336 ,1);raw(336 ,2)]



