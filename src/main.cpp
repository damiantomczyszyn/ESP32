#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
//#include <ArduinoJson.h>
const char* ssid = "";
const char* password = "";


String httpGETRequest(const char* serverName);


unsigned long lastTime = 0;


unsigned long timerDelay = 10000;

String jsonBuffer;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {

    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "";
      
      //jsonBuffer = httpGETRequest(serverPath.c_str());
     // Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(httpGETRequest(serverPath.c_str()));
  //54 KB parsing failed
  //33.47 KB Parsing input failed!
  //27.05 KB Parsing input failed!
  //7 KB JSON achieved

      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.println("JSON object = ");
      Serial.println(myObject);


    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
