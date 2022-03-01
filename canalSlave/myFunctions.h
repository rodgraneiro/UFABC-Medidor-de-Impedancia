



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

float verifSinalNeg(int Nr_de_Amostras, volatile uint32_t *vetor_Amostra, float *converte_volts, float fator_conv_corrente, float Rsentinela){

        for(int contador_aux_2 = 0; contador_aux_2 <= Nr_de_Amostras - 1; contador_aux_2++){            // Laço verificar sinal - número formato complemento de 2
                                                                                                        // O bit 23 indentifica o sinal da amostra: "1" para negativo e "0" para positivo.
          
                                                                                                        // Verifica estado do bit 23 aplicando a operação lógica "AND" por meio da máscara 0x800000.
          volatile uint32_t sinal_negativo = vetor_Amostra[contador_aux_2] & 0x00800000;       
                                                                                                        // Se estado do bit 23 igual a "1", aplicar operação lógica de "complemento de 2" e multiplicar por (-1).
                                                                                                        // Em seguida multiplicar pelo fator de conversão para volts
          if(sinal_negativo == 0x800000){ 
              volatile uint32_t semiciclo_neg  = ((~vetor_Amostra[contador_aux_2] + 0x1)) & 0xffffff;             // "complemento de 2"
              converte_volts[contador_aux_2] = -(semiciclo_neg*fator_conv_corrente)/Rsentinela;
              //Serial.println(sci(converte_volts[contador_aux_2],4));
          
          }
          
          // Se estado do bit 23 igual a "0", aplicar fator de conversão para volts                                                  
          else{
              volatile uint32_t semiciclo_pos = vetor_Amostra[contador_aux_2]; // * fator;
              converte_volts[contador_aux_2] = (semiciclo_pos*fator_conv_corrente)/Rsentinela;
              //Serial.println(sci(converte_volts[contador_aux_2],4));
          }
           
    }     // Final laço verificar sinal - número formato complemento de 2  


}
