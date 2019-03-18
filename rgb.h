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

/*
/sound frequency (THz) x40 = light frequency (nm)
/
/Red is more dominant in the light spectrum due to its long wavelength.
/avg diff (THz): 30 THz per half note on scale
*/
#define F4  349 //near-black (51,0,0) to (0,0,0) circles up to F5 ////3342336
#define FS4 370 // (102,0,0)
#define G4  392 // (153,0,0)
#define GS4 415 // (204,0,0)
#define A4  440 //bright red (roughly 255,0,0) ////16711680
#define AS4 466
#define B4  494 
#define C5  523 //bright green (roughly 0,255,0) ////65280
#define CS5 554
#define D5  587
#define DS5 622 //full blue (roughly 0,0,255)
#define E5  659
#define F5  698 //near-black (0,0,0) to (0,0,51) circles down to F4


void InitTCS3200();

void TCSSelectRed();
void TCSSelectGreen();
void TCSSelectBlue();
void TCSSelectClear();

uint32_t TCSMeasure();


#endif