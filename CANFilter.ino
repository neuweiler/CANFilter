#include "Arduino.h"
#include "variant.h"
#include <due_can.h>

#define Serial SerialUSB
#define NUM_TX_BOXES_0 2
#define NUM_TX_BOXES_1 2
//#define LOG_FRAMES

uint16_t rpm = 0;
CAN_FRAME incoming;

void setup()
{
#ifdef LOG_FRAMES
    Serial.begin(115200);
#endif

    Can0.begin(CAN_BPS_500K, 255); // CEM
    Can1.begin(CAN_BPS_500K, 255); // ECM

    Can0.setNumTXBoxes(NUM_TX_BOXES_0);
    Can1.setNumTXBoxes(NUM_TX_BOXES_1);

//    for (int mailbox = 0; mailbox <= 7 - NUM_TX_BOXES_0; mailbox++) {
    Can0.setRXFilter(0, 0, 0, false);
    //  }
    //for (int mailbox = 0; mailbox <= 7 - NUM_TX_BOXES_1; mailbox++) {
    Can1.setRXFilter(0, 0, 0, false);
    // }
}

void printFrame(uint8_t bus, CAN_FRAME &frame)
{
    Serial.print(millis());
    Serial.print(" #");
    Serial.print(bus);
    Serial.print(" ID: 0x");
    Serial.print(frame.id, HEX);
    Serial.print(" len: ");
    Serial.print(frame.length);
    Serial.print(" Data: 0x");
    for (int count = 0; count < frame.length; count++) {
        Serial.print(frame.data.bytes[count], HEX);
        Serial.print(" ");
    }
    Serial.print("\r\n");
}

void loop()
{
    if (Can0.available() > 0) { // messages from CEM & Co.
        Can0.read(incoming);
        Can1.sendFrame(incoming);

        if (incoming.id == 0x129) {
            rpm = incoming.data.s0;
        }
#ifdef LOG_FRAMES
        printFrame(0, incoming);
#endif
    }
    if (Can1.available() > 0) { // messages from ECM
        Can1.read(incoming);
        switch (incoming.id) {
        case 0x167:
            incoming.data.bytes[4] |= 0x40; // bit "engine running"
            break;
        case 0x3d3: // alternator power, water cooling system ?
            incoming.data.bytes[0] = 0x24;
            incoming.data.bytes[1] = 0x42;
            incoming.data.bytes[2] = 0x0;
            incoming.data.bytes[3] = 0x4;
            incoming.data.bytes[4] = 0x75;
            incoming.data.bytes[5] = 0x78;
            incoming.data.bytes[6] = 0x76;
            incoming.data.bytes[7] = 0x8;
            break;
        case 0x12a: //interval : 15ms
            incoming.data.bytes[6] = 0xe0 | (rpm & 0xff00) >> 8;
            incoming.data.bytes[7] = rpm & 0xff;
            break;
        }
        Can0.sendFrame(incoming);
#ifdef LOG_FRAMES
        printFrame(1, incoming);
#endif
    }
}

            
