#include<SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
int sensorPin = A0; // select the input pin for the LDR
int sensorValue = 0; // variable to store the value coming from the sensor
int sensor=A1;
int rled = 9;
int pir=7;
int pir_value;
int gled=8;// Output pin for LED
int sms_count=0;
int Fire_Set;
int buzzer = 12; // Output pin for Buzzer
const int sensorMin = 0;     
const int sensorMax = 1024;
int smokeA0 = A5;
int sensorThres = 400;

void setup() {
// declare the ledPin and buzzer as an OUTPUT:
pinMode(rled, OUTPUT);
pinMode(gled, OUTPUT);
pinMode(pir,INPUT);
pinMode(smokeA0, INPUT);
pinMode(buzzer,OUTPUT);
pinMode(sensorPin,INPUT);
  mySerial.begin(9600);
Serial.begin(9600);
}

void loop()
{
  checkFire();
  checkSmoke();
  checkMotion();
}

void checkMotion()
{
  pir_value=digitalRead(pir);
  Serial.println("PIR Reading");
   Serial.println(pir_value);
  if(pir_value==HIGH)
  {
    digitalWrite(rled,HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(gled,LOW);
    delay(1000);
  }
  digitalWrite(gled,HIGH);
  digitalWrite(buzzer,LOW);
  digitalWrite(rled,LOW);
}

void checkSmoke()
{
   int analogSensor = analogRead(smokeA0);
               Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(gled, LOW);
    digitalWrite(rled, HIGH);
    digitalWrite(buzzer, HIGH);
   SendTextMessageS();
  }
  else
  {
    digitalWrite(rled, LOW);
    digitalWrite(gled, HIGH);
   digitalWrite(buzzer, LOW);
   
  }
  delay(100);
}

void checkFire()
{
  Serial.println("Welcome to home security alert system");
sensorValue = analogRead(sensorPin);
Serial.println(sensorValue);
int range = map(sensorValue, sensorMin, sensorMax, 0, 3);
   switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire **");
    digitalWrite(rled, HIGH);
      digitalWrite(gled,LOW);
      digitalWrite(buzzer,HIGH);
      delay(1000);
    SendTextMessage(); 
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire **");
       digitalWrite(rled, HIGH);     
      digitalWrite(gled,LOW);
      digitalWrite(buzzer,HIGH);
      delay(1000);
     SendTextMessage();
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    break;
  }
 digitalWrite(rled,LOW);
digitalWrite(gled, HIGH);
digitalWrite(buzzer,LOW);
delay(sensorValue);
}


void SetAlert()
{
while(sms_count<3) //Number of SMS Alerts to be sent
{  
SendTextMessage(); // Function to send AT Commands to GSM module
}
Fire_Set=1; 
}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+919491922437\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("Fire in NEW ROOM!");//the content of the message
  delay(100);
  Serial.println("message sent");
  mySerial.println((char)26);//the stopping character
  delay(1000);
  sms_count++;
}

void  SendTextMessageS()
{
 mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+919491922437\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("smoke in NEW ROOM!");//the content of the message
  delay(100);
Serial.println("message sent");

  mySerial.println((char)26);//the stopping character
  delay(1000); 
}

