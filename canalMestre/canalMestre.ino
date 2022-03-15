//*****************************************************************************************
// Arquitetura para aquisição de sinais de Miografia de Impedância Elétrica
// UFABC - Universidade Federal do ABC
// Código do canal MESTRE do Medidor de Impedância
// Autor: Edson Rodrigues
// 08/03/2021
// versão 1.1 inicial
//******************************************************************************************
//********INICIALIZAÇAO*******************************************************************
//const int buttonPin8 = 8;     // Número do pino do Arduino para o pushbutton
//int buttonState8 = 0;         // Variável p/ armazenar status  do pushbutton
#include "Arduino.h"
#include "myFunctions.h" 
#include "Inicialization.h" 
#include "MathHelpers.h" 
#include <Wire.h>                         // Carrega a biblioteca I2C
                                          // DISPLAY
#include <LiquidCrystal.h>                // Carrega a biblioteca LiquidCrystal       


//#define Nr_de_Amostras  10
#define M_PI 3.141592653589
#define CS 25                        // Port D0 Arduino -> Chip Select AD7762 pin 40
#define RDWR  26                      // Port D1 Arduino -> Read/Write AD77627932384626
#define NOP() asm("nop \n")
#define buttonPin8  8                 // pin 39
#define RESET 27                      // Port D2 Arduino -> Reset AD7762 pin 37
#define DRDY  23                      // Port A14 Arduino -> Data Ready Output AD7762 pin 38
#define SYNC  24                      // Port A15 Arduino -> Synchronization Input AD7762 pin 36const int CS = 25;                        // Port D0 Arduino -> Chip Select AD7762 pin 40
//
//********************CONSTANTES E VARIÁVEIS********************************


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // Define os pinos que serão utilizados para ligação ao display

void setup() {   //*********************INÍCIO SETUP**********************************8
              //Time_1 = micros();
              //pinMode(buttonPin8, INPUT);     // Inicializa pino do pushbutton como input:
              //Serial.begin(115200);
              Serial.begin(9600);

              busColtrolIni(CS, RDWR, RESET, DRDY, SYNC, buttonPin8); // Configuração de Portas do Bus de controle do AD7762 e Arduino
              delay(100);

              unselectADC(RESET, CS, RDWR, SYNC);                     // Desabilita ADC 7762
              //delay(100);

               busOutputADC(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);           // Configura bus de dados como output
               delay(100);
               pulsoPinoADC(RESET, 100);                                                                     //reset ADC7762

               zeraOutputBusDados(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);     // Zerar saída bus de dados
               delay(100);  
               //pulsoPinoADC(SYNC, 100);  
               
  for (int contadorSetup = 0; contadorSetup < 2; contadorSetup++) {  // Laço setup
               
              // Envia Endereço Registrador2 p/ Bus de Dados**************************

//digitalWrite(D0, LOW);      //Endereço Registrador 2  0x0002
digitalWrite(D1, HIGH);

//*****************************************************


//******************************************
// ESCREVE Endereço Registrador2
//*********************************************

//delay(10);
//digitalWrite(CS, LOW);  // Habilita Chip Select do AD7762 para escrita
//digitalWrite(CS, HIGH); // desabilita Chip Select do AD7762 
               pulsoPinoADC(CS, 5);  

              //*****Envia Palavra de controle do Registrador2 p/ Bus de Dados*****
              // set CDIV = 0 metade MCLk
              // set DIPD = 0 habilita Dif Amp
              // set PD = 0 habilita CI (Power ON)
              // set LPWR = 0 seta power no modo normal
              //******************************************************      

digitalWrite(D4, HIGH);   // Default 9B
digitalWrite(D7, HIGH);   //Default 9B

//******************************************
// ESCREVE palavra de controle no Registrador2
//*********************************************      

//delay(10);
//digitalWrite(CS, LOW);  // Habilita Chip Select do AD7762 para escrita
//digitalWrite(CS, HIGH); // desabilita Chip Select do AD7762 
//*********************************************************
               pulsoPinoADC(CS, 5);  

              //*********************************************************
              // ESCREVE END REG 1 0X0001
              //******************************************************** 


              writeBusADC(0x00000004);                                                                      // ESCREVE Endereço 0x04 Registrador1
              delay(10);
              pulsoPinoADC(CS, 10);                                                                         // Habilita pulso Chip Select do AD7762 para escrita
              //zeraOutputBusDados(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);
              zeraBusADC(0x00000004);                                                                       //zera endereço Reg1 do bus de dados
              delay(10);
              pulsoPinoADC(CS, 10);

              //***********************************************
              // ESCREVE WORD REG 1 0X001D
              // DEC2, DEC1, DEC0 = 0X4 PARA DECIMACAO 16X

              writeBusADC(0x00000068);                                                                     // ESCREVE Palavra de controle 0x64do Registrador2
              delay(10);
              pulsoPinoADC(CS, 10);                                                                         // Habilita pulso Chip Select do AD7762 para escrita
              //zeraOutputBusDados(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);
              zeraBusADC(0x00000068);                                                                       //zera endereço Reg1 do bus de dados
              delay(10);
               pulsoPinoADC(CS, 10);

              
  } // Final laço setup


//****************************

                                                                                                           //Prepara PORTC como INPUT           
              busInputADC(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);          // Configura bus de dados como entrada 
              delay(100);
          
              pulsoPinoADC(SYNC, 200);                                                                    // Envia sinal de sincronismo SYNC *******************  

              Wire.begin();                                                                              // Incia comunicação I2C
              
              
                                                                                                          //***************inicia LCD 
              lcd.begin(16, 2);                                                                           // Define o número de colunas e linhas do LCD
              lcd.clear();                                                                                // Limpa a tela
              lcd.setCursor(1, 0);                                                                        // Posiciona o cursor na coluna 1, linha 0;
              lcd.print("MIE-EBM-UFABC");                                                                 // Envia o texto entre aspas para o LCD
              lcd.setCursor(1, 1);                                                                        // Posiciona o cursor na coluna 1, linha 0;
              lcd.print("Pressione bot 1");                                                               // Envia o texto entre aspas para o LCD
              
}         //**********************FINAL de void setup() ****************************
    


void loop() { //***************************** INÍCIO void loop() *****************************

        //**** Habilita interrupção do botão que dispara a Medição das N_amostras
        attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING);       // Habilita interrupção do botão de início de medição
                                                                                  // e vai para interrupção LeAdc              
        while(contadorAmostra < Nr_de_Amostras){                                        // Realiza a leitura das Nr_de_Amostras enquanto                           
                                         }                                        // a interrupção "HabilitaDRDY" estiver habilitad
        detachInterrupt(digitalPinToInterrupt(DRDY));                                   //*** Desabilita interrupção p/ aquisição de amostras   
        
        convert32to24bits(Nr_de_Amostras, vetor_Amostra, vetor_segunda_palavra);                        // coverte palavra de 32 bits para 24 bits 
        verifSinalNeg(Nr_de_Amostras, vetor_Amostra, converte_volts, fator_conv_volts);
        //time 46us
        
                                                                                              //**********************************************************
                                                                                              //          DEMODULAÇÃO PO QUADRATURA
                                                                                              //**********************************************************
        
        soma_seno = convert_BIN_Volts(contador_aux_3, converte_volts, piEs);                  // convertes amostra discretizada em volts
        soma_cosseno = convert_BIN_Volts(contador_aux_3, converte_volts, piEc);               // convertes amostra discretizada em volts
        soma_offset = convert_BIN_Volts(contador_aux_3, converte_volts, piEdc);               // convertes amostra discretizada em volts
        amplitude = 2*sqrt(sq(soma_seno)+sq(soma_cosseno));                                   // Cálculo da amplitude
        fase = atan2(soma_cosseno , soma_seno)*(180/PI);                                      // cálculo da fase
        
            if(fase < 0){ 
                fase = fase + 360;                                                            // convete ândulo 0 - 360 graus
            }
        
        ampTOTAL = amplitude;                                                                 // Soma dos dados para o cálculo de média estatística
        faseTOTAL = fase;                                                         
        offsetTOTAL =  offsetTOTAL;                                                 
        faseTOTALchA = faseTOTAL;
        // 5us
                
/*
// Para debug
//Serial.print(Nr_medicao);
//Serial.print("  ;  ");
//Serial.print("amplitude - fase - TOTAL ");
//Serial.print("  ;  ");
//Serial.print(sci(ampTOTAL,4));
//Serial.print("  ;  ");
//Serial.print(sci(faseTOTAL,4));
//Serial.print("  ;  ");
//Serial.println(sci(offsetTOTAL,4));
*/
        //delay(300);
        contadorAmostra = 0;
        contador_aux_1 = 0;
        contador_aux_2 = 0;
        contador_aux_3 = 0;
        coluna_piE = 0;
        soma_seno = 0;
        soma_cosseno = 0;
        soma_offset = 0;
        amplitude = 0;
        fase =0;
        faseTOTAL = 0;
        offsetTOTAL = 0; 
              // 3us
        delay(10);              
//*****************************************************************************************
                    
        Wire.requestFrom(8, 12);    // request 6 bytes from slave device #8
        // 1192us
        
        while(Wire.available()) { // slave may send less than requested
            Time_1 = micros();
            canal_escravo_data[0] = Wire.read();                            // Lê os 4 bytes da amplitude enviados pelo escravo 
            canal_escravo_data[1] = Wire.read(); 
            canal_escravo_data[2] = Wire.read(); 
            canal_escravo_data[3] = Wire.read(); 
            
            canal_escravo_data[4] = Wire.read();                            // Lê os 4 bytes da fase enviados pelo escravo 
            canal_escravo_data[5] = Wire.read(); 
            canal_escravo_data[6] = Wire.read(); 
            canal_escravo_data[7] = Wire.read(); 
            
            canal_escravo_data[8] = Wire.read();                            // Lê os 4 bytes do offset enviados pelo escravo 
            canal_escravo_data[9] = Wire.read(); 
            canal_escravo_data[10] = Wire.read(); 
            canal_escravo_data[11] = Wire.read();           
            // 6us
        }

        delay(10);
        union Nr_IEEE754_union {byte as_byte[4]; float as_float;} amplitude_union;  //Nr float formato IEEE754 de 32 |Sinal|Expoente|Mantissa| 
            amplitude_union.as_byte[0] = canal_escravo_data[0];
            amplitude_union.as_byte[1] = canal_escravo_data[1];
            amplitude_union.as_byte[2] = canal_escravo_data[2];
            amplitude_union.as_byte[3] = canal_escravo_data[3];   
            float AMPLITUDE = amplitude_union.as_float  ;
            ampTOTALchSlave = AMPLITUDE;
        // 2us

        union Nr_IEEE754_union fase_union;   
            fase_union.as_byte[0] = canal_escravo_data[4];
            fase_union.as_byte[1] = canal_escravo_data[5];
            fase_union.as_byte[2] = canal_escravo_data[6];
            fase_union.as_byte[3] = canal_escravo_data[7];   
            float FASE = fase_union.as_float  ;
            faseTOTALchSlave = FASE;
        
        union Nr_IEEE754_union offset_union;   
            offset_union.as_byte[0] = canal_escravo_data[8];
            offset_union.as_byte[1] = canal_escravo_data[9];
            offset_union.as_byte[2] = canal_escravo_data[10];
            offset_union.as_byte[3] = canal_escravo_data[11];   
            float OFFSET = offset_union.as_float  ;
            offsetTOTALchSlave = OFFSET;
                                   
                impedancia_Z = ampTOTAL / ampTOTALchSlave;             // Cálculo da impedância
                impedancia_fase = faseTOTALchA - faseTOTALchSlave;     // Cálculo do ângulo theta
                // 6us
    
                vetorModulo_Z[indiceSave] = impedancia_Z;
                vetorFase[indiceSave] = impedancia_fase;

            if(indiceSave > vetorSize){
                detachInterrupt(digitalPinToInterrupt(DRDY));
                detachInterrupt(digitalPinToInterrupt(buttonPin8));
                
                ordena_vetores(vetorModulo_Z, vetorFase, vetorSize);
                trima_array(vetorModulo_Z, vetorFase, Z_trimed, Ph_trimed, vetorSize, quartil);
                ordena_vetores(Ph_trimed, Z_trimed, Primeiroquartil);
                trima_array(Z_trimed, Ph_trimed, Z2_trimed, Ph2_trimed, Primeiroquartil, quartil);
                media_polar(Z2_trimed, Ph2_trimed, Segundoquartil, &modulo_Z, &fase_Z);
                delay(10);          
                    // ************ DISPLAY **********************************
                    //Envia os dados calculados para o display
                    lcd.begin(16, 2);                             // Define o número de colunas e linhas do LCD
                    lcd.clear();                                  // Limpa a tela
                    lcd.setCursor(0, 0);                          // Posiciona o cursor na coluna 0, linha 0;
                    lcd.print("Z =");                             // Escrever "Z =" no display
                    lcd.setCursor(4, 0);                          // Posiciona o cursor na coluna 4, linha 0;
                    lcd.print(modulo_Z,4);                        // Escrever valor da Impedância "X.XXXX"
                    lcd.setCursor(15, 0);                         // Posiciona o cursor na coluna 15, linha 1;
                    lcd.write(B11110100);                         // ômega
                    lcd.setCursor(0, 1);                          // Posiciona o cursor na coluna 0, linha 1;
                    lcd.write(B11110010);                         // theta
                    lcd.setCursor(1, 1);                          // Posiciona o cursor na coluna 1, linha 1;
                    lcd.print(" =");                              // Escrever " =" no display
                    lcd.setCursor(4, 1);                          // Posiciona o cursor na coluna 4, linha 1;
                    lcd.print(fase_Z,2);                          // Escrever valor da fase "XX.X"
                    lcd.setCursor(15, 1);                         // Posiciona o cursor na coluna 15, linha 1;
                    lcd.write(B11011111);                         // graus
                
                Serial.print("media trimada:  ");
                Serial.print(modulo_Z, 2);
                Serial.print(" ");
                Serial.println(fase_Z,2);
                indiceSave = 0;
                delay(10);
            }
             
        ampTOTAL = 0;
        ampTOTALchSlave = 0;
        faseTOTALchA =0;
        faseTOTALchSlave = 0;
        offsetTOTAL = 0;
        offsetTOTALchSlave = 0;
}

//**********************************************************************************************************************************

            //*******INTERRUPÇÕES

            //***************************************************
            // Interrupção do botão de início de medição
            //*************************************************   

void HabilitaDRDY(){
            // Desabilita interrupção do botão de início de medição
            detachInterrupt(digitalPinToInterrupt(buttonPin8));
            attachInterrupt(digitalPinToInterrupt(DRDY), leADC, FALLING);
}

          //HabilitaDRDY(int buttonPin8, int DRDY, char leADC)
          //***************************************************
          // Interrupção para  leitura de dados do AD7762
          // Lê "Nr_de_Amostras" 
          //*************************************************    

void leADC() { 
          detachInterrupt(digitalPinToInterrupt(DRDY));
              for(int i = 0; i <= 50; i++){                                       // Delay para calibração do sincronismos
                  asm("nop \n");
              }
              while(contadorAmostra < Nr_de_Amostras){ 
                  REG_PIOD_ODSR = 0x00000004;                                     // CS = 0, DRDW = 0 e RSET = 1 habilita leitura         
                  vetor_Amostra[contadorAmostra] = REG_PIOC_PDSR;                 // lê os 32 bits da palavra 1 (MSD) no registrador  portC
                      for(int i = 0; i <= 9; i++){                                // Delay para calibração dosoncronismos
                          asm("nop \n");
                      }
                                                                                  // e armazena na matriz "vetor_Amostra"
                                                                                  // Palavra de controle do portD para desabilitar CI AD7762
          REG_PIOD_ODSR = 0x00000007;                                             // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura
              for(int i = 0; i <= 4; i++){                                        // Delay para calibração dosoncronismos
                  asm("nop \n");
              }
          
          REG_PIOD_ODSR = 0x00000004;                                             // CS = 0, DRDW = 0 e RSET = 1 habilita leitur             
          vetor_segunda_palavra[contadorAmostra] = REG_PIOC_PDSR;                 // lê os 32 bits da palavra 2 (LSD) no registrador  portC
              for(int i = 0; i <= 9; i++){                                        // Delay para calibração dosoncronismos
                  asm("nop \n");
              }
                                                                                  // e armazena na matriz "vetor_segunda_palavra" 
                                                                                  // Palavra de controle do portD para Habilitar a leitura do AD7762
          REG_PIOD_ODSR = 0x00000007;                                             // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura              
          contadorAmostra++;                                                      //  contador de amostras                                                      
              for(int i = 0; i <= 23; i++){  
                  asm("nop \n");
              }         
          }
       attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING); 
 }             

void serialEvent(){
    if(Serial.available() > 0){
        char cmd = Serial.read();
        if(cmd == 'B'){
            Serial.println(impedancia_Z,2);
            Serial.println(impedancia_fase,2);
        }
    }
}
