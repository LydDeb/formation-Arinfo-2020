/* 
 * File:   main.c
 * Author: Arinfo
 *
 * Created on 28 mai 2020, 09:34
 */
#include "config_bits.h"
//#include "config.h"
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <xc.h>
#include <sys/attribs.h>

#include "lcd.h"
#include "the_final_countdown.h"
#include <string.h>
#include "button.h"
#include "led_rgb.h"

#define SEED_NUMBER 0xcafe
#define MAX_NUMBER 9999
#define MIN_NUMBER 1000
#define MAX_NBR_OF_ROUND 3

enum states {WAITING_START, COUNTING, RESULT, NEXT_ROUND,
GAME_OVER, FINAL_SCORE};

uint16_t next_number(uint16_t* lsfr);

int main(int argc, char** argv) {
    
    //tic = 0 ;
    char lcd_top_buf[17];
    char lcd_bot_buf[17];
    
    uint16_t lsfr = SEED_NUMBER;
    uint16_t start_number;
    uint16_t score;
    uint16_t final_score = 0;
    uint8_t game_over = 0;
    uint8_t end_of_round = 1;
    uint8_t round_count = 1;
    uint8_t status = WAITING_START;
    
    Hardware_Setup();
    LCD_Init();
    LCD_DisplayClear();
    
    while(1){
        lsfr = prng_lfsr(lsfr);
        
        
        switch (status){
            case WAITING_START:
                display_on_lcd(START_MESSAGE,LCD_TOP_LINE);
                final_score = 0;
                round_count = 1;
                break;
                
            case COUNTING:
                start_number = next_number(&lsfr);
                end_of_round = decounting_on_ssd(start_number, &score);
                break;
                
            case RESULT:
                switch_on_rgb_led(score);
                sprintf(lcd_top_buf,"ROUND: %u/%u ",
                        round_count,MAX_NBR_OF_ROUND);
                display_on_lcd(lcd_top_buf,LCD_TOP_LINE);
                sprintf(lcd_bot_buf,"SCORE: %u",score);
                display_on_lcd(lcd_bot_buf,LCD_BOT_LINE);
                (score == 0) ? (game_over = 1) : (game_over = 0);
                break;
                
            case NEXT_ROUND:
                round_count++;
                break;
                
            case GAME_OVER:
                round_count = 1;
                display_on_lcd(GAME_OVER_MESSAGE,LCD_TOP_LINE);
                sprintf(lcd_bot_buf,"    BOUM !!!    ");
                display_on_lcd(lcd_bot_buf,LCD_BOT_LINE);
                game_over = 0;
                break;
                
            case FINAL_SCORE:
                sprintf(lcd_top_buf,"FINAL SCORE:");
                display_on_lcd(lcd_top_buf,LCD_TOP_LINE);
                sprintf(lcd_bot_buf,"%u            ",final_score);
                display_on_lcd(lcd_bot_buf,LCD_BOT_LINE);
                break;
                
            default:
                break;
        }
        if(1 == game_over){
            status = GAME_OVER;
        }else if(1 == button_state(CENTER) && WAITING_START == status){
            status = COUNTING;
            LCD_DisplayClear();
        }
        else if( COUNTING == status && 0 == end_of_round){
            status = RESULT;
            end_of_round = 1;
            final_score += score;
        }
        else if (RESULT == status && 1 == button_state(CENTER)){
            status = NEXT_ROUND;
            Set_LED8_RGB(0);
        }
        else if (NEXT_ROUND == status){
            status = COUNTING;
        }
        else if(1 == button_state(CENTER) && status == GAME_OVER){
            game_over == 0;
            status = WAITING_START;
        }
        else if (MAX_NBR_OF_ROUND == round_count){
            status = FINAL_SCORE;
            Set_LED8_RGB(0);
            round_count = 1;
        }
        else if (FINAL_SCORE == status && 1 == button_state(CENTER)){
            status = WAITING_START;
            LCD_DisplayClear();
        }
    }
    return (EXIT_SUCCESS);
}

uint16_t next_number(uint16_t* lsfr){
    uint16_t start_number = *lsfr%(MAX_NUMBER+1);
    while(start_number < MIN_NUMBER || start_number >MAX_NUMBER){
        *lsfr = prng_lfsr(*lsfr);
        start_number = *lsfr%(MAX_NUMBER+1);
    }
    return start_number;
}