/*
 * Car.h
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#ifndef CAR_H_
#define CAR_H_

#include "FilterListener.h"

class Car: public FilterListener
{
public:
    Car();
    void initialize(CANRaw *in, CANRaw *out);
    void gotFrame(CAN_FRAME *frame, int mailbox);
    bool isRunning();
    uint16_t getRpm();
private:
    uint16_t rpm; // the rpm reported by GEVCU
    bool powerOn; // flag to indicate if the dcdc converter is running
    uint32_t lastMessage; // timestamp when we got the last message from GEVCU
};

extern Car car;

#endif /* CAR_H_ */
