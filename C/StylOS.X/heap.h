#ifndef HEAP_H
#define HEAP_H

#ifndef NULL
#define NULL ((void *)0)
//typedef int size_t;
#endif

void heap_init(void);
void *heap_malloc(int nb_bytes);
void heap_free(void *pointer, int nb_bytes);

#endif /* HEAP_H */