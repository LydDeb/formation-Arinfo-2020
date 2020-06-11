#include "horses.h"
//
static char horse_1_str[12] = "   _"
                              "__/r"
                              "|  /";
//
static char knight_1_str[12] = " o _"
                               "_D/r"
                               "|' /";
//
static char Sleipnir_str[12] = "   _"
                               "__/r"
                               "HHHH";
static char Pegase_str[30] = " 77 _"
                             "_7_/r"
                             "/  / "
                             "    _"
                             "___/r"
                             "/  / ";
// static char ghost_12[12] = "            ";
static char ghost_12[12] = "XXXXYYYYZZZZ";
//
static char horse_2_str[15] = "    _"
                              " __/r"
                              "|[ |[";
static char ghost_15[15] = "               ";
//
static char horse_3_str_1[12] = "   _"
                                "__/r"
                                "| \\\\";

static char horse_3_str_2[12] = "   _"
                                "__/r"
                                "/ \\\\";

static char horse_3_str_3[12] = "   _"
                                "__/r"
                                "/ /\\";

static char horse_3_str_4[12] = "   _"
                                "__/r"
                                "/ /|";

static char horse_3_str_5[12] = "   _"
                                "__/r"
                                "\\ //";

static char horse_3_str_6[12] = "   _"
                                "__/r"
                                "\\ \\\\";

static char horse_3_str_1_6[] = "   _"
                                "__/r"
                                "| \\\\"
                                "   _"
                                "__/r"
                                "/ \\\\"
                                "   _"
                                "__/r"
                                "/ /\\"
                                "   _"
                                "__/r"
                                "/ /|"
                                "   _"
                                "__/r"
                                "\\ //"
                                "   _"
                                "__/r"
                                "\\ \\\\";

/*
static char horse_3_str_1_6[] = "AAAA"
                                "AAAA"
                                "AAAA"
                                "BBBB"
                                "BBBB"
                                "BBBB"
                                "CCCC"
                                "CCCC"
                                "CCCC"
                                "DDDD"
                                "DDDD"
                                "DDDD"
                                "EEEE"
                                "EEEE"
                                "EEEE"
                                "FFFF"
                                "FFFF"
                                "FFFF";
*/
//
/*
Passecerf, ou Passëcerf, destrier de Gerier, l'un des douze paladins3.
Tachëbrun, destrier de Ganelon3.
Tencendur ou Tencendor, destrier du roi Charlemagne3.
Veillantif, destrier de Roland le paladin, également associé à un folklore
important.
*/
//
int main(int argc, char **argv) {
    //
    srand(time(NULL));
    horses_screen();
    print_finish_line();
    //
    int nbr_of_horses = argc - 1;
    int winner[nbr_of_horses];
    for (int i = 0; i < nbr_of_horses; i++) {
        winner[i] = 0;
    }
    //
    horses_arguments *arg;
    arg = parse_arguments(argc, argv);
    //
    print_names(arg);
    //
    pattern *horse_1 = new_pattern();
    set_pattern(horse_1, horse_1_str, 4, 3);
    //
    char **horse_3_str = malloc(sizeof(char *) * 6);
    for (int j = 0; j < 6; j++) {
        *(horse_3_str + j) = malloc(sizeof(char) * 12);
        for (int i = 0; i < 12; i++) {
            horse_3_str[j][i] = horse_3_str_1_6[12 * j + i];
        }
    }
    //
    pattern_move **horses = malloc(sizeof(pattern_move *) * nbr_of_horses);
    for (int i = 0; i < nbr_of_horses; i++) {
        horses[i] = new_pattern_move(6);
        set_pattern_move(horses[i], horse_3_str, 4, 3);
    }
    //
    int x, y;
    x = START_NAME_X + MAX_LEN_NAME;
    y = START_NAME_Y;
    //
    // print_pattern(horse_1, x, y);
    //

    //
    /*
    for( ; x<VT100_SCREEN_XMAX - horse_move_3->width ; x+=horse_move_3->width ){
        print_pattern_move(horse_move_3, x, y);
    }
    */
    //

    //
    int n_threads = nbr_of_horses;
    pthread_t handlers[n_threads];
    threads_param param[n_threads];
    for (size_t t = 0; t < n_threads; t++) {
        param[t].pattern = horses[t];
        param[t].pattern->x_prev = x;
        param[t].x = x;
        param[t].y = y + t * SPACE_NAME_Y + 1;
        param[t].win = 0;
        param[t].running = 1;
        print_pattern_move(param[t].pattern, param[t].x, param[t].y);
    }

    usleep(1000000);
    for (size_t t = 0; t < n_threads; t++) {
        pthread_create(&handlers[t], NULL, print_threads, &param[t]);
    }
    int running = 1;
    while (running == 1) {

        for (int t = 0; t < n_threads; t++) {
            if (param[t].win == 1) {
                running = 0;
                for (int ti = 0; ti < n_threads; ti++) {
                    param[ti].running = 0;
                }
            }
        }
    }
    //
    for (int t = 0; t < n_threads; t++) {
        pthread_join(handlers[t], NULL);
    }

    //
    for (int t = 0; t < nbr_of_horses; t++) {
        if (param[t].win == 1) {
            print_winner(t);
        }
    }

    //
    vt100_move(VT100_SCREEN_XMAX, VT100_SCREEN_YMAX);
    vt100_cursor_on();
    //
    return 0;
}