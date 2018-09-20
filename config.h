/*
 * config.h
 *
 *  Created on: 20 Sep 2018
 *      Author: michaeln
 */

#ifndef CONFIG_H_
#define CONFIG_H_

//#define SerialUSB Serial // uncomment to redirect output to programming USB port
//#define LOG_FRAMES // uncomment to print frames (may take too much time to process all messages!)
#define CFG_IO_BLINK_LED 13 // 13 is L, 73 is TX, 72 is RX
#define CFG_SERIAL_SPEED 115200
#define CFG_LOOP_DELAY 5000

#define NUM_TX_BOXES_CAR 3
#define MBOX_CAR_STATUS 0
#define GEVCU_TIMEOUT 2000

#define NUM_TX_BOXES_ENGINE 3
#define MBOX_ENGINE_RUNNING 0
#define MBOX_ENGINE_ALTERNATOR 1
#define MBOX_ENGINE_RPM 2

#endif /* CONFIG_H_ */
