/* 
 * File:   the_final_countdown.h
 * Author: Arinfo
 *
 * Created on 28 mai 2020, 09:49
 */

#ifndef THE_FINAL_COUNTDOWN_H
#define	THE_FINAL_COUNTDOWN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "hardware.h"
#define LCD_DELAY 150000
static const char START_MESSAGE[] = "Ayez les meilleurs reflexes, appuyer sur "
                                    "BTNC juste avant la fin du compteur. Pour"
                                    " demarrer, appuyer sur BTNC.    ";
static const char GAME_OVER_MESSAGE[] = " :-( Vous avez perdu ! Retentez votre chanc"
                                        "e en appuyant sur BTNC.    ";

void display_on_lcd(const char* message, uint8_t idxLine);
uint8_t decounting_on_ssd(uint16_t start_number,uint16_t* score);
void switch_on_rgb_led(uint16_t score);

#ifdef	__cplusplus
}
#endif

#endif	/* THE_FINAL_COUNTDOWN_H */

