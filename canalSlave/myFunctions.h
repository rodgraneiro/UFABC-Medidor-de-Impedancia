



/*void resetADC(const int x){
  // RESET pino xx do ADC 7762     **************************
      digitalWrite(x, LOW);                             // Pino 27 arduino LOW
      delay(100);
      digitalWrite(x, HIGH);// reset                    // Pino 27 arduino HIGH
      delay(100);
  //************************************************
}*/

void unselectADC(const int x, const int y, const int z){
      // Desabilita ADC
      digitalWrite(x, HIGH);                          // Port D2 Pino 27 arduino HIGH
      digitalWrite(y, HIGH);                          // Port D0 Pino 25 arduino HIGH
      digitalWrite(z, HIGH);                          // Port D1 Pino 26 arduino HIGH
}



void pulsoPinoADC(int x, int tempo){
  // RESET pino xx do ADC 7762     **************************
      delay(tempo);
      digitalWrite(x, LOW);                             // Pino 27 arduino LOW
      delay(tempo);
      digitalWrite(x, HIGH);// reset                    // Pino 27 arduino HIGH
      delay(tempo);
  //************************************************
}
