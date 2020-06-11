#include "hardware.h"
#include "led_rgb.h"
#include "utils.h"

void __ISR(_TIMER_5_VECTOR, IPL2SRS) Timer5ISR(void)
{
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
    int r=0,g=0,b=0;
    r = hex_to_dec(xr);
    g = hex_to_dec(xg);
    b = hex_to_dec(xb);
    Set_LED8_R(xr);
    Set_LED8_G(xg);
    Set_LED8_B(xb);
  
    
}
