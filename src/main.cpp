#include "config.h"
#include "sensor_drivers.h"
#include "motor_driver.h"

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
  analogWrite(MOTOR_PIN_B1, 0);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(TRIG_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial.println("hola");
  initGPIO();
}

void loop() {
  L298Controller(RIGHT,255); 
  Serial.println("RIGHT");
  delay(1000);
  L298Controller(LEFT,255); 
  Serial.println("LEFT");
  delay(1000);
  L298Controller(FORWARD,255); 
  Serial.println("FORWARDS");
  delay(1000);
  L298Controller(BACKWARD,255); 
  Serial.println("BACKWARDS");
  delay(1000);
  L298Controller(BACKWARD,0);
  Serial.println("OFF");
  delay(1000);
}