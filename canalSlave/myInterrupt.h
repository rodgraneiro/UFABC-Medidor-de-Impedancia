/*
#include "defConstVariaveis.h"
//#include "inicialization.h"

const int DRDY = 23;  // Port A14 Arduino -> Data Ready Output AD7762 pin 38
volatile int contadorAmostra = 0;
volatile int Nr_de_Amostras = 20;
volatile uint32_t vetor_Amostra[20] = {0};
volatile uint32_t vetor_segunda_palavra[20] = {0};
void HabilitaDRDY();




//***************************************************
// Interrupção para  leitura de dados do AD7762
// Lê "Nr_de_Amostras" 
//*************************************************    

void leADC() {                                                            // Interrupção para ler Bus de dados do ADC
    detachInterrupt(digitalPinToInterrupt(DRDY));                         // Desabilita interrupção DRDY p/ ler ptos da senoide (Nr_de_Amostras)     
            for(int i = 0; i <= 40; i++){                                 // Delay ajuste sincronismo DRDY
            asm("nop \n");
            }
    
    while(contadorAmostra < Nr_de_Amostras){                                                               
        REG_PIOD_ODSR = 0x00000004;                                           // CS = 0, DRDW = 0 e RSET = 1 habilita leitura
        vetor_Amostra[contadorAmostra] = REG_PIOC_PDSR;                       // lê os 32 bits da palavra 1 (MSD) no registrador  portC     
            for(int i = 0; i <= 10; i++){                                     // periodo de tempo para ler 1a palavara e armazena na matriz "vetor_Amostra"
            asm("nop \n");
            }           
                                                                              // Palavra de controle do portD para desabilitar CI AD7762
        REG_PIOD_ODSR = 0x00000007;                                           // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura
            for(int i = 0; i <= 4; i++){                                      // periodo de tempo para ADC apresentar 2a palavra no buffer
            asm("nop \n");
            }
                    
        REG_PIOD_ODSR = 0x00000004;                                           // CS = 0, DRDW = 0 e RSET = 1 habilita leitura             
        vetor_segunda_palavra[contadorAmostra] = REG_PIOC_PDSR;               // lê os 32 bits da palavra 2 (LSD) no registrador  portC
            for(int i = 0; i <= 9; i++){                                      // periodo de tempo para ler 2a palavara e armazena na matriz "vetor_Amostra"                             
            asm("nop \n");
        }   
                                                                              // Palavra de controle do portD para desabilitar AD7762
        REG_PIOD_ODSR = 0x00000007;                                           // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura              
        contadorAmostra++;                                                    //  contador de amostras 
            for(int i = 0; i <= 22; i++){                                     // periodo de tempo para nova amostra
            asm("nop \n");
        }
    }             
    attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING); // Habilita interrupção do botão de medição             
}

  //*******INTERRUPÇÕES
          
          //***************************************************
          // Interrupção do botão de início de medição
          //*************************************************    
void HabilitaDRDY(){
          detachInterrupt(digitalPinToInterrupt(buttonPin8));// Desabilita interrupção do botão de início de medição
          attachInterrupt(digitalPinToInterrupt(DRDY), leADC, FALLING);  // Habilita interrupção LeADC para  leitura de dados do AD7762
}
*/
