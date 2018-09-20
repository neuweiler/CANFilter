/*
 * Engine.h
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "FilterListener.h"
#include "Car.h"

class Engine: public FilterListener
{
public:
    void initialize(CANRaw *in, CANRaw *out);
    void gotFrame(CAN_FRAME *frame, int mailbox);
};

extern Engine engine;

#endif /* ENGINE_H_ */
