const int in1 = 5;  //Richtungs Pins
const int in2 = 4;
const int in3 = 3;
const int in4 = 2;

const int ena = 9;  //Geschwindigkeits Pins
const int enb = 10;

const int motorSpd = 150;

int incomingByte = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available() > 0) {     //Nur Variable aendern, wenn Daten gesendet werden
    incomingByte = Serial.read();   //Serielle Konsole lesen
    Serial.println(incomingByte, DEC);
  }

  //Motorgeschwindingkeiten auf PWM Pins
  analogWrite(ena, motorSpd);
  analogWrite(enb, motorSpd);
  
  /*
  0 = L und R Stop
  1 = L und R Vorwaerts
  2 = L und R Rueckwaerts 
  3 = Nach links drehen
  */
  switch(incomingByte) {
    case 48:  // 0
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      break;
    case 49:  //1
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      break;
    case 50:  //2
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      break;
   case 51: //3
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      break;
  }
}
