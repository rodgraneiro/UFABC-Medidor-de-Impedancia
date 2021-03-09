//*****************************************************************************************
// Arquitetura para aquisição de sinais de Miografia de Impedância Elétrica
// UFABC - Universidade Federal do ABC
// Código do canal ESCRAVO do Medidor de Impedância
// Autor: Edson Rodrigues
// 08/03/2021
// versão 1.1 inicial
//******************************************************************************************
//********INICIALIZAÇAO*******************************************************************
const int buttonPin8 = 8;     // the number of the pushbutton pin
int buttonState8 = 0;         // variable for reading the pushbutton status
//int DRDYstate = 1;         // variable for reading the pushbutton status
const int habilitaMaster = 9;     // the number of the pushbutton pin
const int Start = 10;     // the number of the pushbutton pin
int habilitaMasterState = 0;         // variable for reading the pushbutton status
int StartState = 0;         // variable for reading the pushbutton status

#define M_PI 3.141592653589793238462643
#define Rsentinela 983
#define NOP() asm("nop \n")

//********************CONSTANTES E VARIÁVEIS*********************************

#include "MathHelpers.h" 
#include <Wire.h>

const int CS = 25;    // Port D0 Arduino -> Chip Select AD7762 pin 40
const int RDWR = 26;  // Port D1 Arduino -> Read/Write AD7762 pin 39
const int RESET = 27; // Port D2 Arduino -> Reset AD7762 pin 37
const int DRDY = 23;  // Port A14 Arduino -> Data Ready Output AD7762 pin 
volatile int Nr_de_Amostras = 100;
volatile uint32_t vetor_Amostra[100];
volatile uint32_t vetor_segunda_palavra[100];
volatile uint32_t sinal_negativo = 0;
volatile uint32_t semiciclo_neg = 0;
volatile uint32_t semiciclo_pos = 0;
volatile uint32_t low8 = 0;
volatile uint32_t low24 = 0;
volatile int contadorSetup = 0;
volatile int contadorAmostra = 0;
volatile int contador_aux_1 = 0;
volatile int contador_aux_2 = 0;

float fator = 0.0000006;
float converte_volts[100];

int ptos_periodo = 0;
int coluna_piE = 0;
float cDC = 0;
float soma_offset = 0;
float offsetTOTAL = 0;
float cDCbTOTAL = 0;
float amplitude = 0;
float ampTOTAL = 0;
float fase = 0;
float faseTOTAL = 0;
unsigned long Tempo_T = 0;
unsigned long Tempo_Inter = 0;


//*****************************Matriz pseudo inversa

float piEs[] = {0.117557050458495, 0.190211303259031, 0.190211303259031, 0.117557050458495, 2.44929359829470e-17, -0.117557050458495, -0.190211303259031, -0.190211303259031, -0.117557050458495, -4.89858719658942e-17};
float piEc[] = {0.161803398874990, 0.0618033988749894, -0.0618033988749895, -0.161803398874989, -0.200000000000000, -0.161803398874990, -0.0618033988749896, 0.0618033988749895, 0.161803398874990, 0.200000000000000};
float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};



float soma_seno = 0;
float soma_cosseno = 0;

int NrMed = 0;
int sinal_offset;

float variavel_float = 0;
byte byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8, byte9, byte10, byte11, byte12, byte13;
unsigned int aux;
  

// Bus de Dados D0 à D15
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

//DISPLAY

void setup() {   //*********************INÍCIO SETUP**********************************8
    
    pinMode(buttonPin8, INPUT);         // initialize the pushbutton pin as an input:
    pinMode(habilitaMaster, OUTPUT);    // initialize the pushbutton pin as an input:
    digitalWrite(habilitaMaster, LOW);  // habilita Master:
    Serial.begin(115200);
    Wire.begin(); //               
    
    
    // Configuração de Ports para iniciar AD7762 
    pinMode(CS, OUTPUT);       // Port D0 do Arduino Due
    pinMode(RDWR, OUTPUT);     // Port D1
    pinMode(RESET, OUTPUT);    // Port D2
    pinMode(DRDY, INPUT);      // Port A14 do Arduino Due
    
    //
    digitalWrite(RESET, HIGH);
    digitalWrite(CS, HIGH);
    digitalWrite(RDWR, HIGH);
    
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(D9, OUTPUT);
    pinMode(D10, OUTPUT);
    pinMode(D11, OUTPUT);
    pinMode(D12, OUTPUT);
    pinMode(D13, OUTPUT);
    pinMode(D14, OUTPUT);
    pinMode(D15, OUTPUT);
    
    // RESET inicial      **************************
    digitalWrite(RESET, LOW);// reset
    delay(100);
    digitalWrite(RESET, HIGH);// reset
    delay(100);
    //************************************************
    
    
    for (int contadorSetup = 0; contadorSetup < 100; contadorSetup ++) {  
    
        // Envia Endereço Registrador2 p/ Bus de Dados**************************
        digitalWrite(D0, LOW); //Endereço Registrador 2  0x0002
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        digitalWrite(D5, LOW);
        digitalWrite(D6, LOW);
        digitalWrite(D7, LOW);
        digitalWrite(D8, LOW);
        digitalWrite(D9, LOW);
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        digitalWrite(D13, LOW);
        digitalWrite(D14, LOW);
        digitalWrite(D15, LOW);
        
        //******************************************
        // ESCREVE Endereço Registrador2
        //*********************************************
        delay(10);
        digitalWrite(CS, LOW);  // Habilita Chip Select do AD7762 para escrita
        digitalWrite(CS, HIGH); // desabilita Chip Select do AD7762 
        
        
        //*****Envia Palavra de controle do Registrador2 p/ Bus de Dados*****
        // set CDIV = 0 metade MCLk
        // set DIPD = 0 habilita Dif Amp
        // set PD = 0 habilita CI (Power ON)
        // set LPWR = 0 seta power no modo normal
        //******************************************************
        
        digitalWrite(D0, LOW); //DIPD
        digitalWrite(D1, HIGH);// "1"
        digitalWrite(D2, LOW);//LPWR
        digitalWrite(D3, LOW);//PD
        digitalWrite(D4, HIGH);// Default 9B
        digitalWrite(D5, LOW);//CDIV
        digitalWrite(D6, LOW);//Default 9B
        digitalWrite(D7, HIGH);//Default 9B
        digitalWrite(D8, LOW);
        digitalWrite(D9, LOW);
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        digitalWrite(D13, LOW);
        digitalWrite(D14, LOW);
        digitalWrite(D15, LOW);
        
        //******************************************
        // ESCREVE palavra de controle no Registrador2
        //*********************************************                
        delay(10);
        digitalWrite(CS, LOW);
        digitalWrite(CS, HIGH);
        
        
        
        //*********************************************************
        // ESCREVE END REG 1 0X0001
        //******************************************************** 
        digitalWrite(D0, HIGH); //Endereço Registrador 1  0x0001
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        digitalWrite(D5, LOW);
        digitalWrite(D6, LOW);
        digitalWrite(D7, LOW);
        digitalWrite(D8, LOW);
        digitalWrite(D9, LOW);
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        digitalWrite(D13, LOW);
        digitalWrite(D14, LOW);
        digitalWrite(D15, LOW);
        
        // REG_PIOC_ODSR = 0x00000004; // END reg 2 
        
        delay(10);
        digitalWrite(CS, LOW);
        delay(1);
        digitalWrite(CS, HIGH);
        //delay(100);
        //***********************************************************
        
        
        //***********************************************
        // ESCREVE WORD REG 1 0X001D
        // DEC2, DEC1, DEC0 = 0X4 PARA DECIMACAO 16X
        digitalWrite(D0, LOW);  //DEC0 = 1 ja ta high
        digitalWrite(D1, HIGH);  // DEC1 = 0 ja ta low
        digitalWrite(D2, LOW); // DEC2 = 1
        digitalWrite(D3, HIGH); // tem que ser 1 (high)
        digitalWrite(D4, HIGH); // BYP F3
        digitalWrite(D5, LOW);
        digitalWrite(D6, LOW);
        digitalWrite(D7, LOW);
        digitalWrite(D8, LOW);
        digitalWrite(D9, LOW);
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        digitalWrite(D13, LOW);
        digitalWrite(D14, LOW);
        digitalWrite(D15, LOW);
        
        // REG_PIOC_ODSR = 0x00000074; // Wor reg 1 
        
        delay(10);
        digitalWrite(CS, LOW);
        delay(1);
        digitalWrite(CS, HIGH);
    
    
    }
    
    delay(100);
    
    //****************************
    //prepara PORTC como INPUT
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
    pinMode(D8, INPUT);
    pinMode(D9, INPUT);
    pinMode(D10, INPUT);
    pinMode(D11, INPUT);
    pinMode(D12, INPUT);
    pinMode(D13, INPUT);
    pinMode(D14, INPUT);
    pinMode(D15, INPUT);
    
    delay(100);
    contadorSetup = 0;
    //**********************FINAL SETUP****************************
}


void loop() {
    
main:
          //**** Habilita interrupção do botão que dispara a Medição das N_amostras
         attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING); // Habilita interrupção do botão de início de medição
                                                                                   // e vai para interrupção LeAdc
 
inicio: 
          // Realiza a leitura das Nr_de_Amostras enquanto a interrupção "HabilitaDRDY" estiver habilitada
          while(contadorAmostra < Nr_de_Amostras){
                                                  NOP();
                                                  }
                                                  
          //*** Desabilita interrupção p/ aquisição de amostras                                      
          detachInterrupt(digitalPinToInterrupt(DRDY));

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
                  // /Arduino   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
                  // Palavra 1  |. |. |. |. |. |. |. |. |. |. |. |. |V |V |V |V |V |V |V |V |. |. |V |V |V |V |V |V |V |V |. |. | 
                  // Palavra 2  |. |. |. |. |. |. |. |. |. |. |. |. |V |V |V |V |V |V |V |V |. |. |. |. |. |. |. |. |. |. |. |. | 
                  //-------------------------------------------------------------------------------------------------------------     
        
    for(contador_aux_1 = 0; contador_aux_1 <= Nr_de_Amostras; contador_aux_1++) {
                            //*******************************************************************
                            // Primeira palavra com os 16 bits mais significativos (de 23 à 8)
                            //*******************************************************************
                            
                            // Zerar bits "0" , "1" e bits de "20" à "31" aplicando a operação lógica "AND" 
                            // por meio da máscara 0x000ffffc  
                             
                                vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] & 0x000ffffc; //
                                vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] >> 2;         // Desloca dois bits p direita para elininar bits "0" e "1"
                             
                             // separa os 8 bits menos significaticos da primrira palavra
                             low8 = vetor_Amostra[contador_aux_1] & 0xff; 
                             
                             //Remove os bits "10 e 11" (Lixo do meio da primeira palavra) deslocando 10 bits para direita
                                  vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] >> 10;
                                   
                             // Rearranjar os 16 bits da primeira palavra
                             // Deslocando 8 bits à esquerda e aplicando a operação lógica "OU" com os
                             // 8 bits menos significativos da primeira palavra armazenados na variável low8
                             
                                vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] << 8 | low8;  //Primeira palavra com os 16 bits mais significativos de 23 à 8


                             //****************************************************************** 
                             // Segunda palavra com os 8 bits menos significativos (de 7 à 0)
                             //******************************************************************

                              // Zera bits de "0 à 11" e bits de "20" à "31" aplicando a operação lógica "AND" 
                              // por meio da máscara 0x000ff000
                                  low24 = vetor_segunda_palavra[contador_aux_1] & 0x000ff000;
                                  
                              // Desloca 12 bits à direita separando os 8 bits menos significaticos da palavra de 24 bits 
                                  low24  =  low24 >> 12;

                             // Rearranjar a amostra discretizada com resolução de 24 bits
                             // deslocando os 8 bits da primeira palavra à esquerda e 
                             // aplicando a operação lógica "OU" com os 8 bits menos significativos
                             // da segunda palavra armazenados na variavel low24

                                vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] << 8 | low24; // Amostra discretizada com 24 bits; 
                                   
                             } 



                            //************************************************** 
                            // Verificação de sinal positivo/negativo no bit 23 e complemento de 2
                            // conversão para tensão em volts
                            //**************************************************
     
   for(contador_aux_2 = 0; contador_aux_2 < Nr_de_Amostras; contador_aux_2++){ 

                          // O bit 23 indentifica o sinal da amostra: "1" para negativo e "0" para positivo.

                          // Verifica estado do bit 23 aplicando a operação lógica "AND" por meio da máscara 0x800000.
                          sinal_negativo = vetor_Amostra[contador_aux_2] & 0x800000;

                          // Se estado do bit 23 igual a "1", aplicar operação lógica de "complemento de 2" e multiplicar por (-1).
                          // Em seguida multiplicar pelo fator de conversão para volts
                              if(sinal_negativo == 0x800000){ 
                                                  semiciclo_neg  = ((~vetor_Amostra[contador_aux_2] + 0x1)) & 0xffffff; // "complemento de 2"
                                                  converte_volts[contador_aux_2] = -(semiciclo_neg*300e-9)/Rsentinela;
                                                  Serial.println(sci(converte_volts[contador_aux_2],4));
    
                                                            }
                                                  
                          // Se estado do bit 23 igual a "0", aplicar fator de conversão para volts                                                  
                                             else{
                                                  semiciclo_pos = vetor_Amostra[contador_aux_2]; // * fator;
                                                  converte_volts[contador_aux_2] = (semiciclo_pos*300e-9)/Rsentinela;
                                                  Serial.println(sci(converte_volts[contador_aux_2],4));
                                                  }
                                    }  




                          //**********************************************************
                          //          DEMODULAÇÃO PO QUADRATURA
                          //**********************************************************

                          // Determinar Amplitude, fase e offset. Serão utilizados os três últimos períodos
                          // para evitar transientes do início da medição;

 for(contador_aux_2 = 60; contador_aux_2 < 90; contador_aux_2 = contador_aux_2 + 10){ // Nr de periodos 
                          for (coluna_piE = 0; coluna_piE < 10; coluna_piE++) { // Nr de amostras
                                                                              int ptos_periodo = contador_aux_2 + coluna_piE; // Nr de amostras de cada periodo
                                                                              
                                                                              // Multiplica a matriz do sinal convertido pela matriz pseudo inversa piE
                                                                              soma_seno += (float)converte_volts[ptos_periodo]*(float)piEs[coluna_piE]; 
                                                                              soma_cosseno += (float)converte_volts[ptos_periodo]*(float)piEc[coluna_piE];
                                                                              soma_offset += (float)converte_volts[ptos_periodo]*(float)piEdc[coluna_piE];
                                                                             }

                           
                           amplitude = 2*sqrt(sq(soma_seno)+sq(soma_cosseno))/2; // Cálculo da amplitude
                           fase = atan2(soma_cosseno , soma_seno)*(180/M_PI);    // cálculo da fase

                           // Imprime dados no monitor serial
                           Serial.print("amplitude e fase DC");
                           Serial.print("  ;  ");
                           Serial.print(sci(amplitude,4));
                           Serial.print("  ;  ");
                           Serial.print(sci(fase,4));
                           Serial.print("  ;  ");
                           Serial.println(sci(soma_offset,4));

                           // Soma dos dados para o cálculo de média estatística
                           ampTOTAL = ampTOTAL + amplitude;
                           faseTOTAL = faseTOTAL + fase;
                           offsetTOTAL =  offsetTOTAL + soma_offset;
                           
                           coluna_piE = 0;
                           amplitude = 0;
                           soma_seno = 0; 
                           soma_cosseno = 0;
                           soma_offset = 0;
                           fase = 0;
                          }





                          
                          //********************************************  
                          // Calcular média da ampltude, fase e offsset
                          //*******************************************

                          ampTOTAL =ampTOTAL/3; // Média da amplitude
                          faseTOTAL = faseTOTAL/3; // Média da fase
                           if (faseTOTAL < 0) { // verifica se o ângulo é negatifo
                                               // converte em ângulo positivo
                                               faseTOTAL = 360 + faseTOTAL;
                                               } 
          
                         offsetTOTAL = offsetTOTAL/3; // média do Offset
                          if (offsetTOTAL < 0) {  // verifica se o DC é negatifo
                                               offsetTOTAL = offsetTOTAL * (-1);
                                               int sinal_offset = 0; 
                                               } 
                                               else{
                                               int sinal_offset = 1;
                                               }


                          // Imprimir dados no monitor serial
                          Serial.print("amplitude - fase - TOTAL ");
                          Serial.print("  ;  ");
                          Serial.print(sci(ampTOTAL,4));
                          Serial.print("  ;  ");
                          Serial.print(sci(faseTOTAL,4));
                          Serial.print("  ;  ");
                          Serial.println(sci(offsetTOTAL,4));
                          //Serial.println(REG_CKGR_MCFR);
            
                          delay(2000);


                          //*******************************************************************
                          // PREPARAÇÃO DOS DADOS PARA SEREM ENVIADOS PARA O CANAL MESTRE 
                          // POR MEIO DA COMUNICAÇÃO SERIAL I2C
                          //*******************************************************************

                          // Os dados de amplitude, fase e offset são enviados em 4 bytes de 8 bits.
                          // Portanto, a variável que está no formato float deve ser convertida em bytes como segue:
                          // 1) Separar parte inteira antes da vírgula e armazena nas variáveis "byte1" e "aux". 
                          // 2) Subtrair a parte inteira pela variável "aux" restando somente a mantissa do número. 
                          // 3) Multiplicar a mantissa por 10.000 para converter em nr inteiro.
                          // 4) Separar a parte inteira desse novo valor e armazenar na variável auxilar "aux"
                          // 5) Montar as variáveis byte4, byte3 e byte2 delocando a  variável "aux" à direita de 8 em 8 bits 
                          // Obs.: Esse foi o procedimento para converter o valor da amplitude em 4 bytes.
                          // O mesmo procedimento é utilizado para converter os valores da fase e offset.
                          // A transmissão serial I2C inicia-se pelo bit mais significativo e termina no menos significativo (bit31, bit30, ... , bit1, bit0)
                          // A variável byte13 envia o sinal (positivo = 1 ; negativo = 0) do offset que está armazenado na variável "sinal_offset". 
                          // Obs1.: Os dados serão reconvertidos para o formato float no Canal Mestre

                                                                // Ajustando o número antes da vírgula
                          aux = (unsigned int) ampTOTAL;        // Pega somente a parte inteira da variável float (0 - 65536)
                          byte1 = aux;                          // parte inteira da variável no formato float                    
                                                                // Ajustando o número depois da vírgula
                          ampTOTAL -= aux;                      // Deixa apenas o número depois da vírgula
                          ampTOTAL *= 10000;                    // Multiplica por 10k para pegar 4 dígitos após a vírgula
                          aux = (unsigned int) ampTOTAL;        // Pega somente o valor antes da vírgula
                          byte4 = aux;                          // byte4
                          byte3 = (aux>>8);                     // byte3
                          byte2 = (aux>>16);                    // byte2
                        
                        
                          aux = (unsigned int) faseTOTAL;       // Pega somente a parte inteira da variável float (0 - 65536)
                          byte5 = aux;                          // parte inteira da variável no formato float
                                                                // Ajustando o número depois da vírgula
                          faseTOTAL -= aux;                     // Deixa apenas o número depois da vírgula
                          faseTOTAL *= 10000;                   // Multiplica por 10k para pegar 4 dígitos após a vírgula
                          aux = (unsigned int) faseTOTAL;       // Pega somente o valor antes da vírgula
                          byte8 = aux;                          // byte8
                          byte7 = (aux>>8);                     // byte7
                          byte6 = (aux>>16);                    // byte6

                        
                          aux = (unsigned int) offsetTOTAL;      // Pega somente a parte inteira da variável float (0 - 65536)
                          byte9 = aux;                           // parte inteira da variável no formato float
                                                                 // Ajustando o número depois da vírgula
                          offsetTOTAL -= aux;                    // Deixa apenas o número depois da vírgula
                          offsetTOTAL *= 10000;                  // Multiplica por 10k para pegar 4 dígitos após a vírgula
                          aux = (unsigned int) offsetTOTAL;      // Pega somente o valor antes da vírgula
                          byte12 = aux;                          // byte12
                          byte11 = (aux>>8);                     // byte11
                          byte10 = (aux>>16);                    // byte10
                        
                          byte13 = sinal_offset;                 // (positivo = 1 ; negativo = 0)


                          //*********************************************************************************************
                          //  TRANSMISSÃO SERIAL (I2C) DE DADOS
                          //*********************************************************************************************
                          

                        delay(10);                            // delay 10us
  
                        Wire.beginTransmission(15);           // Começa transmissão para o mestre 0x0F
                        Wire.write(byte1);                    // Envia o byte do número antes da vírgua da variável float
                        Wire.write(byte2);                    // Em seguida envia dados bytes da mantissa ( multiplicada po 10k)
                        Wire.write(byte3);
                        Wire.write(byte4);
                      
                        Wire.write(byte5);                    // Envia o byte do número antes da vírgua da variável float
                        Wire.write(byte6);                    // Em seguida envia dados bytes da mantissa ( multiplicada po 10k)
                        Wire.write(byte7);
                        Wire.write(byte8);
                      
                        Wire.write(byte9);                    // Envia o byte do número antes da vírgua da variável float
                        Wire.write(byte10);                   // Em seguida envia dados bytes da mantissa ( multiplicada po 10k)
                        Wire.write(byte11);
                        Wire.write(byte12);
                      
                        Wire.write(byte13);                   // Envia sinal do offset
                        
                        Wire.endTransmission();               // Termina a transmissão 
                      
                        delay(1000);                          // delay 1s                            

   
    

        //********************************************
        // ZERAR VARIÁVEIS
        //********************************************


   
          digitalWrite(habilitaMaster, LOW);
          contadorSetup = 0;
          contador_aux_1 = 0;
          contador_aux_2 = 0;
          coluna_piE = 0;
          ptos_periodo = 0;
          soma_seno = 0;
          soma_cosseno = 0;
          amplitude = 0;
          fase = 0;
          cDC = 0;
          ampTOTAL = 0;
          faseTOTAL = 0;
          cDCbTOTAL = 0;
          int semicicloneg = 0;
          int semiciclopos = 0;
          byte1 = 0;
          byte2 = 0;
          byte3 = 0;
          byte4 = 0;
          aux = 0;
          variavel_float = 0;
       
} // Final do loop()
//**********************************************************************************************************************************

                    //*******INTERRUPÇÕES

                    //***************************************************
                    // Interrupção do botão de início de medição
                    //*************************************************    

void HabilitaDRDY(){
                    // Desabilita interrupção do botão de início de medição
                    detachInterrupt(digitalPinToInterrupt(buttonPin8));
                    // Habilita interrupção LeADC para  leitura de dados do AD7762
                    attachInterrupt(digitalPinToInterrupt(DRDY), leADC, FALLING);
                    }

                    //***************************************************
                    // Interrupção para  leitura de dados do AD7762
                    // Lê "Nr_de_Amostras" 
                    //*************************************************    

void leADC() {
              contadorAmostra++;                                        //  contador de amostras
                                                                        // Palavra de controle do portD para Habilitar a leitura do AD7762
              REG_PIOD_ODSR = 0x00000004;                               // CS = 0, DRDW = 0 e RESET = 1 habilita leitura
                
              vetor_Amostra[contadorAmostra] = REG_PIOC_PDSR;           // lê os 32 bits da palavra 1 (MSD) no registrador  portC
                                                                        // e armazena na matriz "vetor_Amostra"

                                                                        // Palavra de controle do portD para desabilitar CI AD7762
             REG_PIOD_ODSR = 0x00000007;                                // CS = 1, DRDW = 1 e RESET = 1 desabilita leitura
              
                                                                        // Palavra de controle do portD para Habilitar a leitura do AD7762
             REG_PIOD_ODSR = 0x00000004;                                // CS = 0, DRDW = 0 e RESET = 1 habilita leitura
   
            
             vetor_segunda_palavra[contadorAmostra] = REG_PIOC_PDSR;    // lê os 32 bits da palavra 2 (LSD) no registrador  portC
                                                                        // e armazena na matriz "vetor_segunda_palavra" 
                                                                        
                                                                        // Palavra de controle do portD para Habilitar a leitura do AD7762
            REG_PIOD_ODSR = 0x00000007;                                 // CS = 1, DRDW = 1 e RESET = 1 desabilita leitura
  
            }
