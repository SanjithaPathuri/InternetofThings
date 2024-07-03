
/* INTRUDER DETECTION USING PIR SENSOR */

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 15;        
int pirPin = 2;    //the digital pin connected to the PIR sensor's output
int ledPin = 12;

void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  /*give the sensor some time to calibrate
//  Serial.print("calibrating sensor ");
   // for(int i = 0; i < calibrationTime; i++){
  //    Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(2000);*/
  }

void loop(){

     if(digitalRead(pirPin) == HIGH){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              digitalWrite(ledPin, LOW);   //the led visualizes the sensors output pin state
       Serial.println("motion detected! ");
       delay(2000);
         }
    else if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, HIGH);  //the led visualizes the sensors output pin state
       Serial.println("motion ended!");      //output
       delay(2000);
      }
       else {
         Serial.println("Sensor Fault");
  }
}
