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
    char *_cport;
    int f[3];
    const char *_url;
    char _proto[10];
    char _host[30];
    char _path[30];
    String line;
  unsigned long timeout;
  uint32_t taketime;
};

#endif
