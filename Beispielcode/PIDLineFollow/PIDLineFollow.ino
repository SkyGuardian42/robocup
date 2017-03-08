#include <QTRSensors.h>

//Sensor Bar Pins
const int S1 = A3;
const int S2 = A4;
const int S3 = A0;
const int S4 = 11;
const int S5 = A1;
const int S6 = 12;
const int S7 = A2;
const int S8 = 13;
const int LEDON = A5;
QTRSensorsRC qtrrc((unsigned char[]) {S1, S2, S3, S4, S5, S6, S7, S8}, 8, 2500, LEDON);
unsigned int sensorValues[8];
//Motor Controller Pins
const int in1 = 6;
const int in2 = 7;
const int in3 = 3;
const int in4 = 2;
const int ena = 9;
const int enb = 10;

//Controller Variables
unsigned int pos;
int error;
int motorSpeed;
int baseMotorSpeed = 110;
int rightMotorSpeed;
int leftMotorSpeed;
//PID
float kp = 0.08;
float kd = 1; 
float lastError;

void setup() {
  //Motor Controller Pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  //Calibrate Sensors
  for (int i = 0; i < 400; i++) 
    qtrrc.calibrate();
  
  Serial.begin(9600);
  
  for (int i = 0; i < 8; i++) {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  
  Serial.println();
  
  for (int i = 0; i < 8; i++) {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  
  Serial.println();
  Serial.println();
  
}

void loop() {
  readValues();
  calculatePID();
  applySpeed();
  serialDebug();
}

void readValues(){
  pos = qtrrc.readLine(sensorValues);

}
void calculatePID(){
  error = pos - 3500;
  motorSpeed = kp * error + kd * (error - lastError);
  Serial.print(motorSpeed);
  Serial.print('\t');
  lastError = error;
  
}
void applySpeed(){
  leftMotorSpeed = baseMotorSpeed + motorSpeed;
  rightMotorSpeed = baseMotorSpeed - motorSpeed;
  Serial.print(leftMotorSpeed);
  Serial.print('\t');
  Serial.print(rightMotorSpeed);
  Serial.print('\t');
  //Wenn die Motorgeschwindigkeit negativ ist, rückwärts fahren
  if(leftMotorSpeed > 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    leftMotorSpeed = constrain(leftMotorSpeed, 1, 255);
    analogWrite(enb, leftMotorSpeed);
  } else {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    leftMotorSpeed = constrain(-leftMotorSpeed, 0, 255);
    analogWrite(ena, leftMotorSpeed);
  } 
  
  if(rightMotorSpeed > 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    rightMotorSpeed = constrain(rightMotorSpeed, 1, 255);
    analogWrite(ena, rightMotorSpeed);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    rightMotorSpeed = constrain(-rightMotorSpeed, 0, 255);
    analogWrite(ena, rightMotorSpeed);
  }
  
}

void serialDebug(){
  for (unsigned char i = 0; i < 8; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.print("pos:");
  Serial.print(pos);
  Serial.print('\t');
  Serial.print("err");
  Serial.print(error);
  Serial.print('\t');
  Serial.print("lm:");
  Serial.print(leftMotorSpeed);
  Serial.print('\t');
  Serial.print("rm:");
  Serial.println(rightMotorSpeed);
}
