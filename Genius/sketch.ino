#define VERMELHO 2
#define AZUL 3
#define VERDE 4
#define AMARELO 5

#define BOT_VERMELHO 8
#define BOT_AZUL 9
#define BOT_VERDE 10
#define BOT_AMARELO 11

#define UM_SEG 1000
#define MEIO_SEG 500

int Leds[4] = {VERMELHO, AZUL, VERDE, AMARELO};
int Bots[4] = {BOT_VERMELHO, BOT_AZUL, BOT_VERDE, BOT_AMARELO};

#define INDEFINIDO -1

void setup() {
  //Inicia LEDs
  for(int i=0; i<4; i++){
    pinMode(Leds[i], OUTPUT);
  }
  //Inicia botões
  for(int i=0; i<4; i++){
    pinMode(Bots[i], INPUT_PULLUP);
  }
  //Testa LEDs
  sequenciaInit();

  Serial.begin(9600);
}

void loop() {
  Serial.println(checaBotao());
  
}

int piscaLed(int LED, int tempo){
  digitalWrite(LED, HIGH);
  delay(tempo);
  digitalWrite(LED, LOW);
  delay(tempo);
  return LED;
}

void sequenciaInit(){
  for(int i=0;i<4;i++){
    piscaLed(Leds[i], MEIO_SEG);
  }
}

int checaBotao(){
  if (digitalRead(BOT_VERMELHO)==LOW){
    return piscaLed(VERMELHO, UM_SEG);
  }
  if (digitalRead(BOT_AZUL)==LOW){
    return piscaLed(AZUL, UM_SEG);
  }
  if (digitalRead(BOT_AMARELO)==LOW){
    return piscaLed(AMARELO, UM_SEG);
  }
  if (digitalRead(BOT_VERDE)==LOW){
    return piscaLed(VERDE, UM_SEG);
  }

  return INDEFINIDO;
}
