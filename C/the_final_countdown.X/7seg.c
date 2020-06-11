#include "7seg.h"
#include <stdint.h>
#include "hardware.h"

void SSD_reset_pattern(pattern* p){
    p->A = SSD_OFF;
    p->B = SSD_OFF;
    p->C = SSD_OFF;
    p->D = SSD_OFF;
    p->E = SSD_OFF;
    p->F = SSD_OFF;
    p->G = SSD_OFF;
    p->DP = SSD_OFF;
}

#define MACRO_SET_PATTERN(X,Y) (1 == X) ? (Y = SSD_ON) : (Y = SSD_OFF)
void SSD_set_pattern(pattern* p,uint8_t A,uint8_t B,uint8_t C,uint8_t D,uint8_t E,
        uint8_t F,uint8_t G,uint8_t DP){
    MACRO_SET_PATTERN(A,p->A);
    MACRO_SET_PATTERN(B,p->B);
    MACRO_SET_PATTERN(C,p->C);
    MACRO_SET_PATTERN(D,p->D);
    MACRO_SET_PATTERN(E,p->E);
    MACRO_SET_PATTERN(F,p->F);
    MACRO_SET_PATTERN(G,p->G);
    MACRO_SET_PATTERN(DP,p->DP);
    
}

void SSD_set_digit_pattern(uint8_t digit, pattern* p){
    switch (digit){
        case 0:
            SSD_set_pattern(p,1,1,1,1,1,1,0,0);
            break;
        case 1:
            SSD_set_pattern(p,0,1,1,0,0,0,0,0);
            break;
        case 2:
            SSD_set_pattern(p,1,1,0,1,1,0,1,0);
            break;
        case 3:
            SSD_set_pattern(p,1,1,1,1,0,0,1,0);
            break;
        case 4:
            SSD_set_pattern(p,0,1,1,0,0,1,1,0);
            break;
        case 5:
            SSD_set_pattern(p,1,0,1,1,0,1,1,0);
            break;
        case 6:
            SSD_set_pattern(p,1,0,1,1,1,1,1,0);
            break;
        case 7:
            SSD_set_pattern(p,1,1,1,0,0,0,0,0);
            break;
        case 8:
            SSD_set_pattern(p,1,1,1,1,1,1,1,0);
            break;
        case 9:
            SSD_set_pattern(p,1,1,1,1,0,1,1,0);
            break;
        
        default:
            break;
    }
}

#define MACRO_SSD_C_PATTERN(X,Y)  if(SSD_ON == X){SSD_set_C##Y##_on();}\
else{SSD_set_C##Y##_off();}

void SSD_C_pattern(pattern* p){
    MACRO_SSD_C_PATTERN(p->A,A);
    MACRO_SSD_C_PATTERN(p->B,B);
    MACRO_SSD_C_PATTERN(p->C,C);
    MACRO_SSD_C_PATTERN(p->D,D);
    MACRO_SSD_C_PATTERN(p->E,E);
    MACRO_SSD_C_PATTERN(p->F,F);
    MACRO_SSD_C_PATTERN(p->G,G);
    MACRO_SSD_C_PATTERN(p->DP,DP);
}

#define MACRO_SSD_PRINT_DIGIT_9999(eX,X,ndigit) if(ndigit > X){\
     SSD_set_digit_pattern(eX,&p7s);\
     SSD_C_pattern(&p7s);\
     SSD_set_AN##X##_on();\
}

void SSD_print_digit_9999 (uint16_t number){
    uint8_t e3,e2,e1,e0;
    e3 = number/1000;
    e2 = (number/100)%10;
    e1 = (number/10)%10;
    e0 = number%10;
    
    uint8_t number_of_digits;
    if(e3 != 0){number_of_digits = 4;}
    else if(e2 != 0){number_of_digits = 3;}
    else if(e1 != 0){number_of_digits = 2;}
    else if(e0 != 0){number_of_digits = 1;}
    
    static uint8_t anode_turn;
    anode_turn = (anode_turn + 1) %4;
        SSD_set_ANs_off();
        switch (anode_turn) {
            case 0:
                MACRO_SSD_PRINT_DIGIT_9999(e0,0,number_of_digits);
                break;
            case 1:
                MACRO_SSD_PRINT_DIGIT_9999(e1,1,number_of_digits);
                break;
            case 2:
                MACRO_SSD_PRINT_DIGIT_9999(e2,2,number_of_digits);
                break;
            case 3:
                MACRO_SSD_PRINT_DIGIT_9999(e3,3,number_of_digits);
                break;
            default:
                break;
        }
    
}