//#include <D:\Arduino\sortgeral\ArduinoSort.h>
#define PI 3.1415926535897932384626433832795
const int arraySize = 100; //Array size
float myArray[arraySize];
float myPhase[arraySize];
const int quartil = floor(arraySize/8);
const int Primeiroquartil = arraySize - 2*quartil;
const int Segundoquartil = Primeiroquartil - 2*quartil;
float Z_trimed[Primeiroquartil];
float Ph_trimed[Primeiroquartil];
float Z2_trimed[Segundoquartil];
float Ph2_trimed[Segundoquartil];
float real_part = 0;
float imag_part = 0;
float modulo_Z = 0;
float fase_Z = 0;

void setup() {
  SerialUSB.begin(9600);
  Serial.begin(9600);
  delay(3000);
}

void loop() {
SerialUSB.println("Un-sorted Array: "); 
  for (int i = 0; i < arraySize ; i++){
    //myArray[i] = i;
    myArray[i] = random(0, 10000)*(0.01);
    myPhase[i] = random(-1000, 1000)*(0.01);
     SerialUSB.print(myArray[i]);
     SerialUSB.print("  ");
     SerialUSB.println(myPhase[i]);
     }
 
 //sort(myArray, arraySize);                   //Pass the array and size
  for(int x = 0; x < arraySize; x++){           //Outer loop
      for (int y = 0; y < (arraySize -1); y++){   //Inner loop
         if(myArray[y] > myArray[y+1]){                 // if this value is bigger than next
            double tmp1 = myArray[y+1];                //Store a temp of the next
            double tmp2 = myPhase[y+1];
            myArray[y+1] = myArray[y];                  // Move this value to next position array
            myPhase[y+1] = myPhase[y];
            myArray[y] = tmp1;                     // Put temp value at the current possition
            myPhase[y] = tmp2;}
         }
      }
      
SerialUSB.println("Primeiro quartil: "); 
      for ( int x = quartil; x < (arraySize - quartil); x++){
        Z_trimed[x - quartil] = myArray[x];
        Ph_trimed[x - quartil] = myPhase[x];
        SerialUSB.print(Z_trimed[x - quartil]);
        SerialUSB.print(" ");
        SerialUSB.println(Ph_trimed[x - quartil]);
      }
  
    for(int x = 0; x < Primeiroquartil; x++){           //Outer loop
      for (int y = 0; y < (Primeiroquartil -1); y++){   //Inner loop
         if(Ph_trimed[y] > Ph_trimed[y+1]){                 // if this value is bigger than next
            double tmp1 = Ph_trimed[y+1];                //Store a temp of the next
            double tmp2 = Z_trimed[y+1];
            Ph_trimed[y+1] = Ph_trimed[y];                  // Move this value to next position array
            Z_trimed[y+1] = Z_trimed[y];
            Ph_trimed[y] = tmp1;                     // Put temp value at the current possition
            Z_trimed[y] = tmp2;}
            }
         }


 SerialUSB.println("Segudo quartil: "); 
    for ( int x = quartil; x < (Primeiroquartil - quartil); x++){
        Z2_trimed[x - quartil] = Z_trimed[x];
        Ph2_trimed[x - quartil] = Ph_trimed[x];
        SerialUSB.print(Z2_trimed[x - quartil]);
        SerialUSB.print(" ");
        SerialUSB.println(Ph2_trimed[x - quartil]);
      }


for(int x = 0; x < Segundoquartil; x++){ // Laço demodulação por quadratura
              //Zmedido = modulo_sort2.*( cos(fase_sort2*pi/180) + i*sin(fase_sort2*pi/180) );                      
             real_part =  real_part + Z2_trimed[x]*cos(Ph2_trimed[x]*PI/180);
             imag_part =  imag_part + Z2_trimed[x]*sin( Ph2_trimed[x]*PI/180);
             }
  real_part = (real_part)/Segundoquartil;
  imag_part = (imag_part)/Segundoquartil;

  modulo_Z = sqrt(sq(real_part)+sq(imag_part))/1; // Cálculo da amplitude
  fase_Z = atan2(imag_part , real_part)*(180/M_PI);    // cálculo da fase
          
 SerialUSB.println("Sorted Array: ");          // Print header sorted
    printArray();
 
SerialUSB.println("RETANGULAR");          // Print retangular
        SerialUSB.print(real_part);
        SerialUSB.print(" ");
        SerialUSB.println(imag_part);

SerialUSB.println("POLAR");          // Print Polar
        SerialUSB.print(modulo_Z);
        SerialUSB.print(" ");
        SerialUSB.println(fase_Z);
        
 delay(7000);
      real_part = 0;
      imag_part = 0;
      modulo_Z = 0;
      fase_Z = 0;
}

void printArray() {
    for (int i = 0; i < arraySize ; i++){
     SerialUSB.print(myArray[i]);
     SerialUSB.print("  ");
     SerialUSB.println(myPhase[i]);
  }
}
