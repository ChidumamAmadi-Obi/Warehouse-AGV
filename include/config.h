#ifndef CONFIG // header gaurds
#define CONFIG

#include <Arduino.h> // arduino framework functions

#define TRIG_PIN    23
#define ECHO_PIN    22
#define BUZZER_PIN  19
#define LED_PIN     18
#define BB_PIN      21
#define L_IR_PIN    4
#define R_IR_PIN    16

#define MOTOR_PIN_A1 25
#define MOTOR_PIN_A2 26
#define MOTOR_PIN_B1 32
#define MOTOR_PIN_B2 33

#define SCAN_INTERVAL 200 // interval at which the ultrasonic distance sensor scans for objects
#define SPEED_OF_SOUND 0.034 // used to calculate distance

#endif