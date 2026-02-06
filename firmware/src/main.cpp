/* MAIN PROGRAM
author: Chidumam Amadi-Obi
student number: B00167937

*/

#include "agv_controller.h"

void initGPIO() { // assigns needed pins as inputs or outputs
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

  analogWrite(MOTOR_PIN_A1, 0);// starts all outputs as low
  analogWrite(MOTOR_PIN_A2, 0);
  analogWrite(MOTOR_PIN_B1, 0);
  analogWrite(MOTOR_PIN_B2, 0);

  digitalWrite(LED_PIN, LOW); 
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(TRIG_PIN, LOW);
  L298Driver(STOP,OFF); 
}

void setup() {
  Serial.begin(115200);
  initGPIO();
  PS4.begin(); // initializes ps4 controller with esp32
  if (!PS4.isConnected()) Serial.println("ERROR CONNECTING PS4 CONTROLLER, CONTINUING WITHOUT BLUETOOTH...");
  // esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  // esp_task_wdt_add(NULL); //add current thread to WDT watch
  melodyManager(STARTUP_MELODY);
  Serial.println("AGV INITALIZED!");
}

void loop() {
  AGVStateMachine(); // state machine is called forever

  /* TESTING PS4 CONTROLLER INPUT
  uint8_t controllerOutput = getPS4ControllerInput(); 
  Serial.print("PS4 CONTROLLER SENT -> "); Serial.println(controllerOutput);  
  */
}

/* refs
print to terminal in color https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
*/

