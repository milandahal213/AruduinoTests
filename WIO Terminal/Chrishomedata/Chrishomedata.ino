#include "AtWiFi.h"
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include"TFT_eSPI.h"
#include <HttpClient.h>
TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClient client;

const char* ssid = "virus";
const char* password =  "smoothie123";

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
  get_ChrisData();
  show_Data();
  delay(300000);
}

 void get_ChrisData(){
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

   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   delay(2000);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println (WiFi.localIP()); // prints out the device's IP address
}
