#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int h, m;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  delay(500);
  showTime(22,0); //Put the current time here
}

void loop() { 
  showTime(0,0);
}

void showTime(int hours, int mins){
  h = hours;
  

  lcd.setCursor(1,0);
  lcd.print("Horario atual");
  lcd.setCursor(7,1);
  lcd.print(":");

  while(h<=23){
    if(h<10){
      lcd.setCursor(5,1);
      lcd.print(0);
      lcd.setCursor(6,1);
      lcd.print(h);
    }
    else{
      lcd.setCursor(5,1);
      lcd.print(h);
    }

    for(m=mins;m<61;m++){
      if(m<10){
        lcd.setCursor(8,1);
        lcd.print(0);
        lcd.setCursor(9,1);
        lcd.print(m);
      }
      else{
        lcd.setCursor(8,1);
        lcd.print(m);
      }
      mins = 0;
      delay(60000);
    }
    h++;
  }
  
}
