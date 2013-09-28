#include <LiquidCrystal.h>
#include <LcdBarGraph.h>

byte lcdNumCols = 16; // -- number of columns in the LCD
byte sensorPin = 0; // -- value for this example

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // -- creating LCD instance
LcdBarGraph lbg(&lcd, lcdNumCols);  // -- creating

void setup(){
  // -- initializing the LCD
  lcd.begin(2, lcdNumCols);
  lcd.clear();
  // -- do some delay: some time I've got broken visualization
  delay(100);
}

void loop()
{
  // -- draw bar graph from the analog value readed
  lbg.drawValue( analogRead(sensorPin), 1024);
  // -- do some delay: frequent draw may cause broken visualization
  delay(100);
}