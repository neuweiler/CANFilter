/*
 * Engine.cpp
 *
 *  Reads the can messages from the engine control unit (ECU), modifies  and
 *  forwards them to the remaining car infrastructure.
 *  It intercepts the message which indicates if the engine is running, the one which
 *  sends the engine speed and then one which indicates the alternator operation and
 *  coolant information.
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#include "Engine.h"

/**
 * Sets the incoming and outgoing can bus and initializes the incoming bus
 * so that enough TX mailboxes are available and the callback for incoming messages
 * is attached to the due_can interrupt.
 */
void Engine::initialize(CANRaw *in, CANRaw *out)
{
    FilterListener::initialize(in, out);

    in->begin(CAN_ENGINE_SPEED, 255);
    in->setNumTXBoxes(CAN_ENGINE_NUM_TX_BOXES);
    in->setRXFilter(CAN_ENGINE_MBOX_RUNNING, 0x167, 0x7FF, false); // engine running
    in->setRXFilter(CAN_ENGINE_MBOX_ALTERNATOR, 0x3d3, 0x7FF, false); // alternator status
    in->setRXFilter(CAN_ENGINE_MBOX_RPM, 0x12a, 0x7FF, false); // rpm (interval 15ms)
    in->setRXFilter(3, 0, 0, false); // catch all standard messages
    in->setRXFilter(4, 0, 0, true); // catch all extended messages

    in->attachObj(this);
    attachMBHandler(CAN_ENGINE_MBOX_RUNNING);
    attachMBHandler(CAN_ENGINE_MBOX_ALTERNATOR);
    attachMBHandler(CAN_ENGINE_MBOX_RPM);
    attachGeneralHandler();
}

/**
 * Callback function called from due_can when a message has arrived and the interrupt was triggered
 */
void Engine::gotFrame(CAN_FRAME* frame, int mailbox)
{
    if (car.isRunning()) { // only manipulate when car reports ready
        switch (mailbox) {
        case CAN_ENGINE_MBOX_RUNNING:
            frame->data.bytes[4] |= 0x40; // set the bit "engine running"
            break;
        case CAN_ENGINE_MBOX_ALTERNATOR: // signal a working alternator and coolant system
            frame->data.bytes[0] = 0x24;
            frame->data.bytes[1] = 0x42;
            frame->data.bytes[2] = 0x0;
            frame->data.bytes[3] = 0x4;
            frame->data.bytes[4] = 0x75;
            frame->data.bytes[5] = 0x78;
            frame->data.bytes[6] = 0x76;
            frame->data.bytes[7] = 0x8;
            break;
        case CAN_ENGINE_MBOX_RPM: // replace the engine speed with the one of the electric motor
            uint16_t rpm = car.getRpm();
            frame->data.bytes[6] = 0xe0 | (rpm & 0xff00) >> 8;
            frame->data.bytes[7] = rpm & 0xff;
            break;
        }
    }
    out->sendFrame(*frame);

#ifdef LOG_FRAMES
    this->printFrame(frame, mailbox, "engine");
#endif
}

Engine engine;
