# RESQ ROVER – Autonomous Obstacle-Avoiding Rescue Rover

## Project Overview

RESQ ROVER is a 4WD robotic rover built as an embedded hardware / robotics project. It uses an Arduino UNO as the main controller, an HC-SR04 ultrasonic sensor mounted on an SG90 servo for directional distance scanning, and an L298N motor driver to control four DC geared motors. The rover detects obstacles in its path and reacts using rule-based logic to avoid them, without any manual remote control.

## Objectives

- Detect obstacles in the rover's path using an ultrasonic sensor
- Measure distance to obstacles in real time
- Perform directional scanning (left/right) using a servo-mounted sensor
- Control four DC geared motors through an L298N motor driver
- Implement autonomous, rule-based obstacle avoidance
- Integrate the Arduino UNO with the sensor, servo, and motor driver into a working 4WD platform

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino UNO | Main microcontroller / logic |
| HC-SR04 Ultrasonic Sensor | Distance measurement / obstacle detection |
| SG90 Servo Motor | Rotates the ultrasonic sensor for left/right scanning |
| L298N Motor Driver | Drives the four DC geared motors |
| 4x DC Geared Motors | Wheel drive |
| 4WD Robotic Chassis | Rover body/platform |
| Rechargeable Battery Pack | Power source |
| Battery Holder | Holds the battery pack |
| ON/OFF Switch | Power control |

## Pin Configuration

| Component | Pin (Arduino) | Function |
|---|---|---|
| HC-SR04 | D9 | TRIG |
| HC-SR04 | D10 | ECHO |
| SG90 Servo | D3 | Signal |
| L298N | D5 | ENA |
| L298N | D7 | IN1 |
| L298N | D8 | IN2 |
| L298N | D6 | ENB |
| L298N | D11 | IN3 |
| L298N | D12 | IN4 |

*(Verified against `arduino/resq_rover.ino`. ENA/IN1/IN2 drive the left-side motors, ENB/IN3/IN4 drive the right-side motors.)*

## Working Principle

1. The rover starts and initializes the sensor, servo, and motor driver.
2. The HC-SR04 continuously measures the distance directly ahead.
3. If the path is clear (distance greater than the defined safe distance, 25 cm), the rover moves forward.
4. If an obstacle is detected within 25 cm, the rover stops.
5. The SG90 servo rotates the ultrasonic sensor to scan the left (150°) and right (30°) directions.
6. The Arduino compares the two measured distances.
7. The rover turns toward whichever side has the greater (clearer) distance.
8. If both the left and right directions are blocked (both readings below the safe distance), the rover reverses briefly and then re-scans.
9. This cycle repeats continuously, allowing the rover to navigate around obstacles.

## Software

- Arduino IDE
- Arduino Embedded C/C++ (using the built-in `Servo.h` library)
- Serial Monitor (used for printing live distance readings and rover status at 9600 baud)

## Repository Structure

```
resq-rover/
│
├── README.md
│
├── arduino/
│   └── resq_rover.ino
│
├── diagrams/
│
├── photos/
│   ├── prototype_front_closeup.png
│   ├── prototype_front_full.png
│   └── prototype_top_internals.png
│
└── documentation/
    └── project_notes.md
```

> Note: The `diagrams/` folder is currently empty. No block diagram, circuit diagram, logical design, or flowchart images were available at the time this repository was prepared. Add these files to the `diagrams/` folder later if/when they are created.

## How to Upload the Code

1. Open Arduino IDE.
2. Open `arduino/resq_rover.ino`.
3. Select **Board → Arduino UNO**.
4. Select the correct COM port under **Tools → Port**.
5. Click **Upload**.
6. Open the Serial Monitor (baud rate **9600**) to view live distance readings and rover status messages.

## Project Images

The `photos/` folder contains photographs of the assembled prototype:

- `prototype_front_closeup.png` – Close-up front view showing the HC-SR04 mounted on the SG90 servo
- `prototype_front_full.png` – Full front view of the assembled 4WD rover
- `prototype_top_internals.png` – Top-down view showing the Arduino UNO, L298N driver, wiring, and battery pack

## Project Status

RESQ ROVER has been developed and prototyped as a working Arduino UNO-based 4WD rover with rule-based ultrasonic obstacle detection and avoidance, driven by the logic implemented in `arduino/resq_rover.ino`.

## Future Scope

This section is intentionally left minimal, as no additional future-work details were provided in the project material beyond the current implementation.
