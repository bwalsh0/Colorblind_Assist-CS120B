/*/////////////////////
COLORBLIND ASSISTANT
Ultrasonic Proximity Sensor
Referenced and adapted from a C++ version of the library by:
https://github.com/JRodrigoTech/Ultrasonic-HC-SR04
Modified to be used on ATmega1284 in C by Bryan Walsh
*//////////////////////

#include "usound.h"

void usound_init(void)
{
    US_DDR |= (1 << US_TRIGGER) | (0 << US_ECHO);
    US_PIN |= (1 << US_ECHO);
}

float readDistance(void) //My usound proximity sensor uses serialization instead of i2c
{
    float status, distToTime = 0;

    _delay_us(2);
    
    US_PORT |= (1 << US_TRIGGER); //keep high for 10 us here, enables trigger bit so that it will output ultrasonic
    _delay_us(10);                //10us recommended by the datasheet
    
    US_PORT &= ~(1 << US_TRIGGER); //clear trigger bit after 10us

    while(status == 0)
    {
        while(US_PIN & (1 << US_ECHO)) //Read input data from Echo (PB0) into PinB
        {
            distToTime++;
            status = 1;
        }
    }

    return distToTime * 0.00862; 
    //calibrated/normalized data in CM, per the datasheet and self-testing
}