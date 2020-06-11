#include "error.h"
static const char *red = "\033[0;31m";
static const char *reset = "\033[0m";
static const char *bold = "\033[1m";
//
void syntax_error() {
    printf("\n\t%s%s[!] => SYNTAX ERROR <= [!]%s\n", red, bold, reset);
    exit(SYNTAX_ERROR);
}
//
void json_syntax_error(char *errstr) {
    printf("\n\t%s%s[!] => SYNTAX ERROR IN JSON FILE <= [!]%s\n", red, bold,
           reset);
    printf("\t%s%s[!] => %s <= [!]%s\n", red, bold, errstr, reset);
    exit(SYNTAX_ERROR);
}
//
void file_error(char *errstr) {
    printf("\n\t%s%s[!] => FILE ERROR <= [!]%s\n", red, bold, reset);
    printf("\t%s%s[!] => %s <= [!]%s\n", red, bold, errstr, reset);
    exit(FILE_ERROR);
}
//
void argument_error(char *errstr) {
    printf("\n\t%s%s[!] => ARGUMENT ERROR <= [!]%s\n", red, bold, reset);
    printf("\t%s%s[!] => %s <= [!]%s\n", red, bold, errstr, reset);
    exit(ARGUMENT_ERROR);
}