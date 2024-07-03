#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN D2     // what pin we're connected to
#define DHTTYPE DHT11   // define type of sensor DHT 11
DHT dht (DHTPIN, DHTTYPE);

const char* ssid     = "SmartBridge";
const char* password = "KeepSmiling4ever";

const char* host = "api.thingspeak.com";
const char* privateKey = "8TX5AD0ZIK23ILE0";

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(15000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/update";
  url += "?api_key=";
  url += privateKey;
  url += "&field1=";
  url += t;
  url += "&field2=";
  url += h;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available())
  {
  char charIn = client.read();
  Serial.print(charIn);
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
  }

