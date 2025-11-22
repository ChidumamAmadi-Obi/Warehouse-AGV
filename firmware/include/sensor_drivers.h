#ifndef SENSORS_H // header gaurds
#define SENSORS_H

#include "config.h"

int UltraSonicScan() { // uses the hc-s04 sensor to scan for obstacles
    static float duration = 0.0;
    static int distanceCm = 0;

    digitalWrite(TRIG_PIN,LOW); // start with emitting low pulse
    delay(2);
    digitalWrite(TRIG_PIN,HIGH); // emit high pulse
    delay(10);
    digitalWrite(TRIG_PIN,LOW);

    duration = pulseIn(ECHO_PIN, HIGH); // time the duration of the high pulse echoed back
    distanceCm = (duration * SPEED_OF_SOUND) / 2; // calculate distance with speed of sound

    return distanceCm;
}

int lineScan(){
    static int lineStatus = 0;

    if (digitalRead(L_IR_PIN)) lineStatus = 1; 
    if (digitalRead(R_IR_PIN)) lineStatus = 2;

    return lineStatus;
}

#endif

// https://projecthub.arduino.cc/lucasfernando/ultrasonic-sensor-with-arduino-complete-guide-284faf
