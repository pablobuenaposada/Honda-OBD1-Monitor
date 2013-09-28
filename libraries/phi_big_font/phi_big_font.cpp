/*
Warning: PLEASE DO NOT REMOVE THIS COMMENT WHEN REDISTRIBUTING!
This is the second official release of the Phi-big-font library version
Released for Phi-2 shields for Arduino
User is encouraged to obtain a Phi-2 shield or is solely responsible for converting it to work on other shields or configurations.

Programmed by Dr. John Liu
Revision: 12/18/2011
Free software for educational and personal uses.
No warrantee!
Commercial use without authorization is prohibited.
Find details of the Phi-2 shield, and Phi-big-font or contact Dr. Liu at
http://liudr.wordpress.com/phi-2-shield/
http://liudr.wordpress.com/phi_big_font/
All rights reserved.

Updates:
12/18/2011: Modified to run on both arduino IDE 1.0 and pre-1.0 versions
06/17/2011: First release of the library. The array names for programmable characters on the LCD has been changed to aviod conflict with other libraries. 
*/
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <stdio.h>
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include "phi_big_font.h"

PROGMEM prog_char pbf_lcd_ch0[]={64,64,64,64,64,64,64,64,0};// 0, Empty
PROGMEM prog_char pbf_lcd_ch1[]={64,64,64,64,64,31,31,31,0};//1, Lower 3 lines 220
PROGMEM prog_char pbf_lcd_ch2[]={64,64,64,31,31,64,64,64,0};//2, middle 2 lines
PROGMEM prog_char pbf_lcd_ch3[]={64,64,64,31,31,31,31,31,0};//3, lower 5 lines
PROGMEM prog_char pbf_lcd_ch4[]={31,31,31,64,64,64,64,64,0};//4, upper 3 lines 223
PROGMEM prog_char pbf_lcd_ch5[]={31,31,31,64,64,31,31,31,0};//5, upper 3 lines + lower 3 lines
PROGMEM prog_char pbf_lcd_ch6[]={31,31,31,31,31,64,64,0};//6, upper 5 lines
PROGMEM prog_char pbf_lcd_ch7[]={31,31,31,31,31,31,31,31,0};//7, all 7 lines 219
PROGMEM const char *pbf_ch_item[] = {pbf_lcd_ch0, pbf_lcd_ch1, pbf_lcd_ch2, pbf_lcd_ch3, pbf_lcd_ch4, pbf_lcd_ch5, pbf_lcd_ch6, pbf_lcd_ch7};

LiquidCrystal *output_lcd;
byte font_35_sym[]={};
byte font_35_09[]={1,2,3,7,1,6, 1,3,0,0,7,0, 2,2,3,7,5,5, 2,2,3,5,5,7, 3,0,3,4,4,7, 3,2,2,5,5,7, 3,2,2,7,5,7, 2,2,3,0,0,7, 3,2,3,7,5,7, 3,2,3,5,5,7};

byte font_35_AZ[]={3,2,3,7,4,7, 3,2,3,7,5,3, 3,2,2,7,1,1, 3,2,1,7,1,6, 3,2,2,7,5,5, 3,2,2,7,4,4, 3,2,2,7,1,7, 3,0,3,7,4,7, 2,3,2,1,7,1, 2,2,3,3,1,7, 3,0,3,7,4,5, 3,0,0,7,1,1, 3,1,3,7,4,7, 3,2,3,7,0,7, 3,2,3,7,1,7, 3,2,3,7,4,4, 3,2,3,4,4,7, 3,2,3,7,4,3, 3,2,2,5,5,7, 2,3,2,0,7,0, 3,0,3,7,1,7, 3,0,3,6,1,6, 3,0,3,7,6,7, 3,0,3,3,4,3, 3,0,3,4,7,4, 2,2,3,3,5,1};

byte font_35_az[]={2,2,1,2,5,7, 3,1,0,7,1,6, 1,2,2,6,1,1, 0,1,3,6,1,7, 1,2,1,6,5,5, 0,1,2,4,7,4, 1,2,1,1,5,6, 3,1,0,7,0,7, 0,2,0,0,7,0, 0,0,2,3,1,6, 3,0,1,7,4,3, 3,0,0,6,1,1, 3,3,1,7,4,7, 3,2,1,7,0,7, 1,2,1,6,1,6, 3,2,1,7,4,0, 1,2,3,0,4,7, 1,2,2,7,0,0, 1,2,2,1,5,2, 1,3,1,0,6,1, 3,0,3,6,1,7, 3,0,3,6,1,6, 3,0,3,6,7,7, 3,0,3,3,4,3, 3,0,3,1,5,6, 2,2,3,3,5,1};

boolean inverted_big_font=false;

void render_big_char_top(char ch)
{
  if ((ch>='0')&&(ch<='9'))
  {
    for (byte i=0; i<3; i++)
    if (!inverted_big_font) output_lcd->write(font_35_09[(ch-'0')*6+i]);
    else output_lcd->write(7-font_35_09[(ch-'0')*6+i]);
  }
  else if ((ch>='A')&&(ch<='Z'))
  {
    for (byte i=0; i<3; i++)
    if (!inverted_big_font) output_lcd->write(font_35_AZ[(ch-'A')*6+i]);
    else  output_lcd->write(7-font_35_AZ[(ch-'A')*6+i]);
  }
  else if ((ch>='a')&&(ch<='z'))
  {
    for (byte i=0; i<3; i++)
    if (!inverted_big_font) output_lcd->write(font_35_az[(ch-'a')*6+i]);
    else output_lcd->write(7-font_35_az[(ch-'a')*6+i]);
  }
  if (!inverted_big_font) output_lcd->write(' ');
  else output_lcd->write(255);
}

void render_big_char_bot(char ch)
{
  if ((ch>='0')&&(ch<='9'))
  {
    for (byte i=0; i<3; i++)
    if (!inverted_big_font) output_lcd->write(font_35_09[(ch-'0')*6+i+3]);
    else output_lcd->write(7-font_35_09[(ch-'0')*6+i+3]);
  }
  else if ((ch>='A')&&(ch<='Z'))
  {
    for (byte i=0; i<3; i++)
    if (!inverted_big_font) output_lcd->write(font_35_AZ[(ch-'A')*6+i+3]);
    else output_lcd->write(7-font_35_AZ[(ch-'A')*6+i+3]);
  }
  else if ((ch>='a')&&(ch<='z'))
  {
    for (byte i=0; i<3; i++)
    if (!inverted_big_font) output_lcd->write(font_35_az[(ch-'a')*6+i+3]);
    else output_lcd->write(7-font_35_az[(ch-'a')*6+i+3]);
  }
  if (!inverted_big_font) output_lcd->write(' ');
  else output_lcd->write(255);
}

void render_big_char(char ch, byte loc_x, byte loc_y)
{
  output_lcd->setCursor(loc_x,loc_y);
  render_big_char_top(ch);
  output_lcd->setCursor(loc_x,loc_y+1);
  render_big_char_bot(ch);
}

void render_big_msg(char msg[], byte loc_x, byte loc_y)
{
  byte i=0;
  while(msg[i])
  {
    render_big_char(msg[i],loc_x+i*4, loc_y);
    i++;
  }
}

void render_big_number(int number, byte loc_x, byte loc_y)
{
  char msg[11];
  sprintf(msg,"%d",number);
  render_big_msg(msg, loc_x, loc_y);
}

//Display strings stored in PROGMEM. Provide the string name stored in PROGMEM to be displayed on the LCD's current cursor position.
void big_msg_lcd(char* msg_line, byte loc_x, byte loc_y)
{
  char msg_buffer[17];
  strcpy_P(msg_buffer,msg_line);
  msg_buffer[4]=0; 
  render_big_msg(msg_buffer, loc_x, loc_y);
}

void lcd_clear()
{
  if (!inverted_big_font) output_lcd->clear();
  else
  {
    output_lcd->setCursor(0,0);
    for (byte i=0;i<80;i++)
    {
      output_lcd->write(255);
    }
  }
}

void invert_big_font(boolean inv)
{
  inverted_big_font=inv;
}

void init_big_font(LiquidCrystal *l)
{
  byte ch_buffer[10]; // This buffer is required for custom characters on the LCD.
  output_lcd=l;
  for (int i=0;i<8;i++)
  {
    strcpy_P((char*)ch_buffer,(char*)pgm_read_word(&(pbf_ch_item[i])));
    output_lcd->createChar(i, ch_buffer);
  }
}

void display_img(byte msg[])
{
  output_lcd->setCursor(0,0);
  for (byte i=0;i<80;i++)
  {
    output_lcd->write(msg[i]);
  }
}
