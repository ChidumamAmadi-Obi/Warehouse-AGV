#ifndef INDICATOR // header gaurds
#define INDICATOR

#include "config.h"

#define REST 50

unsigned long prevLEDMillis = 0.0;
unsigned long prevMelodyMillis = 0.0;
bool LEDState = 0;

typedef enum {
    STARTUP_MELODY,
    OBJECT_DETECTED_MELODY,
    DESTINATION_REACHED_MELODY,
    ERROR_MELODY
} melodies;

// melodies for buzzer
void singNokiaEntertainer() {
  tone(BUZZER_PIN, 262, 62);   // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62);   // E4
  delay(REST);
  tone(BUZZER_PIN, 262, 62);   // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62);   // E4
  delay(REST);
  tone(BUZZER_PIN, 262, 62);   // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62);   // E4
  delay(REST);
  tone(BUZZER_PIN, 262, 62);   // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 62);   // E4
  delay(REST);
  tone(BUZZER_PIN, 220, 125);  // A3
  delay(REST);
  tone(BUZZER_PIN, 262, 125);  // C4
  delay(REST);
  tone(BUZZER_PIN, 330, 125);  // E4
  delay(REST);
  tone(BUZZER_PIN, 440, 125);  // A4
  delay(REST);
  tone(BUZZER_PIN, 247, 125);  // B3
  delay(REST);
  tone(BUZZER_PIN, 294, 125);  // D4
  delay(REST);
  tone(BUZZER_PIN, 392, 125);  // G4
  delay(REST);
  tone(BUZZER_PIN, 494, 125);  // B4
  delay(REST);
}
void singNokiaIntro() {
  tone(BUZZER_PIN, 659, 200);
  delay(REST);
  tone(BUZZER_PIN, 659, 200);
  delay(REST);
  tone(BUZZER_PIN, 659, 400);
  delay(2*REST);
  tone(BUZZER_PIN, 523, 200);
  delay(REST);
  tone(BUZZER_PIN, 659, 200);
  delay(REST);
  tone(BUZZER_PIN, 784, 400);
  delay(2*REST);
  tone(BUZZER_PIN, 392, 400);
  delay(2*REST);
}
void singNokiaAscending() {
  // Simple ascending scale for testing
  tone(BUZZER_PIN, 262, 200);  // C4
  delay(REST);
  tone(BUZZER_PIN, 294, 200);  // D4
  delay(REST);
  tone(BUZZER_PIN, 330, 200);  // E4
  delay(REST);
  tone(BUZZER_PIN, 349, 200);  // F4
  delay(REST);
  tone(BUZZER_PIN, 392, 200);  // G4
  delay(REST);
  tone(BUZZER_PIN, 440, 200);  // A4
  delay(REST);
  tone(BUZZER_PIN, 494, 200);  // B4
  delay(REST);
  tone(BUZZER_PIN, 523, 400);  // C5
  delay(2*REST);
}
void singWarning_1(){ 
  for (int i = 0; i < 2; i++){
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
void singWarning_2(){
    // Sweep up
  for (int freq = 1000; freq <= 2000; freq += 10) {
    tone(BUZZER_PIN, freq);
    delay(5);
  }

  // Sweep down
  for (int freq = 2000; freq >= 1000; freq -= 10) {
    tone(BUZZER_PIN, freq);
    delay(5);
  }
}

void melodyManager(melodies melody){
    switch(melody) {
        case STARTUP_MELODY:               singNokiaAscending(); break;
        case OBJECT_DETECTED_MELODY:       singWarning_2(); break;
        case DESTINATION_REACHED_MELODY:   singNokiaIntro(); break;
        case ERROR_MELODY:                 singWarning_1(); break;
        default: break;
    }
}

void LEDBlinker(int durationOff, int durationOn) {                      
  unsigned long currentMillis = millis(); 
  
  if (LEDState == HIGH) {
    if (currentMillis - prevLEDMillis >= durationOff) { 
      prevLEDMillis = currentMillis;          
      LEDState = LOW;
      digitalWrite(LED_PIN, LEDState);
    }
  } else {                                         
    if (currentMillis - prevLEDMillis >= durationOn) { 
      prevLEDMillis = currentMillis;
      LEDState = HIGH;
      digitalWrite(LED_PIN, LEDState);
    }
  }
}

#endif


// https://codepal.ai/code-generator/query/Zsl4xJci/arduino-code-nokia-intro

// https://www.circuitgeeks.com/arduino-buzzer-tutorial/