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


IPAddress server();//server address separated by commas like (1,7,105,19);
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
