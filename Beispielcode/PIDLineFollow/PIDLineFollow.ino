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
unsigned int pos; //For Line Position

//Motor Controller Pins
const int in1 = 6;
const int in2 = 7;
const int in3 = 3;
const int in4 = 2;
const int ena = 9;
const int enb = 10;

//Controller Variables
int error;
int motorSpeed;
int baseMotorSpeed = 125;

//PID
float kp = 0.2;
float kd = 5; 
float lastError;

void setup() {
  //Motor Controller Pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  //Calibrate Sensors
  for (int i = 0; i < 400; i++) qtrrc.calibrate();

  //Calibrated Readings To Serial Console
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
}

void loop() {
  readValues(); //read all sensor values
  calculatePID(); //calculate error and resulting correction
  applySpeed(); //apply speed to motor controller
  serialDebug();  //option task for debugging to the serial console
}

void readValues() {
  pos = qtrrc.readLine(sensorValues);
}

void calculatePID() {
  error = pos - 3500; //line position ranges from 0 to 7000, thus we are subtracting half to get 0 as desired error
  motorSpeed = kp * error + kd * (error - lastError);
  lastError = error;
}

void applySpeed() {
  analogWrite(ena, contrain(baseMotorSpeed + motorSpeed, 0, 255));
  analogWrite(enb, constrain(baseMotorSpeed - motorSpeed, 0, 255));

  //Drive forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
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
  Serial.println(error);
}
