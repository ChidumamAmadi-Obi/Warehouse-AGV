/* INDICATIORS
indicator leds and the piezo buzzer are controlled here
*/

#pragma once 

#include "config.h"

// melodies for buzzer
// uses tone() to play different notes and tones on the piezo buzzer
void singNokiaEntertainer() {
  tone(BUZZER_PIN, 262, 62); // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62); // E4
  delay(REST);
  tone(BUZZER_PIN, 262, 62); // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62); // E4
  delay(REST);
  tone(BUZZER_PIN, 262, 62); // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62); // E4
  delay(REST);
  tone(BUZZER_PIN, 262, 62); // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62); // E4
  delay(REST);
  tone(BUZZER_PIN, 220, 125); // A3
  delay(REST);
  tone(BUZZER_PIN, 262, 125); // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 125); // E4
  delay(REST);
  tone(BUZZER_PIN, 440, 125); // A4
  delay(REST);
  tone(BUZZER_PIN, 247, 125); // B3
  delay(REST);
  tone(BUZZER_PIN, 294, 125); // D4
  delay(REST);
  tone(BUZZER_PIN, 392, 125); // G4
  delay(REST);
  tone(BUZZER_PIN, 494, 125); // B4
  delay(REST);
}
void singNokiaIntro() {
  tone(BUZZER_PIN, 659, 200);
  delay(REST);
  tone(BUZZER_PIN, 659, 200);
  delay(REST);
  tone(BUZZER_PIN, 659, 400);
  delay(2 * REST);
  tone(BUZZER_PIN, 523, 200);
  delay(REST);
  tone(BUZZER_PIN, 659, 200);
  delay(REST);
  tone(BUZZER_PIN, 784, 400);
  delay(2 * REST);
  tone(BUZZER_PIN, 392, 400);
  delay(2 * REST);
}
void singAscending() {
  tone(BUZZER_PIN, 262, 200); // C4
  delay(REST);
  tone(BUZZER_PIN, 294, 200); // D4
  delay(REST);
  tone(BUZZER_PIN, 330, 200); // E4
  delay(REST);
  tone(BUZZER_PIN, 349, 200); // F4
  delay(REST);
  tone(BUZZER_PIN, 392, 200); // G4
  delay(REST);
  tone(BUZZER_PIN, 440, 200); // A4
  delay(REST);
  tone(BUZZER_PIN, 494, 200); // B4
  delay(REST);
  tone(BUZZER_PIN, 523, 400); // C5
  delay(2 * REST);
}
void singDescending() {
  tone(BUZZER_PIN, 523, 400); // C5
  delay(REST);
  tone(BUZZER_PIN, 494, 200); // B4
  delay(REST);
  tone(BUZZER_PIN, 440, 200); // A4
  delay(REST);
  tone(BUZZER_PIN, 392, 200); // G4
  delay(REST);
  tone(BUZZER_PIN, 349, 200); // F4
  delay(REST);
  tone(BUZZER_PIN, 330, 200); // E4
  delay(REST);
  tone(BUZZER_PIN, 294, 200); // D4
  delay(REST);
  tone(BUZZER_PIN, 262, 200); // C4
  delay(REST*2);
}
void singWarning1() {
  for (int i = 0; i < 2; i++) { // melody twice
    for (int freq = 600; freq <= 1200; freq += 10) { // Sweep up
      tone(BUZZER_PIN, freq);
      delay(5);
    }
    for (int freq = 1200; freq >= 600; freq -= 10) { // Sweep down
      tone(BUZZER_PIN, freq);
      delay(5);
    }
  } noTone(BUZZER_PIN);
}
void singWarning2() {
  for (int freq = 1000; freq <= 2000; freq += 10){ // Sweep up
    tone(BUZZER_PIN, freq);
    delay(5);
  }  
  for (int freq = 2000; freq >= 1000; freq -= 10) { // Sweep down
    tone(BUZZER_PIN, freq);
    delay(5);
  } noTone(BUZZER_PIN);
}

void melodyManager(Melodies melody) { // function to play melody for every scenario
  switch (melody) {
    case STARTUP_MELODY:              singAscending(); break;
    case OBJECT_DETECTED_MELODY:      singWarning2(); break;
    case DESTINATION_REACHED_MELODY:  singNokiaIntro(); break;
    case ERROR_MELODY:                singWarning1(); break;
    case PACKAGE_RECEIVED_MELODY:     singDescending(); break;
    default:                          singWarning1(); break;
    }
  noTone(BUZZER_PIN); // so buzzer does not go forever accidently
}

void LEDBlinker(unsigned long durationOff, unsigned long durationOn) { // controls blinking of LED precisely without blocking other functions
  static bool LEDState = LOW;
  unsigned long currentMillis = millis();

  if (LEDState == HIGH) {
    if (currentMillis - timing.prevLEDMillis >= durationOff) {
      timing.prevLEDMillis = currentMillis;
      LEDState = LOW;
      digitalWrite(LED_PIN, LEDState);
    }
  } else {
    if (currentMillis - timing.prevLEDMillis >= durationOn) {
      timing.prevLEDMillis = currentMillis;
      LEDState = HIGH;
      digitalWrite(LED_PIN, LEDState);
    }
  }
}

// refs & explanations
// https://codepal.ai/code-generator/query/Zsl4xJci/arduino-code-nokia-intro
// https://www.circuitgeeks.com/arduino-buzzer-tutorial/
// https://www.geeksforgeeks.org/c/static-variables-in-c/

/*

the static keyword was used in variables in functions so that these variables can
retain their value bewteen function calls
the global static variable cannot be accessd outside the file indicator.h

*/