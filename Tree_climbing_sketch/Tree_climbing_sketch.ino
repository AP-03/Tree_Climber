#include <Servo.h>

Servo gripper1;
Servo gripper2;
Servo link1;
Servo link2;
Servo link3;

const int gripper1Pin = 3;    //top gripper pin
const int gripper2Pin = 6;   //lower gripper pin
const int link1Pin = 11;       //top gripper link pin
const int link2Pin = 10;       //middle link pin
const int link3Pin = 9;      //lower gripper link pin

#define TRIG_PIN 5 // TRIG pin
#define ECHO_PIN 8 // ECHO pin

// Variable for distance measurement
float distance;

void setup() {

  // setup of serial monitor to display ultrasonic sensor datax
  Serial.begin (9600);

  // configure the trigger and echo pins to output and input modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // assigning each servo to its pin
  gripper1.attach(gripper1Pin);
  gripper2.attach(gripper2Pin);
  link1.attach(link1Pin);
  link2.attach(link2Pin);
  link3.attach(link3Pin);

  // initial condition setup
  gripper1.write(180);
  gripper2.write(180);
  link1.write(45);
  link2.write(100);
  link3.write(0);
  delay(5000);

  // ultrasonic sensor setup and serial monitor display
  distance=measureDistance();
  delay(100);
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // climbing up loop
  while(distance>=18.00){
  distance=measureDistance();
  delay(100);
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  pullUp();
  delay(3000);
  pushUp();
  delay(3000);
  }
  delay(3000);
}
//initial condition setup for climbing down
reverse_ini();

//climbing down loop
void loop() {
  pushDown();
  delay(3000);
  pullDown();
  delay(3000);
}

// initial conditions for the servos such that the robot can start climbing down
void reverse_ini(){
  gripper2.write(180);
  delay(3000);
  gripper1.write(0);
  delay(3000);
  link1.write(90);
  link2.write(180);
  link3.write(45);
  delay(2000);
  gripper1.write(180);
  delay(5000);
}

// function for pulling the bottom gripper up
void pullUp(){
  gripper2.write(0);
  delay(3000);
  link1.write(90);
  link2.write(180);
  link3.write(45);
  delay(2000);
  gripper2.write(180);
}

// function for pushing top gripper up
void pushUp(){
  gripper1.write(0);
  delay(3000);
  link1.write(45);
  link2.write(100);
  link3.write(0);
  delay(3000);
  gripper1.write(180);
}

// function for pushing bottom gripper down
void pushDown(){
  gripper2.write(0);
  delay(3000);
  link1.write(45);
  link2.write(100);
  link3.write(0);
  delay(2000);
  gripper2.write(180);
}

// function for pulling top gripper down
void pullDown(){
  gripper1.write(0);
  delay(3000);
  link1.write(90);
  link2.write(180);
  link3.write(45);
  delay(2000);
  gripper1.write(180);
}

// function for measuring ultrasonic sensor distance
// returns the distance in cm
float measureDistance() {

  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  float duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance
  float distance_cm = 0.017 * duration;
  return distance_cm;
}
