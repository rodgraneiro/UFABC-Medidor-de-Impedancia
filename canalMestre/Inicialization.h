



// ******Sinais Bus de controle
const int CS = 25;                        // Port D0 Arduino -> Chip Select AD7762 pin 40
const int RDWR = 26;                      // Port D1 Arduino -> Read/Write AD7762 pin 39
const int RESET = 27;                     // Port D2 Arduino -> Reset AD7762 pin 37
const int DRDY = 23;                      // Port A14 Arduino -> Data Ready Output AD7762 pin 38
const int SYNC = 24;                      // Port A15 Arduino -> Synchronization Input AD7762 pin 36

const int buttonPin8 = 8;     // Número do pino do Arduino para o pushbutton
int buttonState8 = 0;         // Variável p/ armazenar status  do pushbutton



volatile int Nr_de_Amostras = 20;
volatile uint32_t vetor_Amostra[20] = {0};
volatile uint32_t vetor_segunda_palavra[20] = {0};
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
volatile float converte_volts[20] = {0};

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
long Nr_medicao =0;

int ptos_por_periodo = 10;
int Nr_de_periodos = Nr_de_Amostras/ptos_por_periodo;
//int ptos_periodo = 0;

//*****************************Matriz pseudo inversa 10 ptos excitação 31,25kHz - Sample Rate 312,5kHz
float piEs [] = {0.117557050458495, 0.190211303259031, 0.190211303259031, 0.117557050458495, 2.44929359829470e-17, -0.117557050458495, -0.190211303259031, -0.190211303259031, -0.117557050458495, -4.89858719658942e-17};
float piEc[] = {0.161803398874990, 0.0618033988749894, -0.0618033988749895, -0.161803398874989, -0.200000000000000, -0.161803398874990, -0.0618033988749896, 0.0618033988749895, 0.161803398874990, 0.200000000000000};
float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};


//*****************************Matriz pseudo inversa 10 ptos excitação 125kHz - Sample Rate 625kHz
//float piEs[] = {0,  0.190211303259031, 0.117557050458495, -0.117557050458495,  -0.190211303259031,  -2.26621555905919e-16, 0.190211303259031, 0.117557050458495, -0.117557050458495,  -0.190211303259031};
//float piEc[] = {0.200000000000000, 0.0618033988749895,  -0.161803398874990,  -0.161803398874990,  0.0618033988749895,  0.200000000000000, 0.0618033988749897,  -0.161803398874990,  -0.161803398874990,  0.0618033988749894};
//float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};

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
volatile float fator_conv_volts = 3.97725e-7;
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

char dataToSend;

//*****************************************************************
// Inicia bus de controle no void setup

void busColtrolIni(const int CS, const int RDWR, const int RESET, const int DRDY, const int SYNC, const int buttonPin8){
// Configuração de Ports para iniciar AD7762 
          pinMode(CS, OUTPUT);                // Port D0 do Arduino Due
          pinMode(RDWR, OUTPUT);              // Port D1
          pinMode(RESET, OUTPUT);             // Port D2
          pinMode(SYNC, OUTPUT);             // Port A15 do Arduino Due
          pinMode(DRDY, INPUT);               // Port A14 do Arduino Due

          pinMode(buttonPin8, INPUT_PULLUP);  // initialize the pushbutton pin as an input:
          //pinMode(habilitaMaster, OUTPUT);    // initialize the pushbutton pin as an input:
          delay(10);                          // espera estabilização da porta
          //digitalWrite(habilitaMaster, LOW);  // habilita Master:
} 

void unselectADC(const int x, const int y, const int z, const int w){
      // Desabilita ADC
      digitalWrite(x, HIGH);                          // Port D2 Pino 27 arduino HIGH
      digitalWrite(y, HIGH);                          // Port D0 Pino 25 arduino HIGH
      digitalWrite(z, HIGH);                          // Port D1 Pino 26 arduino HIGH
      digitalWrite(w, HIGH);                          // Port D1 Pino 24 arduino HIGH
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
}

void writeBusADC(long data){        // escreve endereço ou dado na saída
          REG_PIOC_SODR = data;
          delay(10);
}

void zeraBusADC(long data){        // zera Bus antes de escrever um novo dado na saída
          REG_PIOC_CODR = data;
          delay(10);
}
