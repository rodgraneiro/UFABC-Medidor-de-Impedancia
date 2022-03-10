//********INICIALIZAÇAO*******************************************************************

int buttonState8 = 0;         // variable for reading the pushbutton status
int habilitaMasterState = 0;  // variable for reading the pushbutton status
int StartState = 0;           // variable for reading the pushbutton status
int ptos_periodo = 0;

//#define Nr_de_Amostras  10
//#define ptos_por_periodo 10
//volatile int Nr_de_Amostras = 20;
//int ptos_por_periodo = 10;
//volatile int Nr_de_periodos = Nr_de_Amostras/ptos_por_periodo;
//volatile uint32_t vetor_Amostra[Nr_de_Amostras] = {0};
//volatile uint32_t vetor_segunda_palavra[Nr_de_Amostras] = {0};
//volatile float converte_volts[Nr_de_Amostras];

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

float Rsentinela = 55.1;
float fator_conv_corrente = 1.299285e-7;
//unsigned long tempo_inicio = millis();
//unsigned long tempo_exec[20] = {0};
//long Nr_medicao = 0;

int coluna_piE = 0;
volatile float offsetTOTAL = 0;
float amplitude = 0;
volatile float ampTOTAL = 0;
float fase = 0;
volatile float faseTOTAL = 0;

//int NrMed = 0;

//unsigned int aux;
  

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
          
