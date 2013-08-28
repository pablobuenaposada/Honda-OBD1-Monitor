#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR1 0
#define SENSOR2 1
#define SENSOR3 2
#define SENSOR4 3

#define I2C_ADDR 0x20
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define LED_OFF 1
#define LED_ON 0

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setupLCD(){
  lcd.begin (20,4);  
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);
  lcd.clear();
  delay(1000);
  lcd.home();
  lcd.backlight();
}

void initialScreen(){
  lcd.setCursor(0,1);
  lcd.print("  BEYRO MOTORSPORT");
  lcd.setCursor(0,2);
  lcd.print("      CIVIC EK");
}

void setup() {
  setupLCD();
  initialScreen();
  delay(3000);
  lcd.clear();  
}

//for VDO 323-057
float voltage2temp(float voltage){
  
  return -0.05007201037*pow(voltage,10) + 1.171260711*pow(voltage,9) - 11.55461723*pow(voltage,8) + 62.20510364*pow(voltage,7) - 196.4010868*pow(voltage,6) + 356.468504*pow(voltage,5) - 305.3996258*pow(voltage,4) - 57.02805328*pow(voltage,3) + 378.5236931*pow(voltage,2) - 366.4523339*voltage + 243.2379721;

}

void printOil(int row, int temp, float pressure){
  String values="";
  values.concat("OIL: ");  
  char stringPressure[10];
  dtostrf(pressure,1,2,stringPressure);
  values.concat(stringPressure);
  values.concat(" PSI ");
  if (temp < 0){
    if(temp > -10){
      values.concat(" ");
    }
  }
  else if(temp < 10){
    values.concat("  ");
  }
  else if(temp < 100){
    values.concat(" ");
  }  
  values.concat(temp);
  values.concat((char)223);
  values.concat("C");  
  lcd.setCursor(0,row);
  lcd.print(values);
}

void printTurbo(int row, float pressure){
  String values="";
  values.concat("BST: ");
  char stringPressure[10];
  dtostrf(pressure,1,2,stringPressure);
  values.concat(stringPressure);
  values.concat(" PSI");
  lcd.setCursor(0,row);
  lcd.print(values);  
}

void printWater(int row, int temp){
  String values="";
  values.concat("H2O: ");
  values.concat(temp);
  values.concat((char)223);
  values.concat("C");  
  lcd.setCursor(0,row);
  lcd.print(values);
}


float getSensorVoltage(int sensor){
  return (analogRead(sensor)/1024.000)*5;
}

void loop() {
  printOil(0,voltage2temp(getSensorVoltage(SENSOR1)),getSensorVoltage(SENSOR2));      
  printTurbo(1,getSensorVoltage(SENSOR3));
  printWater(2,voltage2temp(getSensorVoltage(SENSOR4)));
  delay(250);
}

