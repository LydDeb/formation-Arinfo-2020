/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    utils.c

  @Description
        This library implements the delay functionality used in other libraries.  
        The delay is implemented using loop, so the delay time is not exact. 
        For exact timing use timers.
        Include the file in the project, together with utils.h, when this library is needed	
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "utils.h"
#include "stdlib.h"
#include "lcd.h"
#include <string.h>
/* ************************************************************************** */

/* ------------------------------------------------------------ */
/***    Delay100Us
**
**	Synopsis:
**		Delay100Us(100)
**
**	Parameters:
**		t100usDelay - the amount of time you wish to delay in hundreds of microseconds
**
**	Return Values:
**      none
**
**	Errors:
**		none
**
**	Description:
**		This procedure delays program execution for the specified number
**      of microseconds. This delay is not precise.
**		
**	Note:
**		This routine is written with the assumption that the
**		system clock is 40 MHz.
*/
void DelayAprox10Us( unsigned int  t100usDelay )
{
    int j;
    while ( 0 < t100usDelay )
    {
        t100usDelay--;
        j = 14;
        while ( 0 < j )
        {
            j--;
        }   // end while 
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
         
    }   // end while
}

/* ------------------------------------------------------------ */
/***    swap_values
**
**	Synopsis:
**		swap_values(&a,&b)
**
**	Parameters:
**		a,b: a couple of values to swap
**
**	Return Values:
**      none
**
**	Errors:
**		none
**
**	Description:
**		This procedure swap value a in b and b in a;
*/
void swap_values(uint8_t* a, uint8_t* b){
                *a = *a + *b;
                *b = *a - *b;
                *a = *a - *b;
}

uint16_t hex_to_dec(uint8_t hex){
        uint16_t dec = 0;
        dec += (1 & (hex >> 0)) * 1;
        dec += (1 & (hex >> 1)) * 2;
        dec += (1 & (hex >> 2)) * 4;
        dec += (1 & (hex >> 3)) * 8;
        dec += (1 & (hex >> 4)) * 16;
        dec += (1 & (hex >> 5)) * 32;
        dec += (1 & (hex >> 6)) * 64;
        dec += (1 & (hex >> 7)) * 128;
        return dec;
    }


uint16_t prng_lfsr(uint16_t start_number){
    uint16_t lfsr = start_number;
    uint16_t bit15;
    bit15 = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    lfsr = (lfsr >> 1) | (bit15 << 15);
    return lfsr;
}


uint16_t next_number(uint16_t* lsfr){
    uint16_t start_number = *lsfr%(LSFR_MAX_NUMBER+1);
    while(start_number < LSFR_MIN_NUMBER || start_number >LSFR_MAX_NUMBER){
        *lsfr = prng_lfsr(*lsfr);
        start_number = *lsfr%(LSFR_MAX_NUMBER+1);
    }
    return start_number;
}


void display_on_lcd(const char* message, uint8_t idxLine, uint16_t buf_shift){
    char buf[128];
    unsigned char  idxPos;
    uint16_t mess_len = strlen(message);
    
    idxPos = 0;
    strcpy(buf, message+buf_shift);
    if(buf_shift > 0 && buf_shift > mess_len - LCD_CHAR_WIDTH){
        strcat(buf,message);
    }
    LCD_WriteStringAtPos(buf, idxLine, idxPos);
}

void display_on_lcd_auto(const char* message, uint8_t idxLine){
    char buf[128];
    unsigned char  idxPos;
    static uint16_t buf_shift = 0;
    uint16_t mess_len = strlen(message);
    
    idxPos = 0;
    if(mess_len<=LCD_CHAR_WIDTH){
        buf_shift = 0;
    }
    strcpy(buf, message+buf_shift);
    if(buf_shift > 0 && buf_shift > mess_len - LCD_CHAR_WIDTH){
        strcat(buf,message);
    }
    LCD_WriteStringAtPos(buf, idxLine, idxPos);
    //DelayAprox10Us(LCD_DELAY);
    buf_shift = (buf_shift + 1) % mess_len;
}


/* *****************************************************************************
 End of File
 */


