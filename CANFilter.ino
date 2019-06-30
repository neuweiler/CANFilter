/**
 * The CanFilter reads status information about the operation of the DCDC converter and the speed of the
 * motor in an electric vehicle and modifies messages from the engine control unit (ECU) of a Volvo S80 2008
 * to simulate a running engine and alternator so that high power consumption devices like demist,
 * seat ventilation / heater, BlindSpotIndicationSystem and swival headlights work.
 * It also modifies the RPM message so the dashboard shows the correct engine speed.
 */

#include <Arduino.h>
#include <variant.h>
#include <due_can.h>
#include "config.h"
#include "Car.h"
#include "Engine.h"

bool led = false;

/**
 * Initialize the devices
 */
void setup()
{
    SerialUSB.begin(CFG_SERIAL_SPEED);

    pinMode(CFG_IO_BLINK_LED, OUTPUT);
    digitalWrite(CFG_IO_BLINK_LED, LOW);

    car.initialize(&Can0, &Can1);
    engine.initialize(&Can1, &Can0);
}

/**
 * Main loop which does nothing but print some status info and blink the led.
 * The CAN messages are handled via interrupt / callback.
 */
void loop()
{
    delay(CFG_LOOP_DELAY);

    SerialUSB.println(car.isRunning());

    led = !led;
    digitalWrite(CFG_IO_BLINK_LED, led);
}
