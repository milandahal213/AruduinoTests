#include <rpcWiFi.h>
#include"TFT_eSPI.h"

TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
WiFiClient client;
const char *ssid="virus";
const char *password="smoothie123";

const char *host = "173.76.105.19";
String line = "";
void setup() {
    Serial.begin(115200);
    delay(1000);
    tft_setup();
    connect_WiFi();
}
void loop() {
  if (get_Data()) {
    show_Data();
    delay(300000);
  }
}
bool get_Data(){
 
    if (!client.connect(host, 80))
    {
        Serial.println("connection failed");
        return false;
    }
    client.println("GET /~crogers/data.html HTTP/1.0");
     client.println("Content-type: text/plain");
     client.println( "Connection: close");
     client.println();
    return getReply();
}
bool getReply(){
   unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return false;
        }
    }
    uint32_t taketime = millis();
    // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    {
        line += client.readStringUntil('\r');
        //Serial.print(line);
    }
    Serial.printf("\n\r---------------\n\rtake time:%d\n\r---------------\n\r", millis()-taketime);
    Serial.println();
    Serial.println("closing connection");
    return true;
}
void show_Data(){
  Serial.println("parsing Data");
  Serial.println(line);
  line = line.substring(line.indexOf("<table>")+7,line.indexOf("</table>"));
  Serial.println(line);
  line.replace("\n","");
  line.replace("<tr> ","");
  line.replace("<td>","");
  line.replace("</td>","");
  line.replace("</tr>","\n");
  Serial.println(line);
  int last;
  int i=1;
  tft.fillScreen(TFT_GREEN);
  delay(500);
  tft.fillScreen(TFT_BLACK);
  while ((last = line.indexOf("\n")) >= 0)  {
    String row = line.substring(0,last);
    line = line.substring(last+1,line.length());
    Serial.println(row);
    tft.setTextColor(TFT_GREEN);
    tft.drawString(line, 5,20*i);
    i++;
  }
  tft.drawString(String(i), 5,200);
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
  tft.setTextSize(2);
}
void connect_WiFi(){
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("Connecting to ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
