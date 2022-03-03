//#include "inicialization.h"
/*


#define NOP() asm("nop \n")

//********INICIALIZAÇAO*******************************************************************
//const int buttonPin8 = 8;     // the number of the pushbutton pin
//int buttonState8 = 0;         // variable for reading the pushbutton status
//int DRDYstate = 1;          // variable for reading the pushbutton status
//int habilitaMaster = 9; // the number of the pushbutton pin
//int Start = 10;         // the number of the pushbutton pin
//int habilitaMasterState = 0;  // variable for reading the pushbutton status
//int StartState = 0;           // variable for reading the pushbutton status


//int CS = 25;    // Port D0 Arduino -> Chip Select AD7762 pin 40
//int RDWR = 26;  // Port D1 Arduino -> Read/Write AD7762 pin 39
//int RESET = 27; // Port D2 Arduino -> Reset AD7762 pin 37
//int DRDY = 23;  // Port A14 Arduino -> Data Ready Output AD7762 pin 38

int Nr_de_Amostras = 20;
int ptos_por_periodo = 10;
int Nr_de_periodos = Nr_de_Amostras/ptos_por_periodo;
int ptos_periodo = 0;
volatile uint32_t vetor_Amostra[20] = {0};
volatile uint32_t vetor_segunda_palavra[20] = {0};
volatile float converte_volts[20];
  
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
unsigned long tempo_inicio = millis();
unsigned long tempo_exec[20] = {0};
long Nr_medicao = 0;


int coluna_piE = 0;
volatile float offsetTOTAL = 0;
float amplitude = 0;
volatile float ampTOTAL = 0;
float fase = 0;
volatile float faseTOTAL = 0;

int NrMed = 0;

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

//*****************************Matriz pseudo inversa 10 ptos excitação 31,25kHz - Sample Rate 312,5kHz
float piEs[] = {0.117557050458495, 0.190211303259031, 0.190211303259031, 0.117557050458495, 2.44929359829470e-17, -0.117557050458495, -0.190211303259031, -0.190211303259031, -0.117557050458495, -4.89858719658942e-17};
float piEc[] = {0.161803398874990, 0.0618033988749894, -0.0618033988749895, -0.161803398874989, -0.200000000000000, -0.161803398874990, -0.0618033988749896, 0.0618033988749895, 0.161803398874990, 0.200000000000000};
float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};


//*****************************Matriz pseudo inversa 10 ptos excitação 125kHz - Sample Rate 625kHz
//float piEs[] = {0,  0.190211303259031, 0.117557050458495, -0.117557050458495,  -0.190211303259031,  -2.26621555905919e-16, 0.190211303259031, 0.117557050458495, -0.117557050458495,  -0.190211303259031};
//float piEc[] = {0.200000000000000, 0.0618033988749895,  -0.161803398874990,  -0.161803398874990,  0.0618033988749895,  0.200000000000000, 0.0618033988749897,  -0.161803398874990,  -0.161803398874990,  0.0618033988749894};
//float piEdc[] = {0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000, 0.100000000000000};

*/
