#include"TFT_eSPI.h"
#include "RTC_SAMD51.h"
#include <Arduino_JSON.h>

TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
  DateTime now;
  RTC_SAMD51 rtc;
  int i =1;
  String check;
  String beginning="";
  String ending="";
  String loopCount;
  int prev_time, currenttime;
  String data="";
void setup() {
    Serial1.begin(115200);
    Serial.begin(115200);
    while(!Serial); // Wait for Serial to be ready
    delay(1000);
    tft_setup();
    rtc.begin();
}

void loop() {
  read_from_SPIKE();
 
}

void read_from_SPIKE(){
  while(!Serial1.available());
  data=Serial1.readStringUntil('\n');
  if(data=="incomingFunction"){
    prev_time=rtc.now().unixtime();
    Serial.println("prev_time");
    Serial.println(prev_time);
    Serial1.write("g2g");
    do{
      beginning=Serial1.readStringUntil('\n');
      ending+=beginning;
    }
    while(beginning.indexOf("done")<0&&(rtc.now().unixtime()-prev_time)<2);   

    if(beginning.indexOf("done")<0)      Serial1.write("False");
    else Serial1.write("True");
    }
  Serial.println(ending);
  decode_SPIKE(ending);
  ending="";
}

void decode_SPIKE(String request){
  String function;
  String arg;
  request=request.substring(0,request.length()-4); //4 is to remove "done"
  JSONVar myObject = JSON.parse(request);
  function = myObject["function"];
  Serial.println(function);
  if(function=="drawString") {
    tft.drawString((const char*) myObject["arg"][0],atoi((const char*) myObject["arg"][1]),atoi((const char*) myObject["arg"][2]));
    }
  else if(function== "fillScreen"){
    tft.fillScreen(atoi((const char*) myObject["arg"][0]));
    Serial.println(atoi((const char*) myObject["arg"][0]));
  }
  else if(function== "setTextSize"){
    tft.setTextSize(atoi((const char*) myObject["arg"][0]));
   }
   else if(function=="drawLine"){
    tft.drawLine(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
   }

}
void tft_setup(){
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
