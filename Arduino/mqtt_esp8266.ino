#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>  // Including library for dht
 
#define DHTPIN 0          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
 
// Update these with values suitable for your network.

const char* ssid = "BELL053";
const char* password = "64E5EC2347D9";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
long lastMsg = 0;
char msg[100];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for Wi-Fi connection");
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  
  Serial.println("Line 1");
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.println("Line 2");
  Serial.begin(115200);
  Serial.println("Line 3");
  setup_wifi();
  dht.begin();
}

void loop() {
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
      
  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degrees Celcius, Humidity: ");
  Serial.print(humidity - 20);
  Serial.println();

  //HTTP connection
  HTTPClient http;
  http.begin(espClient, "http://127.0.0.1:8000/app/");
  http.addHeader("Content-Type", "text/plain");
  String tempString = "";
  tempString.concat(temperature);
  int httpCode = http.POST(tempString);
  String payload = http.getString();
  Serial.println(httpCode);
  Serial.println(payload);
  http.end();
  delay(5000);
}
