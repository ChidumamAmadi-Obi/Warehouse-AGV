
//_____________________________________________________________
// agv control logic
// state machine and helper functions are declared here
//_____________________________________________________________


#ifndef AGV // header gaurds
#define AGV

#include "config.h"
#include "bluetooth_manager.h" // coming soon
#include "indicator.h"
#include "motor_driver.h"
#include "sensor_drivers.h"

void alertOnce(melodies melody) { // only alerts user with melody once per state
    if (!agvStatus.hasBeenAlerted) {
        melodyManager(melody);
        agvStatus.hasBeenAlerted = true;
    }
}

void lineFollowingAlgo(){
    if (!line.cross && (line.statusL || line.statusR) ) { // if the robot goes off course...
        if (line.statusL && (millis() - agvStatus.lastLineCorrection >= CORSE_CORRECTION_INTERVAL)) { // corse correct robot every 100ms
            L298Driver(LEFT, CRUISING_SPEED);                                   // "if ir sensor is off line, turn until it is"
            agvStatus.lastLineCorrection = millis();
        } 
        if (line.statusR && (millis() - agvStatus.lastLineCorrection >= CORSE_CORRECTION_INTERVAL)) {
            L298Driver(RIGHT,CRUISING_SPEED);
            agvStatus.lastLineCorrection = millis();
        }
    } else { // if robot is on course keep driving straight
        L298Driver(FORWARD,CRUISING_SPEED);
    }
}

void AGVStateMachine(){
    agvStatus.isCarryingLoad = digitalRead(BB_PIN);   // check if agv is carrying load  
    if ( ultraSonicScan() < OBSTACLE_DETECTION_THRESHOLD ) agvStatus.isPathObstructed = true;    // check if there is obstacle 
    else agvStatus.isPathObstructed = false; 

    switch(agvStatus.currentAGVState) {
        case STATUS_IDLE: // state 0 __________________________________________________________________________________________________
            LEDBlinker(1000, 250);

            if(agvStatus.isCarryingLoad) { // will also check if destination has been input via blue tooth in the future
                agvStatus.currentAGVState = STATUS_TRAVELLING; // if a load has been placed agv will start traveling
                digitalWrite(LED_PIN,LOW); 
            }
            break;

        case STATUS_TRAVELLING: // state 1 ____________________________________________________________________________________________
            lineScan(); // check and update robots position on the line
            alertOnce(PACKAGE_RECEIVED_MELODY);

            if (line.cross) {
                agvStatus.currentAGVState = STATUS_UNLOADING;  // if destination has been reached the agv will start unloading
                agvStatus.hasBeenAlerted = false; // reset alert flag
            }
            if (agvStatus.isPathObstructed) { // if object detected...
                agvStatus.currentAGVState = STATUS_OBSTACLE_OBSTRUCTION; 
                agvStatus.hasBeenAlerted = false;
            } else lineFollowingAlgo(); // if no object detected, keep following the line
            break;
        
        case STATUS_OBSTACLE_OBSTRUCTION: // state 2  __________________________________________________________________________________
            L298Driver(STOP,OFF); // stop and flash LEDs until obstacle is taken away
            alertOnce(OBJECT_DETECTED_MELODY);
            LEDBlinker(100,100); 

            if (!agvStatus.isPathObstructed) { // if obstacle is taken away go back to traveling
                agvStatus.currentAGVState = STATUS_TRAVELLING;
                agvStatus.hasBeenAlerted = false; 
                digitalWrite(LED_PIN,LOW); 
            }
            break;

        case STATUS_UNLOADING: // state 3  _____________________________________________________________________________________________
            L298Driver(STOP,OFF);
            alertOnce(DESTINATION_REACHED_MELODY);
            if (!agvStatus.isCarryingLoad) agvStatus.currentAGVState = STATUS_IDLE; // if load is removed go back to your idle state
            break;

        case STATUS_ERROR: // state 4  _________________________________________________________________________________________________
            alertOnce(ERROR_MELODY);
            break;

        default: 
            agvStatus.currentAGVState = STATUS_ERROR;
            break;
    }
    Serial.print("STATE: "); Serial.println(agvStatus.currentAGVState);
}

#endif