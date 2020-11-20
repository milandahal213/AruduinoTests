#include "Wioterminal.h"
#include <rpcWiFi.h>
#include "TFT_eSPI.h"
#include "RTC_SAMD51.h"
#include <Arduino_JSON.h>


#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

TFT_eSPI tft;
DateTime now;
RTC_SAMD51 rtc;
WiFiClient client;
int i =1;
String check="";
String beginning="";
String ending="";
String loopCount="";
int prev_time, currenttime;
String data="";
int func=0;

Wioterminal::Wioterminal(int baudrate) {
    _baudrate=baudrate;
}

void Wioterminal::start() {
    while (!Serial) {
    Serial.begin(_baudrate);
    };
    rtc.begin();
    tft_setup();
    
}

void Wioterminal::tft_setup(){
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_GREEN);

  delay(1000);
  // Turning off the LCD backlight
  digitalWrite(LCD_BACKLIGHT, LOW);
  delay(1000);
  // Turning on the LCD backlight
  digitalWrite(LCD_BACKLIGHT, HIGH);

  tft.setTextSize(1);
}

 

void Wioterminal::lookout(){
  if (Serial.available() > 0){
    
    prev_time=rtc.now().unixtime();
    do{
      beginning=Serial.readString();
      ending+=beginning;
      }
    while(ending.indexOf("done")<0&&(rtc.now().unixtime()-prev_time)<2);   
    if(ending.indexOf("done")<0)
      {
        Serial.write("False");
      }
    else {
         _ret=" ";
         decode_message(ending);
         _ret=_ret+"True";
        Serial.println(_ret);
      }
      ending="";
      Serial.flush();
    }
}
void Wioterminal::decode_message(String request){
  String function;
  String lib;
  String arg;
  
  request=request.substring(0,request.length()-4); //4 is to remove "done"
  JSONVar myObject = JSON.parse(request);

  func = atoi((const char*) myObject["function"]);
  lib=myObject["lib"];

  if(lib=="graphics"){

    switch (func){
    case 1: //"drawString"
    tft.drawString((const char*) myObject["arg"][0],atoi((const char*) myObject["arg"][1]),atoi((const char*) myObject["arg"][2]));
    _ret="True";
    break;
    
    case 2: //"fillScreen"
    tft.fillScreen(atoi((const char*) myObject["arg"][0]));
    _ret="True";
    break;
    
    case 3: //"setTextSize"
    tft.setTextSize(atoi((const char*) myObject["arg"][0]));
    _ret="True";
    break;
    
    case 4: //"drawLine"
    tft.drawLine(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
    _ret="True";    
    break;
    
   case 5: //"drawPixel"
   tft.drawPixel(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]));
   _ret="True";
   break;
    
   case 6: //"drawRect"
   tft.drawRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
   _ret="True";
   break;
   
   case 7: //"fillRect"
   tft.fillRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
   _ret="True";
   break;
      
   case 8: //"drawCircle"
   tft.drawCircle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]));
   _ret="True";
   break;
       
   case 9: //"fillCircle"
   tft.fillCircle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]));
   _ret="True";
   break;
      
   case 10: //"drawTriangle"
   tft.drawTriangle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]), atoi((const char*) myObject["arg"][6]));
   _ret="True";
   break;
     
   case 11: //"fillTriangle"
    tft.fillTriangle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]), atoi((const char*) myObject["arg"][6]));
    _ret="True";
    break;
     
   case 12: //"drawRoundRect"
   tft.drawRoundRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]));
   _ret="True";
   break;
     
   case 13: //"fillRoundRect")
   tft.fillRoundRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]));
   _ret="True";
   break;

    default: 
    break;
  }
  }

  else if(lib=="wifi"){

     int m,n;
    switch (func){
    case 1: //"Connect_wifi"
    
    WiFi.begin((const char*) myObject["arg"][0],(const char*) myObject["arg"][1]);
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin((const char*) myObject["arg"][0],(const char*) myObject["arg"][1]);
       
    }
    _ret="Connected";
    break;
    
    case 2: //"get"
        line="";
         _url=(const char*) myObject["arg"][0];

         for(m=0,n=0;m<strlen(_url);m++){
            if(_url[m]=='/'){
              f[n]=m;
              n+=1;
              if(n==3){
                break;
              }
            }
          }

          (String(_url).substring(0,f[0])).toCharArray(_proto,f[0]); 
          (String(_url).substring(f[1]+1,f[2])).toCharArray(_host,f[2]-f[1]);
          (String(_url).substring(f[2])).toCharArray(_path,strlen(_url)-f[2]+1);
         
         //_host="173.76.105.19";
          tft.fillScreen(32);
          tft.drawString(_host,10,140);
          tft.drawString(_proto,10,180);
          tft.drawString(_path,10,200);
    
           if(strcmp(_proto,"https")==0){
              _port=443;
              tft.drawString("port 443 set",80,20);
           }
           else if (strcmp(_proto,"http")==0){
              _port=80;
              tft.drawString("port 80 set",10,20);
           }
           else{
            _ret="Use http or https with your url";
            break;
            }
            
          if (!client.connect(_host, _port))
          {
          Serial.println("connection failed");
          tft.drawString("Connectio failed",50,10);
          }
           client.println("GET " + String(_url) +" HTTP/1.0");
          client.println("Host: " + String(_host));
          client.println("Content-type: application/json");
          client.println( "Connection: close");
          client.println();
          timeout = millis();
          while (client.available() == 0) {
          if (millis() - timeout > 5000) {
              _ret=">>> Client Timeout !";
              client.stop();
              break;
            }
           }
           taketime = millis();
         while (client.available())
            {
            line+= client.readStringUntil('\r');
            }
          _ret+=line;
          break;
     
          default: 
          break;
  }
}
}
