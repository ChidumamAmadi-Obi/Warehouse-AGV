/* BLUE TOOTH MANAGER
 inputs and outputs from the 
 ps4 controller via blue tooth
 are managed here
*/

#pragma once

#include "config.h"

// will handle ps4 controller inputs / outputs here
// Note: the ps4 controller must be linked to the esp32's MAC address to work

PS4Inputs getPS4ControllerInput(){ // gets user input and turns it into a usable interger number
    PS4Inputs ps4Input = INVALID;
    if (PS4.isConnected()) {
        if (PS4.Square()) ps4Input = STATION_HOME;
        else if (PS4.Cross()) ps4Input = STATION_ONE;
        else if (PS4.Circle()) ps4Input = STATION_TWO;
        else if (PS4.Triangle()) ps4Input = STATION_THREE;

        else if (PS4.R1()) ps4Input = EMERGENCY_STOP; // emergency stop
    }
    return ps4Input;
}

// refs & explanations
// https://www.youtube.com/watch?v=dRysvxQfVDw esp32 and ps4 controller how to
// https://github.com/pablomarquez76/PS4_Controller_Host/tree/main/examples where i got the library
