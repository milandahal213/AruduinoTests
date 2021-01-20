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
char *l;
String line = "";

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
  //show_Data();
  delay(300000);
}

 void get_Data(){
  if (client.connect(server, port1)) {
    client.println("GET /~crogers/data/barn.csv HTTP/1.0");
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
int a;
for (int i=0;i<1000;i++){
a=client.read();
Serial.println(a);
}
client.stop();
  Serial.println(l);
  
  Serial.println("okay");

}


void show_Data(){

  Serial.println(line);
  

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
