#pragma once

#include "config.h"

static LineStatusFlags line;

uint16_t  ultraSonicScan() { // uses the hc-sr04 sensor to scan for obstacles
    static float duration = 0.0;
    static uint16_t  distanceCm = 0;

    digitalWrite(TRIG_PIN,LOW); delay(2);  // start with emitting low pulse
    digitalWrite(TRIG_PIN,HIGH); delay(10);// emit high pulse
    digitalWrite(TRIG_PIN,LOW);

    duration = pulseIn(ECHO_PIN, HIGH); // time the duration of the high pulse echoed back
    distanceCm = (duration * SPEED_OF_SOUND) / 2; // calculate distance with speed of sound

    return distanceCm;
}

void lineScan(){ // uses ir sensors to keep tracck of where bot is on the line
    line.statusR = digitalRead(R_IR_PIN) ? true : false;                // variable = (condition) ? a : b
    line.statusL = digitalRead(L_IR_PIN) ? true : false;                // if condition is true, variable = a, if false variable = b
    line.cross = (line.statusL && line.statusR) ? true : false;    
} // tenery operators use less lines of code than if else statements

// refs & explanations
// https://projecthub.arduino.cc/lucasfernando/ultrasonic-sensor-with-arduino-complete-guide-284faf ultrasonic distance sensors
// https://www.geeksforgeeks.org/c/conditional-or-ternary-operator-in-c/ tenery operators
