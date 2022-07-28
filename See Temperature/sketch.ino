#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float sen1, sen2;
const float BETA = 3950;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  tanks();
  delay(500);
}

void loop() {
  sen1 = Temperature(0);
  sen2 = Temperature(1);

  printTanks();

  delay(500);
}

//METHODS
float Temperature(int pin){
  int Analog;
  float temp;

  switch(pin){
    case 0:
      Analog = analogRead(A0);
      break;
    case 1:
      Analog = analogRead(A1);
      break;
  }

  temp = 1 / (log(1 / (1023.0 / Analog - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return temp;
}

void tanks(){
  lcd.setCursor(2,0);
  lcd.print("Tank1  Tank2");
}

void printTanks(){
  if(sen1>0 && sen2>0){

    if(sen1<10 && sen1>-10){
      lcd.setCursor(6,1);
      lcd.print(" ");
    }
    if(sen2<10 && sen2>-10){
      lcd.setCursor(13,1);
      lcd.print(" ");
    }

    lcd.setCursor(2,1);
    lcd.print(sen1);
    lcd.setCursor(9,1);
    lcd.print(sen2);
    lcd.setCursor(7,1);
    lcd.print("  ");
    lcd.setCursor(14,1);
    lcd.print("  ");
  
  }
  else if(sen1<0 && sen2<0){

    if(sen1>-10){
      lcd.setCursor(7,1);
      lcd.print(" ");
    }
    if(sen2>-10){
      lcd.setCursor(14,1);
      lcd.print(" ");
    }
    lcd.setCursor(2,1);
    lcd.print(sen1);
    lcd.setCursor(9,1);
    lcd.print(sen2);
  }
  else if(sen1<0 && sen2>0){

    if(sen2<10 && sen2>-10){
      lcd.setCursor(13,1);
      lcd.print(" ");
    }
    lcd.setCursor(2,1);
    lcd.print(sen1);
    lcd.setCursor(9,1);
    lcd.print(sen2);
    lcd.setCursor(14,1);
    lcd.print("  ");
  }
  else if(sen1>0 && sen2<0){

    if(sen1<10 && sen1>-10){
      lcd.setCursor(6,1);
      lcd.print(" ");
    }
    lcd.setCursor(2,1);
    lcd.print(sen1);
    lcd.setCursor(9,1);
    lcd.print(sen2);
    lcd.setCursor(7,1);
    lcd.print("  ");
  }
}