//#include <D:\Arduino\sortgeral\ArduinoSort.h>

#include "mysort.h"

#define DEBUGSERIAL


const int arraySize = 100;                                        //Array size
float myArray[arraySize];                                         //Vetor modulo Z
float myPhase[arraySize];                                         //Vetor fase Z
const int quartil = floor(arraySize/8);                           // Tamanho do 1o quartil
const int Primeiroquartil = arraySize - 2*quartil;                //Tamanho primeiro quartil
const int Segundoquartil = Primeiroquartil - 2*quartil;           //Tamanho segubdo quartil
float Z_trimed[Primeiroquartil];                                  //Vetor modulo Z trimado 1o quartil
float Ph_trimed[Primeiroquartil];                                 //Vetor fase Z 1o quartil
float Z2_trimed[Segundoquartil];                                  //Vetor modulo Z 2o quartil
float Ph2_trimed[Segundoquartil];                                 //Vetor fase trimada 2o quartil
                                            // media trimada para imaginaria
float modulo_Z = 0;                                               // media modulo Z
float fase_Z = 0;                                                 // media fase de Z em graus

void setup() {                                                    // Inicia comunicação
  SerialUSB.begin(9600);
  Serial.begin(9600);
  delay(3000);
}

void loop() {

    gera_vetor_randomico(myArray, myPhase, arraySize );
    
    #ifdef DEBUGSERIAL
        SerialUSB.print(1);                                       
        SerialUSB.print("  ");
        SerialUSB.println(1);
        for (int i = 0; i < arraySize ; i++){                           //Gerar vetores randomicamente
            SerialUSB.print(myArray[i]);                                 // Imprime Z e fase un-sorted
            SerialUSB.print("  ");
            SerialUSB.println(myPhase[i]);
        }
    #endif

    ordena_vetores(myArray, myPhase, arraySize);

    #ifdef DEBUGSERIAL
        SerialUSB.print(2);                                       
        SerialUSB.print("  ");
        SerialUSB.println(2);
    #endif

    trima_array(myArray, myPhase, Z_trimed, Ph_trimed, arraySize, quartil);

    #ifdef DEBUGSERIAL
        for ( int x = quartil; x < (arraySize - quartil); x++){    //Remove 1o quartil das extremidades superior e inferior 
            SerialUSB.print(Z_trimed[x - quartil]);                  //Imprime Z trimado e fase sorted do 1o quartil
            SerialUSB.print(" ");
            SerialUSB.println(Ph_trimed[x - quartil]);
        }
    #endif

    ordena_vetores(Ph_trimed, Z_trimed, Primeiroquartil);

    #ifdef DEBUGSERIAL
        SerialUSB.print(3);                                       
        SerialUSB.print("  ");
        SerialUSB.println(3);    
    #endif

    trima_array(Z_trimed, Ph_trimed, Z2_trimed, Ph2_trimed, Primeiroquartil, quartil);

    #ifdef DEBUGSERIAL
        for ( int x = quartil; x < (Primeiroquartil - quartil); x++){ //Remove 2o quartil das extremidades superior e inferior 
            SerialUSB.print(Z2_trimed[x - quartil]);                  //Imprime Z e fase trimada  sorted do 2o quartil
            SerialUSB.print(" ");
            SerialUSB.println(Ph2_trimed[x - quartil]);
        }
    #endif

    media_polar(Z2_trimed, Ph2_trimed, Segundoquartil, &modulo_Z, &fase_Z);

    #ifdef DEBUGSERIAL
        SerialUSB.print(4);                                       
        SerialUSB.print("  ");
        SerialUSB.println(4);                                                           // Imprime Z e fase sorted
        printArray();
        SerialUSB.print(5);                                       
        SerialUSB.print("  ");
        SerialUSB.println(5);
        SerialUSB.print(6);                                                         // Print Polar
        SerialUSB.print("  ");
        SerialUSB.println(6);
        SerialUSB.print(modulo_Z);
        SerialUSB.print(" ");
        SerialUSB.println(fase_Z);
    #endif

    delay(2000);                                                                  //delay 7s
     SerialUSB.print("banana");
}

/*void loop() {
    gera_vetor_randomico(myArray, myPhase, arraySize );
    ordena_vetores(myArray, myPhase, arraySize);
    trima_array(myArray, myPhase, Z_trimed, Ph_trimed, arraySize, quartil);
    ordena_vetores(Ph_trimed, Z_trimed, Primeiroquartil);
    trima_array(Z_trimed, Ph_trimed, Z2_trimed, Ph2_trimed, Primeiroquartil, quartil);
    media_polar(Z2_trimed, Ph2_trimed, Segundoquartil, &modulo_Z, &fase_Z);
    delay(7000);                                                                  //delay 7s
}*/

void printArray() {                                                          // Imprime Z e fase sorted                                                      
    for (int i = 0; i < arraySize ; i++){
     SerialUSB.print(myArray[i]);
     SerialUSB.print("  ");
     SerialUSB.println(myPhase[i]);
  }
}
