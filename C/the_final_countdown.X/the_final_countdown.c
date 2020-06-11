#include "the_final_countdown.h"
#include <string.h>
#include "7seg.h"
#include "lcd.h"
#include <stdio.h>
#include "button.h"
#include "led_rgb.h"
#include "hardware.h"
#include "utils.h"

//volatile uint32_t tic;

static char buf[128];

void display_on_lcd(const char* message, uint8_t idxLine){
    
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
    DelayAprox10Us(LCD_DELAY);
    buf_shift = (buf_shift + 1) % mess_len;
}

uint8_t decounting_on_ssd(uint16_t start_number, uint16_t *score){
    DelayAprox10Us(100000);
    SSD_configure();
    SSD_all_off();
    SSD_reset_pattern(&p7s);
    uint16_t number = start_number;
    uint32_t SSD_delay = SSD_DELAY;
    do {
        number--;
        while(SSD_delay--){
            SSD_print_digit_9999(number);
        }
        SSD_delay = SSD_DELAY;
        if(1 == button_state(CENTER)){
            *score = number;
            SSD_all_off();
            return 0;
        }
    }while(number);
    *score = number;
    return 0;
}

void switch_on_rgb_led(uint16_t score){
    Set_RGB_Output();
    if (score == 0){
            RGBLED_SetValue(0xff0000);
        }else{
            RGBLED_SetValue(0x00ff00);
        }
}
