/*/////////////////////
COLORBLIND ASSISTANT
Ultrasonic Proximity Sensor
Referenced and adapted from a C++ version of the library by: 
https://github.com/JRodrigoTech/Ultrasonic-HC-SR04
Modified to be used on ATmega1284 in C by Bryan Walsh

*Enables trigger bit to emit ultrasonic for 10us
*Waits for echo pin to be set high, while incrementing counter
*Calculates distance by dividing counter and speed of sound to get
distance in CM
*//////////////////////

#ifndef USOUND_H
#define USOUND_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>

#define US_DDR		DDRB
#define US_PORT		PORTB
#define US_PIN		PINB

#define US_TRIGGER	PINB2
#define US_ECHO		PINB0



void usound_init(void); //reset bits and prepare to set Trigger PINB2 to high

float readDistance(void);

#endif