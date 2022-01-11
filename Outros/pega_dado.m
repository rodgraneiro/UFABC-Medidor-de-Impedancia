function [modulo_mean, fase_mean, modulo_sort2, fase_sort2, modulo_teorico, fase_teorico, Z] = pega_dado(nome, R, C)
    % le arquivo
    raw = load(nome);
    modulo = raw(:,2);
    fase = raw(:,4);
    fase = fase - 360*(fase>0); % se > 0, subtrai 360
    
    % calcula media trimada removendo outliers na amplitude (retira 1/4 das medidas)
    N_medidas = length(modulo);
    quartil = floor(N_medidas/8);
    [modulo_sort1, ims] = sort(modulo);
    fase_sort1 = fase(ims);
    remove = [1:quartil N_medidas-quartil:N_medidas];
    fase_sort1(remove) = [];
    modulo_sort1(remove) = [];
    
    % calcula media trimada removendo outliers na fase (retira mais 1/4 das medidas)
    N_medidas_sort = length(fase_sort1);
    [fase_sort2, ifs] = sort(fase_sort1);
    modulo_sort2 = modulo_sort1(ifs);
    remove = [1:quartil N_medidas_sort-quartil:N_medidas_sort];
    fase_sort2(remove) = [];
    modulo_sort2(remove) = [];
    
    % calcula valor medio
    Zmedido = modulo_sort2.*( cos(fase_sort2*pi/180) + i*sin(fase_sort2*pi/180) );
    Zmean = mean(Zmedido);
    modulo_mean = abs(Zmean);
    fase_mean = angle(Zmean)*180/pi;
    
    % calcula valores teoricos
    f = 31250;
    Zr = R;
    Zc = - (i/(2*pi*f*C));
    Z = 1/( (1/Zr) + (1/Zc) );
    modulo_teorico = abs(Z);
    fase_teorico = angle(Z)*180/pi;
endfunction
