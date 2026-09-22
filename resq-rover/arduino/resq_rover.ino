/*
  PHASE 4 - FULL AUTONOMOUS OBSTACLE-AVOIDING ROVER
  ------------------------------------------------------
  Combines: HC-SR04 ultrasonic + SG90 servo scanning + L298N motor control

  Pin map:
    HC-SR04:  TRIG = 9   ECHO = 10
    SERVO:    SIGNAL = 3
    L298N:    ENA = 5   IN1 = 7   IN2 = 8   (left side motors)
              ENB = 6   IN3 = 11  IN4 = 12  (right side motors)

  Logic:
    - If front is clear -> move forward
    - If obstacle detected -> stop, scan left & right, turn toward clearer side
    - If both sides blocked -> reverse briefly, then re-scan
*/

#include <Servo.h>

// ---------- Pin definitions ----------
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

const int SERVO_PIN = 3;
const int CENTER_ANGLE = 90;
const int LEFT_ANGLE   = 150;
const int RIGHT_ANGLE  = 30;

const int ENA = 5;
const int IN1 = 7;
const int IN2 = 8;

const int ENB = 6;
const int IN3 = 11;
const int IN4 = 12;

// ---------- Config ----------
const int SAFE_DISTANCE = 25;     // cm - below this, treat as obstacle
const int MOTOR_SPEED = 230;      // 0-255

Servo scanServo;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(CENTER_ANGLE);
  delay(500);

  stopRobot();
  Serial.println("Autonomous Rover Starting...");
}

void loop() {
  float frontDistance = getDistance();
  Serial.print("Front Distance: ");
  Serial.println(frontDistance);

  if (frontDistance == -1 || frontDistance > SAFE_DISTANCE) {
    // Path clear
    moveForward();
  } else {
    // Obstacle detected
    stopRobot();
    delay(200);

    float leftDistance = scanDirection(LEFT_ANGLE);
    float rightDistance = scanDirection(RIGHT_ANGLE);

    scanServo.write(CENTER_ANGLE);
    delay(300);

    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.print(" | Right: ");
    Serial.println(rightDistance);

    if (leftDistance == -1) leftDistance = 999; // treat timeout as "very clear"
    if (rightDistance == -1) rightDistance = 999;

    if (leftDistance < SAFE_DISTANCE && rightDistance < SAFE_DISTANCE) {
      // both blocked - reverse briefly
      Serial.println("Both sides blocked - reversing");
      moveBackward();
      delay(600);
      stopRobot();
      delay(200);
    } else if (leftDistance > rightDistance) {
      Serial.println("Turning Left");
      turnLeft();
      delay(500);
      stopRobot();
    } else {
      Serial.println("Turning Right");
      turnRight();
      delay(500);
      stopRobot();
    }
  }

  delay(100);
}

// ---------- Ultrasonic ----------
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    return -1;
  }
  return duration * 0.0343 / 2;
}

// ---------- Servo scan ----------
float scanDirection(int angle) {
  scanServo.write(angle);
  delay(400); // give servo time to physically reach the angle
  return getDistance();
}

// ---------- Motor control ----------
void moveForward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}