/*/////////////////////
COLORBLIND ASSISTANT
4x20 LCD Driver
Similar to the driver we used in class, but modified for
this project.

CHANGES:
LCD_Cursor - Adapted for 4 rows and 20 column layout
RS and E pins - Moved connected ports
DATA_BUS - My LCD only uses 4-bits for data bus to free up ports
LCD_DisplayString - Removed call to ClearScreen because it threw the prox. sensor out of sync
*//////////////////////

//#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "io.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

/*-------------------------------------------------------------------------*/
#define DATA_BUS PORTB		
#define CONTROL_BUS PORTD	
#define RS 4			
#define E 3			
/*-------------------------------------------------------------------------*/

void LCD_ClearScreen(void) {
	LCD_WriteCommand(0x01);
}

void LCD_init(void) {
	//wait for 100 ms.
	delay_ms(100);
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x0f);
	LCD_WriteCommand(0x01);
	delay_ms(10);
}

void LCD_WriteCommand (unsigned char Command) {
	CLR_BIT(CONTROL_BUS,RS);
	DATA_BUS = Command;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
	SET_BIT(CONTROL_BUS,RS);
	DATA_BUS = Data;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(1);
}

void LCD_DisplayString( unsigned char column, char* string) {
	//LCD_ClearScreen(); //Puts prox. sensor out of sync (still unknown where)
	unsigned char c = column;
	while(*string) {
		LCD_Cursor(c++);
		LCD_WriteData(*string++);
	}
}

void LCD_Cursor(unsigned char column) { //Modified to fit 4 rows & 20 columns
            // 16x1 LCD: column < 9
            // 16x2 LCD: column < 17
            // 20x4 LCD: column < 21
    
	if ( column < 21 ) { //////(0-20)

    	LCD_WriteCommand(0x80 + column - 1);
    	} else if (column < 41 && column > 20) { //////(21-40)
    	LCD_WriteCommand(0xC0 + column - 21);   // 16x1 LCD: column - 1
    	// 16x2 LCD: column - 9
    	} else if (column < 61 && column > 40) { //////(41-60)
    	LCD_WriteCommand(0x94 + column - 41);
    	} else if (column < 81 && column > 60) { //////(61-80)
    	LCD_WriteCommand(0xD4 + column - 61);
	}
	LCD_WriteCommand(0x0C);
}

void delay_ms(int miliSec) //for 8 Mhz crystal

{
	int i,j;
	for(i=0;i<miliSec;i++)
	for(j=0;j<775;j++)
	{
		asm("nop");
	}
}