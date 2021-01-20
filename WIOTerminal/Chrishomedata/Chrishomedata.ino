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

TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClient client;


IPAddress server(173,76,105,19);
int port1=80;

int resets = 0;
String line = "";
String tags[]={"Alarm","Barn","Daikin","Geo","TED","Tesla","Water","WestonSolar"};
int ind[8];
String holders[8];
String _holders[8];
void setup() {
    Serial.begin(115200);
    while(!Serial); // Wait for Serial to be ready
    delay(1000);

    tft_setup();
    connect_WiFi();

}


void loop() {
  get_Data();
  show_Data();
  delay(300000);
}

 void get_Data(){
  if (client.connect(server, port1)) {
    client.println("GET /~crogers/data.html HTTP/1.0");
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



void getReply(){
  //reads lines until connction closed

    char input;

  while (client.connected()) {
    line = client.readStringUntil('\z');
    break;
      }

  client.stop();
  //Serial.println(line);

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
