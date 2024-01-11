#define Vermelho 2
#define Azul 3
#define Verde 4
#define Amarelo 5

#define UM_SEG 1000
#define MEIO_SEG 500

int Leds[4] = {Vermelho, Azul, Verde, Amarelo};

void setup() {
  //Inicia portas
  for(int i=0; i<4; i++){
    pinMode(Leds[i], OUTPUT);
  }
  //Testa LEDs
  sequenciaInit();
}

void loop() {
  
  
}

void piscaLed(int LED, int tempo){
  digitalWrite(LED, HIGH);
  delay(tempo);
  digitalWrite(LED, LOW);
  delay(tempo);
}

void sequenciaInit(){
  for(int i=0;i<4;i++){
    piscaLed(Leds[i], MEIO_SEG);
  }
}
