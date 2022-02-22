//#include <D:\Arduino\sortgeral\ArduinoSort.h>
#define PI 3.1415926535897932384626433832795
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
float real_part = 0;                                              // Media trimada parte real
float imag_part = 0;                                              // media trimada para imaginaria
float modulo_Z = 0;                                               // media modulo Z
float fase_Z = 0;                                                 // media fase de Z em graus

void setup() {                                                    // Inicia comunicação
  SerialUSB.begin(9600);
  Serial.begin(9600);
  delay(3000);
}

void loop() {
SerialUSB.println("Un-sorted Array: ");                           //Gerar vetores randomicamente
  for (int i = 0; i < arraySize ; i++){
    //myArray[i] = i;
    myArray[i] = random(0, 10000)*(0.01);                         // Vetor Z randomico
    myPhase[i] = random(-1000, 1000)*(0.01);                      // Vetor fase randomico
     SerialUSB.print(myArray[i]);                                 // Imprime Z e fase un-sorted
     SerialUSB.print("  ");
     SerialUSB.println(myPhase[i]);
     }
 
                                                                  //Inicio da classificaçao
  for(int x = 0; x < arraySize; x++){                             //Outer loop
      for (int y = 0; y < (arraySize -1); y++){                   //Inner loop
         if(myArray[y] > myArray[y+1]){                           //if this value is bigger than next
            double tmp1 = myArray[y+1];                           //Store a temp of the next
            double tmp2 = myPhase[y+1];
            myArray[y+1] = myArray[y];                            //Move this value to next position array
            myPhase[y+1] = myPhase[y];
            myArray[y] = tmp1;                                    //Put value at the current possition
            myPhase[y] = tmp2;}
         }
      }
      
SerialUSB.println("Primeiro quartil: ");                                         
      for ( int x = quartil; x < (arraySize - quartil); x++){    //Remove 1o quartil das extremidades superior e inferior 
        Z_trimed[x - quartil] = myArray[x];                      //Vetor 1o quartil Z trimado 
        Ph_trimed[x - quartil] = myPhase[x];                     //Vetor 10 quartil fase
        SerialUSB.print(Z_trimed[x - quartil]);                  //Imprime Z trimado e fase sorted do 1o quartil
        SerialUSB.print(" ");
        SerialUSB.println(Ph_trimed[x - quartil]);
      }
  
    for(int x = 0; x < Primeiroquartil; x++){                     //Classificação 2o quartil/Outer loop
      for (int y = 0; y < (Primeiroquartil -1); y++){             //Inner loop
         if(Ph_trimed[y] > Ph_trimed[y+1]){                       //if this value is bigger than next
            double tmp1 = Ph_trimed[y+1];                         //Store a temp of the next
            double tmp2 = Z_trimed[y+1];
            Ph_trimed[y+1] = Ph_trimed[y];                        //Move this value to next position array
            Z_trimed[y+1] = Z_trimed[y];
            Ph_trimed[y] = tmp1;                                  //Put value at the current possition
            Z_trimed[y] = tmp2;}
            }
         }


 SerialUSB.println("Segudo quartil: "); 
    for ( int x = quartil; x < (Primeiroquartil - quartil); x++){ //Remove 2o quartil das extremidades superior e inferior 
        Z2_trimed[x - quartil] = Z_trimed[x];                     //Vetor 2o quartil do modulo Z
        Ph2_trimed[x - quartil] = Ph_trimed[x];                   //Vetor 20 quartil da fase trimada
        SerialUSB.print(Z2_trimed[x - quartil]);                  //Imprime Z e fase trimada  sorted do 2o quartil
        SerialUSB.print(" ");
        SerialUSB.println(Ph2_trimed[x - quartil]);
      }


  for(int x = 0; x < Segundoquartil; x++){                                      //Converte polar para retangular
         real_part =  real_part + Z2_trimed[x]*cos(Ph2_trimed[x]*PI/180);       //Calcula parte real e soma
         imag_part =  imag_part + Z2_trimed[x]*sin( Ph2_trimed[x]*PI/180);      //Calcula parte imaginária e soma
       }
  real_part = (real_part)/Segundoquartil;                                       //Calcula media parte real
  imag_part = (imag_part)/Segundoquartil;                                       //calcula media parte imaginaria

  modulo_Z = sqrt(sq(real_part)+sq(imag_part))/1;                               // Converte retangular para polar - modulo Z
  fase_Z = atan2(imag_part , real_part)*(180/M_PI);    // cálculo da fase       //Fase em graus
          
 SerialUSB.println("Sorted Array: ");                                           // Imprime Z e fase sorted
    printArray();
 
SerialUSB.println("RETANGULAR");                                                // Print retangular
        SerialUSB.print(real_part);
        SerialUSB.print(" ");
        SerialUSB.println(imag_part);

SerialUSB.println("POLAR");                                                     // Print Polar
        SerialUSB.print(modulo_Z);
        SerialUSB.print(" ");
        SerialUSB.println(fase_Z);
        
 delay(7000);                                                                  //delay 7s
      real_part = 0;                                                           //Zerar variaveis 
      imag_part = 0;
      modulo_Z = 0;
      fase_Z = 0;
}

void printArray() {                                                          // Imprime Z e fase sorted                                                      
    for (int i = 0; i < arraySize ; i++){
     SerialUSB.print(myArray[i]);
     SerialUSB.print("  ");
     SerialUSB.println(myPhase[i]);
  }
}
