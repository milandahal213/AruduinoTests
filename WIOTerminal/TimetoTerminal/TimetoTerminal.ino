/*****************************
create a secrets.h file with the following contents

#define SECRET_SSID "your wifi ssid"
#define SECRET_PASS "your wifi password"

****************************/
#include "secrets.h"

#include "AtWiFi.h"
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include"TFT_eSPI.h"
TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClientSecure client;

char timeserver[] = "worldtimeapi.org";   // time website
int port = 443;
String  now, date, previous;
int resets = 0;
String line = "";


void setup() {
    Serial.begin(115200);
    while(!Serial); // Wait for Serial to be ready
    delay(1000);

    tft_setup();

}


void loop() {
  get_Time();
  show_Time();
  delay(10000);
}
 
void get_Time(){
  if (client.connect(timeserver, port)) {
    client.println("GET /api/ip HTTP/1.1");
    client.println("Host: worldtimeapi.org");
    client.println("Content-type:application/json");
    client.println("Connection: close");
    client.println();
  }
  else {
    connect_WiFi();
    resets += 1;
    return;
  }
  getReply();
  String reply = "";
  JSONVar myObject = JSON.parse(line);
  reply = myObject["datetime"];
  int start = 1 + reply.indexOf('T');  //finds location of T
  int end = reply.indexOf(':');  //finds location of hours
  end = reply.indexOf(':',end+1);  //finds location of minutes
  date = reply.substring(5, start-1);   
  now = reply.substring(start, end);   
  Serial.println(now);
 
  }

void getReply(){
  //reads lines until connction closed

  while (client.connected()) {
    line = client.readStringUntil('\n');
  }
  Serial.println("disconnecting from server.");
  client.stop();
  //Serial.println(line);
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

void show_Time(){
  tft.setTextColor(TFT_GREEN);
  tft.drawString(previous, 5, 10);
  tft.setTextColor(TFT_WHITE);
  tft.drawString(now, 5, 10);
  previous=now;
}

void tft_setup(){
   tft.begin();
    tft.setRotation(0);
    tft.fillScreen(TFT_GREEN);
 
    delay(2000);
    // Turning off the LCD backlight
    digitalWrite(LCD_BACKLIGHT, LOW);
    delay(2000);
    // Turning on the LCD backlight
    digitalWrite(LCD_BACKLIGHT, HIGH);
  
    tft.setTextSize(3);
}
