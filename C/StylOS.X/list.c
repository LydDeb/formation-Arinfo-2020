#include "list.h"

static T_element *list_create_element() {
    T_element *new_element = (T_element *)heap_malloc(sizeof(T_element));
    if (new_element != NULL) {
        new_element->data = NULL;
        new_element->next = NULL;
        new_element->previous = NULL;
    }
    return new_element;
}

uint32_t list_length(T_list *list) {
    uint32_t len = 0;
    T_element *elem = list->start;
    while (elem) {
        len++;
        elem = elem->next;
    }
    return len;
}

T_element *list_append(T_list *list, void *data) {
    T_element *new_element = list_create_element();
    if (new_element != NULL) {
        new_element->data = data;
        new_element->previous = list->end;
        if (list->start == NULL)
            list->start = new_element;
        else
            list->end->next = new_element;
        list->end = new_element;
    }
    return new_element;
}

T_element *list_prepend(T_list *list, void *data) {
    T_element *new_element = list_create_element();
    if (new_element != NULL) {
        new_element->data = data;
        new_element->next = list->start;
        if (list->end == NULL)
            list->end = new_element;
        else
            list->start->previous = new_element;
        list->start = new_element;
    }
    return new_element;
}

void *list_pop_first(T_list *list) {
    void *ret;
    T_element *to_be_suppressed = list->start;
    if (to_be_suppressed) {
        list->start = to_be_suppressed->next;
        if (list->start)
            list->start->previous = NULL;
        if (to_be_suppressed->next == NULL)
            list->end = NULL;
        ret = to_be_suppressed->data;
        heap_free(to_be_suppressed, sizeof(T_element));
        return ret;
    }
    return NULL;
}

void *list_pop_last(T_list *list) {
    void *ret;
    T_element *to_be_suppressed = list->end;
    if (to_be_suppressed) {
        list->end = to_be_suppressed->previous;
        if (list->end)
            list->end->next = NULL;
        if (to_be_suppressed->previous == NULL)
            list->start = NULL;
        ret = to_be_suppressed->data;
        heap_free(to_be_suppressed, sizeof(T_element));
        return ret;
    }
    return NULL;
}

T_element *list_insert_at(T_list *list, void *data, uint32_t index) {
    T_element *previous_element = list->start;
    T_element *new_element;
    if (previous_element) // liste non vide
    {
        T_element *new_element = list_create_element();
        if (new_element != NULL) {
            uint32_t i;
            for (i = 0; i < index && previous_element->next; i++)
                previous_element = previous_element->next;

            new_element->data = data;
            new_element->previous = previous_element;
            if (index) {
                new_element->next = previous_element->next;
                previous_element->next = new_element;
                if (new_element->next == NULL)
                    list->end = new_element;
            } else {
                new_element->next = list->start;
                list->start = new_element;
            }
        }
    } else {
        new_element = list_append(list, data);
    }

    return new_element;
}

void *list_remove_at(T_list *list, uint32_t index) {
    void *ret;
    T_element *to_be_suppressed = list->start;
    if (to_be_suppressed) // liste non vide
    {
        uint32_t i;
        for (i = 0; i < index && to_be_suppressed->next; i++)
            to_be_suppressed = to_be_suppressed->next;

        if (i == index) {
            if (to_be_suppressed->previous)
                to_be_suppressed->previous->next = to_be_suppressed->next;
            else
                list->start = to_be_suppressed->next;

            if (to_be_suppressed->next)
                to_be_suppressed->next->previous = to_be_suppressed->previous;
            else
                list->end = to_be_suppressed->previous;

            ret = to_be_suppressed->data;
            heap_free(to_be_suppressed, sizeof(T_element));
            return ret;
        }
    }
    return NULL;
}

void list_map(T_list *list, T_list_map_func function) {
    T_element *elem = list->start;
    while (elem) {
        function(elem->data);
        elem = elem->next;
    }
}