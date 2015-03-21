#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

typedef enum E_MOTOR_ROTATION {
    OFF              = 0,
    CLOCKWISE        = 1,
    COUNTERCLOCKWISE = 2
};

class Motor
{
  /* Properties */
  protected :
    int pinA;
    int pinB;
    E_MOTOR_ROTATION mode;
    
  /* Methods */
  public :
    Motor(int pinA, int pinB) : pinA(pinA), pinB(pinB) {};
    void init() {
      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      mode = OFF;
    };
    void setMode(E_MOTOR_ROTATION mode) {
      this->mode = mode;
      updateMotor();
    };
    
  protected :
    void updateMotor()
    {
      switch(mode) {
        case OFF :
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          break;
        case CLOCKWISE :
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, LOW);
          break;
        case COUNTERCLOCKWISE :
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          break;
      }
    };
};

#endif /* MOTOR_H */
