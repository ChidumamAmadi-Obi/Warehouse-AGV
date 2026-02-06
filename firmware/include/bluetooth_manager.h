#pragma once

#include "config.h"

// will handle ps4 controller inputs / outputs here
// Note: the ps4 controller must be linked to the esp32's MAC address to work

uint8_t getPS4ControllerInput(){ // gets user input and turns it into a usable interger number
    uint8_t ps4Input = -1;
    if (PS4.isConnected()) {
        if (PS4.Square()) ps4Input = 0;
        else if (PS4.Cross()) ps4Input = 1;
        else if (PS4.Circle()) ps4Input = 2;
        else if (PS4.Triangle()) ps4Input = 3;

        else if (PS4.R1()) ps4Input = 4; // emergency stop
    }
    return ps4Input;
}

// refs & explanations
// https://www.youtube.com/watch?v=dRysvxQfVDw esp32 and ps4 controller how to
// https://github.com/pablomarquez76/PS4_Controller_Host/tree/main/examples where i got the library
