 
 //ULTRASONIC SENSOR (HC-SR04) DISTANCE MEASUREMENT//
 
 #define trigPin 12
 #define echoPin 11
 #define led1 10
 #define led2 9 
 #define led3 8
void setup ()
{
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.print("Ultrasonic Sensor Starting!!!");
  Serial.println("");
  delay(1000);
}

void loop ()
{
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance =(duration/2) * 0.0343;// time * speed of sound(0.0343cm/microsec)
  
  if (distance < 8)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  else if(distance<20)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  else if(distance<150)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
  if (distance >= 150)
  {
    Serial.print("Out of Range");
    Serial.println("");
  }
  else
  {
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
  }
}

