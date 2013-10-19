
#include "Wire.h"
#include "LiquidCrystal.h"
#include "Ecu.h"
#include <LcdBarGraph.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <phi_big_font.h>
#include <EEPROM.h>

#define REDLITE 9
#define GREENLITE 10
#define BLUELITE 6
#define brightness 255
#define ON 1
#define OFF 0

Ecu ecu;

String backlightColors[9] = {"        Red","       Blue","       Green","       Purple","       Lime","       Teal","       Orange","   Backlight OFF","       Custom"};
int rgb[27] = {255,0,0,0,0,255,0,255,0,255,0,255,255,255,0,0,255,255,255,128,0,0,0,0,100,100,100};
int colors = sizeof(backlightColors)/sizeof(String);
int color = 4;
int customColorPos;
int a=3000;

LiquidCrystal lcd(7, 8, 12, 11, 13, 4);
LcdBarGraph tpsBar(&lcd, 20);

byte arrowUp[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00100,
	0b01110,
	0b11111,
	0b00000,
	0b00000
};

byte arrowDown[8] = {
	0b00000,
	0b00000,
	0b11111,
	0b01110,
	0b00100,
	0b00000,
	0b00000,
	0b00000
};

byte doubleArrow[8] = {
	0b00100,
	0b01110,
	0b11111,
	0b00000,
	0b00000,
	0b11111,
	0b01110,
	0b00100
};

int beepPin=5;

int buttonReading = 800;
volatile int button1 = 0;
volatile int button2 = 0;
int auxColor;
 
int actualScreen=1;
int maxMonitorScreens = 6;
int maxSettingScreens = -3;

unsigned long last_interrupt_time=0;
int debouncing = 100;

void initialBeep(){
  
  tone(beepPin,3000);    
  delay(50);
  noTone(beepPin);
  delay(300);
  tone(beepPin,3000);
  delay(50);
  noTone(beepPin);
  delay(300);
  tone(beepPin,3000);
  delay(50);
  noTone(beepPin);
  delay(300);
  tone(beepPin,3000);
  delay(200);
  noTone(beepPin);
}

void beep(){
  tone(beepPin,3000);
  delay(50);
  noTone(beepPin);
}

void setBackLight(uint8_t r, uint8_t g, uint8_t b) {
  // normalize the red LED - its brighter than the rest!
  r = map(r, 0, 255, 0, 100);
  g = map(g, 0, 255, 0, 150);
 
  r = map(r, 0, 255, 0, brightness);
  g = map(g, 0, 255, 0, brightness);
  b = map(b, 0, 255, 0, brightness);
 
  // common anode so invert!
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);
  
  analogWrite(REDLITE, r);
  analogWrite(GREENLITE, g);
  analogWrite(BLUELITE, b);
}

void backLightDemo(){
  for (int i = 0; i < 255; i++) {
    setBackLight(i, 0, 255-i);
    delay(5);
  }
  for (int i = 0; i < 255; i++) {
    setBackLight(255-i, i, 0);
    delay(5);
  }
  for (int i = 0; i < 255; i++) {
    setBackLight(0, 255-i, i);
    delay(5);
  }
}

void settingsSaved(){
  lcd.clear();
  lcd.setCursor(3,2);
  lcd.print("SETTINGS SAVED");
  delay(2000);
  lcd.clear();
}

void backLightSettings(){
  auxColor=color;  
  lcd.setCursor(1,0);
  lcd.print("BACKLIGHT SETTINGS");
  lcd.setCursor(9,1);
  lcd.write((uint8_t)0);  
  lcd.setCursor(0,2);   
  lcd.print(backlightColors[auxColor]);
  lcd.setCursor(9,3);
  lcd.write((uint8_t)1);  
  setBackLight(rgb[auxColor*3],rgb[auxColor*3+1],rgb[auxColor*3+2]); 
}

void customBacklightSettings(){
  customColorPos=(colors-1)*3;
  lcd.setCursor(0,0);
  lcd.print("SET CUSTOM BACKLIGHT");
  lcd.setCursor(1,2); 
  lcd.print("R       G       B "); 
  lcd.setCursor(0,3);
  lcd.print(rgb[(colors-1)*3]);
  lcd.setCursor(3,3);
  lcd.write((uint8_t)2);
  lcd.setCursor(8,3);
  lcd.print(rgb[(colors-1)*3+1]);
  lcd.setCursor(16,3);
  lcd.print(rgb[(colors-1)*3+2]);  
  setBackLight(rgb[(colors-1)*3],rgb[(colors-1)*3+1],rgb[(colors-1)*3+2]);
}

void miniDisplaySettings(){
  lcd.setCursor(0,0);
  lcd.print("MINIDISPLAY SETTINGS");
}


void ecuSensorsScreen(){
 
  lcd.setCursor(0,0);
  lcd.print("BAT:");
  lcd.setCursor(4,0);
  float battery = ecu.getBattery();
  if (battery == 0) lcd.print("n/a");
  else lcd.print(battery);  
  
  lcd.setCursor(0,1);  
  lcd.print("RPM:");  
  unsigned int rpm = ecu.getRpm();
  if (rpm < 10){
    lcd.setCursor(4,1);
    lcd.print("000");
    lcd.setCursor(7,1);  
  }
  else if(rpm < 100){
    lcd.setCursor(4,1);
    lcd.print("00");
    lcd.setCursor(6,1);
  }
  else if(rpm < 1000){
    lcd.setCursor(4,1);
    lcd.print("0");
    lcd.setCursor(5,1);    
  }  
  else{
    lcd.setCursor(4,1);
  }
  lcd.print(rpm);  
  
  
  lcd.setCursor(9,1);
  lcd.print("TPS:");  
  int tps = ecu.getTps();
  if(tps < 10){
    lcd.setCursor(13,1);
    lcd.print("00");
    lcd.setCursor(15,1);
  }
  else if(tps < 100){
    lcd.setCursor(13,1);
    lcd.print("0");
    lcd.setCursor(14,1);
  }
  else{
    lcd.setCursor(13,1);      
  }
  lcd.print(tps);
  lcd.setCursor(16,1);
  lcd.print("%");
  
  lcd.setCursor(9,0);
  lcd.print("IAT:");  
  int iat = ecu.getIat();
  if(iat < 10){
    lcd.setCursor(13,0);
    lcd.print("00");
    lcd.setCursor(15,0);
  }
  else if(iat < 100){
    lcd.setCursor(13,0);
    lcd.print("0");
    lcd.setCursor(14,0);
  }
  else{
    lcd.setCursor(13,0);    
  }
  lcd.print(iat);
  lcd.setCursor(16,0);
  lcd.write(0b11011111); //degree symbol
  
  
  lcd.setCursor(0,2);
  lcd.print("ECT:");  
  int ect = ecu.getEct();  
  if (ect < 10){
    lcd.setCursor(4,2);
    lcd.print("00");
    lcd.setCursor(6,2);  
  }
  else if(ect < 100){
    lcd.setCursor(4,2);
    lcd.print("0");
    lcd.setCursor(5,2);  
  }
  else{
    lcd.setCursor(4,2); 
  }
  lcd.print(ect);
  lcd.setCursor(7,2);
  lcd.write(0b11011111); //degree symbol
  
  
  lcd.setCursor(9,2);
  lcd.print("VSS:");  
  int vss = ecu.getVss();
  if(vss < 10){
    lcd.setCursor(13,2);
    lcd.print("00");
    lcd.setCursor(15,2);
  }
  else if(vss < 100){
    lcd.setCursor(13,2);
    lcd.print("0");
    lcd.setCursor(14,2);  
  }
  else{
    lcd.setCursor(13,2);    
  }
  lcd.print(vss);
  lcd.setCursor(16,2);
  lcd.print("km/h");
  
  
  lcd.setCursor(0,3);
  lcd.print("O2:");  
  int o2= ecu.getO2();
  if (o2 < 10){
    lcd.setCursor(3,3);
    lcd.print("00");
    lcd.setCursor(5,3);  
  }
  else if(o2 < 100){
    lcd.setCursor(3,3);
    lcd.print("0");
    lcd.setCursor(4,3);  
  }
  else{
    lcd.setCursor(3,3); 
  }
  lcd.print(o2);
  
    
  lcd.setCursor(9,3);
  lcd.print("INJ:");
  int inj = ecu.getInj();
  if(inj < 10){
    lcd.setCursor(13,3);
    lcd.print("00");
    lcd.setCursor(15,3);
  }
  else if(inj < 100){
    lcd.setCursor(13,3);
    lcd.print("0");
    lcd.setCursor(14,3);  
  }
  else{
    lcd.setCursor(13,3);    
  }
  lcd.print(inj);
  lcd.setCursor(16,3);
  lcd.print("ms");  
}

int readButton(){  
  buttonReading = analogRead(A1);  
  if (buttonReading <= 1) return 3;
  else if (buttonReading >= 1020) return 4;
  else if (buttonReading >= 350 && buttonReading <= 700) return 5;  
  else return -1;
}

void screen2(){
  lcd.setCursor(0,0);
  lcd.print("THROTTLE POS. SENSOR");  
  int tps = ecu.getTps();
  tpsBar.drawValue(0,2,tps, 100);
    if(tps < 10){
    lcd.setCursor(9,3);
    lcd.print("00");
    lcd.setCursor(11,3);
  }
  else if(tps < 100){
    lcd.setCursor(9,3);
    lcd.print("0");
    lcd.setCursor(10,3);
  }
  else{
    lcd.setCursor(9,3);      
  }
  lcd.print(tps); 
  lcd.setCursor(12,3);
  lcd.print("%");  
}

void screen3(){
  
  lcd.setCursor(0,0);
  lcd.print("IGN:");
  lcd.setCursor(4,0);
  int ign = ecu.getIgn();
  lcd.print(ign);  
  
  lcd.setCursor(0,1);  
  lcd.print("MAP:");  
  float map = ecu.getMap();
  if (map < 10){
    lcd.setCursor(4,1);
    lcd.print("000");
    lcd.setCursor(7,1);  
  }
  else if(map < 100){
    lcd.setCursor(4,1);
    lcd.print("00");
    lcd.setCursor(6,1);
  }
  else if(map < 1000){
    lcd.setCursor(4,1);
    lcd.print("0");
    lcd.setCursor(5,1);    
  }  
  else{
    lcd.setCursor(4,1);
  }
  lcd.print(map);  
  
  
  lcd.setCursor(9,1);
  lcd.print("DTY:");  
  int duty = ecu.getDutyCycle();
  if(duty < 10){
    lcd.setCursor(13,1);
    lcd.print("00");
    lcd.setCursor(15,1);
  }
  else if(duty < 100){
    lcd.setCursor(13,1);
    lcd.print("0");
    lcd.setCursor(14,1);
  }
  else{
    lcd.setCursor(13,1);      
  }
  lcd.print(duty);
  
  
  lcd.setCursor(9,0);
  lcd.print("FUE:");  
  float cons = ecu.getInstantConsumption();
  if(cons < 10){
    lcd.setCursor(13,0);
    lcd.print("00");
    lcd.setCursor(15,0);
  }
  else if(cons< 100){
    lcd.setCursor(13,0);
    lcd.print("0");
    lcd.setCursor(14,0);
  }
  else{
    lcd.setCursor(13,0);    
  }
  lcd.print(cons);
  lcd.setCursor(16,0);
  lcd.print("L");
  
  
  lcd.setCursor(0,2);
  lcd.print("VTC:");  
  int vtec = ecu.getVtec();  
  if (vtec < 10){
    lcd.setCursor(4,2);
    lcd.print("00");
    lcd.setCursor(6,2);  
  }
  else if(vtec < 100){
    lcd.setCursor(4,2);
    lcd.print("0");
    lcd.setCursor(5,2);  
  }
  else{
    lcd.setCursor(4,2); 
  }
  lcd.print(vtec);  
}

void bigRpm(){
  lcd.setCursor(9,0);
  lcd.print("RPM"); 
  int rpm = ecu.getRpm();  
  String rpmString;
  if (rpm < 10){
    rpmString = "0000"+String(rpm);
  }
  else if (rpm < 100){
    rpmString = "000"+String(rpm);
  }
  else if (rpm < 1000){
    rpmString = "00"+String(rpm);  
  }
  else if (rpm < 10000){
    rpmString = "0"+String(rpm);
  }
  else{
    rpmString = String(rpm);
  }
  char charBuf[6];
  rpmString.toCharArray(charBuf, 6); 
  render_big_msg(charBuf,0,1);    
  lcd.setCursor(13,3);
  lcd.print("rev/min");
}

void bigEct(){
  lcd.setCursor(9,0);
  lcd.print("ECT"); 
  int ect = ecu.getEct();  
  String ectString;
  if (ect < 10){
    ectString = "00"+String(ect);
  }
  else if (ect < 100){
    ectString = "0"+String(ect);
  }  
  else{
    ectString = String(ect);
  }
  char charBuf[4];
  ectString.toCharArray(charBuf, 4); 
  render_big_msg(charBuf,4,1);    
  lcd.setCursor(15,2);
  lcd.write(0b11011111);
  lcd.setCursor(16,2);
  lcd.print("C");
}

void bigVss(){
  lcd.setCursor(9,0);
  lcd.print("VSS"); 
  int vss = ecu.getVss();  
  String vssString;
  if (vss < 10){
    vssString = "00"+String(vss);
  }
  else if (vss < 100){
    vssString = "0"+String(vss);
  }  
  else{
    vssString = String(vss);
  }
  char charBuf[4];
  vssString.toCharArray(charBuf, 4); 
  render_big_msg(charBuf,2,1);    
  lcd.setCursor(13,2);  
  lcd.print("km/h");
}

void execScreen(int screen){
     
  if (screen == 1) ecuSensorsScreen();
  else if (screen == 2) screen2();
  else if (screen == 3) screen3();
  else if (screen == 4) bigRpm();
  else if (screen == 5) bigEct();
  else if (screen == 6) bigVss();
  else if (screen == -1) backLightSettings();
  else if (screen == -2) miniDisplaySettings();
  else if (screen == -3) customBacklightSettings();
  else return;
}

void nextScreen(int button){
  
  if (button == 1){
    if (actualScreen < 0) actualScreen=1;
    else actualScreen = actualScreen+1;
    if(actualScreen > maxMonitorScreens){
      actualScreen = 1;
    }    
  }
  else if (button == 2){
    if (actualScreen > 0) actualScreen=-1;
    else actualScreen = actualScreen-1;
    if (actualScreen < maxSettingScreens){
      actualScreen = -1;
    }  
  }  
}

void loadArrowIcons(){
  lcd.createChar(0,arrowUp);
  lcd.createChar(1,arrowDown);
  lcd.createChar(2,doubleArrow);  
}
      

void setup() {
  pinMode(beepPin,OUTPUT);
  Serial.begin(38400);  
  lcd.begin(20,4);
  
  lcd.setCursor(1,1);
  lcd.print("HONDA OBD1 MONITOR");
  lcd.setCursor(0,3);
  lcd.print("v1.0     by Pablo B");
  backLightDemo();
  //initialBeep();
  backLightDemo();
  pinMode(2,INPUT);
  digitalWrite(2,LOW);
  attachInterrupt(0, button1ISR, FALLING);
  pinMode(3,INPUT);
  digitalWrite(3,LOW);
  attachInterrupt(1, button2ISR, FALLING);
  pinMode(A1,INPUT);  
  lcd.clear();
  color = EEPROM.read(1);  
  setBackLight(rgb[color*3],rgb[color*3+1],rgb[color*3+2]);  
}

void loop() {
  
  if (actualScreen == -1){    
    int button=readButton();
    if (button == -1) button=readButton(); //second chance baby!!    
    
      if (button == 3){
        auxColor=auxColor+1;
        if (auxColor > colors-1) auxColor=0;
      }
      else if (button == 4){
        auxColor=auxColor-1;
        if (auxColor < 0) auxColor=colors-1;
      }
      else if (button == 5){
        if (color != auxColor) color=auxColor;
        EEPROM.write(1,color);
        settingsSaved();
          
      }
      if (button != -1){
        lcd.clear(); 
        lcd.setCursor(1,0);
        lcd.print("BACKLIGHT SETTINGS");
        lcd.setCursor(9,1);
        lcd.write((uint8_t)0);
        lcd.setCursor(0,2);   
        lcd.print(backlightColors[auxColor]);
        lcd.setCursor(9,3);
        lcd.write((uint8_t)1);  
        setBackLight(rgb[auxColor*3],rgb[auxColor*3+1],rgb[auxColor*3+2]);
      }
      delay(70);      
  }
 
 else if (actualScreen == -3){
  
    int button=readButton();
    if (button == -1) button=readButton(); //second chance baby!!    
    
      if (button == 3){
        if (rgb[customColorPos] >= brightness-1) rgb[customColorPos]=brightness;
        else rgb[customColorPos]=rgb[customColorPos]+1;        
                
      }
      else if (button == 4){
        if (rgb[customColorPos] <= 0) rgb[customColorPos]=0;
        else rgb[customColorPos]=rgb[customColorPos]-1;        
      }
      else if (button == 5){
        if (customColorPos >= (colors-1)*3+2){
          customColorPos= (colors-1)*3;
          settingsSaved();
        }           
        else customColorPos=customColorPos+1;          
      }
      if (button != -1){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("SET CUSTOM BACKLIGHT");
        lcd.setCursor(1,2); 
        lcd.print("R       G       B "); 
        lcd.setCursor(0,3);
        lcd.print(rgb[(colors-1)*3]);        
        lcd.setCursor(8,3);
        lcd.print(rgb[(colors-1)*3+1]);
        lcd.setCursor(16,3);
        lcd.print(rgb[(colors-1)*3+2]);
        if (customColorPos == (colors-1)*3){
          lcd.setCursor(3,3);
          lcd.write((uint8_t)2);  
        }
        else if (customColorPos == (colors-1)*3+1){
          lcd.setCursor(11,3);
          lcd.write((uint8_t)2);        
        }
        else{
          lcd.setCursor(19,3);
          lcd.write((uint8_t)2);        
        }
        setBackLight(rgb[(colors-1)*3],rgb[(colors-1)*3+1],rgb[(colors-1)*3+2]);
        delay(100);        
      }
 } 
 
  if (button1 == ON){
    beep();
    if (actualScreen == -1 || actualScreen == -3) setBackLight(rgb[color*3],rgb[color*3+1],rgb[color*3+2]);    
    nextScreen(1);
    if (actualScreen == 2) LcdBarGraph tpsBar(&lcd, 20);
    else if (actualScreen == 4) init_big_font(&lcd);   
    lcd.clear();      
    execScreen(actualScreen);
    button1=OFF;    
  }
  else if(button2 == ON){
    beep();
    if (actualScreen == -1 || actualScreen == -3) setBackLight(rgb[color*3],rgb[color*3+1],rgb[color*3+2]);
    nextScreen(2);
    if (actualScreen == -1) loadArrowIcons();    
    lcd.clear();      
    execScreen(actualScreen);
    button2=OFF; 
  }
  else{
    if (actualScreen != -1 && actualScreen != -3) execScreen(actualScreen);    
  }

  
}

void button1ISR(){ 
  
  unsigned long interrupt_time = millis();  
  if (button1 == OFF && (interrupt_time - last_interrupt_time > debouncing)){
    button1=ON;      
  } 
  last_interrupt_time = interrupt_time;
}

void button2ISR(){ 
  
  unsigned long interrupt_time = millis();  
  if (button2 == OFF && (interrupt_time - last_interrupt_time > debouncing)){
    button2=ON;      
  } 
  last_interrupt_time = interrupt_time;
}
