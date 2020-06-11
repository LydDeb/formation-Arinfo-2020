#ifndef LIST_H
#define LIST_H

#include "heap.h"
#include <stdint.h>

typedef struct _element {
    void *data;
    struct _element *next;
    struct _element *previous;
} T_element;

typedef struct {
    T_element *start;
    T_element *end;
} T_list;

typedef void (*T_list_map_func)(void *data);

uint32_t list_length(T_list *list);
T_element *list_append(T_list *list, void *data);
T_element *list_prepend(T_list *list, void *data);
void *list_pop_first(T_list *list);
void *list_pop_last(T_list *list);
T_element *list_insert_at(T_list *list, void *data, uint32_t index);
void *list_remove_at(T_list *list, uint32_t index);
void list_map(T_list *list, T_list_map_func function);

#endif /* LIST_H */