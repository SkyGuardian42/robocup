#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
long duration, distance; // Duration used to calculate distance

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(9600);
  while(!Serial){;}
}

void loop() {
  
  /* The following trigPin/echoPin cycle is used to determine the
  distance of the nearest object by bouncing soundwaves off of it. */ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  
  Serial.print("Distance ");
  Serial.println(distance);
  Serial.print("Duration: ");
  Serial.println(duration);
  delay(800);
  

}
