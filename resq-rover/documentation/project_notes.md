# Project Notes – RESQ ROVER

## Project Title
RESQ ROVER – Autonomous Obstacle-Avoiding Rescue Rover

## Project Type
Embedded Hardware / Robotics project (Arduino-based)

## System Overview
RESQ ROVER is a 4WD rover controlled by an Arduino UNO. It uses an HC-SR04 ultrasonic sensor mounted on an SG90 servo to detect obstacles ahead and scan left/right when blocked. An L298N motor driver controls four DC geared motors, allowing the rover to move forward, reverse, and turn. The obstacle-avoidance behaviour is fully rule-based and runs autonomously once powered on — there is no remote control or external navigation aid involved.

## Hardware List
- Arduino UNO
- HC-SR04 ultrasonic sensor
- SG90 servo motor
- L298N motor driver
- 4x DC geared motors
- 4WD robotic chassis
- Rechargeable battery pack
- Battery holder
- ON/OFF switch

## Pin Configuration

| Component | Pin | Function |
|---|---|---|
| HC-SR04 | D9 | TRIG |
| HC-SR04 | D10 | ECHO |
| SG90 Servo | D3 | Signal |
| L298N | D5 | ENA (left motors enable) |
| L298N | D7 | IN1 |
| L298N | D8 | IN2 |
| L298N | D6 | ENB (right motors enable) |
| L298N | D11 | IN3 |
| L298N | D12 | IN4 |

Additional constants used in code:
- `SAFE_DISTANCE = 25` cm — threshold below which an object is treated as an obstacle
- `MOTOR_SPEED = 230` — PWM value (0–255) applied to ENA/ENB
- `CENTER_ANGLE = 90°`, `LEFT_ANGLE = 150°`, `RIGHT_ANGLE = 30°` — servo scan positions

## Working Principle
1. Initialize sensor, servo (centered), and motor driver pins; motors start stopped.
2. Continuously measure distance directly ahead using the HC-SR04.
3. If the distance is greater than `SAFE_DISTANCE` (or the sensor times out), move forward.
4. If an obstacle is within `SAFE_DISTANCE`:
   - Stop the rover.
   - Sweep the servo to `LEFT_ANGLE` and measure distance, then to `RIGHT_ANGLE` and measure distance.
   - Return the servo to `CENTER_ANGLE`.
   - If both left and right distances are below `SAFE_DISTANCE`, reverse briefly and stop.
   - Otherwise, turn toward whichever side gave the larger distance reading.
5. Repeat the loop continuously (100 ms delay between cycles).

Distance is calculated from the HC-SR04 echo pulse duration using the standard formula: `distance = duration * 0.0343 / 2` (cm). A sensor timeout (`pulseIn` returning 0 within 30 ms) is treated as "no obstacle detected" (-1), which is handled as a clear path.

## Software Used
- Arduino IDE
- Arduino Embedded C/C++
- `Servo.h` library (for SG90 control)
- Serial Monitor at 9600 baud (used for debug output of distance readings and rover state)

## Repository Contents
- `README.md` — Project overview, hardware, pin map, working principle, and usage instructions
- `arduino/resq_rover.ino` — Original, unmodified Arduino source code
- `diagrams/` — Reserved for block diagram, circuit diagram, logical design, and flowchart (currently empty — none were available at time of upload)
- `photos/` — Photographs of the assembled physical prototype
- `documentation/project_notes.md` — This file
