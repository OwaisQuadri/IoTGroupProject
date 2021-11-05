#include <ArduinoJson.h>

/**
   BasicHTTPClient.ino
    Created on: 24.05.2015
*/

#include <Arduino.h>
#include <base64.h> 
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <DHT_U.h>
#define DHTPIN 0  
ESP8266WiFiMulti WiFiMulti;
DHT dht(DHTPIN, DHT11);
void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("OnePlus 6T", "Raveenth15");
  dht.begin();
}

void loop() {

  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
      
  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degrees Celcius, Humidity: ");
  Serial.print(humidity);
  Serial.println();
  String tempString = "";
  tempString.concat(temperature);
  String humString = "";
  humString.concat(humidity);

  DynamicJsonDocument doc(2048);
  doc["temperature"] = tempString;
  doc["humidity"] = humString;
  
  String json;
  serializeJson(doc, json);
  
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://ros-temphumid.herokuapp.com/")) {  // HTTP

      http.addHeader("Content-Type", "application/json");
//      String auth = base64::encode("owais:admin");
//      http.addHeader("Authorization", "Basic " + auth);
      Serial.print("[HTTP] POST...\n");
      // start connection and send HTTP header
      int httpCode = http.POST(json);

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK) {
          const String& payload = http.getString();
          Serial.println("received payload:\n<<");
          Serial.println(payload);
          Serial.println(">>");
        }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}