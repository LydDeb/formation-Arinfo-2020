#ifndef MY_DEBUG_H
#define MY_DEBUG_H
//
char debug_str[8192];
//
#ifdef DEBUG
#define debug_flag                                                             \
    printf("(DEBUG) %s:%s:%d\n", __FILE__, __PRETTY_FUNCTION__, __LINE__)
#else
#define debug_flag                                                             \
    {}
#endif
//
#ifdef DEBUG
#define debug_print(STR)                                                       \
    printf("(DEBUG) %s:%s:%d %s", __FILE__, __PRETTY_FUNCTION__, __LINE__, STR)
#else
#define debug_print(STR)                                                       \
    {}
#endif
//
#ifdef DEBUG
#define debug_printf(fmt, ...)                                                 \
    do {                                                                       \
        if (DEBUG)                                                             \
            printf(fmt, __VA_ARGS__);                                          \
    } while (0)
#else
#define debug_printf(fmt, ...)                                                 \
    {}
#endif
//
#endif