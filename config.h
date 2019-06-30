/*
 * config.h
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#ifndef CONFIG_H_
#define CONFIG_H_

//#define SerialUSB Serial // uncomment to redirect output to slower programming USB port
//#define LOG_FRAMES // uncomment to print frames (may take too much time to process all messages!)
#define CFG_IO_BLINK_LED 13 // 13 is L, 73 is TX, 72 is RX
#define CFG_SERIAL_SPEED 115200
#define CFG_LOOP_DELAY 1000

// config for can bus connected to car control units (GEVCU)
#define CAN_CAR_SPEED CAN_BPS_500K
#define CAN_CAR_NUM_TX_BOXES 3
#define CAN_CAR_MBOX_STATUS 0
#define CAN_CAR_TIMEOUT 2000

// config for can bus connected to engine control unit (ECU)
#define CAN_ENGINE_SPEED CAN_BPS_500K
#define CAN_ENGINE_NUM_TX_BOXES 3
#define CAN_ENGINE_MBOX_RUNNING 0
#define CAN_ENGINE_MBOX_ALTERNATOR 1
#define CAN_ENGINE_MBOX_RPM 2

#endif /* CONFIG_H_ */
