  int periodo = 20;  //20ms --> 50z   20us --> 50kHz
  float k=0.2083; //D.C ideal
  int count_DC = 0;
  int tolerancia = 12; // resolución 4.88mV  --> 12*4.88 = +- 58.56mV
  
void setup() {
  pinMode(3, OUTPUT);    // pin 3 output
  pinMode(5, OUTPUT);    // pin 5 output
  pinMode(A0,INPUT);     // A0 entrada
  pinMode(A1,INPUT);     // A1 entrada

  //solo para test
  pinMode(7, OUTPUT);    // pin 7 output
  pinMode(6, OUTPUT);    // pin 6 output

}

void loop() {
  int in=analogRead(A0);  // Leer A0 --> Voltaje de VIN
  int out=analogRead(A1);  // Leer A1 --> Voltaje de VOUT

  if(in>901 || in<683){    //ADC: 901 --> 4.397V (sensando: 26.4V)    ||  684 --> 3.338V  (sensando: 20V) // divisor resisitvo [2k/(2k+10k)]
    digitalWrite(3,HIGH);     // Fuera del rango se prende el LED
  }
  else{                        // Si se encuentra dentro del rango se mantiene apagado el LED y sale la PWM
    digitalWrite(3,LOW); 
    // Salida PWM
    float high_p= periodo*k;
    float low_p= periodo*(1-k);
    digitalWrite(5, HIGH); 
    delay(high_p);            
    digitalWrite(5, LOW);  
    delay(low_p);           

    count_DC=count_DC+1;
    //Ajustar DutyCycle de la PWM en función a la salida 
    if(count_DC>20){
      count_DC=0;
      if(out>513+tolerancia && k > 0){ // ADC: 513 --> 2.5V (sensando: 5V)  Tolerancia +- 0.117V (2*58.56mV)  // divisor resisitvo [10k/(10k+10k)]
        k=k-0.01;
        digitalWrite(7,HIGH);
      }
      else if(out<513-tolerancia && k<1){ // ADC: 513 --> 2.5V (sensando: 5V)  Tolerancia +- 0.117V (2*58.56mV) // divisor resisitvo [10k/(10k+10k)]
        k=k+0.01;
        digitalWrite(6,HIGH);
      }
    } 
  } 
}
