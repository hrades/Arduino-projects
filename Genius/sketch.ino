#define Vermelho 2
#define Azul 3
#define Verde 4
#define Amarelo 5

int Leds[4] = {2,3,4,5}

void setup() {
  for(int i=0; i<4; i++){
    pinMode(Leds[i], OUTPUT);
  }

}

void loop() {
  
  
}
