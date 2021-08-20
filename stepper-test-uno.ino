
#include <Arduino.h>
#include <A4988.h>
#include <BasicStepperDriver.h>
#include <MultiDriver.h>
#include <SyncDriver.h>

#define MOTOR_STEPS 200 // using a 200-step motor (most common)
// configure the pins connected

#define DIR 5
#define STEP 6
#define MS1 7
#define MS2 8
#define MS3 9
#define MICROSTEPS 16
#define RPM 120

A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

long revolutions = 0;
short direction = 1;
void setup()
{
    Serial.begin(9600);
    stepper.begin(RPM, MICROSTEPS);
    Serial.println("Start 1:16");
}

void loop()
{
    revolutions += 0.5;
    stepper.rotate(direction * 1 * 180); // in microsteps
    Serial.println(revolutions);
}
