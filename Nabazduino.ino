
#include "Motor.h"

Motor motorLeft = Motor(2, 3);
Motor motorRight = Motor(4, 5);

void setup() {
  motorLeft.init();
  motorRight.init();
}


void loop() {
  motorLeft.setMode(CLOCKWISE);
  motorRight.setMode(COUNTERCLOCKWISE);
  delay(2000);
  motorLeft.setMode(OFF);
  motorRight.setMode(COUNTERCLOCKWISE);
  delay(2000);
  motorLeft.setMode(COUNTERCLOCKWISE);
  motorRight.setMode(COUNTERCLOCKWISE);
  delay(2000);
  motorLeft.setMode(COUNTERCLOCKWISE);
  motorRight.setMode(OFF);
  delay(2000);
  motorLeft.setMode(COUNTERCLOCKWISE);
  motorRight.setMode(CLOCKWISE);
  delay(2000);
  motorLeft.setMode(OFF);
  motorRight.setMode(CLOCKWISE);
  delay(2000);
  motorLeft.setMode(CLOCKWISE);
  motorRight.setMode(CLOCKWISE);
  delay(2000);
  motorLeft.setMode(CLOCKWISE);
  motorRight.setMode(OFF);
  delay(2000);
}
