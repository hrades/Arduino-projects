#include <AFMotor.h> 

//Configuração motores 
AF_DCMotor M1(1); //Direito frontal 
AF_DCMotor M2(2); //Direito traseiro 
AF_DCMotor M3(3); //Esquerdo frontal 
AF_DCMotor M4(4); //Esquerdo traseiro 

#define SensorEsq 47  //Sensor Infravermelho Esquerdo  
#define SensorDir 30  //Sensor Infravermelho Direito  
#define SensorTras 26 //Sensor Infravermelho Traseiro 

//Pinos sensores ultrassonicos 
int pinTrigFrontal = 36; // pino usado para disparar os pulsos do sensor 
int pinEchoFrontal = 37; // pino usado para ler a saida do sensor 
int pinTrigTraseiro = 33; 
int pinEchoTraseiro = 32; 

float tempoEchoFrontal = 0; 
float tempoEchoTraseiro = 0; 
  
// Obs. Velocidade do som = 340,29 m/s = 0.00034029 m/us 
const float velocidadeSom = 0.00034029; // em metros por microsegundo 

//Ponteiro 
void (*Ponteiro)();  

void configura(); 
void procura(); 
void ataque(); 
void linhaEsquerdo(); 
void linhaDireito(); 
void linhaTras(); 
void linhaDois(); 
void fuga(); 

void setup() { 
  Ponteiro = configura; 
} 
  
void loop() { 
  //procura inimigo 
  if(tempoEchoFrontal<=45.0){Ponteiro=procura;} 
  //Identifica branco nos dois e foge da borda 
  if (digitalRead(SensorEsq) == 0 && digitalRead(SensorDir) == 0){Ponteiro=linhaDois;} 
  //Identifica branco no esquerdo e foge da borda 
  if(digitalRead(SensorEsq) == 0 && digitalRead(SensorDir) == 1){Ponteiro=linhaEsquerdo;} 
  //Identifica branco no direito e foge da borda 
  if(digitalRead(SensorEsq) == 1 && digitalRead(SensorDir) == 0){Ponteiro=linhaDireito;} 
  //Identifica linha branca na parte de tras 
  if(digitalRead(SensorTras) == 0){Ponteiro=linhaTras;} 
  //foge se o inimigo estiver atrás
  if(tempoEchoTraseiro<=15.0){Ponteiro=fuga;}
} 

void  gatilhoSensorFrontal(){
  //Leitura do ultrassônico frontal
  digitalWrite(pinTrigFrontal, HIGH); //Pino Trig frontal como nível alto
  delayMicroseconds(10); //Delay de 10 microsegundos
  digitalWrite(pinTrigFrontal, LOW); //Pino Trig frontal como nível baixo
  tempoEchoFrontal = calculaDistancia(pulseIn(pinEchoFrontal, HIGH))*100; //Armazena a distância de um objeto em cm
}

void  gatilhoSensorTraseiro(){
  //Leitura do ultrassônico traseiro
  digitalWrite(pinTrigTraseiro, HIGH); //Pino Trig frontal como nível alto
  delayMicroseconds(10); //Delay de 10 microsegundos
  digitalWrite(pinTrigTraseiro, LOW); //Pino Trig frontal como nível baixo
  tempoEchoTraseiro = calculaDistancia(pulseIn(pinEchoTraseiro, HIGH))*100; //Armazena a distância de um objeto em cm 
}

float calculaDistancia(float tempoMicrossegundos){
  return((tempoMicrossegundos*velocidadeSom)/2); //Calcula distância do objeto encontrado
}  

//Funçõpes de ponteiro 

void configura() 
{ 
  //Configura sensores infravermelhos 
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
  Ponteiro=procura;

}  

void procura() 
{ 
//Verifica se está perto do oponente
  gatilhoSensorFrontal();
  gatilhoSensorTraseiro();
  
//Gira até encontrar oponente
  direita(100);  
  
  /*esquerda(115); 
  delay(250); 
  frente(115); 
  delay(1500); 
  direita(115); 
  delay(250); 
  frente(115); 
  delay(1500);*/
} 

void ataque() 
{ 
  frente(200); 
} 

void linhaEsquerdo() 
{ 
  tras(120); 
  delay(300); 
  direta(120); 
  delay(300); 
  frente(120); 
  delay(300); 
} 

void linhaDireito() 
{ 
  tras(120); 
  delay(300); 
  esquerda(120); 
  delay(300); 
  frente(120); 
  delay(300); 
} 

void linhaTras()
{
  frente(127);
  delay(1000);
}

void linhaDois()
{
  tras(120);
  delay(500);
}

void fuga()
{
  direita(120);
  delay(500);
  frente(127);
  delay(500);
}

//Funções de movimentação 

void frente(int pot){ 
    //Todos os motores para frente 
    M1.run(BACKWARD);  
    M1.setSpeed(pot);   
    M2.run(FORWARD); 
    M2.setSpeed(pot);  
    M3.run(BACKWARD);  
    M3.setSpeed(pot); 
    M4.run(FORWARD); 
    M4.setSpeed(pot); 
} 

void tras(int pot){ 
  //Todos os motores para trás 
    M1.run(FORWARD);  
    M1.setSpeed(pot);   
    M2.run(BACKWARD);  
    M2.setSpeed(pot);  
    M3.run(FORWARD);  
    M3.setSpeed(pot); 
    M4.run(BACKWARD); 
    M4.setSpeed(pot);   
} 
  
void esquerda(int pot){ 
  //Motores da esquerda para frente, motores da direit para trás 
    M1.run(FORWARD);  
    M1.setSpeed(pot);   
    M2.run(BACKWARD);  
    M2.setSpeed(pot);  
    M3.run(BACKWARD);  
    M3.setSpeed(pot); 
    M4.run(FORWARD); 
    M4.setSpeed(pot);   
} 
  
void direita(int pot){ 
  //Motores da direita para frente, motores da esquerda para trás 
    M1.run(BACKWARD);  
    M1.setSpeed(pot);   
    M2.run(FORWARD);  
    M2.setSpeed(pot);  
    M3.run(FORWARD);  
    M3.setSpeed(pot); 
    M4.run(BACKWARD);
    M4.setSpeed(pot);   
} 