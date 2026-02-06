
//_____________________________________________________________
// agv control logic
// state machine and helper functions are declared here
//_____________________________________________________________

#pragma once

// include all helper header files
#include "config.h"
#include "bluetooth_manager.h" 
#include "indicator.h"
#include "motor_driver.h"
#include "sensor_drivers.h"

static AGVStatusFlags agvStatus;

void trackLocation(){ // tracks location of agv 
    if (line.cross && (millis() - timing.lastDestinationIncriment > LOCATION_TRACK_INTERVAL)) { // if docking station is reached...
        agvStatus.agvLocation++; // location is updated
        timing.lastDestinationIncriment = millis();
    }
}

void getUserInput(){ // gets user input from ps4 controller ( using serial.parseInt() for simulation and testing )
    // uint8_t userInputDestination = Serial.parseInt(); 
    uint8_t userInputDestination = getPS4ControllerInput();

    // if (Serial.available() == 0) userInputDestination = -1; // if user has not put anything... 

    if ((userInputDestination != agvStatus.agvLocation) && (userInputDestination != -1)) {
        agvStatus.agvDestination = userInputDestination;
        agvStatus.hasDestination = true; 
        Serial.print(agvStatus.agvDestination);
        // Serial.println(" is your destination");

    } else if (userInputDestination == -1) {
        // Serial.println("input a destination...");
        
    } else if (userInputDestination == agvStatus.agvLocation) {
        // Serial.println("AGV is already at location, try again");
    }
}

void alertOnce(Melodies melody) { // only alerts user with melody once per state
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
    if ( millis() - timing.lastDistanceSensorScan >= SCAN_INTERVAL) { // scan for obstacles every 200ms
        timing.lastDistanceSensorScan = millis();
        if ( ultraSonicScan() < OBSTACLE_DETECTION_THRESHOLD ) agvStatus.isPathObstructed = true;    // check if there is obstacle
        else agvStatus.isPathObstructed = false;  // if no obstacles...
    }

    //=================================================================================================================================

    switch(agvStatus.currentAGVState) {
        case STATUS_IDLE: // state 0 __________________________________________________________________________________________________
            LEDBlinker(1000, 250);
            getUserInput(); // get user destination input

            if(agvStatus.isCarryingLoad && agvStatus.hasDestination) { // checks if load has been placed and destination has been given
                agvStatus.currentAGVState = STATUS_TRAVELLING; // if a load has been placed agv will start traveling
                alertOnce(PACKAGE_RECEIVED_MELODY);
                digitalWrite(LED_PIN,LOW); // reset leds
            }
            break;

        case STATUS_TRAVELLING: // state 1 ____________________________________________________________________________________________
            lineScan(); // check and update robots position on the line
            trackLocation(); // check and update robots location

            if (agvStatus.agvDestination == agvStatus.agvLocation) { // if destination has been reached the agv will start unloading
                agvStatus.currentAGVState = STATUS_UNLOADING;  
                agvStatus.hasBeenAlerted = false; // reset alert flag
                // NOTE: should also move forward a bit past the cross
            }
            if (agvStatus.isPathObstructed) { // if object detected...
                agvStatus.currentAGVState = STATUS_OBSTACLE_OBSTRUCTION; 
                agvStatus.hasBeenAlerted = false;
            } else lineFollowingAlgo(); // if no object detected, keep following the line
            break;
        
        case STATUS_OBSTACLE_OBSTRUCTION: // state 2  __________________________________________________________________________________
            L298Driver(STOP,OFF); // stop and flash LEDs quickly until obstacle is taken away
            alertOnce(OBJECT_DETECTED_MELODY);
            LEDBlinker(100,100); 

            if (!agvStatus.isPathObstructed) { // if obstacle is taken away go back to traveling
                agvStatus.currentAGVState = STATUS_TRAVELLING;
                agvStatus.hasBeenAlerted = false; 
                digitalWrite(LED_PIN,LOW); 
            }
            break;

        case STATUS_UNLOADING: // state 3  _____________________________________________________________________________________________
            L298Driver(STOP,OFF); // stop and wait for user to remove load
            alertOnce(DESTINATION_REACHED_MELODY);
            agvStatus.agvDestination = -1; // reset chosen destination 
            agvStatus.hasDestination = false;
            if (!agvStatus.isCarryingLoad) agvStatus.currentAGVState = STATUS_IDLE; // if load is removed go back to your idle state
            break;

        case STATUS_ERROR: // state 4  _________________________________________________________________________________________________
            alertOnce(ERROR_MELODY); // 
            break;

        default: // if invalid state
            agvStatus.currentAGVState = STATUS_ERROR;
            break;
    }
    Serial.print(" STATE: "); Serial.println(agvStatus.currentAGVState);
    Serial.printf(" LOCATION: %d, DESTINATION: %d ", agvStatus.agvLocation, agvStatus.agvDestination);
}

// https://www.circuitbasics.com/how-to-read-user-input-from-the-arduino-serial-monitor/ 

/*

future improvements
1. when the robot reaches the end of the line is should possibly do a u turn and go back, looping forever
2. emergency stop with ps4 controller
3. error handling state machine inside of main state machine

void uTurn() {  // ***** in progress
    // uturn flag true
    // go forward for half a second to get off cross
    // turn left until left ir sensor is on line
    // if left ir sensor is on line keep turning left until both ir sensors are not on line, (robot is on track)
    // urturn flag false
}

*/