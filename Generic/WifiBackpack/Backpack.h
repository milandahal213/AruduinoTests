#ifndef Backpack_h
#define Backpack_h

#include "Graphics.h"

#include "Arduino.h"

class Backpack
{
  public:
    Backpack(int baudrate);
    void start();
    void checkwifi();
    void connectwifi();
    void tft_setup();
    void lookout();
    void lookout1();
    void decode_message(String request);
    private:
    String request;
    String _ret;
    int _baudrate;
    const char *_ssid;
    const char *_password;
    String _wifi;
    const char *host;
    int _port;
    char *_cport;
    int slash[3];
    int colon;
    const char *_url;
    char _proto[10];
    char _host[100];
    char _path[100];
    String line;
  unsigned long timeout;
  uint32_t taketime;
  

};

#endif
