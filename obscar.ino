#include <Servo.h>
#include <AFMotor.h>

// Motor connections
AF_DCMotor motor1(1);  // M1
AF_DCMotor motor2(2);  // M2
AF_DCMotor motor3(3);  // M3
AF_DCMotor motor4(4);  // M4

// Servo connection
Servo myServo;

// Ultrasonic sensor pins
const int trigPin = A0;
const int echoPin = A1;

// Variables
long duration;
int distance;
int leftDistance;
int rightDistance;

void setup() {
  Serial.begin(9600);

  // Initialize motor speed
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);

  // Attach servo to pin 9
  myServo.attach(9);

  // Move servo to the center position
  myServo.write(90);

  // Start moving forward
  moveForward();
}

void loop() {
  // Continuously scan forward for obstacles
  scanObstacle();

  if (distance < 10) {
    // Stop the car if obstacle detected
    stopCar();

    // Check left and right distances
    myServo.write(0);  // Look left
    delay(500);
    leftDistance = getDistance();

    myServo.write(180);  // Look right
    delay(500);
    rightDistance = getDistance();

    // Decide the direction based on more space
    if (leftDistance > rightDistance) {
      turnLeft();
    } else {
      turnRight();
    }

    // Move forward after turning
    moveForward();
  } else {
    // Keep moving forward if no obstacle
    moveForward();
  }

  delay(100);  // Short delay to prevent overloading the loop
}

void scanObstacle() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
}

int getDistance() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  return duration * 0.034 / 2;
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void stopCar() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
}
