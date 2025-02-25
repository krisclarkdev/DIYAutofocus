#include <Wire.h>
#include <VL53L0X.h>
#include <AccelStepper.h>

// Stepper Motor Pins
#define DIR_PIN 5
#define STEP_PIN 6
#define ENABLE_PIN 7  // LOW = Enabled

// Autofocus Range (Adjust for Your Lens)
#define NEAR_DISTANCE 300  // mm (Closest focus)
#define FAR_DISTANCE 2000  // mm (Farthest focus)
#define FOCUS_STEPS 400  // Motor steps per full focus travel

// Initialize VL53L0X Distance Sensor
VL53L0X sensor;

// Initialize Stepper Motor with AccelStepper Library
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Initialize Distance Sensor
    sensor.init();
    sensor.setTimeout(500);
    sensor.startContinuous();

    // Setup Stepper Motor
    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, LOW);  // Enable motor driver

    stepper.setMaxSpeed(1000);  // Steps per second
    stepper.setAcceleration(500);  // Smooth acceleration
}

void loop() {
    // Read Distance
    int distance = sensor.readRangeContinuousMillimeters();
    
    // Handle sensor timeout
    if (sensor.timeoutOccurred()) {
        Serial.println("VL53L0X Timeout!");
        return;
    }
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" mm");

    // Map distance to stepper position
    int focusPosition = map(distance, NEAR_DISTANCE, FAR_DISTANCE, 0, FOCUS_STEPS);
    focusPosition = constrain(focusPosition, 0, FOCUS_STEPS);

    // Move stepper to focus position
    stepper.moveTo(focusPosition);
    stepper.run();
}
