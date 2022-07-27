//import and set LCD library
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //LiquidCrystal lcd("RS", "E", "D4", "D5", "D6", "D7"); <- put pins in this order
char numbers[10] = {"0123456789"};
#define button1 23
void setup() {
  pinMode(button1, INPUT);
  lcd.begin(16,2); /*begin(Columns, lines)*/
  printTest();
  delay(500);
}

void loop() {
  if(digitalRead(button1)==1){ //It will only work if the switch is on
    lcd.clear();
    NewYear(1000); //Enter the time range along with the method
  }
  else{ //Default message informing to turn on the switch
    lcd.setCursor(3,0);
    lcd.print("Switch to");
    lcd.setCursor(5,1);
    lcd.print("Begin");
  }
}


//METHODS
void printTest(){
  //To print smth -> inform where it starts printing (Column, Line)
  lcd.setCursor(2,0);
  lcd.print("Hello World!");
  lcd.setCursor(2,1);
  lcd.print("Let's start");
  delay(1000);
  lcd.clear();
}

void counting(int period){ //Count numbers from 0 to 9 and restarts when it finishes
  lcd.setCursor(0,0);
  lcd.print("Contador");

  for(int i=0;i<sizeof(numbers);i++){
    lcd.setCursor(0,1);
    lcd.print(numbers[i]);
    delay(period);
  }
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Restarting");
  for(int time=10;time<=13;time++){
    delay(500);
    if(time<13){
      lcd.setCursor(time,0);
      lcd.print(".");
    }
  }

  lcd.clear();
  delay(200);
}

void NewYear(int period){ //Simulates a countdown and prints a New Year message
  lcd.setCursor(0,0);
  lcd.print("Time left");
  for(int i=10;i>0;i--){
    lcd.setCursor(0,1);
    lcd.print(numbers[(i-1)]);
    delay(period);
  }
  lcd.clear();

  lcd.setCursor(5,0);
  lcd.print("Happy");
  lcd.setCursor(4,1);
  lcd.print("New Year");
  delay(1500);
  lcd.clear();
}