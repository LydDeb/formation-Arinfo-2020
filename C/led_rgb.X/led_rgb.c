
#include "hardware.h"
#include "led_rgb.h"
#include "utils.h"

extern volatile uint16_t tic;


void __ISR(_TIMER_5_VECTOR, IPL2SOFT) Timer5ISR(void)
{
    tic++;
    IFS0bits.T5IF = 0; // clear interrupt flag
}



void RGBLED_Timer5Setup()
{
    PR5 = (int)(((float)(TMR_TIME * PB_FRQ) / 256) + 0.5); //set period register, generates one interrupt every 300 us
    TMR5 = 0;                                              //    initialize count to 0
    T5CONbits.TCKPS = 3;                                   //    1:256 prescaler value
    IPC5bits.T5IP = 2;                                     //    INT step 4: priority
    IPC5bits.T5IS = 0;                                     //    subpriority
    IFS0bits.T5IF = 0;                                     //    clear interrupt flag
    ENABLE_INTERRUPT(); 
    T5CONbits.ON = 1;                                      //    turn on Timer5

    // enable interrupts at CPU
    unsigned int val = 0;
    asm volatile("mfc0 %0,$13"
                : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0 %0,$13"
                : "+r"(val));
    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
}

void RGBLED_Init()
{
    Set_RGB_Output();
    RGBLED_Timer5Setup();
}

void RGBLED_SetValue(uint32_t rgb)
{
    
    uint8_t xr,xg,xb;
    xr = 0xff & (rgb >> 16);
    xg = 0xff & (rgb >> 8);
    xb = 0xff & rgb;
    
    
    Set_LED8_R(xr);
    Set_LED8_G(xg);
    Set_LED8_B(xb);
  
    
}
#define PERIOD_1 (0x03*0xff)
void RGBLED_signal_1(uint8_t* xcolor, uint16_t shift, uint32_t time, uint32_t scale){
    
    uint32_t b0 = 0*scale;
    uint32_t b1 = 0xff*scale;
    uint32_t b2 = 0x02*0xff*scale;
    uint32_t b3 = 0x03*0xff*scale;
    uint32_t t = (time+shift*scale)%(PERIOD_1*scale);
    if ( t == b0){
        *xcolor = 0x00;
    }
    else if(b0 < t && t < b1){
        if(t%scale == 0){
            *xcolor =  (*xcolor + 1)%0x100;
        }
    }
    else if (t == b1){
        *xcolor = 0xff;
    }
    else if (b1 < t && t < b2){
        if(t%scale == 0){
            *xcolor =  (*xcolor - 1)%0x100;
        }
    }
    else if (t == b2){
        *xcolor = 0x00;
    }
    else if (b2 < t && t <= b3){
        *xcolor = 0x00;
    }
    
}