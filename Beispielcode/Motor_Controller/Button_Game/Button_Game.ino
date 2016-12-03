const int in1 = 5;  //Richtungs Pins
const int in2 = 4;
const int in3 = 3;
const int in4 = 2;

const int ena = 9;  //Geschwindigkeits Pins
const int enb = 10;

const int btnPin = 13;

const int motorSpd = 50;

int incomingByte = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(btnPin, INPUT_PULLUP);  //Mit INPUT_PULLUP brauchen wir keine pull-up Widerstand
  
  Serial.begin(9600);
}

void loop() {
  
  //Geschwindigkeit bestimmen
  analogWrite(ena, 50); 
  analogWrite(enb, 50);
  
  if(digitalRead(btnPin) == HIGH) //Button nicht gedrückt = Vorwärts
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } 
  else  //Button gedrückt = Rückwärts
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}
