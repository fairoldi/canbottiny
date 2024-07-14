// 2015 Coretech Robotics
// Servo Library: http://www.cunningturtle.com/attiny4585-servo-library/
// IR Code: David Cuartielles: http://forum.arduino.cc/index.php?topic=17965.0

#include <Servo_ATTinyCore.h>
#include <DistanceSensor.h>
#define trigPin 0
#define echoPin 4
#define ledPin 3

int motorPinL = 2;
int motorPinR = 1;
Servo motorL, motorR;

#define SERVO_MIN 950
#define SERVO_MAX 2100


DistanceSensor sensor(trigPin, echoPin);

void setup() {
  pinMode(ledPin, OUTPUT);
  motorL.attach(motorPinL, SERVO_MIN, SERVO_MAX);
  motorR.attach(motorPinR, SERVO_MIN, SERVO_MAX);
  //Serial.begin(9600);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if(sensor.getCM() < 50){
    digitalWrite(ledPin, HIGH);
    stop();
    backward();
    delay(1000);
    if (random(1) == 0) {
      left_turn();
    }
    else {
      right_turn();
    }
    forward();
    delay(4000);
  }
  else{
    digitalWrite(ledPin, LOW);
    switch (random(50)) {
      case 0:
        forward();
        delay(4000);
        break;
      case 1:
        left_turn();
        delay(500);
        forward();
        delay(3500);
        break;
      case 2:
        right_turn();
        delay(500);
        forward();
        delay(3500);
        break;
      default:
        stop();
        delay(500);
        break;
    }
  }
  
}

void stop() {
  if (motorL.attached()) {
    motorL.detach();
  }
  if (motorR.attached()) {
    motorR.detach();
  }
}


void backward() {
  if (!motorL.attached()) {
    motorL.attach(motorPinL, SERVO_MIN, SERVO_MAX);
  }
  if (!motorR.attached()) {
    motorR.attach(motorPinR, SERVO_MIN, SERVO_MAX);
  }
  motorL.write(0);
  motorR.write(180);
}

void forward() {
  if (!motorL.attached()) {
    motorL.attach(motorPinL, SERVO_MIN, SERVO_MAX);
  }
  if (!motorR.attached()) {
    motorR.attach(motorPinR, SERVO_MIN, SERVO_MAX);
  }
  motorL.write(180);
  motorR.write(0);
}


void left_turn() {
  if (!motorL.attached()) {
    motorL.attach(motorPinL, SERVO_MIN, SERVO_MAX);
  }
  if (!motorR.attached()) {
    motorR.attach(motorPinR, SERVO_MIN, SERVO_MAX);
  }
  motorL.write(0);
  motorR.write(0);
  delay(500);
  stop();
}

void right_turn() {
  if (!motorL.attached()) {
    motorL.attach(motorPinL, SERVO_MIN, SERVO_MAX);
  }
  if (!motorR.attached()) {
    motorR.attach(motorPinR, SERVO_MIN, SERVO_MAX);
  }
  motorL.write(180);
  motorR.write(180);
  delay(500);
  stop();
}



int getDistance() {
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return (duration / 2) / 29.1;
}
