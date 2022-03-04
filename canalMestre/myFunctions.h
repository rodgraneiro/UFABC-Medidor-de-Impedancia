

void delayFunc(int temp){
          delay(temp);
}


void pulsoPinoADC(int x, int tempo){
  // RESET pino xx do ADC 7762     **************************
      delay(tempo);
      digitalWrite(x, LOW);                             // Pino  arduino LOW
      delay(tempo);
      digitalWrite(x, HIGH);// reset                    // Pino  arduino HIGH
      delay(tempo);
}
