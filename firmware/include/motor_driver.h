#ifndef MOTOR_DRIVER // header gaurds
#define MOTOR_DRIVER

#include "config.h"

typedef enum { // define direction codes for motor driver
    RIGHT,
    LEFT,
    FORWARD,
    BACKWARD
} dir;

void L298Driver(dir direction, uint8_t speed){ // controls motor direction and speed
    if ( speed > 0 ) { // if given a speed...
        switch(direction) {
            case RIGHT: 
                analogWrite(MOTOR_PIN_A1, speed);
                analogWrite(MOTOR_PIN_A2, 0);
                analogWrite(MOTOR_PIN_B1, speed);
                analogWrite(MOTOR_PIN_B2, 0);
                break;

            case LEFT: 
                analogWrite(MOTOR_PIN_A1, 0);
                analogWrite(MOTOR_PIN_A2, speed);
                analogWrite(MOTOR_PIN_B1, 0);
                analogWrite(MOTOR_PIN_B2, speed);
                break;

            case FORWARD: 
                analogWrite(MOTOR_PIN_A1, 0);
                analogWrite(MOTOR_PIN_A2, speed);
                analogWrite(MOTOR_PIN_B1, speed);
                analogWrite(MOTOR_PIN_B2, 0);
                break;

            case BACKWARD:
                analogWrite(MOTOR_PIN_A1, speed);
                analogWrite(MOTOR_PIN_A2, 0);
                analogWrite(MOTOR_PIN_B1, 0);
                analogWrite(MOTOR_PIN_B2, speed);
                break;

            default: // if invalid direction code turn motors off
                analogWrite(MOTOR_PIN_A1, 0);
                analogWrite(MOTOR_PIN_A2, 0);
                analogWrite(MOTOR_PIN_B1, 0);
                analogWrite(MOTOR_PIN_B2, 0);
                break;
        }
    } else { // if speed = 0 turn motors off
        analogWrite(MOTOR_PIN_A1, 0);
        analogWrite(MOTOR_PIN_A2, 0);
        analogWrite(MOTOR_PIN_B1, 0);
        analogWrite(MOTOR_PIN_B2, 0);
    }
}

#endif