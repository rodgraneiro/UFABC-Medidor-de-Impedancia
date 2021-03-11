//*****************************************************************************************
// Arquitetura para aquisição de sinais de Miografia de Impedância Elétrica
// UFABC - Universidade Federal do ABC
// Código do canal MESTRE do Medidor de Impedância
// Autor: Edson Rodrigues
// 08/03/2021
// versão 1.1 inicial
//******************************************************************************************
//********INICIALIZAÇAO*******************************************************************
const int buttonPin8 = 8;     // the number of the pushbutton pin
int buttonState8 = 0;         // variable for reading the pushbutton status

#define M_PI 3.141592653589793238462643
#define NOP() asm("nop \n")
//********************CONSTANTES E VARIÁVEIS*********************************

#include "MathHelpers.h" 
#include <Wire.h>
const int CS = 25;    // Port D0 Arduino -> Chip Select AD7762 pin 40
const int RDWR = 26;  // Port D1 Arduino -> Read/Write AD7762 pin 39
const int RESET = 27; // Port D2 Arduino -> Reset AD7762 pin 37
const int DRDY = 23;  // Port A14 Arduino -> Data Ready Output AD7762 pin 38
const int SYNC = 24;  // Port A15 Arduino -> Synchronization Input AD7762 pin 36
volatile int Nr_de_Amostras = 100;
volatile uint32_t vetor_Amostra[100];
volatile uint32_t vetor_segunda_palavra[100];
volatile uint32_t neg;
volatile int contadorAmostra = 0;
volatile int j = 0;
volatile int k = 0;
float fator = 0.0000006;
float volts[100];

int s = 0;
float cDC = 0;
float cDCb = 0;
float cDCTOTAL = 0;
float cDCbTOTAL = 0;
float cDCbTOTALchB = 0;
float amplitude = 0;
float ampTOTAL = 0;
float ampTOTALchB = 0;
float fase = 0;
float faseTOTAL = 0;
float faseTOTALchA = 0;
float faseAmenosB = 0;
float faseTOTALchB = 0;
byte sinalcDCchB =0;
unsigned long Tempo_T =0;
unsigned long Tempo_Inter =0;

//float piEs [] = {0.000000, 0.117557, 0.190211, 0.1902117, 0.117557, 1.1331e-16, -0.117557, -0.190211, -0.1902117, -0.117557};
//float piEc[] = {0.2, 0.161803, 0.06180, -0.06180, -0.161803, -0.20000, -0.161803, -0.06180, 0.06180, 0.161803};
//float piEdc[] = {0.1000000, 0.100000, 0.1000000, 0.1000000, 0.1000000, 0.1000000, 0.1000000, 0.1000000, 0.1000000, 0.1000000};
float piEs [] = {0.117557050458495, 0.190211303259031, 0.190211303259031, 0.117557050458495, 2.44929359829470e-17, -0.117557050458495, -0.190211303259031, -0.190211303259031, -0.117557050458495, -4.89858719658942e-17};
float piEc[] = {0.161803398874990, 0.0618033988749894, -0.0618033988749895, -0.161803398874989, -0.200000000000000, -0.161803398874990, -0.0618033988749896, 0.0618033988749895, 0.161803398874990, 0.200000000000000};
float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};


float seno = 0;
float cosseno = 0;

  float variavel_float;
  byte byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8, byte9, byte10, byte11, byte12, byte13;
  unsigned int aux1;
  unsigned int aux2;
  unsigned int aux3;
  int quantidade_bytes_esperados = 13;

  


const int D0 = 34; //Port C2
const int D1 = 35; // C3
const int D2 = 36; // C4
const int D3 = 37; // C5
const int D4 = 38; // C6
const int D5 = 39; // C7
const int D6 = 40; // C8
const int D7 = 41; // C9
//*************
const int D8 = 51; // C12
const int D9 = 50; // C13
const int D10 = 49; // C14
const int D11 = 48; // C15
const int D12 = 47; // C16
const int D13 = 46; // C17
const int D14 = 45; // C18
const int D15 = 44; // C19

//DISPLAY

#include <LiquidCrystal.h> //Carrega a biblioteca LiquidCrystal
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Define os pinos que serão utilizados para ligação ao display 

void setup() {   //*********************INÍCIO SETUP**********************************8
    
              pinMode(buttonPin8, INPUT);// initialize the pushbutton pin as an input:
              digitalWrite(LED_BUILTIN, LOW); // initialize the LED pin as an output:
              Serial.begin(115200);
              Wire.begin(15);
              Wire.onReceive(receiveEvent); // register event
           
              
// inicia LCD 
    lcd.begin(16, 2); //Define o número de colunas e linhas do LCD
    lcd.clear(); //Limpa a tela
    lcd.setCursor(1, 0);  //Posiciona o cursor na coluna 1, linha 0;
    lcd.print("MIE-EBM-UFABC"); //Envia o texto entre aspas para o LCD
    lcd.setCursor(1, 1);  //Posiciona o cursor na coluna 1, linha 0;
    lcd.print("Pressione bot 1"); //Envia o texto entre aspas para o LCD
    //lcd.setCursor(1, 1);  //Posiciona o cursor na coluna 1, linha 1;
    //lcd.print("A="); 
    //lcd.setCursor(3, 1); //Posiciona o cursor na coluna 7, linha 1;
    //lcd.print(ampTOTAL);
    //lcd.setCursor(7, 8); //Posiciona o cursor na coluna 7, linha 1;
    //lcd.print("F=");
    //lcd.setCursor(7, 10); //Posiciona o cursor na coluna 7, linha 1;
    //lcd.print("F=");  
 
 //inicia AD7763 
   pinMode(CS, OUTPUT); // D0
   pinMode(RDWR, OUTPUT); //D1
   pinMode(RESET, OUTPUT); //D2
   pinMode(SYNC, OUTPUT); //A15
   //REG_PIOD_OWER = 0x00000007; 
   //REG_PIOD_OWDR = 0xfffffffc; 
   pinMode(DRDY, INPUT);
    
   digitalWrite(RESET, HIGH);
   digitalWrite(CS, HIGH);
   digitalWrite(RDWR, HIGH);
   digitalWrite(SYNC, HIGH);
  
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
  

  for (int i = 0; i < 100; i++) {  
  
// END reg 2 ******************************************
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
  // REG_PIOC_ODSR = 0x00000008; // END reg 2 
  //*****************************************************
  

    //******************************************
  // ESCREVE END REG 2
  //digitalWrite(CS, HIGH);// escreve word reg 2 0x0002
  delay(10);
  digitalWrite(CS, LOW);
  //delay(1);
  digitalWrite(CS, HIGH);
   //delay(100);
  
  //ESCREVE WORD REG 2: COMO EH IGUAL AO END EH SO HABILITAR CS 
  // set CDIV = 0 metade MCLk
  // set DIPD = 0 habilita Dif Amp
  // set PD = 0 habilita CI (Power ON)
  // set LPWR = 0 seta power no modo normal
  // 0x0002 Obs.: mesma word do registrador
  
        
         // REG_PIOC_ODSR = 0x00000148;  //ESCREVE WORD REG 2 
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

  delay(10);
  digitalWrite(CS, LOW);
  //delay(1);
  digitalWrite(CS, HIGH);
   //delay(100);
  
    // REG_PIOC_ODSR = 0x00000000;  //ESCREVE WORD REG 2 
//*********************************************************


// ESCREVE END REG 1 0X0001
// 
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
  //delay(1);
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
  
  delay(500);
  contadorAmostra = 0;
  //attachInterrupt(digitalPinToInterrupt(DRDY), leADC, FALLING);
  //**********************FINAL SETUP****************************

   digitalWrite(SYNC, LOW);
   delay(500);
   digitalWrite(SYNC, HIGH);
   delay(100);
   
}


void loop() {

main:

  attachInterrupt(digitalPinToInterrupt(buttonPin8), HabilitaDRDY, RISING);
  //buttonState8 = digitalRead(buttonPin8); // read the state of the pushbutton value:
 
         // if (buttonState8 == HIGH) {  
                   
                                  //  } 
          // else {               attachInterrupt(digitalPinToInterrupt(DRDY), leADC, FALLING);
                                    //goto inicio;
                 //detachInterrupt(digitalPinToInterrupt(DRDY));
                 //goto main;
                //}

 inicio:    // Realiza a leitura das Nr_de_Amostras enquanto a interrupção "HabilitaDRDY" estiver habilitada
            while(contadorAmostra < Nr_de_Amostras){
                                                    NOP();
                                                    }
            //*** Desabilita interrupção p/ aquisição de amostras   
            detachInterrupt(digitalPinToInterrupt(DRDY));

    for(j = 0; j <= Nr_de_Amostras; j++) {
                             vetor_Amostra[j] = vetor_Amostra[j] & 0xffffc;  //clear top 11 and bottom 2 bits with mask
                             vetor_Amostra[j] = vetor_Amostra[j] >> 2;       //shift away the lower 2 cleared bits
                                //remove the two junk bits from center of data
                             int lo8 = vetor_Amostra[j] & 0xff;               //mask and save lower 8 bits
                             vetor_Amostra[j] = vetor_Amostra[j] >> 10;       //shift away the lower 10 bits to clear middle two
                             vetor_Amostra[j] = vetor_Amostra[j] << 8 | lo8;  //reassemble continuous 16 bits

                             int lo24 = vetor_segunda_palavra[j] & 0xff000;
                             lo24  =  lo24 >> 12;
                             vetor_Amostra[j] = vetor_Amostra[j] << 8 | lo24; //reassemble continuous 16 bits     
                             } 

   for(k = 0; k < Nr_de_Amostras; k++){
    
                          neg = vetor_Amostra[k] & 0x800000;
                              if(neg == 0x800000){ 
                                                  int semicicloneg  = ((~vetor_Amostra[k] + 0x1)) & 0xffffff;
                                                  volts[k] = -(semicicloneg*630e-9);
                                                  Serial.println(sci(volts[k],4));
    
                                                  }
                             else{
                                  int semiciclopos = vetor_Amostra[k]; // * fator;
                                  volts[k] = (semiciclopos*630e-9);
                                  Serial.println(sci(volts[k],4));
  
                                 }
                         }

 for(k=60; k<90; k=k + 10){ 
                          for (s = 0; s < 10; s++) {
                                                    int m = k + s;
                                                    seno += (float)volts[m]*(float)piEs[s]; 
                                                    cosseno += (float)volts[m]*(float)piEc[s];
                                                    cDCb += (float)volts[m]*(float)piEdc[s];
                                                   }
                           amplitude = 2*sqrt(sq(seno)+sq(cosseno))/2;
                           fase = atan2(cosseno , seno)*(180/M_PI);;
                           Serial.print("amplitude e fase DC");
                           Serial.print("  ;  ");
                           Serial.print(sci(amplitude,4));
                           Serial.print("  ;  ");
                           Serial.print(sci(fase,4));
                           Serial.print("  ;  ");
                           Serial.println(sci(cDCb,4));
                           ampTOTAL = ampTOTAL + amplitude;
                           faseTOTAL = faseTOTAL + fase;
                           cDCbTOTAL =  cDCbTOTAL + cDCb;
                           s=0;
                           amplitude=0;
                           seno =0; 
                           cosseno=0;
                           cDCb=0;
                           fase = 0;
                          }


ampTOTAL =ampTOTAL/3;
faseTOTAL = faseTOTAL/3;
if (faseTOTAL < 0) {  // verifica se o ângulo é negatifo
                                     faseTOTAL = 2*M_PI - faseTOTAL; // sutrai pi()
                                     } 
cDCbTOTAL = cDCbTOTAL/3;

//Wire.onReceive(receiveEvent);

 
Serial.print("amplitude - fase - TOTAL ");
Serial.print("  ;  ");
Serial.print(sci(ampTOTAL,4));
Serial.print("  ;  ");
Serial.print(sci(faseTOTAL,4));
Serial.print("  ;  ");
Serial.println(sci(cDCbTOTAL,4));
//Serial.println(Tempo_Inter);
//Tempo_T = 0;
//Tempo_Inter = 0;

//  lcd.setCursor(7, 1);
//lcd.print(ampTOTAL); //lcd.print(valor da amplitude);
   lcd.begin(16, 2); //Define o número de colunas e linhas do LCD
   lcd.clear(); //Limpa a tela
   lcd.setCursor(1, 0);  //Posiciona o cursor na coluna 1, linha 1;
    lcd.print("Z="); 
    lcd.setCursor(3, 0); //Posiciona o cursor na coluna 7, linha 1;
    lcd.print(ampTOTAL,4);
    lcd.setCursor(1, 1); //Posiciona o cursor na coluna 7, linha 1;
    lcd.print("F=");
    lcd.setCursor(3, 1); //Posiciona o cursor na coluna 7, linha 1;
    lcd.print(faseTOTAL); 
  //Serial.println(volts[0]);
  //Serial.println(volts[999]);
  //Serial.println(piEc[0]);
    delay(2000);

    //faseTOTALchA = faseTOTAL;
    
    contadorAmostra = 0;
    j=0;
    k=0;
    s=0;
    int m=0;
    seno = 0;
    cosseno = 0;
    amplitude = 0;
    fase =0;
    cDCb =0;
    ampTOTAL = 0;
    faseTOTAL = 0;
    cDCbTOTAL = 0;
    int semicicloneg =0;
    int semiciclopos = 0;
    //attachInterrupt(digitalPinToInterrupt(DRDY), leADC, FALLING);

}
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
               contadorAmostra++;                                       //  contador de amostras
                                                                        // Palavra de controle do portD para Habilitar a leitura do AD7762
               REG_PIOD_ODSR = 0x00000004;                              // CS = 0, DRDW = 0 e RSET = 1 habilita leitura
               
               vetor_Amostra[contadorAmostra] = REG_PIOC_PDSR;          // lê os 32 bits da palavra 1 (MSD) no registrador  portC
                                                                        // e armazena na matriz "vetor_Amostra"

                                                                        // Palavra de controle do portD para desabilitar CI AD7762
               REG_PIOD_ODSR = 0x00000007;                              // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura

                                                                        // Palavra de controle do portD para Habilitar a leitura do AD7762
               REG_PIOD_ODSR = 0x00000004;                              // CS = 0, DRDW = 0 e RSET = 1 habilita leitura
               
               vetor_segunda_palavra[contadorAmostra] = REG_PIOC_PDSR;  // lê os 32 bits da palavra 2 (LSD) no registrador  portC
                                                                        // e armazena na matriz "vetor_segunda_palavra" 
               
                                                                        // Palavra de controle do portD para Habilitar a leitura do AD7762
                REG_PIOD_ODSR = 0x00000007;                             // CS = 1, DRDW = 1 e RSET = 1 desabilita leitura
                 
              }


/*void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int NrMed = Wire.read();    // receive byte as an integer
  Serial.println(NrMed);         // print the integer
}*/

void receiveEvent(int quantidade_bytes_esperados) { // Está código é executado quando "quantidade_bytes_esperados" foi recebido via I2C
    byte1 = Wire.read();                            // Lê os 4 bytes enviados pelo mestre 
    byte2 = Wire.read(); 
    byte3 = Wire.read(); 
    byte4 = Wire.read(); 


    byte5 = Wire.read();                            // Lê os 4 bytes enviados pelo mestre 
    byte6 = Wire.read(); 
    byte7 = Wire.read(); 
    byte8 = Wire.read(); 

    byte9 = Wire.read();                            // Lê os 4 bytes enviados pelo mestre 
    byte10 = Wire.read(); 
    byte11 = Wire.read(); 
    byte12 = Wire.read();

    byte13 = Wire.read();

     


    // Ajustando os bytes recebidos para obetr a variavel_float
    aux1 = (byte2<<16) | (byte3<<8) | byte4;        // Ajusta a parte fracionáia (depois da vírgula)
    ampTOTALchB = (float) (aux1*0.000001);          // Atribui a parte fracionária, depois da vírgula 
    aux1 = byte1; 
    ampTOTALchB += aux1; // Atribui a parte iteira

    aux2 = (byte6<<16) | (byte7<<8) | byte8;        // Ajusta a parte fracionáia (depois da vírgula)
    faseTOTALchB = (float) (aux2*0.000001);          // Atribui a parte fracionária, depois da vírgula 
    aux2 = byte5; 
    faseTOTALchB += aux2; // Atribui a parte inteira

    aux3 = (byte10<<16) | (byte11<<8) | byte12;        // Ajusta a parte fracionáia (depois da vírgula)
    cDCbTOTALchB = (float) (aux3*0.000001);          // Atribui a parte fracionária, depois da vírgula 
    aux3 = byte9; 
    cDCbTOTALchB += aux3; // Atribui a parte inteira

    sinalcDCchB = byte13;

    if (sinalcDCchB == 0) {  // verifica se o ângulo é negatifo
                                     cDCbTOTALchB = cDCbTOTALchB * (-1); // subtrai pi()
                                     } 



 //faseAmenosB =  faseTOTALchA  - faseTOTALchB;
    Serial.println("Variavel recebida do canal B:");
    //Serial.println(variavel_float, DEC);

    Serial.print("amplitude - fase - TOTAL ");
    
Serial.print("  ;  ");
Serial.print(sci(ampTOTALchB,4));
Serial.print("  ;  ");
Serial.print(sci(faseTOTALchB,4));
Serial.print("  ;  ");
Serial.println(sci(cDCbTOTALchB,4));
//Serial.println(sci(faseTOTALchA,4));
//Serial.println(sci(faseAmenosB,4));
//Serial.println(byte1));
//Serial.println(sci(byte2,8));
//Serial.println(sci(byte3,8));
//Serial.println(sci(byte4,8));
//Serial.println(sci(byte5,8));
//Serial.println(sci(byte6,8));
//Serial.println(sci(byte7,8));
//Serial.println(sci(byte8,8));
//Serial.println(sci(byte9,8));
//Serial.println(sci(byte10,8));
//Serial.println(sci(byte11,8));
//Serial.println(sci(byte12,8));
//Serial.println(sci(byte13,8));
//Serial.println(Tempo_Inter);
//Tempo_T = 0;

faseTOTALchA =0;
      
}
