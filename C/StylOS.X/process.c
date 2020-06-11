#include "process.h"
#include "heap.h"

T_process *process_create(const char *const name,
                          const T_process_entry_point entry_point,
                          void *const user_context){
    T_process *process = heap_malloc(sizeof(T_process));
    int i;
    for(i = 0; i<PROCESS_NAME_LENGTH; i ++){
        process->name[i] = name[i];
    }
    process->entry_point = entry_point;
    process->user_context = user_context;
    process->step = 0;
    process->sleep = 0;
    return process;
}


void process_destroy(T_process *process){
    heap_free(process, sizeof(process));
}
