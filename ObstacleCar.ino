#include "L293.h"
#include"Servo.h"
int large_find(int []);
AF_DCMotor rightBack(2); //Create an object to control each motor
AF_DCMotor rightFront(4);
AF_DCMotor leftFront(3);
AF_DCMotor leftBack(1);
Servo servoLook;
byte trig=2;
byte echo=13;
byte motorSpeed=200;
byte maxDist = 150;
int motorOffset = 10; //Factor to account for one side being more powerful
int turnSpeed = 50;
float timeOut=2*(maxDist+10)/100/340*1000000;

void setup() {
rightBack.setSpeed(motorSpeed); //Set the motors to the motor speed
rightFront.setSpeed(motorSpeed);
leftFront.setSpeed(motorSpeed);
leftBack.setSpeed(motorSpeed);
rightBack.run(RELEASE); //Ensure all motors are stopped
rightFront.run(RELEASE);
leftFront.run(RELEASE);
leftBack.run(RELEASE); //Assign the servo pin
pinMode(trig,OUTPUT); //Assign ultrasonic sensor pin modes
pinMode(echo,INPUT);
servoLook.attach(10);
Serial.begin(9600);
}

void loop() {
servoLook.write(90);
rightFront.run(FORWARD);
leftFront.run(FORWARD);
rightBack.run(FORWARD);
leftBack.run(FORWARD); //Create a variable to store the pulse travel time
int distance;
int distances[4]={0,0,0,0};
distance=get_distance(); //Create a variable to store the calculated distance
if(distance<=15)
{
rightBack.run(RELEASE); //Ensure all motors are stopped
rightFront.run(RELEASE);
leftFront.run(RELEASE);

leftBack.run(RELEASE);
delay(200);
rightBack.run(BACKWARD);
rightFront.run(BACKWARD);
leftFront.run(BACKWARD);
leftBack.run(BACKWARD);
delay(500);
rightBack.run(RELEASE); //Ensure all motors are stopped
rightFront.run(RELEASE);
leftFront.run(RELEASE);
leftBack.run(RELEASE);
servoLook.write(180); //left
delay(750);
distances[0]=get_distance(); //left
servoLook.write(135); //left-right
delay(400);
distances[1]=get_distance(); //left-right
servoLook.write(45); //right-left
delay(750);
distances[2]=get_distance(); //right-left
servoLook.write(0); //right side
delay(400);
distances[3]=get_distance(); //right
int lg=large_find(distances);
if(lg==0) //condition for turn left side
{
turn_left(700);
}
else if(lg==1) //condition for turn right

{
turn_left(350);
}
else if(lg==2)
{
turn_right(350);
}
else if(lg==3)
{
turn_right(700);
}
}
}
void turn_left(int duration)
{
rightBack.setSpeed(motorSpeed+turnSpeed); //Set the motors to the motor speed
rightFront.setSpeed(motorSpeed+turnSpeed);
leftFront.setSpeed(motorSpeed);
leftBack.setSpeed(motorSpeed);
rightBack.run(FORWARD);
rightFront.run(FORWARD);
leftFront.run(BACKWARD);
leftBack.run(BACKWARD);
delay(duration);
rightBack.setSpeed(motorSpeed); //Set the motors to the motor speed
rightFront.setSpeed(motorSpeed);
leftFront.setSpeed(motorSpeed);
leftBack.setSpeed(motorSpeed);
rightBack.run(RELEASE);

rightFront.run(RELEASE);
leftFront.run(RELEASE);
leftBack.run(RELEASE);
}
void turn_right(int duration)
{
rightBack.setSpeed(motorSpeed); //Set the motors to the motor speed
rightFront.setSpeed(motorSpeed);
leftFront.setSpeed(motorSpeed+turnSpeed);
leftBack.setSpeed(motorSpeed+turnSpeed);
rightBack.run(BACKWARD);
rightFront.run(BACKWARD);
leftFront.run(FORWARD);
leftBack.run(FORWARD);
delay(duration);
rightBack.setSpeed(motorSpeed); //Set the motors to the motor speed
rightFront.setSpeed(motorSpeed);
leftFront.setSpeed(motorSpeed);
leftBack.setSpeed(motorSpeed);
rightBack.run(RELEASE);
rightFront.run(RELEASE);
leftFront.run(RELEASE);
leftBack.run(RELEASE);
}
int get_distance()
{
int distances;
unsigned long pulseTime;
digitalWrite(trig, HIGH); //Generate a 10 microsecond pulse

delayMicroseconds(10);
digitalWrite(trig, LOW);
pulseTime = pulseIn(echo, HIGH, timeOut);
distances = (float)pulseTime * 340 / 2 / 10000;
return distances;
}
int large_find(int distances[])
{
int lg=0;
int lg_dis=distances[0];
int i=0;
while(i<4)
{
if(distances[i]>lg_dis)
{
lg_dis=distances[i];
lg=i;
}
i++;
}
return lg;
}
