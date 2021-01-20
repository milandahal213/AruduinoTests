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

}
  /*while(!Serial1.available());
  Serial.println("start");
  check = Serial1.readStringUntil('\n');
  Serial.println("recvd first message");
  if(check=="incomingFunction"){
     Serial1.println("TU");
     Serial.println("sent TU");
     while(!Serial1.available());
     loopCount=Serial1.readStringUntil('\n');
     Serial.println("loopCount");
     Serial.println(loopCount);
     Serial.println("loopCount.toInt()");
     Serial.println(loopCount.toInt());
     Serial1.println("pass");
     Serial.println("sent pass");
     for (int j=0;j<loopCount.toInt();j++){
        Serial.println("inside the loop");
        
        while(!Serial1.available());
        beginning=Serial1.readStringUntil('\n');
        Serial1.println("pass");
        ending=ending+beginning;
      }
   beginning="";
   Serial.println(ending);
  /*if(Serial1.available()){
   beginning = Serial1.readStringUntil('\n');
   Serial.println("first");
   Serial1.write("fpass");
   while(!Serial1.available());
   ending = Serial1.readStringUntil('\n');
   Serial.println(beginning+ending);
   Serial.println("done");
  }
*/
  //}
  //get_Data();
  //display_Data();
//}

 /*void get_Data(){
  if (client.connect(server, port1)) {
    client.println("GET /~crogers/data.txt HTTP/1.0");
    client.println("Content-type: text/plain");
    client.println("Connection: close");
    client.println();
  }
  else {
    connect_WiFi();
    resets += 1;
    return;
  }
  getReply();
  
 
 }




void show_Data(){

  Serial.println(line);
  for(int i =0;i<8;i++){
    ind[i]=line.indexOf(tags[i]);
      }
  for(int i =0;i<8-1;i++){
    holders[i]=line.substring(ind[i],ind[i+1]);
  }
  for( int i=0;i <8; i++){
    
    tft.setTextColor(TFT_GREEN);
    tft.drawString(_holders[i], 5, 10*(i+1));
    tft.setTextColor(TFT_BLACK);
    tft.drawString(holders[i], 5,10*(i+1));
    _holders[i]=holders[i];
  }
*/
//}

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
