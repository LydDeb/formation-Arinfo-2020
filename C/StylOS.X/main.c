
#include "heap.h"
#include "utils.h"
#include "config_bits.h"
#include "config.h"
#include "hardware.h"
#include "OS.h"
#include <string.h>
#include <stdio.h>

static uint16_t lsfr = 0xCAFE;

typedef struct {
    uint8_t LCD_idxLine;
    uint16_t LCD_shift;
    uint8_t *LED_idx;
    uint8_t LED_on_off;
} T_user_context;

void switch_LED(uint8_t LED_idx, uint8_t LED_on_off) {
    switch (LED_idx) {
        case 7:
            setLED7(LED_on_off);
            break;
        case 6:
            setLED6(LED_on_off);
            break;
        case 5:
            setLED5(LED_on_off);
            break;
        case 4:
            setLED4(LED_on_off);
            break;
        case 3:
            setLED3(LED_on_off);
            break;
        case 2:
            setLED2(LED_on_off);
            break;
        case 1:
            setLED1(LED_on_off);
            break;
        case 0:
            setLED0(LED_on_off);
            break;
        default:
            break;
    }
}

#define SLEEP_TIME 20000

uint8_t process_func(T_process *process) {
    T_user_context* param = process->user_context;
    uint8_t d_shift = 1; //next_number(&lsfr);
    COROUTINE_START{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[0], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[1], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        param->LED_on_off = (param->LED_on_off + 1) % 2;
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[0], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[1], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        param->LED_on_off = (param->LED_on_off + 1) % 2;
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[0], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[1], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        param->LED_on_off = (param->LED_on_off + 1) % 2;
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[0], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[1], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        param->LED_on_off = (param->LED_on_off + 1) % 2;
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[0], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[1], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        param->LED_on_off = (param->LED_on_off + 1) % 2;
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[0], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_STEP{
        display_on_lcd(process->name, param->LCD_idxLine, param->LCD_shift);
        switch_LED(param->LED_idx[1], param->LED_on_off);
        param->LCD_shift = (param->LCD_shift + d_shift) % strlen(process->name);
        param->LED_on_off = (param->LED_on_off + 1) % 2;
        OS_sleep(SLEEP_TIME);
    }
    COROUTINE_RESTART
}

uint8_t process_func_2(T_process *process) {
    COROUTINE_START{
        uint16_t time = os_get_time();
    SSD_print_digit_9999 (time);
    }
    COROUTINE_RESTART
    (void) process;
}

int main(void) {
    os_init();

    ALL_DIGITAL_IO();
    Set_All_LEDs_Output();
    Set_All_LEDs_Off();
    LCD_Init();
    SSD_configure();
    SSD_all_off();
    char buf[PROCESS_NAME_LENGTH];

    T_user_context user_context_1 = {.LCD_idxLine = 0,
    .LED_on_off = 1, .LCD_shift = 0};
    user_context_1.LED_idx = heap_malloc(2*sizeof(uint8_t));
    user_context_1.LED_idx[0] = 2;
    user_context_1.LED_idx[1] = 3;
    sprintf(buf, "<--(1)(LED %u)(LED %u)                 ",
            user_context_1.LED_idx[0], user_context_1.LED_idx[1]);
    T_process *process1 = process_create(buf, process_func, &user_context_1);
    os_start_process(process1);

    T_user_context user_context_2 = {.LCD_idxLine = 1,
    .LED_on_off = 1, .LCD_shift = 0};
    user_context_2.LED_idx = heap_malloc(2*sizeof(uint8_t));
    user_context_2.LED_idx[0] = 6;
    user_context_2.LED_idx[1] = 7;
    sprintf(buf, "<--(2)(LED %u)(LED %u)                 ",
            user_context_2.LED_idx[0], user_context_2.LED_idx[1]);
    T_process *process2 = process_create(buf, process_func, &user_context_2);
    os_start_process(process2);
    
    T_user_context user_context_3;
    sprintf(buf, "3");
    T_process *process3 = process_create(buf, process_func_2, &user_context_3);
    os_start_process(process3);

    os_infinite_loop();
    return 0;
}
