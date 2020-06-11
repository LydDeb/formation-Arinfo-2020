#ifndef PROCESS_H
#define PROCESS_H
#include <stdint.h>
#define PROCESS_NAME_LENGTH (40)

struct _process;
typedef uint8_t (*T_process_entry_point)(struct _process *context);

typedef struct _process {
    char name[PROCESS_NAME_LENGTH];
    T_process_entry_point entry_point;
    void *user_context;
    uint8_t step;
    uint32_t sleep;
} T_process;

T_process *process_create(const char *const name,
                          const T_process_entry_point entry_point,
                          void *const user_context);
void process_destroy(T_process *process);

#endif /* PROCESS_H */
