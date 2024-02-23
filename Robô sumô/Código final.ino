#include <AFMotor.h>
AF_DCMotor M1(1); //Direito frontal
AF_DCMotor M2(2); //Direito traseiro
AF_DCMotor M3(3); //Esquerdo frontal
AF_DCMotor M4(4); //Esquerdo traseiro
#define SensorEsq 47 //Sensor Infravermelho Esquerdo
#define SensorDir 30 //Sensor Infravermelho Direito
#define SensorTras 26 //Sensor Infravermelho Traseiro
int pinTrigFrontal = 36; // pino usado para disparar os pulsos do sensor frontal
int pinEchoFrontal = 37; // pino usado para ler a saida do sensor frontal
int pinTrigTraseiro = 33;
int pinEchoTraseiro = 32;
float tempoEchoFrontal = 0;
float tempoEchoTraseiro = 0;
// Obs. Velocidade do som = 340,29 m/s = 0.00034029 m/us
const float velocidadeSom = 0.00034029; // em metros por microsegundo

void setup(){
  pinMode(SensorEsq, INPUT);
  pinMode(SensorDir, INPUT);
  pinMode(SensorTras, INPUT);
// Configura pinos Trig e Echo
  pinMode(pinTrigFrontal, OUTPUT); // configura pino TRIG como saída
  pinMode(pinEchoFrontal, INPUT); // configura pino ECHO como entrada
  pinMode(pinTrigTraseiro, OUTPUT); // configura pino TRIG como saída
  pinMode(pinEchoTraseiro, INPUT); // configura pino ECHO como entrada
// Inicializa pino Trig em nível baixo
  digitalWrite(pinTrigFrontal, LOW);
  digitalWrite(pinTrigTraseiro, LOW);
// Inicializa a porta serial
  Serial.begin(9600);
}

void gatilhoSensorFrontal(){
  digitalWrite(pinTrigFrontal, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigFrontal, LOW);
  tempoEchoFrontal = calculaDistancia(pulseIn(pinEchoFrontal, HIGH))*100;
}

void gatilhoSensorTraseiro(){
  digitalWrite(pinTrigTraseiro, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigTraseiro, LOW);
  tempoEchoTraseiro = calculaDistancia(pulseIn(pinEchoTraseiro, HIGH))*100;
}

float calculaDistancia(float tempoMicrossegundos){
  return((tempoMicrossegundos*velocidadeSom)/2);
}

void frente(){
  //Todos os motores para frente
  M1.run(BACKWARD);
  M1.setSpeed(140);
  M2.run(FORWARD);
  M2.setSpeed(140);
  M3.run(BACKWARD);
  M3.setSpeed(140);
  M4.run(FORWARD);
  M4.setSpeed(140);
}

void tras(){
  //Todos os motores para trás
  M1.run(FORWARD);
  M1.setSpeed(140);
  M2.run(BACKWARD);
  M2.setSpeed(140);
  M3.run(FORWARD);
  M3.setSpeed(140);
  M4.run(BACKWARD);
  M4.setSpeed(140);
}

void esquerda(){
  //Motores da esquerda para frente, motores da direit para trás
  M1.run(FORWARD);
  M1.setSpeed(140);
  M2.run(BACKWARD);
  M2.setSpeed(140);
  M3.run(BACKWARD);
  M3.setSpeed(140);
  M4.run(FORWARD);
  M4.setSpeed(140);
}

void direita(){
  //Motores da direita para frente, motores da esquerda para trás
  M1.run(BACKWARD);
  M1.setSpeed(140);
  M2.run(FORWARD);
  M2.setSpeed(140);
  M3.run(FORWARD);
  M3.setSpeed(140);
  M4.run(BACKWARD);
  M4.setSpeed(140);
}

void procurar(){
  M1.run(FORWARD);
  M1.setSpeed(80);
  M2.run(BACKWARD);
  M2.setSpeed(80);
  M3.run(BACKWARD);
  M3.setSpeed(80);
  M4.run(FORWARD);
  M4.setSpeed(80);
}

void sensores()
{
  gatilhoSensorFrontal();
  gatilhoSensorTraseiro();
  procurar();
  if(digitalRead(SensorEsq) == 1 && digitalRead(SensorDir) == 1){ // Robô identifica faixa preta nos dois
    if(tempoEchoFrontal <= 45.0){
      frente();
    }
    if(tempoEchoTraseiro <= 10.0){
      direita();
      delay(1500);
    }
  }
  if (digitalRead(SensorEsq) == 0 && digitalRead(SensorDir) == 0) //Robô identifica faixa clara nos dois
  {
    tras();
    delay(750);
    esquerda;
    delay(1500);
    frente();
    delay(1500);
  }
  if (digitalRead(SensorEsq) == 1 && digitalRead(SensorDir) == 0) //Robô identifica faixa claro no direito
  {
    tras();
    delay(750);
    direita();
    delay(1500);
    frente();
    delay(1500);
  }
  if (digitalRead(SensorEsq) == 0 && digitalRead(SensorDir) == 1) //Robô identifica faixa clara no esquerdo
  {
    tras();
    delay(750);
    esquerda();
    delay(1500);
    frente();
    delay(1500);
  }
  if(digitalRead(SensorTras) == 0) //Robô identifica faixa preta no sensor traseiro
  {
    frente();
    delay(750);
  }
}

void loop()
{
/*if (botLiga == 1){
girar();
while(true){
infravermelho();
}
}*/
  while(true){
    sensores();
  }
}