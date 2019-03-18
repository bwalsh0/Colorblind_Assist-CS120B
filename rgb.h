/*/////////////////////
COLORBLIND ASSISTANT
Color Sensor Library
I frankensteined some code from a TCS3200 sensor library, a similar non-i2c color sensor
and also the Adafruit C++ library for the TCS34725 sensor.

TCS3200: http://extremeelectronics.co.in/avr-tutorials/interfacing-tcs3200-colour-sensor-with-avr-atmega32/
TCS34725: https://github.com/adafruit/Adafruit_TCS34725
*//////////////////////

#ifndef TCS3200_H_
#define TCS3200_H_

//SCL (yellow wire) [clock]
#define TCS_S2_DDR DDRC
#define TCS_S2_PORT PORTC
#define TCS_S2_POS PC0

//SDA (orange) [data]
#define TCS_S3_DDR DDRC
#define TCS_S3_PORT PORTC
#define TCS_S3_POS PC1

//LED Color sensor's light
#define TCS_LED_DDR DDRA
#define TCS_LED_PORT PORTA
#define TCS_LED_POS PA3

#define	TCSS2High()	TCS_S2_PORT |= (1<<TCS_S2_POS)
#define	TCSS2Low()	TCS_S2_PORT &=~ (1<<TCS_S2_POS)
#define	TCSS3High()	TCS_S3_PORT |= (1<<TCS_S3_POS)
#define	TCSS3Low()	TCS_S3_PORT &=~ (1<<TCS_S3_POS)
#define TCSLEDOn()	TCS_LED_PORT |= (1<<TCS_LED_POS)
#define TCSLEDOff() TCS_LED_PORT &=~ (1<<TCS_LED_POS)

void InitTCS3200();

void TCSSelectRed();
void TCSSelectGreen();
void TCSSelectBlue();
void TCSSelectClear();

uint32_t TCSMeasure();


#endif