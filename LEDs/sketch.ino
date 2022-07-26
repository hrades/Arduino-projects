#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7

int saidas[4] = {4,5,6,7};

void setup() {
  for (int i=0; i<sizeof(saidas); i++){
    pinMode(saidas[i], OUTPUT);
  }

  /* testa as portas de output
  for (int i=0; i<sizeof(saidas); i++){
    digitalWrite(saidas[i], HIGH);
    delay(500);
    digitalWrite(saidas[i], LOW);
    delay(500);
  }*/
}

void loop() {
  desafio();
}

void exercicioUm(){
  //teste de 2 leds com diferentes tempos
  digitalWrite(LED1, 1);
  delay(1000);
  digitalWrite(LED1, 0);

  digitalWrite(LED4, 1);
  delay(500);
  digitalWrite(LED4, 0);
}

void semaforo(){
//simular o funcionamento de um semáforo
  digitalWrite(LED2, 1);
  delay(2500);
  digitalWrite(LED2, 0);

  digitalWrite(LED3, 1);
  delay(500);
  digitalWrite(LED3, 0);

  digitalWrite(LED4, 1);
  delay(2000);
  digitalWrite(LED4, 0);
}

void desafio(){
//ligar todos os leds e dps apagar com intervalo de 1 segundo em ordem
  for(int i=0; i<sizeof(saidas); i++){
    digitalWrite(saidas[i], 1);
  }
  delay(300);
  for(int i=0; i<sizeof(saidas); i++){
    digitalWrite(saidas[i], 0);
    delay(1000);
  }
}