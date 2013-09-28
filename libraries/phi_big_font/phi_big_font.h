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

#include <LiquidCrystal.h>

void invert_big_font(boolean inv);
void lcd_clear();
void big_msg_lcd(char* msg_line, byte loc_x, byte loc_y);
void render_big_number(int number, byte loc_x, byte loc_y);
void render_big_msg(char msg[], byte loc_x, byte loc_y);
void render_big_char(char ch, byte loc_x, byte loc_y);
void render_big_char_bot(char ch);
void render_big_char_top(char ch);
void init_big_font(LiquidCrystal *l);
void display_img(byte msg[]);
