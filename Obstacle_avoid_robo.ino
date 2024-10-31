#include <Servo.h>

Servo myServo;  
const int trigPin = 9;
const int echoPin = 8;
const int motor1Pin1 = 7;  // Motor 1 
const int motor1Pin2 = 6;  // Motor 1 
const int motor2Pin1 = 5;  // Motor 2 
const int motor2Pin2 = 4;  // Motor 2 

long duration;
int distance;

void setup() {
  // Set motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Set sensor pins as input/output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  
  myServo.attach(10);
  
  Serial.begin(9600);
}

void loop() {
  // Scan environment using the ultrasonic sensor
  scanforEnvironment();
  
  // Read the distance from the sensor
  if (distance < 200) {  //obstace detected <200cm (for simulation only)
    avoidObstacle();     // move the servo head to search
  } else {
    moveForward();
  }
}

void scanforEnvironment() {
  // Rotate the servo to scan
  myServo.write(90);  // Scan front
  delay(500);
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
}

int getDistance() {
  // 10us pulse to trigger US
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the echo time
  duration = pulseIn(echoPin, HIGH);
  
  // Convert echo time to distance (in cm)
  int dist = duration * 0.032 / 2;  //Using speed of sound
  return dist;
}

void avoidObstacle() {
  // Stop motors, then decide where to move
  stopMotors();
  
  // Rotate servo to check left and right
  myServo.write(0);  // Check right
  delay(500);
  int rightDistance = getDistance();
  
  myServo.write(180);  // Check left
  delay(500);
  int leftDistance = getDistance();
  
  // Choose the direction with the most space
  if (leftDistance > rightDistance) {
    turnLeft();
  } else {
    turnRight();
  }
}

void moveForward() {
  // Move both motors forward
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  // Move only the right motor forward to turn left
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(500);  
}

void turnRight() {
  // Move only the left motor forward to turn right
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(500);  
}

void stopMotors() {
  // Stop both motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
