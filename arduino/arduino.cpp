#include <Servo.h>
#include "pitches.h"

// Pin definitions
const int STOCK_LED_PIN_1 = 8;
const int STOCK_LED_PIN_2 = 9;
const int READY_LED_PIN = 10;
const int UDS_TRIG_PIN = 5;
const int UDS_ECHO_PIN = 6;
const int SPEAKER_PIN = 13;
const int SERVO_ONE_PIN = 7;
const int SERVO_TWO_PIN = 11;

Servo servo_one;
Servo servo_two;

const int melody[] = { NOTE_C4, NOTE_G3 }; // Notes in the melody:
const int noteDurations[] = { 4, 8 }; // Note durations: 4 = quarter note, 8 = eighth note, etc.
const int noteCount = 2;

// --------------------------
// Setup and loop
// --------------------------
void setup() {
  // Set LED pins to output mode
  pinMode(STOCK_LED_PIN_1, OUTPUT);
  pinMode(STOCK_LED_PIN_2, OUTPUT);
  pinMode(READY_LED_PIN, OUTPUT);

  // Set up UDS pins
  pinMode(UDS_TRIG_PIN, OUTPUT);
  pinMode(UDS_ECHO_PIN, INPUT);

  // Set up servo
  servo_one.attach(SERVO_ONE_PIN);
  servo_two.attach(SERVO_TWO_PIN);

  // Set up serial monitor
  Serial.begin(9600);

  // Play a test tune on the speaker
  playTune();

  delay(500);
  Serial.println("Uno ready!");
  Serial.println("");
}

void loop() {
  Serial.println("Looping!");

  // Turn on both stock indicator LEDs
  digitalWrite(STOCK_LED_PIN_1, HIGH);
  digitalWrite(STOCK_LED_PIN_2, HIGH);

  // Measure distance
  int dist = measureDistance();
  
  // Blink the "Medication ready" LED
  blinkLED(READY_LED_PIN);

  // Rotate both servos
  rotateServoCont(servo_one);
  rotateServoCont(servo_two);
}


// --------------------------
// Functions
// --------------------------
void blinkLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);
}

int measureDistance() {
  const float speedSound = 0.034; // Centimeters per microsecond

  digitalWrite(UDS_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(UDS_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(UDS_TRIG_PIN, LOW);

  long duration = pulseIn(UDS_ECHO_PIN, HIGH);
  Serial.print("Pulse duration: ");
  Serial.println(duration);
  
  int distance = duration * speedSound / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  
  return distance;
}

void rotateServoCont(Servo servo) {
  // Let the servo turn at a speed of 100 for 2260ms
  servo.write(100);
  delay(2260);

  // Stop the servo from rotating (90 is neutral)
  servo.write(90);
  delay(2000);

  Serial.println("Finished rotating servo!");
}

void playTune() {
  for (int thisNote = 0; thisNote < noteCount; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];

    tone(SPEAKER_PIN, melody[thisNote], noteDuration);

    // To distinguish the notes, set a minimum time between them
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // Stop the tone playing
    noTone(SPEAKER_PIN);
  }
}
