#include <Wire.h> //I2C Library
#include <LiquidCrystal_I2C.h>  //LCD Display Library

// I2C Adresse & Pins die am I2C Slave hängen
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0,0);
  lcd.print("Test");
  delay(1000);
  lcd.clear();
  lcd.print("Besser Test");
}

void loop() {}
