#ifndef BLUETOOTH // header gaurds
#define BLUETOOTH

#include "config.h"

// will handle ps4 controller inputs / outputs here
// Note: the ps4 controller must be linked to the esp32's MAC address to work

int getPS4ControllerInput(){ // gets user input and turns it into a usable interger number
    int PS4InputDestination = -1;
    if (PS4.isConnected()) {
        if (PS4.Square()) PS4InputDestination = 0;
        if (PS4.Cross()) PS4InputDestination = 1;
        if (PS4.Circle()) PS4InputDestination = 2;
        if (PS4.Triangle()) PS4InputDestination = 3;
        else PS4InputDestination = -1; // invalid user input
    }
    return PS4InputDestination;
}

#endif

// refs & explanations
// https://www.youtube.com/watch?v=dRysvxQfVDw esp32 and ps4 controller how to
// https://github.com/pablomarquez76/PS4_Controller_Host/tree/main/examples where i got the library
