/* 
 * File:   main.c
 * Author: Arinfo
 *
 * Created on 2 juin 2020, 09:21
 */

#include "config_bits.h"
//#include "config.h"
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <xc.h>
#include <sys/attribs.h>


#include <string.h>

#include "led_rgb.h"

volatile uint16_t tic;


int main(int argc, char** argv) {
    tic = 0;
    Hardware_Setup();
    RGBLED_Init();
    uint32_t rgb =0x00ff00;
    uint8_t xr,xg,xb;
    uint16_t shift_r = 0;
    uint16_t shift_g = 0xff;
    uint16_t shift_b = 0x02*0xff;
    
    uint32_t scale = 20000;
    
    while(1){
        xr = 0xff & (rgb >> 16);
        xg = 0xff & (rgb >> 8);
        xb = 0xff & rgb;
        
        RGBLED_signal_1(&xr, shift_r, tic, scale);
        RGBLED_signal_1(&xg, shift_g, tic, scale);
        RGBLED_signal_1(&xb, shift_b, tic, scale);
        
        rgb = (xr << 16) | (xg << 8) | xb;
        RGBLED_SetValue(rgb);
        
    }
    
    

    return (EXIT_SUCCESS);
}

