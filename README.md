# CANFilter
A CAN filter to spoof a running engine and rpm signal in a Volvo S80 2008

The basic principle is that it receives rpm of the electirc motor and the status of the DCDC converter from the GEVCU.
Depending on this information, the messages coming from the engine control unit (ECU) are then modified to spoof:

* a running engine
* an operating alternator and coolant system
* the correct rpm signal so it's displayed correctly in the dashboard

The application uses the more advanced interrupt/callback mechanism of the due_can library by Collin Kidder.
It requires an Arduino Due and a CAN shield with two CAN tranceivers.
