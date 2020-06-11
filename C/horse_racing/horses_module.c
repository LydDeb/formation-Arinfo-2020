#include "horses_module.h"
//
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// static pthread_mutex_t lock2;

//
void horses_screen() {
    uint8_t x, y;
    int i;
    vt100_clear_screen();
    x = VT100_SCREEN_XMIN;
    y = VT100_SCREEN_YMIN;
    vt100_move(x, y);
    // putchar('+');
    printf("\u250c");
    i = 2;
    while (i < VT100_SCREEN_XMAX) {
        // putchar('-');
        printf("\u2500");
        i++;
    }
    // putchar('+');
    printf("\u2510");
    x = VT100_SCREEN_XMAX;
    i = 2;
    y++;
    while (i < VT100_SCREEN_YMAX) {
        vt100_move(x, y++);
        // putchar('|');
        printf("\u2502");
        i++;
    }
    vt100_move(x, y++);
    // putchar('+');
    printf("\u2518");
    x = VT100_SCREEN_XMIN;
    y = VT100_SCREEN_YMIN;
    vt100_move(x, y);
    i = 2;
    y++;
    while (i < VT100_SCREEN_YMAX) {
        vt100_move(x, y++);
        // putchar('|');
        printf("\u2502");
        i++;
    }
    vt100_move(x, y++);
    // putchar('+');
    printf("\u2514");
    i = 2;
    while (i < VT100_SCREEN_XMAX) {
        // putchar('-');
        printf("\u2500");
        i++;
    }
}
//
horses_arguments *parse_arguments(int argc, char **argv) {
    if (argc < 2) {
        char strerr[64];
        sprintf(strerr, "%s:%s:%d", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        argument_error(strerr);
    }
    horses_arguments *arg = malloc(sizeof(horses_arguments));
    arg->names = malloc(sizeof(char *) * (argc - 1));
    arg->names = argv;
    arg->nbr = argc;
    return arg;
}
//
void print_names(horses_arguments *arg) {
    int x, y;
    x = START_NAME_X;
    y = START_NAME_Y;
    for (int i = 1; i < arg->nbr; i++) {
        vt100_move(x, y);
        int l_name = strlen(arg->names[i]);
        for (int c = 0; c < l_name && c < MAX_LEN_NAME; c++) {
            putchar(arg->names[i][c]);
        }
        for (int c = l_name; c < MAX_LEN_NAME; c++) {
            putchar('.');
        }
        y += SPACE_NAME_Y;
    }
    x = VT100_SCREEN_XMAX;
    y = VT100_SCREEN_YMAX;
    vt100_move(x, y);
}
//
void print_pattern(pattern *p, int x, int y) {
    /*
    y\x| 0123
    0  |    _
    1  | __/r
    2  | | |
    ............
    012345678901
    000011112222
    012301230123
       ___/r| |
    */
    for (int yi = 0; yi < p->height; yi++) {
        vt100_move(x, y + yi - p->height + 1);
        for (int xi = 0; xi < p->width; xi++) {
            putchar(p->string[yi * p->width + xi]);
        }
    }
    vt100_move(VT100_SCREEN_XMAX, VT100_SCREEN_YMAX);
}
//
pattern *new_pattern() {
    pattern *p = malloc(sizeof(pattern));
    p->string = malloc(sizeof(char) * MAXCHAR);
    p->string[0] = '\0';
    p->height = 0;
    p->width = 0;
    return p;
}
//
void set_pattern(pattern *p, char *string, int width, int height) {
    p->height = height;
    p->width = width;
    p->string = string;
}
//
pattern_move *new_pattern_move(int nbr_of_patterns) {
    pattern_move *p = malloc(sizeof(pattern_move));
    p->string = malloc(sizeof(char *) * nbr_of_patterns);
    p->nbr_of_patterns = nbr_of_patterns;
    return p;
}
//
void set_pattern_move(pattern_move *p, char **string, int width, int height) {
    p->height = height;
    p->width = width;
    p->step = 0;
    for (int yi = 0; yi < p->nbr_of_patterns; yi++) {
        p->string[yi] = malloc(sizeof(char) * width);
        for (int i = 0; i < width * height; i++) {
            p->string[yi][i] = string[yi][i];
        }
    }
    p->ghost = malloc(sizeof(char) * width);
    for (int i = 0; i < width * height; i++) {
        p->ghost[i] = ' ';
    }
}
//
void print_pattern_move(pattern_move *p, int x, int y) {
    pthread_mutex_lock(&lock);

    for (int yi = 0; yi < p->height; yi++) {
        vt100_move(p->x_prev, y + yi - p->height + 1);
        for (int xi = 0; xi < p->width; xi++) {
            printf("%c", p->ghost[yi * p->width + xi]);
        }
    }
    // pthread_mutex_unlock(&lock2);
    // pthread_mutex_lock(&lock2);

    for (int yi = 0; yi < p->height; yi++) {
        vt100_move(x, y + yi - p->height + 1);
        for (int xi = 0; xi < p->width; xi++) {
            printf("\033[0;31m%c\033[0m",
                   p->string[p->step][yi * p->width + xi]);
        }
    }
    p->step = (p->step + 1) % (p->nbr_of_patterns);
    fflush(stdout);
    pthread_mutex_unlock(&lock);
}
//
void *print_threads(void *args) {
    threads_param *param = (threads_param *)args;
    while (param->win == 0 && param->running == 1) {
        int t_reac = 100 * 1000 * (rand() % 10);
        usleep(t_reac);
        param->pattern->x_prev = param->x;
        param->x += rand() % MAX_MOVE;
        // pthread_mutex_lock(&lock);
        print_pattern_move(param->pattern, param->x, param->y);
        // pthread_mutex_unlock(&lock);
        if ((param->x >= FINISH_LINE + param->pattern->width) &&
            (param->running == 1)) {
            param->win = 1;
            param->running = 0;
        }
    }
    return NULL;
}
//
void print_winner(int id_horse) {
    int x, y;
    x = START_NAME_X - 1;
    y = id_horse * SPACE_NAME_Y + START_NAME_Y - 1;
    vt100_move(x, y);
    printf("\u2554");
    for (int i = 0; i < MAX_LEN_NAME; i++) {
        printf("\u2550");
    }
    printf("\u2557");
    x = START_NAME_X - 1;
    y = id_horse * SPACE_NAME_Y + START_NAME_Y;
    vt100_move(x, y);
    printf("\u2551");
    x = START_NAME_X + MAX_LEN_NAME;
    y = id_horse * SPACE_NAME_Y + START_NAME_Y;
    vt100_move(x, y);
    printf("\u2551");
    vt100_move(x + 2, y);
    printf("\033[1m\033[0;32mWINNER !\033[0m");
    x = START_NAME_X - 1;
    y = id_horse * SPACE_NAME_Y + START_NAME_Y + 1;
    vt100_move(x, y);
    printf("\u255a");
    for (int i = 0; i < MAX_LEN_NAME; i++) {
        printf("\u2550");
    }
    printf("\u255d");
    vt100_move(VT100_SCREEN_XMAX, VT100_SCREEN_YMAX);
}
//
void print_finish_line() {
    for (int y = 2; y < VT100_SCREEN_YMAX; y++) {
        vt100_move(FINISH_LINE, y);
        printf("\u2591");
    }
}