/*****************************
create a secrets.h file with the following contents

#define SECRET_SSID "your wifi ssid"
#define SECRET_PASS "your wifi password"
String  apikey="your systemlink api key";




*****************************/
#include "secrets.h"
#include <rpcWiFi.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

WiFiClientSecure client;

char host[] = "api.systemlinkcloud.com"; // Server URL
int port = 443;

void setup() {
    Serial.begin(115200);
    Connect();
    delay(1000);
    

}

void loop() {
    PutSL("test1","STRING","site");
    GetReply();
    GetSL("test1");
    GetReply();
    delay(10*1000);
  
}

//--------------------------------- Subroutines -------------------------------------

void Connect(){
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
void GetSL(String tag) {

    Serial.println("\nStarting connection to server...");
    if (!client.connect(host, port)) {
        Serial.println("Connection failed!");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000);
        return;
    } 
    Serial.println("Connected to server!");
        // Make a HTTP request:
    client.println("GET /nitag/v2/tags/"+tag+"/values HTTP/1.1");
    client.println("Host: api.systemlinkcloud.com");
    client.println("Content-Type:application/json");
    client.println("Accept:application/json");
    client.println("x-ni-api-key: " + apikey);
    client.println("Connection: close");
    client.println();


    
}

void PutSL(String tag, String Type, String Value) {

  //propValue = {"value":{"type":Type,"value":Value}}
    String data= "{\"value\":{\"type\": \"" + Type + "\",\"value\":\""+Value+"\"}}";
    Serial.println(data);
    Serial.println("\nStarting connection to server...");
    if (!client.connect(host, port)) {
        Serial.println("Connection failed!");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000);
        return;
    } 
    Serial.println("Connected to server!");
        // Make a HTTP request:
    client.println("PUT /nitag/v2/tags/"+tag+"/values/current HTTP/1.1");
    client.println("Host: api.airtable.com");
    client.println("Connection: keep-alive");
    client.println("Keep-Alive: timeout=10, max=100");
    client.println("Content-Type: application/json");
 
    client.print("Content-Length: ");
    client.println(data.length());
    client.println("x-ni-api-key: " + apikey);
    client.println("Accept: application/json");

    client.println();
    client.println(data); 
 
}


void GetReply() {
    while (client.connected()) {
            String line = client.readStringUntil('\n');
            Serial.println(line);
            if (line == "\r") {
                Serial.println("headers received");
                break;
            }
        }
        // if there are incoming bytes available
        // from the server, read them and print them:
        while (client.available()) {
            char c = client.read();
            if (c == '\n') {
                Serial.write('\r');
            }
            Serial.write(c);
        }
        client.stop();
    
    Serial.println("Waiting 5 seconds before restarting...");
    delay(5000);
}
