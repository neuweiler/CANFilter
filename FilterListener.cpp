/*
 * FilterListener.cpp
 *
 * An abstract class for the car and engine filters providing some basic logging functionality
 * and holds the incoming and outgoing can bus.
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#include "FilterListener.h"

FilterListener::FilterListener()
{
    in = out = NULL;
}

FilterListener::~FilterListener()
{
}

void FilterListener::initialize(CANRaw *in, CANRaw *out)
{
    this->in = in;
    this->out = out;
}

void FilterListener::printFrame(CAN_FRAME *frame, int mailbox, char *source)
{
    SerialUSB.print(source);
    SerialUSB.print(", MB: ");
    SerialUSB.print(mailbox);
    SerialUSB.print(" ID: 0x");
    SerialUSB.print(frame->id, HEX);
    SerialUSB.print(" Len: ");
    SerialUSB.print(frame->length);
    SerialUSB.print(" Data: 0x");
    for (int count = 0; count < frame->length; count++) {
        SerialUSB.print(frame->data.bytes[count], HEX);
        SerialUSB.print(" ");
    }
    SerialUSB.print("\r\n");
}

