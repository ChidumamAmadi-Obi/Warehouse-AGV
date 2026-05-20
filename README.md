# Warehouse AGV 
*(3rd Year Capstone Project)*

Automated Guided Vehicle that transports loads along predetermined paths. Features line following, obstacle detection, location tracking, and PS4 controller input via Bluetooth. Built with a Finite State Machine (FSM) architecture with LED/buzzer alerts for user feedback.

### Links
 - [**Demo Video**](https://github.com/user-attachments/assets/4ddb8e79-1c91-4d6d-a385-816ef9b9aa53) <br>
 - [*STL Files*](https://github.com/ChidumamAmadi-Obi/Warehouse-AGV/tree/main/mechanical%20design/STL%20FIles) <br>
 - [*Gerber Files*](https://github.com/ChidumamAmadi-Obi/Warehouse-AGV/tree/main/hardware/gerbers-files) <br>
 - [*Schematic Diagram*](https://github.com/ChidumamAmadi-Obi/Warehouse-AGV/blob/main/hardware/schematic-pdf.pdf) <br>
 - [*Firmware Source Code*](https://github.com/ChidumamAmadi-Obi/Warehouse-AGV/tree/main/firmware) <br>

<img width="845" height="429" alt="image" src="https://github.com/user-attachments/assets/c0beffa6-a7b3-4663-b2af-edc8c3e35523" />

### Features
- PS4 Bluetooth controller for destination waypoints
- Line following with obstacle avoidance
- Real-time location tracking with waypoint markers on track
- Finite State Machine with robust transitions 
- Visual/audio alerts (LEDs & buzzer)
- 3D printable chassis (STL files included)
- Custom PCB with integrated motor driver, voltage regulation and sensor headers

### Firmware Prerequisites
The chosen controller needs to be paired with the ESP32’s Bluetooth MAC address before use.
Additionally, project also relies on [this](https://github.com/pablomarquez76/PS4_Controller_Host/tree/main) ps4 controller library to handle the Bluetooth communication between the ESP32 and the PS4 controller.

Once this library is installed it is to be inserted into the `./lib` PlatformIO project directory

### Custom PCB
<img width="835" height="428" alt="image" src="https://github.com/user-attachments/assets/a431d56e-2ec1-41e9-bd5c-a05350027860" />

### Schematic Diagram
<img width="1172" height="808" alt="image" src="https://github.com/user-attachments/assets/a0ec0011-8499-48c1-8c18-9887b932f3a0" />

### State Diagram
<img width="1482" height="720" alt="image" src="https://github.com/user-attachments/assets/7069c154-9a0f-4674-ab5c-f3d895138404" />


