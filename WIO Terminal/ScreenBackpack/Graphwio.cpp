#include "Graphwio.h"

#include "TFT_eSPI.h"
#include "RTC_SAMD51.h"
#include <Arduino_JSON.h>


#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

TFT_eSPI tft;
DateTime now;
RTC_SAMD51 rtc;

  int i =1;
  String check="";
  String beginning="";
  String ending="";
  String loopCount="";
  int prev_time, currenttime;
  String data="";

Graphwio::Graphwio(int baudrate) {
    _baudrate=baudrate;
}

void Graphwio::start() {
    while (!Serial) {
    Serial.begin(_baudrate);
    };
    rtc.begin();
    tft_setup();
}

void Graphwio::tft_setup(){
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

 

void Graphwio::lookout(){
  if (Serial.available() > 0){
    prev_time=rtc.now().unixtime();
    do{
      beginning=Serial.readStringUntil('\n');
      ending+=beginning;
    }
    while(beginning.indexOf("done")<0&&(rtc.now().unixtime()-prev_time)<2);   
    if(beginning.indexOf("done")<0)
      {
        Serial.write("False");
      }
    else {
      Serial.write("True");
      }
      decode_message(ending);
      Serial.println(ending);
      ending="";
    }
}
void Graphwio::decode_message(String request){
  String function;
  String lib;
  String arg;
  request=request.substring(0,request.length()-4); //4 is to remove "done"
  JSONVar myObject = JSON.parse(request);

  function = myObject["function"];
  lib=myObject["lib"];

  if(lib=="graphics"){
  if(function=="drawString") {
    tft.drawString((const char*) myObject["arg"][0],atoi((const char*) myObject["arg"][1]),atoi((const char*) myObject["arg"][2]));
    }
  else if(function== "fillScreen"){
    tft.fillScreen(atoi((const char*) myObject["arg"][0]));
  }
  else if(function== "setTextSize"){
    tft.setTextSize(atoi((const char*) myObject["arg"][0]));
   }
   else if(function=="drawLine"){
    tft.drawLine(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
   }
   else if(function=="drawPixel"){
   tft.drawPixel(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]));
   }

   else if(function=="drawRect"){
   tft.drawRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
   }
   else if(function=="fillRect"){
   tft.fillRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
      }
   else if(function=="drawCircle"){
   tft.drawCircle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]));
      }
   else if(function=="fillCircle"){
   tft.fillCircle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]));
      }
   else if(function=="drawTriangle"){
   tft.drawTriangle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]), atoi((const char*) myObject["arg"][6]));
       }
   else if(function=="fillTriangle"){
    tft.fillTriangle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]), atoi((const char*) myObject["arg"][6]));
     }
   else if(function=="drawRoundRect"){
  tft.drawRoundRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]));
     }
   else if(function=="fillRoundRect"){
  tft.fillRoundRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]));
   }
  }
  
}
