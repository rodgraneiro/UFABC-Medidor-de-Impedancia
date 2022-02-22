
#define PI 3.1415926535897932384626433832795


void gera_vetor_randomico(float *myArray1, float *myArray2, int tamanho_do_array ){
    for (int i = 0; i < tamanho_do_array ; i++){                           //Gerar vetores randomicamente
        myArray1[i] = random(0, 10000)*(0.01);                         // Vetor Z randomico
        myArray2[i] = random(-1000, 1000)*(0.01);                      // Vetor fase randomico
    }
}


void ordena_vetores(float *ArrayPrincipal, float *ArraySecundario, int tamanho_do_array){
    for(int x = 0; x < tamanho_do_array; x++){                             //Outer loop
        for (int y = 0; y < (tamanho_do_array -1); y++){                   //Inner loop
            if(ArrayPrincipal[y] > ArrayPrincipal[y+1]){                           //if this value is bigger than next
                float tmp1 = ArrayPrincipal[y+1];                           //Store a temp of the next
                float tmp2 = ArraySecundario[y+1];
                ArrayPrincipal[y+1] = ArrayPrincipal[y];                            //Move this value to next position array
                ArraySecundario[y+1] = ArraySecundario[y];
                ArrayPrincipal[y] = tmp1;                                    //Put value at the current possition
                ArraySecundario[y] = tmp2;
            }
        }
    }
}

void trima_array(float *Array1, float *Array2, float *Trim1, float*Trim2, int tamanho_do_array, int quartil){
    for ( int x = quartil; x < (tamanho_do_array - quartil); x++){    //Remove 1o quartil das extremidades superior e inferior 
        Trim1[x - quartil] = Array1[x];                      //Vetor 1o quartil Z trimado 
        Trim2[x - quartil] = Array2[x];                     //Vetor 10 quartil fase
    }
}

void media_polar(float *ArrayAmpl, float *ArrayPhase, int tamanho_do_array,
                 float *media_Z, float *phase_Z){
    
    float real_part = 0;                                              // Media trimada parte real
    float imag_part = 0;  
    for(int x = 0; x < tamanho_do_array; x++){                                      //Converte polar para retangular
        real_part =  real_part + ArrayAmpl[x]*cos( ArrayPhase[x]*PI/180);       //Calcula parte real e soma
        imag_part =  imag_part + ArrayAmpl[x]*sin( ArrayPhase[x]*PI/180);      //Calcula parte imaginária e soma
    }
    real_part = (real_part)/tamanho_do_array;                                       //Calcula media parte real
    imag_part = (imag_part)/tamanho_do_array;                                       //calcula media parte imaginaria
    
    *media_Z = sqrt(sq(real_part)+sq(imag_part));                               // Converte retangular para polar - modulo Z
    *phase_Z = atan2(imag_part , real_part)*(180/PI);    // cálculo da fase       //Fase em graus
  
}
