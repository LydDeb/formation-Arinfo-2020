#include "OS.h"
#include "list.h"
#include "heap.h"


static T_list os_process_ready = {.start = NULL, .end = NULL};
static T_list os_process_waiting = {.start = NULL, .end = NULL};
static uint32_t os_timer = 0;
/*
 Initialise des listes chaînées de process
 */
void os_init(void){
    heap_init();
    os_Timer5Setup();
}



/*
 Décrémenteur
 */
void os_sleep(T_process *process, uint32_t time){
    process->sleep=time+os_timer;
    //list_append(&os_process_waiting, process);
}

/*
 Ajoute les process dans la liste ready
 */
void os_start_process(T_process *process){
    T_element * new_element = list_append(&os_process_ready,(void*) process);
}

void os_wait_process(T_process *process){
    T_element * new_element = list_append(&os_process_waiting,(void*) process);
}

/*
 Lance l'exécution des process ready
 */
void os_infinite_loop(void){
    uint8_t test_waiting = list_length(&os_process_waiting);
    uint8_t test_ready   = list_length(&os_process_ready);
    
    while(test_waiting || test_ready){
        test_waiting = list_length(&os_process_waiting);
        test_ready   = list_length(&os_process_ready);
        
        if(test_waiting){
            T_process *process =list_pop_first(&os_process_waiting);
            if(process->sleep <= os_timer){
                process->sleep = 0;
                os_start_process(process);
            }
            else{
                os_wait_process(process);
            }
        }
        
        if(test_ready){
            T_process* process = list_pop_first(&os_process_ready);
            uint8_t status = process->entry_point(process);
            if(OS_COROUTINE_INTERRUPTED == status){
                if(0 == process->sleep){
                    os_start_process(process);
                }
                else{
                    os_wait_process(process);
                }
            }
            else {
                process_destroy(process);
            }
        }
    }
    
    while(1);
}

void __ISR(_TIMER_5_VECTOR, IPL2SOFT) Timer5ISR(void)
{
    os_timer ++;
    IFS0bits.T5IF = 0; // clear interrupt flag
}
void os_Timer5Setup()
{
    PR5 = (int)(((float)(OS_TMR_TIME * OS_PB_FRQ) / 256) + 0.5); //set period register, generates one interrupt every 300 us
    TMR5 = 0;                                              //    initialize count to 0
    T5CONbits.TCKPS = 3;                                   //    1:256 prescaler value
    IPC5bits.T5IP = 2;                                     //    INT step 4: priority
    IPC5bits.T5IS = 0;                                     //    subpriority
    IFS0bits.T5IF = 0;                                     //    clear interrupt flag
    IEC0bits.T5IE = 1;                                     //    enable interruption
    T5CONbits.ON = 1;                                      //    turn on Timer5

    // enable interrupts at CPU
    unsigned int val = 0;
    asm volatile("mfc0 %0,$13"
                : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0 %0,$13"
                : "+r"(val));
    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
}

uint16_t os_get_time(void){
    uint16_t time = os_timer  / (100000);
    return time;
}