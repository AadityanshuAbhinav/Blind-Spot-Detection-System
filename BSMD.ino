#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// Define pins
#define TRIG_PIN 2  // Connect to HC-SR04 trigger pin
#define ECHO_PIN 3  // Connect to HC-SR04 echo pin
#define LED_PIN 5   // Connect to LED strip (anode or +)

// Constants
const int MAX_DISTANCE = 30; // Distance threshold for LED behavior
const int MIN_DISTANCE = 15; // Minimum distance for dark red color

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  //LED
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Turn off LED initially  
  lcd.begin();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
}

void loop() {
  for (pos = 0; pos <= 60; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 60; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  // Measure distance
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58; // Calculate distance in cm
  lcd.setCursor(1, 0);
  lcd.print("Distance: ");
  lcd.setCursor(1, 1);
  lcd.print(distance);
  lcd.println(" cm");
  delay(50);
  // Control LED based on distance
  if (distance != 0) 
  {
      if (distance > MAX_DISTANCE)
      {
        digitalWrite(LED_PIN, LOW); // Turn off LED
      }
      else if (distance < MIN_DISTANCE)
      {
        digitalWrite(LED_PIN, HIGH); // Set LED to dark red (adjust brightness as needed)
        delay(500);
      } 
    else 
{
      // Blinking effect
      int blinkSpeed = map(distance, MAX_DISTANCE, MIN_DISTANCE, 500, 100); // Adjust blinking speed
      digitalWrite(LED_PIN, HIGH);
      delay(blinkSpeed);
      digitalWrite(LED_PIN, LOW);
      delay(blinkSpeed);
    }
  }
  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
