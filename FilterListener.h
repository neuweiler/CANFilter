/*
 * FilterListener.h
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#ifndef FILTERLISTENER_H_
#define FILTERLISTENER_H_

#include <due_can.h>
#include "config.h"

class FilterListener: public CANListener
{
public:
    FilterListener();
    virtual ~FilterListener();
    virtual void initialize(CANRaw *in, CANRaw *out);
    void printFrame(CAN_FRAME *frame, int mailbox, char* source);
protected:
    CANRaw *in; // can bus where data comes in
    CANRaw *out; // can bus where to send modified data to
};

#endif /* FILTERLISTENER_H_ */
