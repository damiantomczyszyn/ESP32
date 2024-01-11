#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";

const size_t capacity = JSON_OBJECT_SIZE(10) + 3000;

WiFiClient client;
HTTPClient http;

DynamicJsonDocument doc(capacity);

String httpGETRequest(const char* serverName);


unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

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
      
      String jsonResponse = httpGETRequest(serverPath.c_str());
      Serial.println(jsonResponse);
      
      deserializeJson(doc, jsonResponse);
      Serial.println("Estimated memory usage: " + String(measureJson(doc)) + " bytes");
      if (doc.isNull()) {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.println("JSON object = ");
      serializeJsonPretty(doc, Serial);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode > 0) {
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
