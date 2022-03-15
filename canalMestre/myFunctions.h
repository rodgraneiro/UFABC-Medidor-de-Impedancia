  #include "MathHelpers.h"                             // Número do pino do Arduino para o pushbutton

void pulsoPinoADC(int x, int tempo){
                                                                      // RESET pino xx do ADC 7762     **************************
      delay(tempo);
      digitalWrite(x, LOW);                                           // Pino  arduino LOW
      delay(tempo);
      digitalWrite(x, HIGH);// reset                                  // Pino  arduino HIGH
      delay(tempo);
}

volatile uint32_t convert32to24bits(int Nr_de_Amostras, volatile uint32_t *vetor_Amostra, volatile uint32_t *vetor_segunda_palavra){
        
//*************************************************************
// Rearranjar 32 bits "NÃO CONSECUTIVOS" do portC do Arduino em 24 bits CONSECUTIVOS
// O AD7762 disponibiliza a amostra discretizada com resolução de 24 bits em duas "palavras" de 16 bits.
// Entretanto, o kit do Arduino DUE não tem 16 bits consecutivos disponíveis para uso.
// Portanto, é necessário mapear as palavras 1 e 2 do AD7762 como segue:
// bit do registrador PortC UTILIZADO  = " V "
// bit do registrador PortC NÃO UTILIZADO  = " . "
// OBS. Arduino Due
//*************************************************************
//   Mapeamento das palavras: 
//   Primeira palavra (MSD) -> 16 bits de 23 à 8 
//   Segunda palavta (LSD)  -> 8 bits de 7 à 0
//   A seguir, mapa com os pinos do portC do Arduino DUE utilzados no hardware.
//-------------------------------------------------------------------------------------------------------------        
// N_bt PortC/|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|9 |8 |7 |6 |5 |4 |3 |2 |1 | 0|
//  Arduino   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
// Palavra 1  |. |. |. |. |. |. |. |. |. |. |. |. |V |V |V |V |V |V |V |V |. |. |V |V |V |V |V |V |V |V |. |. | 
// Palavra 2  |. |. |. |. |. |. |. |. |. |. |. |. |V |V |V |V |V |V |V |V |. |. |. |. |. |. |. |. |. |. |. |. | 
//-------------------------------------------------------------------------------------------------------------  

    for(int contador_aux_1 = 0; contador_aux_1 < Nr_de_Amostras; contador_aux_1++) { // Laço Rearranjar 32 bits NÃO CONSECUTIVOS
                                                                                    //*******************************************************************
                                                                                    // Primeira palavra com os 16 bits mais significativos (de 23 à 8)
                                                                                    //*******************************************************************
        
        vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] & 0x000ffffc; // Zerar bits "0" , "1" e bits de "20" à "31" aplicando a operação lógica "AND" por meio da máscara 0x000ffffc  
        vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] >> 2;         // Desloca dois bits p direita para elininar bits "0" e "1"
        
        uint32_t low8 = vetor_Amostra[contador_aux_1] & 0x000000ff;                 // separa os 8 bits menos significaticos da primrira palavra
        
        vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] >> 10;        //Remove os bits "10 e 11" (Lixo do meio da primeira palavra) deslocando 10 bits para direita
                                                                                    // Rearranjar os 16 bits da primeira palavra
                                                                                    // Deslocando 8 bits à esquerda e aplicando a operação lógica "OU" com os
                                                                                    // 8 bits menos significativos da primeira palavra armazenados na variável low8 
        vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] << 8 | low8;  //Primeira palavra com os 16 bits mais significativos de 23 à 8
        
                                                                                    //****************************************************************** 
                                                                                    // Segunda palavra com os 8 bits menos significativos (de 7 à 0)
                                                                                    //******************************************************************
        
        uint32_t low24 = vetor_segunda_palavra[contador_aux_1] & 0x000ff000;        // Zera bits de "0 à 11" e bits de "20" à "31" aplicando a operação lógica "AND"  
                                                                                    // por meio da máscara 0x000ff000
        low24  =  low24 >> 12;                                                      // Desloca 12 bits à direita separando os 8 bits menos significaticos da palavra de 24 bits
        low24  =  low24 & 0x000000ff;
                                                                                    // Rearranjar a amostra discretizada com resolução de 24 bits
                                                                                    // deslocando os 8 bits da primeira palavra à esquerda e 
                                                                                    // aplicando a operação lógica "OU" com os 8 bits menos significativos
                                                                                    // da segunda palavra armazenados na variavel low24
        vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] << 8 | low24; // Amostra discretizada com 24 bits;    
    }                                                                               // Final laço Rearranjar 32 bits NÃO CONSECUTIVOS 
}


float verifSinalNeg(int Nr_de_Amostras, volatile uint32_t *vetor_Amostra, volatile float *converte_volts, volatile float fator_conv_volts){
    
        for(int contador_aux_2 = 0; contador_aux_2 < Nr_de_Amostras ; contador_aux_2++){                      // Laço verificação sinal da amostra em complemento de 2
                                                                                                              // O bit 23 indentifica o sinal da amostra: "1" para negativo e "0" para positivo.
            volatile uint32_t sinal_negativo = vetor_Amostra[contador_aux_2] & 0x00800000;                    // Verifica estado do bit 23 aplicando a operação lógica "AND" por meio da máscara 0x800000.
            
                                                                                                              // Se estado do bit 23 igual a "1", aplicar operação lógica de "complemento de 2" e multiplicar por (-1).
                                                                                                              // Em seguida multiplicar pelo fator de conversão para volts
            if(sinal_negativo == 0x800000){ 
                volatile uint32_t semiciclo_neg  = ((~vetor_Amostra[contador_aux_2] + 0x1)) & 0xffffff;       // lê amostra e aplica operação "complemento de 2"
                converte_volts[contador_aux_2] = -(semiciclo_neg*fator_conv_volts);                           // converte para volts e multiplicar por -1
                }
                // Se estado do bit 23 igual a "0", aplicar fator de conversão para volts   
                    else{
                        volatile uint32_t semiciclo_pos = vetor_Amostra[contador_aux_2];                      // lê amostra
                        converte_volts[contador_aux_2] = (semiciclo_pos*fator_conv_volts);                    // converte pata volts      
                }
        } // Final do Laço verificação sinal da amostra em complemento de 2 
    }
    
volatile float convert_BIN_Volts(int contador, volatile float *converte_volts, float *arrayPIE){
    for (int coluna_piE = 0; coluna_piE < 10; coluna_piE++) {                                                 // Nr de amostras
        int ptos_periodo = contador + coluna_piE; // Nr de amostras de cada periodo
       // Multiplica a matriz do sinal convertido pela matriz pseudo inversa piE
        volatile float SigConverted = SigConverted + (float)converte_volts[ptos_periodo]*(float)arrayPIE[coluna_piE];
    }
}
//****************************************************************************************************************************
void ordena_vetores(volatile float *ArrayPrincipal, volatile float *ArraySecundario, int tamanho_do_array){
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

void trima_array(volatile float *Array1, volatile float *Array2, volatile float *Trim1, volatile float*Trim2, int tamanho_do_array, int quartil){
    for ( int x = quartil; x < (tamanho_do_array - quartil); x++){            //Remove 1o quartil das extremidades superior e inferior 
        Trim1[x - quartil] = Array1[x];                                       //Vetor 1o quartil Z trimado 
        Trim2[x - quartil] = Array2[x];                                       //Vetor 10 quartil fase
    }
}

void media_polar(float *ArrayAmpl, float *ArrayPhase, int tamanho_do_array,
                 float *media_Z, float *phase_Z){
    
    float real_part = 0;                                                         // Media trimada parte real
    float imag_part = 0;  
      for(int x = 0; x < tamanho_do_array; x++){                                //Converte polar para retangular
          real_part =  real_part + ArrayAmpl[x]*cos( ArrayPhase[x]*PI/180);     //Calcula parte real e soma
          imag_part =  imag_part + ArrayAmpl[x]*sin( ArrayPhase[x]*PI/180);     //Calcula parte imaginária e soma
      }
    real_part = (real_part)/tamanho_do_array;                                   //Calcula media parte real
    imag_part = (imag_part)/tamanho_do_array;                                   //calcula media parte imaginaria
    
    *media_Z = sqrt(sq(real_part)+sq(imag_part));                               // Converte retangular para polar - modulo Z
    *phase_Z = atan2(imag_part , real_part)*(180/PI);                           // cálculo da fase   
}
