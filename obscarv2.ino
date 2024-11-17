#include <AFMotor.h>
#include <Servo.h>

const int trigPin = A0;
const int echoPin = A2;
long duration;
int distance;

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);

Servo myservo; // Create servo object to control a servo
const int servoPin = 9; // Define pin for servo motor

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  
  // Initialize the servo motor
  myservo.attach(servoPin);
  myservo.write(90); // Initial position at 90 degrees (straight ahead)
  
  // Set initial speed for the motors
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor3.setSpeed(250);
  motor4.setSpeed(250);
}

void loop() {
  // Measure distance using the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  movestop();
  delay(1000);

  if (distance < 75) {   
    backward();
    delay(1000);

    movestop();
    delay(1000);
    
    lookright();
    delay(750);

    centerServo(); // Return to center after looking
  } else {
    forward();
    delay(1000); 
  }
}

void movestop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

void backward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

void lookright() {
  myservo.write(0); // Rotate the servo to the right (0 degrees)
  delay(500); // Allow time for servo to move
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

void lookleft() {
  myservo.write(180); // Rotate the servo to the left (180 degrees)
  delay(500); // Allow time for servo to move
  
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

void centerServo() {
  myservo.write(90); // Return servo to center position
  delay(500); // Allow time for servo to move
}
