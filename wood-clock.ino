#include <LiquidCrystal_PCF8574.h>
#include <DS3231.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27);
DS3231 clock;

const int buttonPinA = 2;
const int buttonPinB = 3;

bool century = false;
bool h12Flag;
bool pmFlag;

void setup()
{
  Wire.begin();
  Wire.beginTransmission(0x27);

  lcd.begin(20, 4);
  lcd.setBacklight(255);
  lcd.home();
}

void loop()
{
    printClock();
    setClock();


    delay(1000);
}

void setClock() {
    if (digitalRead(buttonPinA) == HIGH) {
      if (clock.getHour(h12Flag, pmFlag) < 23) {
        clock.setHour(clock.getHour(h12Flag, pmFlag) + 1);
      } else {
        clock.setHour(0);
      }
    }

    if (digitalRead(buttonPinB) == HIGH) {
      if (clock.getMinute() < 59) {
        clock.setMinute(clock.getMinute() + 1);
      } else {
        clock.setMinute(0);
      }
    }
}

void printClock() {
    lcd.setCursor(5, 1);
    lcdPrint(clock.getHour(h12Flag, pmFlag));
    if (clock.getSecond() % 2) {
      lcd.print(":");
    } else {
      lcd.print(" ");
    }
    lcdPrint(clock.getMinute());
    lcd.print(" ");
    lcdPrint(clock.getTemperature());
    lcd.print((char)223);
    lcd.print("C");
}

void lcdPrint(int value) {
  if (value < 10) {
    lcd.print("0");
  }
  lcd.print(value, DEC);
}
