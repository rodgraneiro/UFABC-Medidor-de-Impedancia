//*****************************************************************************************
// Arquitetura para aquisição de sinais de Miografia de Impedância Elétrica
// UFABC - Universidade Federal do ABC
// Código do canal MESTRE do Medidor de Impedância
// Autor: Edson Rodrigues
// 08/03/2021
// versão 1.1 inicial
//******************************************************************************************
//********INICIALIZAÇAO*******************************************************************
const int buttonPin8 = 8;     // Número do pino do Arduino para o pushbutton
int buttonState8 = 0;         // Variável p/ armazenar status  do pushbutton

#define M_PI 3.141592653589793238462643
#define NOP() asm("nop \n")
//********************CONSTANTES E VARIÁVEIS*********************************

#include "MathHelpers.h" 
#include <Wire.h>                         // Carrega a biblioteca I2C
                                          // DISPLAY
#include <LiquidCrystal.h>                // Carrega a biblioteca LiquidCrystal
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // Define os pinos que serão utilizados para ligação ao display
                                          // AD7762 
const int CS = 25;                        // Port D0 Arduino -> Chip Select AD7762 pin 40
const int RDWR = 26;                      // Port D1 Arduino -> Read/Write AD7762 pin 39
const int RESET = 27;                     // Port D2 Arduino -> Reset AD7762 pin 37
const int DRDY = 23;                      // Port A14 Arduino -> Data Ready Output AD7762 pin 38
//const int DRDY = 14;                      // Port D4 Arduino -> Data Ready Output AD7762 pin 38
const int SYNC = 24;                      // Port A15 Arduino -> Synchronization Input AD7762 pin 36
volatile int Nr_de_Amostras = 100;
volatile uint32_t vetor_Amostra[100] = {0};
volatile uint32_t vetor_segunda_palavra[100] = {0};
volatile uint32_t sinal_negativo = 0;
volatile uint32_t semiciclo_neg = 0;
volatile uint32_t semiciclo_pos = 0;
volatile uint32_t low8 = 0;
volatile uint32_t low24 = 0;
volatile int contadorSetup = 0;
volatile int contadorAmostra = 0;
//volatile int Transmissao_OK = 0;
int contador_aux_1 = 0;
int contador_aux_2 = 0;
int contador_aux_3 = 0;
//float fator = 0.0000006;
float converte_volts[100] = {0};

int ptos_periodo = 0;
int coluna_piE = 0;
volatile float offsetTOTALchSlave = 0;
float amplitude = 0;
float ampTOTAL = 0;
volatile float ampTOTALchSlave = 0;
float impedancia_Z = 0;
float impedancia_fase = 0;
float fase = 0;
float faseTOTAL = 0;
float faseTOTALchA = 0;
//float faseAmenosB = 0;
volatile float faseTOTALchSlave = 0;
//byte sinal_offset_Slave =0;
//byte sinal_fase_Slave = 0;
//unsigned long Tempo_T =0;
//unsigned long Tempo_Inter =0;

float piEs [] = {0.117557050458495, 0.190211303259031, 0.190211303259031, 0.117557050458495, 2.44929359829470e-17, -0.117557050458495, -0.190211303259031, -0.190211303259031, -0.117557050458495, -4.89858719658942e-17};
float piEc[] = {0.161803398874990, 0.0618033988749894, -0.0618033988749895, -0.161803398874989, -0.200000000000000, -0.161803398874990, -0.0618033988749896, 0.0618033988749895, 0.161803398874990, 0.200000000000000};
float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};


float soma_seno = 0;
float soma_cosseno = 0;
float soma_offset = 0;
float offsetTOTAL = 0;

//float variavel_float;
//byte byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8, byte9, byte10, byte11, byte12, byte13, byte14;
unsigned int aux1;
unsigned int aux2;
unsigned int aux3;
int quantidade_bytes_esperados = 12;
byte canal_escravo_data[12];
byte amplitude_byte[4]; 
float amplitude_float;
byte fase_byte[4]; 
float fase_float;
byte offset_byte[4]; 
float offset_float;
float fator_conv_volts = 630e-9;
unsigned long tempo_inicio = millis();
unsigned long tempo_exec[100] = {0};

  

                                // Bus de Dados D0 à D15
const int D0 = 34;              // Port C2
const int D1 = 35;              // Port C3
const int D2 = 36;              // Port C4
const int D3 = 37;              // Port C5
const int D4 = 38;              // Port C6
const int D5 = 39;              // Port C7
const int D6 = 40;              // Port C8
const int D7 = 41;              // Port C9
                                //*************
const int D8 = 51;              // Port C12
const int D9 = 50;              // Port C13
const int D10 = 49;             // Port C14
const int D11 = 48;             // Port C15
const int D12 = 47;             // Port C16
const int D13 = 46;             // Port C17
const int D14 = 45;             // Port C18
const int D15 = 44;             // Port C19


void setup() {   //*********************INÍCIO SETUP**********************************8
    
              pinMode(buttonPin8, INPUT);     // Inicializa pino do pushbutton como input:
              Serial.begin(115200);
              Wire.begin(15);                 // Endereço canalSlave
              Wire.onReceive(receiveEvent);   // register event
              
              
              //***************inicia LCD 
              lcd.begin(16, 2);                 // Define o número de colunas e linhas do LCD
              lcd.clear();                      // Limpa a tela
              lcd.setCursor(1, 0);              // Posiciona o cursor na coluna 1, linha 0;
              lcd.print("MIE-EBM-UFABC");       // Envia o texto entre aspas para o LCD
              lcd.setCursor(1, 1);              // Posiciona o cursor na coluna 1, linha 0;
              lcd.print("Pressione bot 1");     // Envia o texto entre aspas para o LCD
              
                                              // Configuração de Ports para iniciar AD7762  
              pinMode(CS, OUTPUT);               // Port D0 do Arduino Due
              pinMode(RDWR, OUTPUT);             // Port D1 do Arduino Due
              pinMode(RESET, OUTPUT);            // Port D2 do Arduino Due
              pinMode(SYNC, OUTPUT);             // Port A15 do Arduino Due
              pinMode(DRDY, INPUT);              // Port A14 do Arduino Due
              
              digitalWrite(RESET, HIGH);
              digitalWrite(CS, HIGH);
              digitalWrite(RDWR, HIGH);
              digitalWrite(SYNC, HIGH);
           
                                              // Configuração de Bus de dados comos saída  
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
        
              //  ********************* RESET inicial      **************************
              digitalWrite(RESET, LOW);     // reset low 
              delay(100);
              digitalWrite(RESET, HIGH);    // reset high
              delay(100);
              //************************************************
  
  for (contadorSetup = 0; contadorSetup < 100; contadorSetup++) {  // Laço setup
  
              // Envia Endereço Registrador2 p/ Bus de Dados**************************
              digitalWrite(D0, LOW);      //Endereço Registrador 2  0x0002
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
              //*****************************************************
              
              
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
              
              digitalWrite(D0, LOW);    //DIPD
              digitalWrite(D1, HIGH);   // "1"
              digitalWrite(D2, LOW);    //LPWR
              digitalWrite(D3, LOW);    //PD
              digitalWrite(D4, HIGH);   // Default 9B
              digitalWrite(D5, HIGH);    //CDIV
              digitalWrite(D6, LOW);    //Default 9B
              digitalWrite(D7, HIGH);   //Default 9B
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
               digitalWrite(CS, LOW);  // Habilita Chip Select do AD7762 para escrita
               digitalWrite(CS, HIGH); // desabilita Chip Select do AD7762 
              //*********************************************************
          
          
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
              
               delay(10);
              
              digitalWrite(CS, LOW);      // Habilita Chip Select do AD7762 para escrita
              digitalWrite(CS, HIGH);
             
              //***********************************************************


              //***********************************************
              // ESCREVE WORD REG 1 0X001D
              // DEC2, DEC1, DEC0 = 0X4 PARA DECIMACAO 16X
              digitalWrite(D0, HIGH);      // DEC0 = 1 
              digitalWrite(D1, LOW);     // DEC1 = 0 
              digitalWrite(D2, LOW);      // DEC2 = 1
              digitalWrite(D3, HIGH);     // tem que ser 1 (high)
              digitalWrite(D4, HIGH);     // BYP F3
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
              
              delay(10);
              digitalWrite(CS, LOW);  // Habilita Chip Select do AD7762 para escrita
              digitalWrite(CS, HIGH); // desabilita Chip Select do AD7762  
  } // Final laço setup

              delay(100);
              
              //****************************
              //Prepara PORTC como INPUT
              //****************************
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
              
              delay(500);
              contadorAmostra = 0;
          
          
              //************ Envia sinal de sincronismo SYNC ******************* 
              digitalWrite(SYNC, LOW);
              delay(500);
              digitalWrite(SYNC, HIGH);
              delay(100);





              
    }         //**********************FINAL de void setup() ****************************
    
              //******************************************************************************
              //***************************** INÍCIO void loop() *****************************
              //******************************************************************************

void loop() {
              
              //**** Habilita interrupção do botão que dispara a Medição das N_amostras
              attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING);     // Habilita interrupção do botão de início de medição
                                                                                            // e vai para interrupção LeAdc              
              // Realiza a leitura das Nr_de_Amostras enquanto a interrupção "HabilitaDRDY" estiver habilitada
              while(contadorAmostra < Nr_de_Amostras){                                 
                                                     }
                contador_aux_1 = 0;
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
     

  for(contador_aux_1 = 0; contador_aux_1 < Nr_de_Amostras; contador_aux_1++) { // Laço rearranjo dos 32 bits NÃO CONSECUTIVOS
  
              //*******************************************************************
              // Primeira palavra com os 16 bits mais significativos (de 23 à 8)
              //*******************************************************************
              
              // Zerar bits "0" , "1" e bits de "20" à "31" aplicando a operação lógica "AND" 
              // por meio da máscara 0x000ffffc
              
               vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] & 0xffffc;  // clear top 11 and bottom 2 bits with mask
               vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] >> 2;       // Desloca dois bits p direita para elininar bits "0" e "1"
              
               // separa os 8 bits menos significaticos da primrira palavra
               low8 = vetor_Amostra[contador_aux_1] & 0x000000ff;                               //mask and save lower 8 bits
              
               // Remove os bits "10 e 11" (Lixo do meio da primeira palavra) deslocando 10 bits para direita
               vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] >> 10;
              
               // Rearranjar os 16 bits da primeira palavra
               // Deslocando 8 bits à esquerda e aplicando a operação lógica "OU" com os
               // 8 bits menos significativos da primeira palavra armazenados na variável low8
                      
               vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] << 8 | low8;
              
               //****************************************************************** 
               // Segunda palavra com os 8 bits menos significativos (de 7 à 0)
               //******************************************************************
              
                // Zera bits de "0 à 11" e bits de "20" à "31" aplicando a operação lógica "AND" 
                // por meio da máscara 0x000ff000  
            
                 low24 = vetor_segunda_palavra[contador_aux_1] & 0xff000;
                
                 // Desloca 12 bits à direita separando os 8 bits menos significaticos da palavra de 24 bits
                 low24  =  low24 >> 12;
                 low24  =  low24 & 0x000000ff;
                
                 // Rearranjar a amostra discretizada com resolução de 24 bits
                 // deslocando os 8 bits da primeira palavra à esquerda e 
                 // aplicando a operação lógica "OU" com os 8 bits menos significativos
                 // da segunda palavra armazenados na variavel low24
                 
                 vetor_Amostra[contador_aux_1] = vetor_Amostra[contador_aux_1] << 8 | low24; // Amostra discretizada com 24 bits;
                  
  } //Final Laço rearranjo dos 32 bits NÃO CONSECUTIVOS
                  contador_aux_1 = 0;
              
                //********************************************************************* 
                // Verificação de sinal positivo/negativo no bit 23 e complemento de 2
                // conversão para tensão em volts
                //*********************************************************************



  for(contador_aux_2 = 0; contador_aux_2 <= Nr_de_Amostras - 1; contador_aux_2++){ // Laço verificação sinal da amostra em complemento de 2

                // O bit 23 indentifica o sinal da amostra: "1" para negativo e "0" para positivo.
                
                // Verifica estado do bit 23 aplicando a operação lógica "AND" por meio da máscara 0x800000.
                sinal_negativo = vetor_Amostra[contador_aux_2] & 0x00800000;
                
                // Se estado do bit 23 igual a "1", aplicar operação lógica de "complemento de 2" e multiplicar por (-1).
                // Em seguida multiplicar pelo fator de conversão para volts
                if(sinal_negativo == 0x800000){ 
                  semiciclo_neg  = ((~vetor_Amostra[contador_aux_2] + 0x1)) & 0xffffff;       // lê amostra e aplica operação "complemento de 2"
                  converte_volts[contador_aux_2] = -(semiciclo_neg*fator_conv_volts);         // converte para volts e multiplicar por -1
                  //Serial.println(sci(converte_volts[contador_aux_2],4));                      // Envia para o Monitor Serial
                }
                // Se estado do bit 23 igual a "0", aplicar fator de conversão para volts   
                else{
                  semiciclo_pos = vetor_Amostra[contador_aux_2];                              // lê amostra
                  converte_volts[contador_aux_2] = (semiciclo_pos*fator_conv_volts);          // converte pata volts
                  //Serial.println(sci(converte_volts[contador_aux_2],4));                      // Envia para o Monitor Serial            
                }
  } // Final do Laço verificação sinal da amostra em complemento de 2 

              contador_aux_2 = 0;
              Serial.println("Valor convertido X valor decimal");                                    // imprime amostras p debug
    for(contador_aux_2 = 0; contador_aux_2 <= Nr_de_Amostras - 1; contador_aux_2++){                 // imprime amostras p debug
              Serial.print(tempo_exec[contador_aux_2]);
              Serial.print("  ;  ");   
              Serial.print(sci(converte_volts[contador_aux_2],4));
              Serial.print("  ;  ");
              Serial.print(vetor_Amostra[contador_aux_2]);
              Serial.print("  ;  ");
              Serial.println(vetor_Amostra[contador_aux_2], BIN);
    }



  
                        



                //**********************************************************
                //          DEMODULAÇÃO PO QUADRATURA
                //**********************************************************
                
                // Determinar Amplitude, fase e offset. Serão utilizados os três últimos períodos
                // para evitar transientes do início da medição;
                          
  for(contador_aux_3 = 60; contador_aux_3 < 90; contador_aux_3 = (contador_aux_3 + 10)){ // Laço Matriz pseudo inversa
            for (coluna_piE = 0; coluna_piE < 10; coluna_piE++) {
                ptos_periodo = contador_aux_3 + coluna_piE;
                // Multiplica a matriz do sinal convertido pela matriz pseudo inversa piE
                soma_seno += (float)converte_volts[ptos_periodo]*(float)piEs[coluna_piE]; 
                soma_cosseno += (float)converte_volts[ptos_periodo]*(float)piEc[coluna_piE];
                soma_offset += (float)converte_volts[ptos_periodo]*(float)piEdc[coluna_piE];
             }
                amplitude = 2*sqrt(sq(soma_seno)+sq(soma_cosseno))/2;    // Cálculo da amplitude
                fase = atan2(soma_cosseno , soma_seno)*(180/M_PI);       // Cálculo da fase
                Serial.print("amplitude e fase DC");
                Serial.print("  ;  ");
                Serial.print(sci(amplitude,4));
                Serial.print("  ;  ");
                Serial.print(sci(fase,4));
                Serial.print("  ;  ");
                Serial.println(sci(soma_offset,4));
                ampTOTAL = ampTOTAL + amplitude;
                faseTOTAL = faseTOTAL + fase;
                offsetTOTAL =  offsetTOTAL + soma_offset;
                coluna_piE = 0;
                amplitude = 0;
                soma_seno = 0; 
                soma_cosseno = 0;
                soma_offset = 0;
                fase = 0;
  } // Final Laço Matriz pseudo inversa
                                                
              //********************************************  
              // Calcular média da ampltude, fase e offsset
              //*******************************************
              
              ampTOTAL =ampTOTAL/3;             // Média da amplitude
              faseTOTAL = faseTOTAL/3;          // Média da fase
              offsetTOTAL = offsetTOTAL/3;      // média do Offset
              faseTOTALchA = faseTOTAL;

              // Para debug

 
              Serial.print("amplitude - fase - TOTAL ");
              Serial.print("  ;  ");
              Serial.print(sci(ampTOTAL,4));
              Serial.print("  ;  ");
              Serial.print(sci(faseTOTAL,4));
              Serial.print("  ;  ");
              Serial.println(sci(offsetTOTAL,4));
              
              delay(2000);
              contadorAmostra = 0;
              contador_aux_1 = 0;
              contador_aux_2;
              contador_aux_3 = 0;
              coluna_piE = 0;
              soma_seno = 0;
              soma_cosseno = 0;
              soma_offset = 0;
              amplitude = 0;
              fase =0;
              faseTOTAL = 0;
              offsetTOTAL = 0;           
              //*****************************************************************************************
              
              delay(200);

              //***************************
              Serial.println("Variaveis recebidas do canal ESCRAVO:");
              Serial.print("amplitude - fase - offset ");
              Serial.print("  ;  ");
              Serial.print(sci(ampTOTALchSlave,4));
              Serial.print("  ;  ");
              Serial.print(sci(faseTOTALchSlave,4));
              Serial.print("  ;  ");
              Serial.println(sci(offsetTOTALchSlave,4));
              
              // Cálculo da impedância e ângulo theta              
              impedancia_Z = ampTOTAL / ampTOTALchSlave;             // Cálculo da impedância
              impedancia_fase = faseTOTALchA - faseTOTALchSlave;     // Cálculo do ângulo theta
        

              // ************ DISPLAY **********************************
              //Envia os dados calculados para o display
              
              lcd.begin(16, 2);             // Define o número de colunas e linhas do LCD
              lcd.clear();                  // Limpa a tela
              lcd.setCursor(0, 0);          // Posiciona o cursor na coluna 0, linha 0;
              lcd.print("Z =");             // Escrever "Z =" no display
              lcd.setCursor(4, 0);          // Posiciona o cursor na coluna 4, linha 0;
              lcd.print(impedancia_Z,4);    // Escrever valor da Impedância "X.XXXX"
              lcd.setCursor(15, 0);         // Posiciona o cursor na coluna 15, linha 1;
              lcd.write(B11110100);         // ômega
              lcd.setCursor(0, 1);          // Posiciona o cursor na coluna 0, linha 1;
              lcd.write(B11110010);         // theta
              lcd.setCursor(1, 1);          // Posiciona o cursor na coluna 1, linha 1;
              lcd.print(" =");              // Escrever " =" no display
              lcd.setCursor(4, 1);          // Posiciona o cursor na coluna 4, linha 1;
              lcd.print(impedancia_fase,2); // Escrever valor da fase "XX.X"
              lcd.setCursor(15, 1);         // Posiciona o cursor na coluna 15, linha 1;
              lcd.write(B11011111);          // graus
  
  
              Serial.print(" IMPEDANCIA - FASE ");
              Serial.print("  ;  ");
              Serial.print(sci(impedancia_Z,4));
              Serial.print("  ;  ");
              Serial.println(sci(impedancia_fase,4));


              ampTOTAL = 0;
              ampTOTALchSlave = 0;
              faseTOTALchA =0;
              faseTOTALchSlave = 0;
              offsetTOTAL = 0;
              offsetTOTALchSlave = 0;
              //sinal_fase_Slave = 0;
                      
    
}
//**********************************************************************************************************************************

            //*******INTERRUPÇÕES

            //***************************************************
            // Interrupção do botão de início de medição
            //*************************************************   

void HabilitaDRDY(){
            //long i = 0;
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
    detachInterrupt(digitalPinToInterrupt(DRDY));
    long i = 0;
        for(i = 0; i <= 21; i++){                                                   // Delay para calibração dosoncronismos
            asm("nop \n");
        }
        while(contadorAmostra < Nr_de_Amostras){ 
            REG_PIOD_ODSR = 0x00000004;                                             // CS = 0, DRDW = 0 e RSET = 1 habilita leitura         
            vetor_Amostra[contadorAmostra] = REG_PIOC_PDSR;                         // lê os 32 bits da palavra 1 (MSD) no registrador  portC
                                                                                    // e armazena na matriz "vetor_Amostra"
                                                                                    // Palavra de controle do portD para desabilitar CI AD7762
            REG_PIOD_ODSR = 0x00000007;                                             // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura
            NOP();
            NOP();
            NOP();
            REG_PIOD_ODSR = 0x00000004;                                             // CS = 0, DRDW = 0 e RSET = 1 habilita leitur             
            vetor_segunda_palavra[contadorAmostra] = REG_PIOC_PDSR;                 // lê os 32 bits da palavra 2 (LSD) no registrador  portC
                                                                                    // e armazena na matriz "vetor_segunda_palavra" 
                                                                                    // Palavra de controle do portD para Habilitar a leitura do AD7762
            REG_PIOD_ODSR = 0x00000007;                                             // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura              
            contadorAmostra++;                                                      //  contador de amostras                                                      
                for(i = 0; i <= 10; i++){                                           // Delay para calibração dosoncronismos
                    asm("nop \n");
                }         
        }
        attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING); 
}             




void receiveEvent(int quantidade_bytes_esperados) { 

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

             
            union Nr_IEEE754_union {byte as_byte[4]; float as_float;} amplitude_union;  //Nr float formato IEEE754 de 32 |Sinal|Expoente|Mantissa| 
             amplitude_union.as_byte[0] = canal_escravo_data[0];
             amplitude_union.as_byte[1] = canal_escravo_data[1];
             amplitude_union.as_byte[2] = canal_escravo_data[2];
             amplitude_union.as_byte[3] = canal_escravo_data[3];   
             float AMPLITUDE = amplitude_union.as_float  ;
             ampTOTALchSlave = AMPLITUDE;
           
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
             
}
