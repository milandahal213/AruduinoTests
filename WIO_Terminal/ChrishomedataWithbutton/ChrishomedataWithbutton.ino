/*****************************
create a secrets.h file with the following contents

#define SECRET_SSID "your wifi ssid"
#define SECRET_PASS "your wifi password"

*****************************/
#include "secrets.h"

#include "AtWiFi.h"
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include"TFT_eSPI.h"
#include <HttpClient.h>
#include "RTC_SAMD51.h"
#include <Arduino.h>


TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClient client;

IPAddress server();//server address separated by commas like (1,7,105,19);
void(* resetFunc) (void) = 0;
int port1=80;
int resets = 0;
String line = "";
String tags[]={"Alarm","Barn","Daikin","Geo","TED","Tesla","Water","WestonSolar"};
int ind[8];
String holders[8];
String datetime[8];
String data[8];

String _datetime;
String _data;
String _title;
int i=0;
int screen=0;
boolean updatescreen=false;
DateTime now;
int prev_time, currenttime;
RTC_SAMD51 rtc;


void setup() {
    Serial.begin(115200);
    //while(!Serial); // Wait for Serial to be ready
    delay(1000);

    tft_setup();
    connect_WiFi();
    
    setupButton();

    rtc.begin();
    prev_time=rtc.now().unixtime(); 
    get_Data();
    show_Data(screen);
}


void loop() {

  currenttime=rtc.now().unixtime();
  if(rtc.now().unixtime()-prev_time>20){
    prev_time=rtc.now().unixtime();
    get_Data();
  }
  if (digitalRead(WIO_5S_LEFT) == LOW && screen >0)   { 
    delay(500);
    updatescreen=true; 
    screen=screen-1;   
    }
  else if (digitalRead(WIO_5S_RIGHT) == LOW && screen <7)  {
    delay(500); 
    updatescreen=true; 
    screen=screen+1;   
    }
  if(updatescreen==true){
    updatescreen=false;
    show_Data(screen);
  }



}

void setupButton(){
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
}
void get_Data(){
  if (client.connect(server, port1)) {
    client.println("GET /~crogers/data.txt HTTP/1.0");
    client.println("Content-type: text/plain");
    client.println("Connection: close");
    client.println();
  }
  else {
    resetFunc();
    return;
  }
  getReply();
  
  for(int i =0;i<8;i++){
    ind[i]=line.indexOf(tags[i]);                                   //getting the index of tags to split 
  }
  for(int i =0;i<8-1;i++){
    holders[i]=line.substring(ind[i]+tags[i].length() +2,ind[i+1]); //splitting data after {tags} : 
  }
  holders[7]=line.substring(ind[7]+tags[7].length()+2);             //getting the final data

  for(int i =0;i<8;i++){
    ind[i]=holders[i].indexOf(',');                                  //splitting the date and time from the data
    datetime[i]=holders[i].substring(0,ind[i]);
    data[i]=holders[i].substring(ind[i] + 1);
  }
}


void getReply(){
  while (client.connected()) {
    line = client.readStringUntil('\z');
    break;
      }
  client.stop();
  //Serial.println(line);
}




void show_Data(int screen){


    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(3);
    tft.drawString(_title, 5, 10);
    tft.setTextSize(2);
    tft.drawString(_datetime, 5, 40);
    tft.drawString(_data, 5, 70);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.drawString(tags[screen], 5,10);
    tft.setTextSize(2);
    tft.drawString(datetime[screen], 5,40);
    tft.drawString(data[screen], 5,70);
    _title=tags[screen];
    _datetime=datetime[screen];
    _data=data[screen];
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


}
void connect_WiFi(){
// SECRET_SSID, SECRET_PASS defined in secrets.h  
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(2000);
    Serial.print("Attempting to connect to " + String(SECRET_SSID));
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    while (WiFi.status() != WL_CONNECTED)  {
      delay(500);   // just sit here until you connect
      Serial.print(".");
      WiFi.begin(SECRET_SSID, SECRET_PASS);
    }
    Serial.print(" WiFi connected\r\nIP address: ");
    Serial.println(WiFi.localIP());
}
