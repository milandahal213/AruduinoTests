#include"Graphics.h"
Graphics graph;


#include "Backpack.h"
#include <rpcWiFi.h>            // change this to the wifi library for your board
#include <WiFiClientSecure.h>   // change this to the wifi Client for your board for SSL
#include "TFT_eSPI.h"           // change this to the LCD library for your board
#include "RTC_SAMD51.h"         // change this to the RTC library
#include <Seeed_FS.h>           // change this to the File system library for your board
#include "SD/Seeed_SD.h"        // SD card library for your board
#include <SPI.h>

#include <Arduino_JSON.h>


 // create objects 
File myFile;                  
WiFiClientSecure client;
WiFiClient client1;
JSONVar wifi_cred;
TFT_eSPI tft;
DateTime now;
RTC_SAMD51 rtc;


#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD


int i =1;
String check="";
String beginning="";
String ending="";
String loopCount="";
int prev_time, currenttime;
String data="";
int func=0;

const unsigned char wifi_connected[] = {
0x00  , 0x00  , 0x00  , 0x00  ,0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0xF8  , 0x1F  , 0x00  ,0x80  , 0xFF  , 0xFF  , 0x01  ,
0xE0  , 0xFF  , 0xFF  , 0x07  ,0xF8  , 0xFF  , 0xFF  , 0x1F  ,
0xFC  , 0x01  , 0x80  , 0x3F  ,0x7E  , 0x00  , 0x00  , 0x7E  ,
0x1F  , 0x00  , 0x00  , 0xF8  ,0x1F  , 0x00  , 0x00  , 0xF8  ,
0x07  , 0xE0  , 0x07  , 0xE0  ,0x06  , 0xFC  , 0x3F  , 0x60  ,
0xC0  , 0xFF  , 0xFF  , 0x03  ,0xE0  , 0xFF  , 0xFF  , 0x07  ,
0xF0  , 0xFF  , 0xFF  , 0x0F  ,0xF0  , 0x07  , 0xE0  , 0x0F  ,
0xF0  , 0x03  , 0xC0  , 0x0F  ,0xF0  , 0x01  , 0x80  , 0x0F  ,
0x70  , 0x00  , 0x00  , 0x0E  ,0x60  , 0xC0  , 0x03  , 0x06  ,
0x00  , 0xF8  , 0x1F  , 0x00  ,0x00  , 0xFE  , 0x7F  , 0x00  ,
0x00  , 0xFC  , 0x3F  , 0x00  ,0x00  , 0xF8  , 0x1E  , 0x00  ,
0x00  , 0xE0  , 0x07  , 0x00  ,0x00  , 0xE0  , 0x07  , 0x00  ,
0x00  , 0xC0  , 0x03  , 0x00  ,0x00  , 0xC0  , 0x03  , 0x00  ,
0x00  , 0x80  , 0x01  , 0x00  ,0x00  , 0x80  , 0x01  , 0x00  ,
0x00  , 0x80  , 0x01  , 0x00  ,0x00  , 0x00  , 0x00  , 0x00  ,
  };  

const unsigned char wifi_disconnected[]={
  0x00  , 0x00  , 0x00  , 0x00  ,0x00  , 0x00  , 0x00  , 0x00  ,
0x00  , 0x08  , 0x10  , 0x00  ,0x80  , 0x0F  , 0xF0  , 0x01  ,
0xE0  , 0x0F  , 0xF0  , 0x07  ,0xF8  , 0x0F  , 0xF0  , 0x1F  ,
0xFC  , 0x01  , 0x80  , 0x3F  ,0x7E  , 0x00  , 0x00  , 0x7E  ,
0x1F  , 0x00  , 0x00  , 0xF8  ,0x1F  , 0x00  , 0x00  , 0xF8  ,
0x07  , 0x00  , 0x00  , 0xE0  ,0x06  , 0x0C  , 0x30  , 0x60  ,
0xC0  , 0x0F  , 0xF0  , 0x03  ,0xE0  , 0x0F  , 0xF0  , 0x07  ,
0xF0  , 0x0F  , 0xF0  , 0x0F  ,0xF0  , 0x07  , 0xE0  , 0x0F  ,
0xF0  , 0x03  , 0xC0  , 0x0F  ,0xF0  , 0x01  , 0x80  , 0x0F  ,
0x70  , 0x00  , 0x00  , 0x0E  ,0x60  , 0x00  , 0x00  , 0x06  ,
0x00  , 0x08  , 0x10  , 0x00  ,0x00  , 0x0E  , 0x70  , 0x00  ,
0x00  , 0x0C  , 0x30  , 0x00  ,0x00  , 0xF8  , 0x1E  , 0x00  ,
0x00  , 0xE0  , 0x07  , 0x00  ,0x00  , 0xE0  , 0x07  , 0x00  ,
0x00  , 0xC0  , 0x03  , 0x00  ,0x00  , 0xC0  , 0x03  , 0x00  ,
0x00  , 0x80  , 0x01  , 0x00  ,0x00  , 0x80  , 0x01  , 0x00  ,
0x00  , 0x80  , 0x01  , 0x00  ,0x00  , 0x00  , 0x00  , 0x00  ,
};

Backpack::Backpack(int baudrate) {
    _baudrate=baudrate;
}

void Backpack::start() {
    while (!Serial) {
    Serial.begin(_baudrate);
    };
    rtc.begin();
    tft_setup();
    if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
      tft.drawString("Insert SD card",10,10);
  
    }
    checkwifi();
}

void Backpack::checkwifi(){
  if(WiFi.status() != WL_CONNECTED)
        { 
          tft.drawXBitmap(260,13, wifi_disconnected, 32, 32, TFT_RED);
          connectwifi();
         }
}

void Backpack::connectwifi(){
  myFile = SD.open("wifi.txt", FILE_READ);
    if (myFile) {
        while (myFile.available()) {
        _wifi+=char(myFile.read());
      }
       wifi_cred=JSON.parse(_wifi);
      myFile.close();
      _ssid=(const char*) wifi_cred["ssid"];
      _password=(const char*) wifi_cred["password"];
        while (WiFi.status() != WL_CONNECTED)
        {
          WiFi.begin(_ssid,_password);
         }
      tft.drawXBitmap(260,13, wifi_connected, 32, 32, TFT_WHITE);
     } 
    else {
      
    }
}

void Backpack::tft_setup(){
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


void Backpack::lookout(){
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
         request= String(ending);
         request=request.substring(0,request.length()-4);  //4 is to remove "done"
         decode_message(request);
         _ret=_ret+"True";
        Serial.println(_ret);
      }
      ending="";
      Serial.flush();
    }
}
void Backpack::decode_message(String request){
  String function;
  String lib;
  String arg;
  
  //request=request.substring(0,request.length()-4); //4 is to remove "done"
  JSONVar myObject = JSON.parse(request);

  func = atoi((const char*) myObject["function"]);
  lib=myObject["lib"];

  if(lib=="graphics"){
    _ret=graph.ExGraph(func, request);
   
  }

else if(lib=="wifi"){
  int m,n;
  colon=0;
  switch (func){
  case 1: //"Connect_wifi"
    myFile = SD.open("wifi.txt", FILE_WRITE);
    if (myFile) {

      myFile.println( "{\"ssid\":\""+String((const char*)myObject["arg"][0]) + "\",\"password\":\"" + String((const char*)myObject["arg"][1]) + "\"}" );
      myFile.close();
       } 
    else {
      }
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
        if(_url[m]==':' && n==2){
          colon=m;
        }
        if(_url[m]=='/'){
          slash[n]=m;
          n+=1;
          if(n==3){
            break;
          }
        }
      }

      (String(_url).substring(0,slash[0])).toCharArray(_proto,slash[0]); 
      if(colon == 0){
        (String(_url).substring(slash[1]+1,slash[2])).toCharArray(_host,slash[2]-slash[1]);
      }
      else{
        (String(_url).substring(slash[1]+1,colon)).toCharArray(_host,colon-slash[1]);
      }
      (String(_url).substring(slash[2])).toCharArray(_path,strlen(_url)-slash[2]+1);
     

      if(strcmp(_proto,"https")==0){
        _port=443;
        if (!client.connect(_host, _port))
          {
          Serial.println("connection failed");
          tft.drawString("Connection failed",50,10);
          }
        client.println("GET " + String(_url) +" HTTP/1.0");
        client.println("Host: " + String(_host));
        
        client.println("Content-type: application/json");
        client.println("AppKey:92f871d8-c3bd-4fd7-8fab-ee50e1fbd0e5");
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
        
        } 

        
      else if (strcmp(_proto,"http")==0){
        _port=80;
        if (!client1.connect(_host, _port))
          {
          Serial.println("connection failed");
          tft.drawString("Connectio failed",50,10);
          }
        client1.println("GET " + String(_url) +" HTTP/1.0");
        client1.println("Host: " + String(_host));
        
        client1.println("Content-type: application/json");
        client1.println( "Connection: close");
        client1.println();
        timeout = millis();
        while (client1.available() == 0) {
          if (millis() - timeout > 5000) {
            _ret=">>> Client Timeout !";
            client1.stop();
            break;
            }
          }
        taketime = millis();
        while (client1.available())
          {
          line+= client1.readStringUntil('\r');
          }
        _ret+=line;
        
        }  
      else{
        _ret="Use http or https with your url";
        }
      break;
    default: 
      break;
    }
  }
}
