#ifndef Graphwio_h
#define Graphwio_h

#include "Arduino.h"


#include"TFT_eSPI.h"
#include "RTC_SAMD51.h"

#include <Arduino_JSON.h>

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

class Graphwio
{
  public:
    Graphwio(int baudrate);
    void start();
    void tft_setup();
    void read_from_SPIKE();
    void decode_message(String request);
    private:
    int _baudrate;
    
};

#endif
