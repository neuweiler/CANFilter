/*
 * Car.cpp
 *
 *  Reads the status message and engine speed from a specific message id and stores it
 *  for later use by the engine filter.
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#include "Car.h"

/**
 * Constructor
 */
Car::Car() :
        FilterListener()
{
    rpm = 0;
    powerOn = false;
    timestamp = 0;
}

/**
 * Sets the incoming and outgoing can bus and initializes the incoming bus
 * so that enough TX mailboxes are available and the callback for incoming messages
 * is attached to the due_can interrupt.
 */
void Car::initialize(CANRaw *in, CANRaw *out)
{
    FilterListener::initialize(in, out);

    in->begin(CAN_BPS_500K, 255);
    in->setNumTXBoxes(NUM_TX_BOXES_CAR);
    in->setRXFilter(MBOX_CAR_STATUS, 0x129, 0x7FF, false); // status and rpm from GEVCU
    in->setRXFilter(1, 0, 0, false); // catch all standard messages
    in->setRXFilter(2, 0, 0, true); // catch all extended messages

    in->attachObj(this);
    attachMBHandler(MBOX_CAR_STATUS);
    attachGeneralHandler();
}

/**
 * Callback function called from due_can when a message has arrived and the interrupt was triggered
 */
void Car::gotFrame(CAN_FRAME* frame, int mailbox)
{
    switch (mailbox) {
    case MBOX_CAR_STATUS: // read status information coming from the car
        rpm = frame->data.s0;
        powerOn = frame->data.s1 & 0x01;
        timestamp = millis();
        break;
    }
    out->sendFrame(*frame);

#ifdef LOG_FRAMES
    this->printFrame(frame, mailbox, "car");
#endif
}

/**
 * Indicates if the car reports a running DCDC converter.
 * If no message is received within a specified timeout, it is assumed the car was
 * turned off.
 *
 * \return true if the car / DCDC converter is running and no timeout occured
 */
bool Car::isRunning()
{
    return (powerOn && ((millis() - timestamp) < GEVCU_TIMEOUT));
}

/**
 * Get the engine rpm as reported by the electric motor controller
 *
 * \return the speed of the motor in rpm's
 */
uint16_t Car::getRpm()
{
    return rpm;
}

Car car;
