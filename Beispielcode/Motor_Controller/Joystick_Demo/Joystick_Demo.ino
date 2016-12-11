//Richtungs Pins für Motorcontroller
const int in1 = 5;
const int in2 = 4;
const int in3 = 3;
const int in4 = 2;
//Geschwindigkeits Pins für Motorcontroller
const int ena = 9;
const int enb = 10;

//Joystick Pins
const int yPin = A0;
int yReading;
const int xPin = A1;
int xReading;
const int btnPin = A2;

int baseSpd = 0;
int spdMod = 0;
int leftSpd = 0;
int rightSpd = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  yReading = analogRead(yPin);  //Seitwärts
  xReading = analogRead(xPin);  //Vorwärts

  spdMod = map(yReading, 511, 1023, 0, 255);
  baseSpd = map(xReading, 511, 1023, 0, 255);
  
  leftSpd = baseSpd + spdMod, 0, 255;
  rightSpd = baseSpd - spdMod, 0, 255;
  
  if (leftSpd < 0)
  {
    Serial.print(leftSpd);
    Serial.print("\t");
    Serial.print("Bckwd");
    Serial.print("\t");
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    leftSpd *= -1;
  }
  else 
  {
    Serial.print(leftSpd);
    Serial.print("\t");
    Serial.print("Fwd");
    Serial.print("\t");
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  
  if (rightSpd < 0)
  {
    Serial.print("\t");
    Serial.print(rightSpd);
    Serial.print("\t");
    Serial.println("Bckwd");
    
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    rightSpd *= -1;
  }
  else 
  {
    Serial.print("\t");
    Serial.print(rightSpd);
    Serial.print("\t");
    Serial.println("Fwd");
    
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  
  //Motorgeschwindingkeiten auf PWM Pins
  analogWrite(ena, constrain(leftSpd, 0, 255));
  analogWrite(enb, constrain(rightSpd, 0, 255));
  
}
