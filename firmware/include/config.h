#ifndef CONFIG // header gaurds
#define CONFIG

#include <Arduino.h> // for arduino framework functions
#include <PS4Controller.h> // for ps4 bluetooth control
#include <esp_task_wdt.h> // for watchdog timer

#define TRIG_PIN    23 // define pin numbers
#define ECHO_PIN    22
#define BUZZER_PIN  19
#define LED_PIN     18
#define BB_PIN      21
#define L_IR_PIN    4
#define R_IR_PIN    16
#define MOTOR_PIN_A1 25
#define MOTOR_PIN_A2 26
#define MOTOR_PIN_B1 32
#define MOTOR_PIN_B2 33

// define needed constants
#define SCAN_INTERVAL 200 // (ms) interval at which the ultrasonic distance sensor scans for objects
#define CORSE_CORRECTION_INTERVAL 100 
#define OBSTACLE_DETECTION_THRESHOLD 100 // 100cm
#define SPEED_OF_SOUND 0.034 // used to calculate distance
#define REST 50 // music speed
#define WDT_TIMEOUT 3 // watch dog timer times out after 3 seconds

typedef enum { // defines direction codes for motor driver
    RIGHT,
    LEFT,
    FORWARD,
    BACKWARD,
    STOP
} Dir;

typedef enum { // for agv states
    STATUS_IDLE,                    // waiting for a package, and a destination
    STATUS_TRAVELLING,              // traveling to destination
    STATUS_OBSTACLE_OBSTRUCTION,    // pausing until obstacle is removed
    STATUS_UNLOADING,               // when destination is reached...
    STATUS_ERROR 
} AGVState;

typedef enum { // defines melody codes for melody manager
    STARTUP_MELODY,
    OBJECT_DETECTED_MELODY,
    DESTINATION_REACHED_MELODY,
    ERROR_MELODY,
    PACKAGE_RECEIVED_MELODY
} Melodies;

typedef enum {
    OFF = 0,
    CRUISING_SPEED = 125,
    MAX_SPEED = 255
} SpeedModes;

typedef enum {
 // erros types here
} Errors;

typedef struct { // for agv status flags and other variables
    bool isOnLine = true;
    bool isDestinationReached = false;
    bool isCarryingLoad = false;
    bool isPathObstructed = false;  
    bool hasBeenAlerted = false;
    bool hasDestination = false;
    AGVState currentAGVState = STATUS_IDLE;  // keeps track of agv state
    unsigned long lastLineCorrection = 0.0; 
    int agvDestination = -1; // -1 means no chosen destination 
    int agvLocation = 0; // keeps track of which docking spot the robot is (0-3)
} AGVStatusFlags;

typedef struct { // using a struct encapsulates similar data making code more readable
    bool statusR = false; // on line
    bool statusL = false; // on line
    bool cross = false; // detects if bot is at a cross
} LineStatusFlags;

LineStatusFlags line;
AGVStatusFlags agvStatus;

#endif

// refs & explanations
// https://www.w3schools.com/c/c_enums.php 
// https://www.geeksforgeeks.org/c/structures-c/
// https://riptutorial.com/c/example/7662/header-include-guards
// https://iotassistant.io/esp32/enable-hardware-watchdog-timer-esp32-arduino-ide/ watchdog timer 

/*

enums were used here to give names to constant values, it makes
the program easier to read and maintain 
by default, the first member of an enum is equal to 0
the second is equal to 1 and so on

structs were used here to group related variables of different data types
into a single unit, making it easier to manage and organize complex data.
for example we have a struct for the AGV, this struct is used to store various bits
of information about the AGV like its location, state, load and sensor inputs

header gaurds were used here to make sure when header files are includes in multiple
places, like config.h, there are no duplicate delcarations

*/