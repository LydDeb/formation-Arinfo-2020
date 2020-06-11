/* 
 * File:   7seg.h
 * Author: Arinfo
 *
 * Created on 28 mai 2020, 09:38
 */

#ifndef SEVEN_SEG_H
#define	SEVEN_SEG_H
#include <stdint.h>

static const uint32_t SSD_DELAY = 1000;

typedef struct pattern{
    uint8_t A:1;
    uint8_t B:1;
    uint8_t C:1;
    uint8_t D:1;
    uint8_t E:1;
    uint8_t F:1;
    uint8_t G:1;
    uint8_t DP:1;
}pattern;

static pattern p7s;

void SSD_reset_pattern(pattern* p);
void SSD_set_digit_pattern(uint8_t digit, pattern* p);
void SSD_set_pattern(pattern* p,uint8_t A,uint8_t B,uint8_t C,uint8_t D,uint8_t E,
        uint8_t F,uint8_t G,uint8_t DP);
void SSD_C_pattern(pattern *p);
void SSD_print_digit_9999 (uint16_t number);

#endif

