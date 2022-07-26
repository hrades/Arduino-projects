//set list and vars to work with
int exits[2] = {3, 4};

int Analog0;
float temp;
const float BETA = 3950;
int last_inter = 0, current_inter;
int pin_button = 2;

#define LED1 3
#define LED2 4
#define sen1 A0

void setup() {
  //initiate output pins
  for(int i2=0; i2<sizeof(exits); i2++){
    pinMode(exits[i2], OUTPUT);
  }
  //initiate input pin
  pinMode(sen1, INPUT);
  //initiate serial monitor
  Serial.begin(9600);
  //config serial interruption
  pinMode(pin_button, INPUT);  
  attachInterrupt(digitalPinToInterrupt(pin_button), configInterrupt, RISING);
  //test leds
  testOutput();
}

void loop() {
  readTemp();

  if(temp>0){ //LEDs light up according to the temperature
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 1);
  }
  else{
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 0);
  }

}

//METHODS
void testOutput(){
  Serial.println("Setup defined succesfully!");
  for(int i=0; i<sizeof(exits); i++){
    digitalWrite(exits[i], !digitalRead(exits[i]));
    delay(500);
    digitalWrite(exits[i], !digitalRead(exits[i]));
    delay(500);
  }
}

void readTemp(){
  Analog0 = analogRead(sen1);
  temp = 1 / (log(1 / (1023.0 / Analog0 - 1)) / BETA + 1.0 / 298.15) - 273.15;
}

//If you click the button, the monitor will show the current temperature
void configInterrupt()
{
  current_inter = millis();
  
  if ((current_inter - last_inter) > 200){
  	Serial.println(temp);
  }
  
  last_inter = current_inter;
}