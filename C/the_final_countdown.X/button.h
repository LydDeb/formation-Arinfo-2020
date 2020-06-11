/* 
 * File:   button.h
 * Author: Arinfo
 *
 * Created on 28 mai 2020, 09:38
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <stdint.h>

enum {UP,LEFT,RIGHT,CENTER,DOWN};
static const uint32_t BUTTON_DELAY = 2000;

uint8_t button_state(int position);

#endif	/* BUTTON_H */

