/* 
 * File:   led_rgb.h
 * Author: Arinfo
 *
 * Created on 28 mai 2020, 09:39
 */

#ifndef LED_RGB_H
#define	LED_RGB_H

#define TMR_TIME 0.0003 // 300 us for each tick
#define PB_FRQ 40000000

#define ENABLE_INTERRUPT() IEC0bits.T5IE = 1
#define DISABLE_INTERRUPT() IEC0bits.T5IE = 0

//void __ISR(_TIMER_5_VECTOR, IPL2SOFT) Timer5ISR(void);
void RGBLED_Timer5Setup();
void RGBLED_Init();
void RGBLED_SetValue(uint32_t rgb);

#endif	/* LED_RGB_H */

