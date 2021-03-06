#include "TFT_eSPI.h"           // change this to the LCD library for your board

TFT_eSPI tft;

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

int x_pos=20;
int y_pos=120;
int x_pos_p=20;
int y_pos_p=120;

int gx_pos=200;
int gy_pos=120;
int gx_pos_p=200;
int gy_pos_p=120;

int score=0;
int life=3;

 int dir=1;

char C_score[8];
char C_life[8];
const unsigned char mario_yellow[] = {
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xF0  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x10  , 0xFF  , 0x0F  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0xF0  , 0x10  , 0xFF  , 0x0F  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0xF0  , 0x10  , 0xFF  , 0x0F  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0xF0  , 0x10  , 0xFF  , 0x0F  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  ,
0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  ,
0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  ,
0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  ,
0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 
  };

  const unsigned char mario_red[] = {
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xF0  , 0xFF  , 0xF0  , 0xF0  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xF0  , 0xFF  , 0xF0  , 0xF0  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xF0  , 0xFF  , 0xF0  , 0xF0  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xF0  , 0xFF  , 0xF0  , 0xF0  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  ,
  };
  const unsigned char mario_brown[] = {
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0x00  , 0x0F  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0x00  , 0x0F  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0x00  , 0x0F  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0x00  , 0x0F  , 0xF0  , 0xFF  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  , 0x0F  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  , 0x0F  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  , 0x0F  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0x00  , 0x0F  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x0F  , 0xFF  , 0x00  , 0xF0  , 0x00  , 0xF0  ,
0x00  , 0x00  , 0x0F  , 0xFF  , 0x00  , 0xF0  , 0x00  , 0xF0  ,
0x00  , 0x00  , 0x0F  , 0xFF  , 0x00  , 0xF0  , 0x00  , 0xF0  ,
0x00  , 0x00  , 0x0F  , 0xFF  , 0x00  , 0xF0  , 0x00  , 0xF0  ,
0x00  , 0x00  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xF0  , 0x00  ,
0x00  , 0xFF  , 0xFF  , 0x0F  , 0xFF  , 0x0F  , 0x0F  , 0x00  ,
0x00  , 0xFF  , 0xFF  , 0x0F  , 0xFF  , 0x0F  , 0x0F  , 0x00  ,
0x00  , 0xFF  , 0xFF  , 0x0F  , 0xFF  , 0x0F  , 0x0F  , 0x00  ,
0x00  , 0xFF  , 0xFF  , 0x0F  , 0xFF  , 0x0F  , 0x0F  , 0x00  ,
0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xF0  , 0xFF  , 0x00  , 0xF0  ,
0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xF0  , 0xFF  , 0x00  , 0xF0  ,
0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xF0  , 0xFF  , 0x00  , 0xF0  ,
0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xF0  , 0xFF  , 0x00  , 0xF0  ,
0x00  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0xF0  ,
0x00  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0xF0  ,
0x00  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0xF0  ,
0x00  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  , 0xF0  ,
0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0x00  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0xF0  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
  };

    const unsigned char goomba_brown[] = {
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0xF0  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x0F  , 0x00  ,
0x00  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0x00  ,
0x00  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0x00  ,
0x00  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0x00  ,
0x00  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0x00  ,
0xF0  , 0xFF  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x0F  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  ,
0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0xFF  ,
0xF0  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0xFF  , 0x0F  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
  };

 const unsigned char goomba_black[] = {
  0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  ,
0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  ,
0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  ,
0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0x00  , 0x00  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x00  ,
0x00  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x00  ,
0x00  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x00  ,
0x00  , 0xFF  , 0x00  , 0x00  , 0x00  , 0x00  , 0xFF  , 0x00  ,
0xF0  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  ,
0xF0  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x0F  ,
0x00  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x00  ,
0x00  , 0xFF  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0xFF  , 0x00  ,
 };

  const unsigned char goomba_yellow[] = {
 0x00 , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x00  , 0x00  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0xF0  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0xF0  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0xF0  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x0F  , 0x0F  , 0xF0  , 0xF0  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0x0F  , 0xF0  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xF0  , 0xFF  , 0xFF  , 0x0F  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0xFF  , 0xFF  , 0xFF  , 0xFF  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xFF  , 0xFF  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0xF0  , 0x0F  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  , 0x00  ,
    
 };
  void setup(){

    pinMode(WIO_BUZZER, OUTPUT);
    Serial.begin(115200);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_GREEN);

  delay(1000);
  digitalWrite(LCD_BACKLIGHT, LOW);
  delay(1000);
  digitalWrite(LCD_BACKLIGHT, HIGH);
  tft.setTextSize(2);


  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  drawMario();
  tft.setTextSize(3);
  tft.drawString("SUPER MARIO",50,10);
  tft.setTextSize(2);
  tft.drawString("milan's version",50,40);
  while(digitalRead(WIO_KEY_A) == HIGH);
  tft.fillScreen(TFT_GREEN);
  drawMario();
  }


void loop(){

  if (digitalRead(WIO_5S_UP) == LOW) {
  up();

   }
   else if (digitalRead(WIO_5S_DOWN) == LOW) {
    
   }
   else if (digitalRead(WIO_5S_LEFT) == LOW) {
   moveBack();
   }
   else if (digitalRead(WIO_5S_RIGHT) == LOW) {
    moveForward();
   }
   else if (digitalRead(WIO_5S_PRESS) == LOW) {
   }
  moveGoomba();
  drawGoomba();
  collisonCase();
  showScore();
  delay(10);
  
}


void drawGoomba(){
  tft.drawXBitmap(gx_pos_p,gy_pos_p, goomba_brown, 64, 64, TFT_GREEN);
  tft.drawXBitmap(gx_pos_p,gy_pos_p, goomba_black, 64, 64, TFT_GREEN);
  tft.drawXBitmap(gx_pos_p,gy_pos_p, goomba_yellow, 64, 64, TFT_GREEN);
  
  tft.drawXBitmap(gx_pos,gy_pos, goomba_brown, 64, 64, TFT_MAROON);
  tft.drawXBitmap(gx_pos,gy_pos, goomba_black, 64, 64, TFT_BLACK);
  tft.drawXBitmap(gx_pos,gy_pos, goomba_yellow, 64, 64, TFT_YELLOW); 
}

void drawMario(){
  tft.drawXBitmap(x_pos_p,y_pos_p, mario_yellow, 64, 64, TFT_GREEN);
  tft.drawXBitmap(x_pos_p,y_pos_p, mario_red, 64, 64, TFT_GREEN);
  tft.drawXBitmap(x_pos_p,y_pos_p, mario_brown, 64, 64, TFT_GREEN);
  
  tft.drawXBitmap(x_pos,y_pos, mario_yellow, 64, 64, TFT_YELLOW);
  tft.drawXBitmap(x_pos,y_pos, mario_red, 64, 64, TFT_RED);
  tft.drawXBitmap(x_pos,y_pos, mario_brown, 64, 64, TFT_BLACK); 
}

void up(){
  for (int i=6; i >0; i--){
    dir=1;
      y_pos_p=y_pos;
      x_pos_p=x_pos;
      y_pos=y_pos-i*5;
      drawMario();
      moveGoomba();
    drawGoomba();
      collisonCase();
      delay(10);
      
  }

    for (int i=1; i <7; i++){
      dir=-1;
      y_pos_p=y_pos;
      x_pos_p=x_pos;
      y_pos=y_pos+i*5;
      drawMario();
        moveGoomba();
    drawGoomba();
      collisonCase();
      delay(10);
  }
dir=1;

}

void moveGoomba(){
  gx_pos_p=gx_pos;
  gx_pos=gx_pos-10;

  if(gx_pos<0){
    gx_pos=300;
  }
}

void moveForward(){
  x_pos_p=x_pos;
  y_pos_p=y_pos;
  x_pos=x_pos+7;
  drawMario();

  
}

void moveBack(){
  x_pos_p=x_pos;
  y_pos_p=y_pos;
  x_pos=x_pos-7;
  drawMario();
}

void collisonCase(){
  if(gx_pos< (x_pos+50) && gy_pos < (y_pos+50)){
      if(dir==1){
      life=life-1;
      gx_pos_p=gx_pos;
      gx_pos=400;
      drawGoomba();
       drawMario();
        analogWrite(WIO_BUZZER, 128);
        delay(1000);
        analogWrite(WIO_BUZZER, 0);
        delay(1000);
      }
  }
  else if ( gx_pos< (x_pos+32) && gy_pos > (y_pos+50)){
      score=score+1;
      gx_pos_p=gx_pos;
      gx_pos=400;
      drawGoomba();
       drawMario();
      }
}

void showScore(){
    tft.drawString("SCORE:",120,10);
  tft.drawString(itoa(score,C_score,10),190,10);
  tft.drawString("LIFE:",120,30);
  tft.drawString(itoa(life,C_life,10),190,30);
  if (life<1){
      tft.setTextSize(3);
    tft.fillScreen(TFT_GREEN);
    tft.drawString("GAME OVER",100,50);
    tft.drawString(itoa(score,C_score,10),120,80);

    while(digitalRead(WIO_KEY_A) == HIGH);
    tft.setTextSize(2);
    tft.fillScreen(TFT_GREEN);
    life=3;
    score=0;
  }

}
