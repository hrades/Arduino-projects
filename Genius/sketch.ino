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

#define TAMANHO 30
int sequenciaLuzes[TAMANHO];

int rodada = 0;
int usuario = 0;

#define INDEFINIDO -1

enum Estados{
  PROXIMA_RODADA,
  RESPOSTA,
  SUCESSO,
  FALHA
};

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
  sequenciaJogo();
  Serial.begin(9600);
  delay(UM_SEG);

}

void loop() {
  switch (estadoAtual()) {
    case PROXIMA_RODADA:
      novaRodada();
      Serial.println("Pronto para a proxima rodada");
      break;
    case RESPOSTA:
      respostaUsuario();
      Serial.println("Jogador respondendo");
      break;
    case SUCESSO:
      Serial.println("Jogo finalizado com sucesso");
      finalSucesso();
      break;
    case FALHA:
      Serial.println("Jogo finalizado com falha");
      finalFalha();
      break;
  }
  delay(MEIO_SEG);

}

int estadoAtual(){
  if(rodada <= TAMANHO){
    if(usuario == rodada) {
      return PROXIMA_RODADA;
    }
    else{
      return RESPOSTA;
    }
  }
  else if(rodada == TAMANHO + 1){
    return SUCESSO;
  }
  else{
    return FALHA;
  }
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
    piscaLed(Leds[i], 100);
  }
}

int sorteiaCor(){
  return random(VERMELHO, AMARELO+1);
}

void sequenciaJogo(){
  int jogo = analogRead(A0);
  randomSeed(jogo);
  for(int i = 0; i < TAMANHO; i ++) {
    sequenciaLuzes[i] = sorteiaCor();
  } 
}

void piscaSequencia() {
  for (int i = 0; i < rodada; i++) {
    piscaLed(sequenciaLuzes[i], MEIO_SEG);
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

void novaRodada(){
  rodada++;
  usuario = 0;
  if(rodada<=TAMANHO){
    piscaSequencia();
  }
  
}

void respostaUsuario(){
  int resposta = checaBotao();

  if(resposta == INDEFINIDO){
    return;
  }
  if(resposta == sequenciaLuzes[usuario]){
    usuario++;
  }
  else{
    rodada = TAMANHO + 2;
  } 
}

void finalSucesso(){
  for(int i=0;i<4;i++){
    digitalWrite(Leds[i], HIGH);
  }
}

void finalFalha(){
  for(int c=0;c<3;c++){
    for(int i=0;i<4;i++){
      digitalWrite(Leds[i], HIGH);
    }
    delay(250);
    for(int i=0;i<4;i++){
      digitalWrite(Leds[i], LOW);
    }
    delay(250);
  }
}
