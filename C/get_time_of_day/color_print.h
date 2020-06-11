#ifndef COLOR_PRINT_H
#define COLOR_PRINT_H
#define CP_RED(X) printf("\033[0;31m%s\033[0m", X)
#define CP_GREEN(X) printf("\033[0;32m%s\033[0m", X)
#define CP_YELLOW(X) printf("\033[0;33m%s\033[0m", X)
#define CP_BLUE(X) printf("\033[0;34m%s\033[0m", X)
#define CP_MAGENTA(X) printf("\033[0;35m%s\033[0m", X)
#define CP_CYAN(X) printf("\033[0;36m%s\033[0m", X)
#define CP_SET_RED printf("\033[31m")
#define CP_SET_GREEN printf("\033[32m")
#define CP_SET_YELLOW printf("\033[33m")
#define CP_SET_BLUE printf("\033[34m")
#define CP_SET_MAGENTA printf("\033[35m")
#define CP_SET_CYAN printf("\033[36m")
#define CP_SET_BOLD printf("\033[1m")
#define CP_RESET printf("\033[0m")
#endif