//*****************************************************************************************
// Arquitetura para aquisição de sinais de Miografia de Impedância Elétrica
// UFABC - Universidade Federal do ABC
// Código do canal ESCRAVO do Medidor de Impedância
// Autor: Edson Rodrigues
// 08/03/2021
// versão 1.1 inicial
//******************************************************************************************

#include "myFunctions.h"
#include "inicialization.h"  
#include "MathHelpers.h" 
#include <Wire.h>

//********INICIALIZAÇAO*******************************************************************
/*
int buttonState8 = 0;         // variable for reading the pushbutton status
int habilitaMasterState = 0;  // variable for reading the pushbutton status
int StartState = 0;           // variable for reading the pushbutton status
*/
//********************CONSTANTES E VARIÁVEIS*********************************
//#define M_PI 3.141592653589793238462643
//#define Rsentinela 55.1
//#define NOP() asm("nop \n")
#define CS 25                   // Port D0 Arduino -> Chip Select AD7762 pin 40
#define RDWR 26                 // Port D1 Arduino -> Read/Write AD7762 pin 39
#define RESET 27                // Port D2 Arduino -> Reset AD7762 pin 37
#define DRDY 23                 // Port A14 Arduino -> Data Ready Output AD7762 pin 38
#define buttonPin8 8            // the number of the pushbutton pin
#define habilitaMaster 9        // the number of the pushbutton pin
#define Start  10               // the number of the pushbutton pin
#define Nr_de_Amostras 10
#define ptos_por_periodo 10

//volatile int Nr_de_Amostras = 10;
//int ptos_por_periodo = 10;
//int Nr_de_periodos = Nr_de_Amostras/ptos_por_periodo;
//int ptos_periodo = 0;
volatile uint32_t vetor_Amostra[Nr_de_Amostras] = {0};
volatile uint32_t vetor_segunda_palavra[Nr_de_Amostras] = {0};
volatile float converte_volts[Nr_de_Amostras];
  

/*
volatile uint32_t semiciclo_pos = 0;
volatile uint32_t low8 = 0;
volatile uint32_t low24 = 0;
volatile int contadorSetup = 0;
volatile int contadorAmostra = 0;
volatile int contador_aux_1 = 0;
volatile int contador_aux_2 = 0;
int contador_aux_3 = 0;
float soma_seno = 0;
float soma_cosseno = 0;
float soma_offset = 0;
*/
//float Rsentinela = 55.1;
//float fator_conv_corrente = 1.299285e-7;
//unsigned long tempo_inicio = millis();
//unsigned long tempo_exec[20] = {0};
//long Nr_medicao = 0;
/*
int coluna_piE = 0;
volatile float offsetTOTAL = 0;
float amplitude = 0;
volatile float ampTOTAL = 0;
float fase = 0;
volatile float faseTOTAL = 0;
*/


//int NrMed = 0;

//unsigned int aux;
  
/*
 //Bus de Dados D0 à D15

const int D0 = 34; //Port C2 Arduino DUE
const int D1 = 35; //Port C3
const int D2 = 36; //Port C4
const int D3 = 37; //Port C5
const int D4 = 38; //Port C6
const int D5 = 39; //Port C7
const int D6 = 40; //Port C8
const int D7 = 41; //Port C9
//*************
const int D8 = 51; //Port C12
const int D9 = 50; //Port C13
const int D10 = 49; //Port C14
const int D11 = 48; //Port C15
const int D12 = 47; //Port C16
const int D13 = 46; //Port C17
const int D14 = 45; //Port C18
const int D15 = 44; //Port  C19

//*****************************Matriz pseudo inversa 10 ptos excitação 31,25kHz - Sample Rate 312,5kHz
float piEs[] = {0.117557050458495, 0.190211303259031, 0.190211303259031, 0.117557050458495, 2.44929359829470e-17, -0.117557050458495, -0.190211303259031, -0.190211303259031, -0.117557050458495, -4.89858719658942e-17};
float piEc[] = {0.161803398874990, 0.0618033988749894, -0.0618033988749895, -0.161803398874989, -0.200000000000000, -0.161803398874990, -0.0618033988749896, 0.0618033988749895, 0.161803398874990, 0.200000000000000};
float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};
*/

void setup() {   //*********************INÍCIO SETUP**********************************8
    
          Serial.begin(9600);
          Wire.begin(8); 
          Wire.onRequest(requestEvent); // register event              
          
          busColtrolIni(CS, RDWR, RESET, DRDY, buttonPin8, habilitaMaster);                             // Configuração de Portas do Bus de controle do AD7762 e Arduino
          delayFunc(150);
          
          unselectADC(RESET, CS, RDWR);                                                                 // Desabilita ADC 7762

          busOutputADC(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);           // Configura bus de dados como output
          delayFunc(260);
          pulsoPinoADC(RESET, 100);                                                                     //reset ADC7762
           
          zeraOutputBusDados(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);     // Zerar saída bus de dados
          delayFunc(100);  

           writeBusADC(0x00000008);                                                                     // ESCREVE Endereço Registrador2
           pulsoPinoADC(CS, 10);                                                                        // Habilita pulso Chip Select do AD7762 para escrita
          
          //*****Envia Palavra de controle do Registrador2 p/ Bus de Dados*****
          // set CDIV = 0 metade MCLk
          // set DIPD = 0 habilita Dif Amp
          // set PD = 0 habilita CI (Power ON)
          // set LPWR = 0 seta power no modo normal
          //******************************************************

          zeraBusADC(0x00000008);                                                                       //zera bus de dados
          delayFunc(100);

        
          writeBusADC(0x00000248);                                                                      // ESCREVE Palavra de controle do Registrador2
          
          pulsoPinoADC(CS, 10);                                                                         // Habilita pulso Chip Select do AD7762 para escrita
          zeraBusADC(0x00000248);                                                                       //zera bus de dados
          delayFunc(10);

          writeBusADC(0x00000004);                                                                      // ESCREVE Endereço 0x04 Registrador1
          pulsoPinoADC(CS, 10);                                                                         // Habilita pulso Chip Select do AD7762 para escrita
          zeraBusADC(0x00000004);                                                                       //zera endereço Reg1 do bus de dados
          delayFunc(10);
       
          writeBusADC(0x000000064);                                                                     // ESCREVE Palavra de controle 0x64do Registrador2
          pulsoPinoADC(CS, 10);                                                                         // Habilita pulso Chip Select do AD7762 para escrita
          
          zeraBusADC(0x00000064);                                                                       //zera endereço Reg1 do bus de dados
          delayFunc(10);

          busInputADC(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);            // Configura bus de dados como entrada 
          delayFunc(100);                                                                               // aguarda sinal de SYNC
}                                                                                                       //**********************FINAL SETUP PRINCIPAL ****************************/



void loop() {
   

          //**** Habilita interrupção do botão que dispara a Medição das N_amostras
         
          attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING);                       // Habilita interrupção do botão de início de medição
                                                                                   
          while(contadorAmostra < Nr_de_Amostras){                                                        // Realiza a leitura das Nr_de_Amostras enquanto a interrupção 
                                                                                                          //"HabilitaDRDY" estiver habilitada
                                                                                                          //Aguarda fim da interrupção
          } 
                                                 
          detachInterrupt(digitalPinToInterrupt(DRDY));                                                   //*** Desabilita interrupção p/ aquisição de amostras 
           
          convert32to24bits(Nr_de_Amostras, vetor_Amostra, vetor_segunda_palavra);                        // coverte palavra de 32 bits para 24 bits


          //************************************************** 
          // Verificação de sinal positivo/negativo no bit 23 e complemento de 2
          // conversão para tensão em volts
          //**************************************************

          verifSinalNeg(Nr_de_Amostras, vetor_Amostra, converte_volts, fator_conv_corrente, Rsentinela); //verifica sinal positivo - negativo
 


          //**********************************************************
          //          DEMODULAÇÃO PO QUADRATURA
          //**********************************************************
          
          soma_seno = convert_BIN_Volts(contador_aux_3, converte_volts, piEs);                  // convertes amostra discretizada em volts
          soma_cosseno = convert_BIN_Volts(contador_aux_3, converte_volts, piEc);               // convertes amostra discretizada em volts
          soma_offset = convert_BIN_Volts(contador_aux_3, converte_volts, piEdc);               // convertes amostra discretizada em volts
          amplitude = 2*sqrt(sq(soma_seno)+sq(soma_cosseno));                                   // Cálculo da amplitude
          fase = atan2(soma_cosseno , soma_seno)*(180/PI);                                      // cálculo da fase
          
              if(fase < 0){ 
                    fase = fase + 360;                                                          // convete ândulo 0 - 360 graus
              }          
          ampTOTAL = amplitude;                                                      // Soma dos dados para o cálculo de média estatística
          faseTOTAL = fase;                                                         //
          offsetTOTAL = soma_offset;                                             //
          
    
                                                                                                                            
      //*********************************************************************************************
      //  TRANSMISSÃO SERIAL (I2C) DE DADOS
      //*********************************************************************************************
      
      delay(10);                                                                         // delay 10us                   
      //********************************************
      // ZERAR VARIÁVEIS
      //********************************************                 
      digitalWrite(habilitaMaster, LOW);
      contadorAmostra = 0;
      contadorSetup = 0;
      contador_aux_1 = 0;
      contador_aux_2 = 0;
      contador_aux_3 = 0;
      coluna_piE = 0;
      ptos_periodo = 0;
      soma_seno = 0;
      soma_cosseno = 0;
      amplitude = 0;
      fase = 0;
      semiciclo_pos = 0;
      //aux = 0;      
}                                                                                               // Final do loop()
//**********************************************************************************************************************************


          //***************************************************
          // Interrupção do botão de início de medição
          //*************************************************    
void HabilitaDRDY(){
          detachInterrupt(digitalPinToInterrupt(buttonPin8));// Desabilita interrupção do botão de início de medição
          attachInterrupt(digitalPinToInterrupt(DRDY), leADC, FALLING);  // Habilita interrupção LeADC para  leitura de dados do AD7762
}

//***************************************************
// Interrupção para  leitura de dados do AD7762
// Lê "Nr_de_Amostras" 
//*************************************************    

void leADC() {                                                            // Interrupção para ler Bus de dados do ADC
    detachInterrupt(digitalPinToInterrupt(DRDY));                         // Desabilita interrupção DRDY p/ ler ptos da senoide (Nr_de_Amostras)     
            for(int i = 0; i <= 45; i++){                                 // Delay ajuste sincronismo DRDY
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


void requestEvent() {

union Nr_IEEE754_union {float as_float ; byte as_byte[4];} amplitude_union;            // Coversão foat ampTOTAL em 4 bytes para transmissão serial I2C 
amplitude_union.as_float = ampTOTAL;
union Nr_IEEE754_union fase_union;                                                    // Coversão foat faseTOTAL em 4 bytes para transmissão serial I2C 
fase_union.as_float = faseTOTAL;
union Nr_IEEE754_union offset_union;                                                  // Coversão foat offsetTOTAL em 4 bytes para transmissão serial I2C 
offset_union.as_float = offsetTOTAL;

Wire.write(amplitude_union.as_byte[0]);                                               // Envia o bytes da ampTOTAL
Wire.write(amplitude_union.as_byte[1]);                                              
Wire.write(amplitude_union.as_byte[2]);
Wire.write(amplitude_union.as_byte[3]);

Wire.write(fase_union.as_byte[0]);                              // Envia o bytes da faseTOTAL
Wire.write(fase_union.as_byte[1]);                    
Wire.write(fase_union.as_byte[2]);
Wire.write(fase_union.as_byte[3]);

Wire.write(offset_union.as_byte[0]);                            // Envia o bytes do offsetTOTAL
Wire.write(offset_union.as_byte[1]);                    
Wire.write(offset_union.as_byte[2]);
Wire.write(offset_union.as_byte[3]); 
ampTOTAL = 0;
faseTOTAL = 0;
offsetTOTAL = 0;
}

void serialEvent(){
  if(Serial.available() > 0){
    char cmd = Serial.read();
    if(cmd == 'B'){
     //lcd.setCursor(15, 1);         // Posiciona o cursor na coluna 15, linha 1;
     //lcd.write("E");          // graus
                                                        //Serial.println(0);
                                                        //Serial.println(0);
    }
  }
}
