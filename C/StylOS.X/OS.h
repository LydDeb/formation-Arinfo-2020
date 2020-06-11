#ifndef OS_H
#define OS_H
#include "hardware.h"
#include "lcd.h"
#include "process.h"
#include <stdint.h>

#ifndef NULL
#define NULL ((void *)0)

#endif

#define OS_COROUTINE_INTERRUPTED (0)
#define OS_COROUTINE_FINISHED (1)
#define COROUTINE_START switch (process->step){\
case 0:
#define COROUTINE_STEP process->step = __LINE__;\
            return OS_COROUTINE_INTERRUPTED;\
        case __LINE__:
#define COROUTINE_END return OS_COROUTINE_FINISHED;\
    }
#define COROUTINE_RESTART process->step = 0;return OS_COROUTINE_INTERRUPTED;\
    }
#define OS_TMR_TIME 0.0001 // 300 us for each tick
#define OS_PB_FRQ 40000000
#define OS_sleep(time) os_sleep(process,time);
void os_init(void);
void os_sleep(T_process *process, uint32_t time);
void os_infinite_loop(void);
void os_start_process(T_process *process);
void os_Timer5Setup();
void Timer5ISR(void);
uint16_t os_get_time(void);

#endif /* OS_H */
