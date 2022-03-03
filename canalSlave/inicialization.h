#include "defConstVariaveis.h"


void busColtrolIni(const int CS, const int RDWR, const int RESET, const int DRDY, const int buttonPin8, const int habilitaMaster){
// Configuração de Ports para iniciar AD7762 
          pinMode(CS, OUTPUT);                // Port D0 do Arduino Due
          pinMode(RDWR, OUTPUT);              // Port D1
          pinMode(RESET, OUTPUT);             // Port D2
          pinMode(DRDY, INPUT);               // Port A14 do Arduino Due

          pinMode(buttonPin8, INPUT_PULLUP);  // initialize the pushbutton pin as an input:
          pinMode(habilitaMaster, OUTPUT);    // initialize the pushbutton pin as an input:
          delay(10);                          // espera estabilização da porta
          digitalWrite(habilitaMaster, LOW);  // habilita Master:
}

void delayFunc(int temp){
          delay(temp);
}

void busOutputADC(int D0, int D1, int D2, int D3, int D4, int D5, int D6, int D7, int D8, int D9, int D10, int D11, int D12, int D13, int D14, int D15){
          delay(10);
                                              // Configura bus de dados como output   (Bus de Dados D0 à D15) 
          pinMode(D0, OUTPUT);                //D0 pino 34 Port C2 Arduino DUE
          pinMode(D1, OUTPUT);                //D1 pino 35; //Port C3
          pinMode(D2, OUTPUT);                //D2 pino 36; //Port C4
          pinMode(D3, OUTPUT);                //D3 pino 37; //Port C5
          pinMode(D4, OUTPUT);                //D4 pino 38; //Port C6
          pinMode(D5, OUTPUT);                //D5 pino 39; //Port C7
          pinMode(D6, OUTPUT);                //D6 pino 40; //Port C8
          pinMode(D7, OUTPUT);                //D7 pino 41; //Port C9
          pinMode(D8, OUTPUT);                //D8 pino 51; //Port C12
          pinMode(D9, OUTPUT);                //D9 pino 50; //Port C13
          pinMode(D10, OUTPUT);               //D10 pino 49; //Port C14
          pinMode(D11, OUTPUT);               //D11 pino 48; //Port C15
          pinMode(D12, OUTPUT);               //D12 pino 47; //Port C16
          pinMode(D13, OUTPUT);               //D13 pino 46; //Port C17
          pinMode(D14, OUTPUT);               //D14 pino 45; //Port C18
          pinMode(D15, OUTPUT);               //D15 pino44; //Port  C19

          //delay(100);
}

void busInputADC(int D0, int D1, int D2, int D3, int D4, int D5, int D6, int D7, int D8, int D9, int D10, int D11, int D12, int D13, int D14, int D15){
          delay(10);
                                              // Configura bus de dados como output   (Bus de Dados D0 à D15) 
          pinMode(D0, INPUT);                //D0 pino 34 Port C2 Arduino DUE
          pinMode(D1, INPUT);                //D1 pino 35; //Port C3
          pinMode(D2, INPUT);                //D2 pino 36; //Port C4
          pinMode(D3, INPUT);                //D3 pino 37; //Port C5
          pinMode(D4, INPUT);                //D4 pino 38; //Port C6
          pinMode(D5, INPUT);                //D5 pino 39; //Port C7
          pinMode(D6, INPUT);                //D6 pino 40; //Port C8
          pinMode(D7, INPUT);                //D7 pino 41; //Port C9
          pinMode(D8, INPUT);                //D8 pino 51; //Port C12
          pinMode(D9, INPUT);                //D9 pino 50; //Port C13
          pinMode(D10, INPUT);               //D10 pino 49; //Port C14
          pinMode(D11, INPUT);               //D11 pino 48; //Port C15
          pinMode(D12, INPUT);               //D12 pino 47; //Port C16
          pinMode(D13, INPUT);               //D13 pino 46; //Port C17
          pinMode(D14, INPUT);               //D14 pino 45; //Port C18
          pinMode(D15, INPUT);               //D15 pino44; //Port  C19

          //delay(100);
}

void zeraOutputBusDados(int D0, int D1, int D2, int D3, int D4, int D5, int D6, int D7, int D8, int D9, int D10, int D11, int D12, int D13, int D14, int D15){
          delay(10);
          digitalWrite(D0, LOW);              //Zerar output
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
          //delay(100);
}

void writeBusADC(long data){        // escreve endereço ou dado na saída
          REG_PIOC_SODR = data;
          delay(10);
}

void zeraBusADC(long data){        // zera Bus antes de escrever um novo dado na saída
          REG_PIOC_CODR = data;
          delay(10);
}
          
