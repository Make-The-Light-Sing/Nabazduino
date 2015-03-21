
#include "Motor.h"
#include <FastSPI_LED2.h>
#include <Color.h>
#include <Segment.h>

#define HEAD_BUTTON    7
#define DEBOUNCE_DELAY 100      // the debounce time; increase if the output flickers
#define LEDSTRIP_PIN   6
#define NUM_LEDS       12
#define NB_SEGMENT     1

struct CRGB leds[NUM_LEDS];

TM1809Controller800Mhz<LEDSTRIP_PIN> LED;
SegmentCollection segments(leds);
SegmentCollection segments_on(leds);

Motor motorLeft = Motor(2, 3);
Motor motorRight = Motor(4, 5);

// Configure each segment with point to leds and segment length
T_SegmentConfig seg_config[NB_SEGMENT] = {
  {
    .start = 0,
    .length = NUM_LEDS,
    .effect = {
      .color = CWhite,
      .direction = UP,
      .type = Spark
    }
  }
};

T_SegmentConfig seg_config_on[NB_SEGMENT] = {
  {
    .start = 0,
    .length = NUM_LEDS,
    .effect = {
      .color = CBlue,
      .direction = UP,
      .type = Wave
    }
  }
};


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  memset(leds, 0x00, NUM_LEDS * sizeof(CRGB));

  for(unsigned int i = 0; i < NB_SEGMENT; i++) {
    segments.addSegment(new Segment(seg_config[i]));
  }
  for(unsigned int i = 0; i < NB_SEGMENT; i++) {
    segments_on.addSegment(new Segment(seg_config_on[i]));
  }
  segments.init();
  segments_on.init();
  LED.init();
  
  motorLeft.init();
  motorRight.init();
  
  pinMode(HEAD_BUTTON, INPUT);
  digitalWrite(HEAD_BUTTON, HIGH);  
}

int mode = 0;

void loop() {
  SegmentCollection * s;

  mode = readMode();
/*  if(Serial.available() > 0){      // if data present, blink
    mode = Serial.read();
  }*/

  switch(mode) {
    case 0 :
      motorLeft.setMode(OFF);
      motorRight.setMode(OFF);
      s = & segments;
      break;
    case 1 :
      motorLeft.setMode(CLOCKWISE);
      motorRight.setMode(COUNTERCLOCKWISE);
      s = & segments_on;
      break;
  }
  s->preStep();
  LED.showRGB((unsigned char *) leds, NUM_LEDS);
  s->postStep();
  delay(20);
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

      // only toggle the LED if the new button state is LOW
      if (buttonState == LOW) {
        mode = (mode+1) % 2;
        memset(leds, 0x00, NUM_LEDS * sizeof(CRGB));
      }
    }
  }
  lastButtonState = reading;
  return mode;
}
