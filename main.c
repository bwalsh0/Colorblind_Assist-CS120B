/*/////////////////////
COLORBLIND ASSISTANT
Bryan Walsh
UC Riverside, CS 120B Winter 2019 - Lab Section 024
Final Project
Credits to references are given in .h and .c files 
*//////////////////////

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h> //Defining F_CPU works breaks timing for some reason, left undeclared

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

#include "io.h" //4x20 LCD Driver
#include "usound.h" //Ultrasonic Proximity Sensor Driver
#include "rgb.h" //Color Sensor Driver
#include "i2c.h" //i2c protocol for data, only used by color sensor for SDA/SCL

enum MODE {color, lcd, prox} DEBUG_MODE;

float value = 0;
const static char OORstr[20] = "Object too far";
const static char IRstr[10] = "In range";
unsigned char stringOutput[256]; //256 might be larger than needed

uint32_t MeasureR(), MeasureG(), MeasureB(), MeasureC();

void set_PWM(double frequency) {
    static double current_frequency; // Keeps track of the currently set frequency
    // Will only update the registers when the frequency changes, otherwise allows
    // music to play uninterrupted.
    if (frequency != current_frequency) {
        if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
        else { TCCR3B |= 0x03; } // resumes/continues timer/counter
        // prevents OCR3A from overflowing, using prescaler 64
        // 0.954 is smallest frequency that will not result in overflow
        if (frequency < 0.954) { OCR3A = 0xFFFF; }
        // prevents OCR3A from underflowing, using prescaler 64
        // 31250 is largest frequency that will not result in underflow
        else if (frequency > 31250) { OCR3A = 0x0000; }
        // set OCR3A based on desired frequency
        else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
        TCNT3 = 0; // resets counter
        current_frequency = frequency; // Updates the current frequency
    }
}
void PWM_on() {
    TCCR3A = (1 << COM3A0);
    // COM3A0: Toggle PB3 on compare match between counter and OCR3A
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    // WGM32: When counter (TCNT3) matches OCR3A, reset counter
    // CS31 & CS30: Set a prescaler of 64
    set_PWM(0);
}
void PWM_off() {
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

int main(void)
{
    uint8_t x = 0;
    int8_t vx = 1;
    unsigned char ret;
    
    DDRA = 0xFF; PORTA = 0x00; //init A as output
    DDRB = 0x3C; PORTB = 0xC3; //Set 4 bits B2-5 as LCD data out, other as input
    
    initModulesHelper();
    
    i2c_init();
    i2c_start_wait(0x29+I2C_WRITE); //Write to the color sensor's device address, I2C_WRITE converts address
            LCD_ClearScreen();
            LCD_DisplayString(1, "i2c initialized");
    if (!i2c_write(0x80)) {         //Write enable command
        LCD_ClearScreen();
        LCD_DisplayString(1, "i2c failed to write 0x80");
    }
    
    _delay_ms(50);                          //Wait before reading data, according to Fleury's documentation
        
    i2c_rep_start(0x29+I2C_READ);       // Read from address

    ret = i2c_readNak();                    // read one byte
    i2c_stop();
    
    state_p = Start_p;
        
    LCD_ClearScreen();
    while(1) {

        proxSensor();  
        
        TCSLEDOn();    
        _delay_ms(60);


                //Show
                uint32_t r,g,b;
                LCD_ClearScreen();
                LCD_DisplayString(1, "Getting RGB");

                TCSLEDOn();
                      
                r=MeasureR();
                g=MeasureG();
                b=MeasureB();

                TCSLEDOff();
                if (r <= 82 && g <=51 && b <= 51) {
                    set_PWM(F4);
                }
                else if (r <= 130 && g <=80 && b <= 80) {
                    set_PWM(FS4);
                }
                else if (r <= 180 && g <=80 && b <= 80) {
                    set_PWM(G4);
                }
                else if (r <= 238 && g <=80 && b <= 80) {
                    set_PWM(GS4);
                    //oldNote = GS4;
                }
                else if (r <= 255 && g <=120 && b <= 51) {
                    set_PWM(A4);
                    //oldNote = A4;
                }
                else if (r <= 255 && g <=210 && b <= 110) {
                    set_PWM(AS4);
                    //oldNote = AS4;
                }
                else if (r <= 90 && g <=255 && b <= 51) {
                    set_PWM(C5);
                    //oldNote = C5;
                }
                else if (r <= 153 && g <=255 && b <= 51) {
                    set_PWM(B4);
                    //oldNote = B4;
                }
                else if (r <= g && g <=255 && b <= g) {
                    set_PWM(CS5);
                    //oldNote = CS5;
                }
                else if (r <= 100 && g <=110 && b <= 255) {
                    set_PWM(D5);
                    //oldNote = D5;
                }
                else if (r <= 100 && g <=51 && b <= 255) {
                    set_PWM(DS5);
                    //oldNote = DS5;
                }
                else if (r <= 90 && g <=110 && b <= 255) {
                    set_PWM(E5);
                    //oldNote = E5;
                }
                else if (r <= 90 && g <=120 && b <= 190) {
                    set_PWM(F5);
                    //oldNote = F5;
                }

                TCSLEDOff();
   
                sprintf(stringOutput,"#%lu", r);
                LCD_ClearScreen();
                LCD_DisplayString(1,stringOutput);
                sprintf(stringOutput,"%lu", g);
                LCD_DisplayString(21, stringOutput);
                sprintf(stringOutput,"%lu", b);
                LCD_DisplayString(41, stringOutput);
    }    
    
enum proxSensor{Start_p, Echo, UpdStatus_p} state_p;
    
switch (state_p) { //transitions
    case Start_p:
        state_p = Echo;
    break;
    
    case Echo:
        state_p = UpdStatus_p;
    break;
    
    case UpdStatus_p:
        state_p = Echo;
    break;
    
    default:
        state_p = Start_p;
    break;
}

switch (state_p) { //actions
    case Start_p:
    break;
        
    case Echo:
        value = readDistance();
    break;
        
    case UpdStatus_p:
        LCD_ClearScreen();
        sprintf(stringOutput,"%f", value); //convert float to string for output
        if (value < 7) {
            //LCD_DisplayString(61, IRstr);
            LCD_DisplayString(81, stringOutput);
            } else {
            LCD_DisplayString(61, OORstr);
            LCD_DisplayString(81, stringOutput);
        }
    break;
    
    default:
    break;
}
    
void initModulesHelper() {
        LCD_init();
        
        usound_init();
        LCD_ClearScreen();
        LCD_DisplayString(1, "Ultrasonic initialized"); //A bit unnecessary, but serves as a good breakpoint
        _delay_ms(250);
        
        InitTCS3200();
        LCD_ClearScreen();
        LCD_DisplayString(1, "RGB initialized"); //Also
        _delay_ms(250);
}    
    
uint32_t MeasureR()
{
    TCSSelectRed();
    uint32_t r;

    _delay_ms(10);
    r=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    return r/3.3;

}

uint32_t MeasureG()
{
    TCSSelectGreen();
    uint32_t r;

    _delay_ms(10);
    r=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    return r/3.1;

}

uint32_t MeasureB()
{
    TCSSelectBlue();
    uint32_t r;

    _delay_ms(10);
    r=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    return r/3;

}

uint32_t MeasureC()
{
    TCSSelectClear();
    uint32_t r;

    _delay_ms(10);
    r=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    _delay_ms(10);
    r+=TCSMeasure();

    return r/3;
}
