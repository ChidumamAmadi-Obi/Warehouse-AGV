// author: Chidumam Amadi-Obi
// student number: B00167937

#include "agv_controller.h"

void initGPIO() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(MOTOR_PIN_A1, OUTPUT);
  pinMode(MOTOR_PIN_A2, OUTPUT);
  pinMode(MOTOR_PIN_B1, OUTPUT);
  pinMode(MOTOR_PIN_B2, OUTPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BB_PIN, INPUT);
  pinMode(L_IR_PIN,INPUT);
  pinMode(R_IR_PIN,INPUT);


  analogWrite(MOTOR_PIN_A1, 0);
  analogWrite(MOTOR_PIN_A2, 0);
  analogWrite(MOTOR_PIN_B1, 0);
  analogWrite(MOTOR_PIN_B2, 0);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(TRIG_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  initGPIO();
  // PS4.begin(); // initializes ps4 controller with esp32
  // esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  // esp_task_wdt_add(NULL); //add current thread to WDT watch
  melodyManager(STARTUP_MELODY);
  Serial.println("AGV INITALIZED!");
}

void loop() {
  AGVStateMachine();
  delay(10);
}


