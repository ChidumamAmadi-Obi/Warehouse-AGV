/* MAIN PROGRAM
author: Chidumam Amadi-Obi
student number: B00167937

NOTES:

after removing unnessesary code, the robot followed the line almot perfectly, it is going off track at specific points so that is easily fixable

to detect the cross / docking station, the robot times how long it is detecting a cross (both line sensors are low as no light is reflected)
if both sensors are low for a specific amount of time the robot will dock
this is because there are many false positivves of cross detection for split seconds.

the line the robot follows was also made thinner so the robot does not oscillate too much

removed watch dog timer

*/

#include "agv_controller.h"

// ***************************************************************
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

void calliIRSensors(){ // callibrate ir line following sensors and test line following of robot
  lineFollowingAlgo();
  line.cross ?  digitalWrite(LED_PIN,HIGH) :  digitalWrite(LED_PIN,LOW); // leds turn on when robot crosses docking station
}

// ***************************************************************


void setup() {
  Serial.begin(115200);
  initGPIO();
  PS4.begin(); // initializes ps4 controller with esp32
  if (!PS4.isConnected()) Serial.println("ERROR CONNECTING PS4 CONTROLLER, CONTINUING WITHOUT BLUETOOTH...");
  // melodyManager(ERROR_MELODY);
  Serial.println("AGV INITALIZED!");

}

void loop() {
  AGVStateMachine(); // state machine is called forever

  //calliIRSensors();
  delay(10);
}



/* refs
print to terminal in color https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
*/

