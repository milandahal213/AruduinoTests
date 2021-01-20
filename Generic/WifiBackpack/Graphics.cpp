#include "Graphics.h"
#include "TFT_eSPI.h"           // change this to the LCD library for your board
#include <Arduino_JSON.h>

 // create objects 
TFT_eSPI tft;
Graphics::Graphics(){
  
}
String Graphics::ExGraph(int func, String request) {   
  JSONVar myObject = JSON.parse(request); 
    switch (func){
      case 1: //"drawString"
      tft.drawString((const char*) myObject["arg"][0],atoi((const char*) myObject["arg"][1]),atoi((const char*) myObject["arg"][2]));
      _ret="True";
      break;
      
      case 2: //"fillScreen"
      tft.fillScreen(atoi((const char*) myObject["arg"][0]));
      _ret="True";
      break;
      
      case 3: //"setTextSize"
      tft.setTextSize(atoi((const char*) myObject["arg"][0]));
      _ret="True";
      break;
      
      case 4: //"drawLine"
      tft.drawLine(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
      _ret="True";    
      break;
      
     case 5: //"drawPixel"
     tft.drawPixel(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]));
     _ret="True";
     break;
      
     case 6: //"drawRect"
     tft.drawRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
     _ret="True";
     break;
     
     case 7: //"fillRect"
     tft.fillRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]));
     _ret="True";
     break;
        
     case 8: //"drawCircle"
     tft.drawCircle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]));
     _ret="True";
     break;
         
     case 9: //"fillCircle"
     tft.fillCircle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]));
     _ret="True";
     break;
        
     case 10: //"drawTriangle"
     tft.drawTriangle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]), atoi((const char*) myObject["arg"][6]));
     _ret="True";
     break;
       
     case 11: //"fillTriangle"
      tft.fillTriangle(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]), atoi((const char*) myObject["arg"][6]));
      _ret="True";
      break;
       
     case 12: //"drawRoundRect"
     tft.drawRoundRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]));
     _ret="True";
     break;
       
     case 13: //"fillRoundRect")
     tft.fillRoundRect(atoi((const char*) myObject["arg"][0]), atoi((const char*) myObject["arg"][1]), atoi((const char*) myObject["arg"][2]), atoi((const char*) myObject["arg"][3]), atoi((const char*) myObject["arg"][4]), atoi((const char*) myObject["arg"][5]));
     _ret="True";
     break;
  
      default: 
      break;
    }
    
}
