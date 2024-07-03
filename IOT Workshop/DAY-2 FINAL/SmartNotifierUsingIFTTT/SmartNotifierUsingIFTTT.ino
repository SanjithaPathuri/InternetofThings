/*
 *  This sketch sends data via HTTP GET requests to api.thingspeak.com service.
 *
 *  You need to get API write Key at api.thingspeak.com  and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN D2     // what pin we're connected to
#define DHTTYPE DHT11   // define type of sensor DHT 11
DHT dht (DHTPIN, DHTTYPE);

const char* ssid     = "SSID";
const char* password = "password";
const char* host = "maker.ifttt.com";//dont change
const String IFTTT_Event = "dooropen"; //Write your ifttt event name here
const int puertoHost = 80;
const String Maker_Key = "ccgrLuCecu6kfkUpS7ncvp";

String WebRequest = "POST /trigger/"+IFTTT_Event+"/with/key/"+Maker_Key +" HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" + 
                    "Content-Type: application/x-www-form-urlencoded\r\n\r\n";
                   
              

void setup() {
  Serial.begin(115200); 
  delay(10);  
  Serial.print("Connecting to ");
  Serial.println(ssid);  
  WiFi.begin(ssid, password);
  dht.begin();
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  } 
}


void loop() {
  
  
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
  
 if (t > 30){
  // This will send the request to the server
  Serial.println("Trigger Generated");
  client.print(WebRequest);
  delay(10);
 }
 else {
  // This will send the request to the server
  Serial.println("ifttt disconnected"); 
  delay(10);
 } 
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
 Serial.println();
 Serial.println("closing connection");
 delay(10000);
}

