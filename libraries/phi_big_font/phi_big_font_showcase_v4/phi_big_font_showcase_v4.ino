/*
Warning: PLEASE DO NOT REMOVE THIS COMMENT WHEN REDISTRIBUTING!
This is an example showcasing the first official release of the Phi-big-font library version 20110418
Released for Phi-2 shield for Arduino
User is encouraged to obtain a Phi-2 shield or is solely responsible for converting it to work on other shields or configurations.

Programmed by Dr. John Liu
Revision: 03/22/2012
Free software for educational and personal uses.
No warrantee!
Commercial use without authorization is prohibited.
Find details of the Phi-2 shield, and Phi-big-font or contact Dr. Liu at
http://liudr.wordpress.com/phi-2-shield/
http://liudr.wordpress.com/phi_big_font/
All rights reserved.
*/

#define phi_2_shield // Define this if you are using the phi 2 shield
//#define phi_1_shield // Define this if you are using the phi 1 shield
#define lcd_20X4 // Define this if you have a 20 X 4 display.
//#define lcd_16X2 // Define this if you have a 16 X 2 display.
#include <LiquidCrystal.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <phi_big_font.h>
#include "defs.h"

LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7); // Create the lcd object

byte img1[]={
0,0,3,3,4,4,4,3,3,0,0,0,3,3,4,4,4,3,3,0,
0,6,1,4,4,7,4,4,1,6,4,6,1,4,4,4,4,4,1,6,
0,3,4,1,1,7,1,1,4,3,1,3,4,1,1,1,1,1,4,3,
0,0,6,6,1,1,1,6,6,0,0,0,6,6,1,1,1,6,6,0
};// line 0, 2, 1, 3 order.

boolean inverted=false;

void setup()
{
  lcd.begin(20, 4);
  init_big_font(&lcd);
  show_credit();
  
#ifdef lcd_20X4
  show_arduino();
#endif
}

void loop()
{
#ifdef lcd_20X4
  demo_20X4();
#endif

#ifdef lcd_16X2
  demo_16X2();
#endif
}

void demo_20X4() //Asks you for password for a given number of trials
{
  char msg[4];

// Animate message sideways (not scrolling yet)  
  for (byte i=0;i<5;i++)
  {
    lcd_clear();
    render_big_msg("Big", i,0);
    render_big_msg("Font", 4-i,2);
    delay(1000);
  }
  
  inverted=!inverted;
  invert_big_font(inverted);
  for (byte i=0;i<5;i++)
  {
    lcd_clear();
    render_big_msg("Big", 4-i,0);
    render_big_msg("Font", i,2);
    delay(1000);
  }
  delay(2000);
  inverted=!inverted;
  invert_big_font(inverted);

// Animate message up (with half characters)
  char msg1[]="Hello";
  byte x=0;
  byte j=0;
  for (int i=3;i>=-1;i--)
  {
    lcd_clear();
    switch (i)
    {
      case -1:
      j=0;
      lcd.setCursor(x,0);
      while(msg1[j])
      {
        render_big_char_bot(msg1[j]);
        j++;
      }
      delay(1000);
      break;
      
      case 3:
      j=0;
      lcd.setCursor(x,3);
      while(msg1[j])
      {
        render_big_char_top(msg1[j]);
        j++;
      }
      delay(1000);
      break;
      
      default:
      render_big_msg(msg1,0,i);
      delay(1000);
      break;
    }
  }
  delay(1000);

// Show messages inside PROGMEM
  lcd_clear();
  for (byte i=0;i<7;i++)
  {
    big_msg_lcd(dow_00+i*4, 0,0);
    lcd.setCursor(13,0);
    msg_lcd(dow_00+i*4);
    delay(1000);
  }
  
  for (byte i=0;i<12;i++)
  {
    big_msg_lcd(month_00+i*4,8,2);
    lcd.setCursor(13,0);
    msg_lcd(month_00+i*4);
    delay(1000);
  }

// Display numbers
  lcd_clear();
  for (byte i=0;i<20;i++)
  {
    lcd.setCursor(0,0);
    render_big_number(i,0,0);
    delay(400-i*6);
  }
  
  lcd_clear();
  render_big_msg("Big",0,0);
  render_big_msg("0To9",4,2);
  delay(1000);

// Show all numbers  
  lcd_clear();
  for (byte i='0';i<='9';i++)
  {
    render_big_char(i,(i-'0')%5*4, ((i-'0')/5%2)*2);
    lcd.setCursor(19,0);
    lcd.write(i);
    delay(500);
  }
  delay(1000);

// Show all characters
  lcd_clear();
  render_big_msg("Big",0,0);
  render_big_msg("ATOZ",4,2);
  delay(1000);
  
  lcd_clear();
  for (byte i='A';i<='Z';i++)
  {
    if (!((i-'A')%10)) lcd_clear();
    render_big_char(i,(i-'A')%5*4, ((i-'A')/5%2)*2);
    lcd.setCursor(19,0);
    lcd.write(i);
    delay(500);
  }
  delay(1000);

  lcd_clear();
  render_big_msg("Big",0,0);
  render_big_msg("atoz",4,2);
  delay(1000);
  
  lcd_clear();
  for (byte i='a';i<='z';i++)
  {
    if (!((i-'a')%10)) lcd_clear();
    render_big_char(i,(i-'a')%5*4, ((i-'a')/5%2)*2);
    lcd.setCursor(19,0);
    lcd.write(i);
    delay(500);
  }
  delay(1000);
  
  lcd_clear();
  render_big_msg("DrLiu",0,0);
  render_big_msg("MAR12",0,2);
  delay(2000);

// Invert display polarity for the next loop.
  inverted=!inverted;
  invert_big_font(inverted);
}

void demo_16X2() //Asks you for password for a given number of trials
{
  char msg[4];

  lcd_clear();
  render_big_msg("Big", 0,0);
  delay(2000);
  
  render_big_msg("Font", 0,0);
  delay(2000);
  
  inverted=!inverted;
  invert_big_font(inverted);
  lcd_clear();
  render_big_msg("Big", 0,0);
  delay(2000);
  
  render_big_msg("Font", 0,0);
  delay(2000);
  

  inverted=!inverted;
  invert_big_font(inverted);

  char msg1[]="HI";
  byte x=0;
  byte j=0;
  render_big_msg(msg1,3,0);
  delay(1000);

// Show messages inside PROGMEM
  lcd_clear();
  for (byte i=0;i<7;i++)
  {
    big_msg_lcd(dow_00+i*4, 0,0);
    lcd.setCursor(13,0);
    msg_lcd(dow_00+i*4);
    delay(1000);
  }
  
  for (byte i=0;i<12;i++)
  {
    big_msg_lcd(month_00+i*4,0,0);
    lcd.setCursor(13,0);
    msg_lcd(month_00+i*4);
    delay(1000);
  }

// Display numbers
  lcd_clear();
  for (byte i=0;i<20;i++)
  {
    lcd.setCursor(0,0);
    render_big_number(i,0,0);
    delay(400-i*6);
  }
  
  lcd_clear();
  render_big_msg("Big",0,0);
  delay(2000);
  render_big_msg("0To9",0,0);
  delay(2000);

// Show all numbers  
  lcd_clear();
  for (byte i='0';i<='9';i++)
  {
    if (!((i-'0')%4)) lcd_clear();
    render_big_char(i,(i-'0')%4*4, 0);
    lcd.setCursor(15,0);
    lcd.write(i);
    delay(500);
  }
  delay(1000);

// Show all characters
  lcd_clear();
  render_big_msg("Big",0,0);
  delay(2000);
  render_big_msg("ATOZ",0,0);
  delay(2000);
  
  lcd_clear();
  for (byte i='A';i<='Z';i++)
  {
    if (!((i-'A')%4)) lcd_clear();
    render_big_char(i,(i-'A')%4*4, 0);
    lcd.setCursor(15,0);
    lcd.write(i);
    delay(500);
  }
  delay(1000);

  lcd_clear();
  render_big_msg("Big",0,0);
  delay(2000);
  render_big_msg("atoz",0,0);
  delay(2000);
  
  lcd_clear();
  for (byte i='a';i<='z';i++)
  {
    if (!((i-'a')%4)) lcd_clear();
    render_big_char(i,(i-'a')%4*4, 0);
    lcd.setCursor(15,0);
    lcd.write(i);
    delay(500);
  }
  delay(1000);
  
  lcd_clear();
  render_big_msg("LIU",2,0);
  delay(2000);
  render_big_msg("0312",0,0);
  delay(2000);

// Invert display polarity for the next loop.
  inverted=!inverted;
  invert_big_font(inverted);
}

//Utility functions
void msg_lcd(char* msg_line)
{
  char msg_buffer[17];
  strcpy_P(msg_buffer,msg_line); 
  lcd.print(msg_buffer);
}

void show_credit()
{
  // Display credits
  lcd.clear();
  msg_lcd(msg_00);
  lcd.setCursor(0,1);
  msg_lcd(msg_01);
  delay(2000);
  lcd.clear();
  msg_lcd(msg_02);
  lcd.setCursor(0,1);
  msg_lcd(msg_03);
  delay(2000);
  lcd.clear();
}

void show_arduino()
{
  display_img(img1);
  delay(5000);
}
