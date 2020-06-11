#ifndef HORSES_MODULE_H
#define HORSES_MODULE_H
#include "error.h"
#include "vt100.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//
#define START_NAME_X (VT100_SCREEN_XMIN + 5)
#define START_NAME_Y (VT100_SCREEN_YMIN + 2)
#define MAX_LEN_NAME 20
#define MAX_NBR_OF_HORSES 8
#define SPACE_NAME_Y 3
#define MAXCHAR 100
#define MAX_MOVE 4
#define FINISH_LINE (VT100_SCREEN_WIDTH - 4)
//

//
typedef struct horses_arguments {
    char **names;
    int nbr;
} horses_arguments;

typedef struct pattern {
    char *string;
    int width;
    int height;
} pattern;

typedef struct pattern_move {
    char **string;
    char *ghost;
    int x_prev;
    int nbr_of_patterns;
    int width;
    int height;
    int step;
} pattern_move;

typedef struct threads_param {
    pattern_move *pattern;
    int x;
    int y;
    int win;
    int running;
} threads_param;
//
void horses_screen();
horses_arguments *parse_arguments(int argc, char **argv);
void print_names(horses_arguments *arg);
void print_pattern(pattern *p, int x, int y);
void print_pattern_move(pattern_move *p, int x, int y);
pattern *new_pattern();
pattern_move *new_pattern_move(int nbr_of_patterns);
void set_pattern(pattern *p, char *string, int width, int height);
void set_pattern_move(pattern_move *p, char **string, int width, int height);
void *print_threads(void *args);
void print_winner(int id_horse);
void print_finish_line(void);
//

//

#endif