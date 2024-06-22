#include <Servo.h>
#define trigPin 12
#define echoPin 11
#define trigPin2 10
#define echoPin2 8
#define trigPin3 13
#define echoPin3 7
#define trigPin4 3
#define echoPin4 4
Servo servo;
Servo servo2;

double Kp = 0.7; 
double Ki = 0.25;
double Kd = 0.05;

double integralSum = 0.0;
double prevError = 0.0;
double output = 0.0;
double reald;
double error;



int sound = 250;
void setup() {
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, INPUT);
servo.attach(9);
servo2.attach(6);
}
void loop() {
long duration, distance;
long duration2, distance2;
long duration3, distance3;
long duration4, distance4;
long gatePercentage;
long setpo;
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
  
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2 = (duration2/2) / 29.1;
  
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);
distance3 = (duration3/2) / 29.1;
  
digitalWrite(trigPin4, LOW);
delayMicroseconds(2);
digitalWrite(trigPin4, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin4, LOW);
duration4 = pulseIn(echoPin4, HIGH);
distance4 = (duration4/2) / 29.1;
  
reald = 30 - (distance4+distance3);
setpo = reald/30*90;

if((distance + distance2/60.0)>0.5){
gatePercentage = 90.0 * (distance + distance2) / 60.0 + output;
}else{
gatePercentage = 90.0 * (1 - ((distance + distance2) / 60.0)) + output; 
}
delayMicroseconds(10);
  
if(gatePercentage <=90){
// Calculate error
error = setpo - gatePercentage;

// Proportional term
double P = Kp * error;

// Integral term
integralSum += error;
double I = Ki * integralSum;

// Derivative term
double D = Kd * (error - prevError);
prevError = error;

// Calculate total output
output = P + I + D;

// Apply the output to the servo
servo.write(gatePercentage);
servo2.write(180 - gatePercentage);
  
}else{
delayMicroseconds(500);
gatePercentage = 0;
prevError = 0;
output = 0;
servo.write(0);
servo2.write(0);
}
  
Serial.print("Gate Percentage: ");
Serial.println(gatePercentage);
Serial.print("PID: ");
Serial.println(output);
Serial.print("distance: ");
Serial.println(distance);
Serial.print("distance2: ");
Serial.println(distance2);
Serial.print("distance3: ");
Serial.println(distance3);
Serial.print("distance4: ");
Serial.println(distance4);
Serial.print("gatedistance: ");
Serial.println(gatePercentage/90.0*30.0);
Serial.print("realdistance: ");
Serial.println(reald);
Serial.print("gatePercentage real: ");
Serial.println(setpo);
Serial.print("Error: ");
Serial.println(error);
Serial.println(gatePercentage/90.0*30.0);
Serial.println(" ");
}
