/*
Programmed by Dr. John Liu
Revision: 04/18/2011
Free software for educational and personal uses.
No warrantee!
Commercial use without authorization is prohibited.
Find details of the Phi-1 shield, Phi-2 shield or contact Dr. Liu at
http://liudr.wordpress.com/phi-1-shield/
http://liudr.wordpress.com/phi-2-shield/
All rights reserved.
*/

PROGMEM prog_char msg_00[]="LCD big fonts V4";
PROGMEM prog_char msg_01[]="Dr.Liu 03/22/12";
PROGMEM prog_char msg_02[]="http://liudr.";
PROGMEM prog_char msg_03[]="wordpress.com";

PROGMEM prog_char dow_00[]="SUN";
PROGMEM prog_char dow_01[]="MON";
PROGMEM prog_char dow_02[]="TUE";
PROGMEM prog_char dow_03[]="WED";
PROGMEM prog_char dow_04[]="THU";
PROGMEM prog_char dow_05[]="FRI";
PROGMEM prog_char dow_06[]="SAT";
PROGMEM const char *dow_item[] = {dow_00, dow_01, dow_02, dow_03, dow_04, dow_05, dow_06};

PROGMEM prog_char month_00[]="JAN";
PROGMEM prog_char month_01[]="FEB";
PROGMEM prog_char month_02[]="MAR";
PROGMEM prog_char month_03[]="APR";
PROGMEM prog_char month_04[]="MAY";
PROGMEM prog_char month_05[]="JUN";
PROGMEM prog_char month_06[]="JUL";
PROGMEM prog_char month_07[]="AUG";
PROGMEM prog_char month_08[]="SEP";
PROGMEM prog_char month_09[]="OCT";
PROGMEM prog_char month_10[]="NOV";
PROGMEM prog_char month_11[]="DEC";
PROGMEM const char *month_item[] = {month_00, month_01, month_02, month_03, month_04, month_05, month_06, month_07, month_08, month_09, month_10, month_11};
#ifdef phi_1_shield
//Phi-1 shield definitions

#define buzzer 16
#define ch1 16
#define ch1_analog 2
#define led 17
#define ch2 17
#define ch2_analog 3
#define btn_u 5
#define btn_d 10
#define btn_l 11
#define btn_r 3
#define btn_b 14
#define btn_a 15

#define LCD_RS 8
#define LCD_EN 9
#define LCD_D4 7
#define LCD_D5 6
#define LCD_D6 2
#define LCD_D7 4

#endif

#ifdef phi_2_shield
//Phi-2 shield definitions

#define buzzer 16
#define btn_u 5
#define btn_d 10
#define btn_l 11
#define btn_r 4
#define btn_b 14
#define btn_a 15

#define LCD_RS 8
#define LCD_EN 9
#define LCD_D4 7
#define LCD_D5 6
#define LCD_D6 2
#define LCD_D7 3

#endif

