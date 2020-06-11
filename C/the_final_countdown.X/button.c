#include "button.h"
#include "hardware.h"

#define MACRO_BUTTON_STATE(X) btn_stat = BTN_##X();\
            while(step--){\
                if(btn_stat != BTN_##X()){\
                    step = BUTTON_DELAY;\
                }\
            }

uint8_t button_state(int position){
    uint8_t btn_stat;
    uint32_t step;
    step = BUTTON_DELAY;
    switch (position){
        case UP:
            MACRO_BUTTON_STATE(U);
            break;
        case LEFT:
            MACRO_BUTTON_STATE(L);
            break;
        case RIGHT:
            MACRO_BUTTON_STATE(R);
            break;
        case CENTER:
            MACRO_BUTTON_STATE(C);
            break;
        case DOWN:
            MACRO_BUTTON_STATE(D);
            break;
        default:
            btn_stat = 0;
            break;
    }
    return btn_stat;
}
