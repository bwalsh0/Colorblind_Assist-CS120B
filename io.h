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
#ifndef __io_h__
#define __io_h__

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column, char* string);
void delay_ms(int miliSec);
#endif