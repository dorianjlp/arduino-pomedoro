/*
 * Author: Dorian Levine
 * Date: June 27, 2020
 * 
 * A simple Pomedoro timer:
 * LED off = work time (25 min)
 * LED on = break time (5 min)
 * Arduino checks for reset button press every 8 seconds
 * whilst entering low power sleep in between.
 * 
 * Uses https://github.com/adafruit/Adafruit_SleepyDog
 */

#include <Adafruit_SleepyDog.h>

const unsigned short  buttonPin = 11; // Reset button pin
const unsigned short  ledPin = 12; // Main indicator LED pin
unsigned short ledState = LOW;
unsigned long timer = 0;

void setup() 
{
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Turn off built in LED
}

void loop() 
{
  timer += Watchdog.sleep(8000); // Sleep for 8 seconds
  
  // Check if button is being pressed
  if (digitalRead(buttonPin) == HIGH) 
  {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    timer = 0;
    ledState = LOW;
  }

  // 25 minutes are up
  if (timer >= 1500000 && !ledState)
  {
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
    timer = 0;
  }

  // 5 minutes are up
  if (timer >= 300000 && ledState)
  {
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    timer = 0;
  }
}
