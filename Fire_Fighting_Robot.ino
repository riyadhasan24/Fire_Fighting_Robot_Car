#include <Servo.h>  //include servo.h library
Servo myservo;

int pos = 0;
boolean fire = false;

#define Left 5      // left sensor
#define Right 3     // right sensor
#define Forward 4   // front sensor
#define gas 13       // Gas sensor

#define LM1 11        // left motor
#define LM2 12        // left motor

#define RM1 9        // right motor
#define RM2 10        // right motor

#define enA 7        // Enable Pin for left motor speed control
#define enB 8        // Enable Pin for right motor speed control

#define pump 13      // Water pump

int Speed = 200;    // Initial motor speed (0-255)

void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(gas, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(pump, OUTPUT);

  myservo.attach(6);
  myservo.write(90);
}

void put_off_fire() {
  delay(500);

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);

  analogWrite(enA, Speed); // Set speed for left motor
  analogWrite(enB, Speed); // Set speed for right motor

  digitalWrite(pump, HIGH);
  delay(500);

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }

  digitalWrite(pump, LOW);
  myservo.write(90);

  fire = false;
}

void loop() {
  myservo.write(90); // Sweep_Servo();

  if (digitalRead(Left) == 1 && digitalRead(Right) == 1 && digitalRead(Forward) == 1 && digitalRead(gas) == 1) {
    // Move forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    analogWrite(enA, Speed); // Set speed for left motor
    analogWrite(enB, Speed); // Set speed for right motor
  } 
  else if (digitalRead(Forward) == 0) {
    // Fire detected straight ahead
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(enA, Speed);
    analogWrite(enB, Speed);
    fire = true;
  } 
  else if (digitalRead(Left) == 0) {
    // Turn left
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    analogWrite(enA, Speed);
    analogWrite(enB, Speed);
  } 
  else if (digitalRead(Right) == 0) {
    // Turn right
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(enA, Speed);
    analogWrite(enB, Speed);
  }

  while (fire == true) {
    put_off_fire();
  }
}
