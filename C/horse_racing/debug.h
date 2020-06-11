#ifndef DEBUG_H
#define DEBUG_H
//
char debug_str[256];
//
#ifdef DEBUG
#define debug_print(STR)                                                       \
    printf("(DEBUG) %s:%s:%d %s", __FILE__, __PRETTY_FUNCTION__, __LINE__, STR)
#else
#define debug_print(STR)                                                       \
    {}
#endif
//
#endif