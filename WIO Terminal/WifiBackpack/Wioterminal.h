#ifndef Wioterminal_h
#define Wioterminal_h

#include "Arduino.h"
#include <rpcWiFi.h>

#include"TFT_eSPI.h"
#include "RTC_SAMD51.h"

#include <Arduino_JSON.h>

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

class Wioterminal
{
  public:
    Wioterminal(int baudrate);
    void start();
    void tft_setup();
    void lookout();
    void decode_message(String request);
    private:
    String _ret;
    int _baudrate;
    char *_ssid;
    char *_password;
    const char *host;
    int _port;
    const char *_url;
    String line;
  unsigned long timeout;
  uint32_t taketime;
};

#endif
