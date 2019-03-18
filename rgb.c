/*/////////////////////
COLORBLIND ASSISTANT
Color Sensor Library
I frankensteined some code from a TCS3200 sensor library, a similar non-i2c color sensor
and also the Adafruit C++ library for the TCS34725 sensor.

TCS3200: http://extremeelectronics.co.in/avr-tutorials/interfacing-tcs3200-colour-sensor-with-avr-atmega32/
TCS34725: https://github.com/adafruit/Adafruit_TCS34725
*//////////////////////

#include <avr/io.h>
#include <avr/interrupt.h>
#include "rgb.h"
#include "io.h"

void InitTCS3200()
{
	//SDA/SLK
	TCS_S2_DDR|=(1<<TCS_S2_POS);
	TCS_S3_DDR|=(1<<TCS_S3_POS);
	
	//LED Port
	TCS_LED_DDR|=(1<<TCS_LED_POS);	
}


void TCSSelectRed()
{
	TCSS2Low();
	TCSS3Low();
}

void TCSSelectGreen()
{
	TCSS2High();
	TCSS3High();
}

void TCSSelectBlue()
{
	TCSS2Low();
	TCSS3High();
}

void TCSSelectClear()
{
	TCSS2High();
	TCSS3Low();
}

uint32_t TCSMeasure() 
{
	if(!(TCS_OUT_PORT & (1<<TCS_OUT_POS))) {
		while(!(TCS_OUT_PORT & (1<<TCS_OUT_POS)));	//Wait for rise	
	}
	
	while(TCS_OUT_PORT & (1<<TCS_OUT_POS));	//Wait for fall
	
	TCNT1=0x0000; //Reset counter
	TCCR1B=(1<<CS10);	//Begin timer (F_CPU/1)
	
	while(!(TCS_OUT_PORT & (1<<TCS_OUT_POS)));	//Wait for rise
	
	TCCR1B=0x00; //Stop Timer
    
    //LCD_DisplayString(1, TCNT1);
    //_delay_ms(1000);
    
	
	return ((float)8000000UL/TCNT1);
}