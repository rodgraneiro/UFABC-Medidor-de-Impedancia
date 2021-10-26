%clear;
%file_impedancia = importdata('WAVE100.dat');
%im = readtable('WAVE100.dat')
fileID = fopen('WAVE057.DAT');


 A = fread(fileID,'uint16');
 %B = A(10:650);
 plot(A);
 axis([0 650 0 256])