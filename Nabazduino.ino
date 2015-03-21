
#include "Motor.h"

#define HEAD_BUTTON    6
#define DEBOUNCE_DELAY 100      // the debounce time; increase if the output flickers

Motor motorLeft = Motor(2, 3);
Motor motorRight = Motor(4, 5);

void setup() {
  motorLeft.init();
  motorRight.init();
  
  pinMode(HEAD_BUTTON, INPUT);
  digitalWrite(HEAD_BUTTON, HIGH);  
}

void loop() {
  switch(readMode()) {
    case 0 :
      motorLeft.setMode(OFF);
      motorRight.setMode(OFF);
      break;
    case 1 :
      motorLeft.setMode(CLOCKWISE);
      motorRight.setMode(COUNTERCLOCKWISE);
      break;
  }
}

/**
 * Read mode from Head button
 */
int readMode()
{
  static int mode = 0;
  static int buttonState;             // the current reading from the input pin
  static int lastButtonState = LOW;   // the previous reading from the input pin
  static long lastDebounceTime = 0;  // the last time the output pin was toggled
  
  int reading = digitalRead(HEAD_BUTTON);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        mode = (mode+1) % 2;
      }
    }
  }
  lastButtonState = reading;
  return mode;
}
