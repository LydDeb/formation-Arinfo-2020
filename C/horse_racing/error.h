#ifndef ERROR
#define ERROR
#include <stdio.h>
#include <stdlib.h>
/*----------------------------------------------------*/
static const int SYNTAX_ERROR = -1;
static const int FILE_ERROR = -2;
static const int ARGUMENT_ERROR = -3;
/*----------------------------------------------------*/
void syntax_error();
void json_syntax_error(char *);
void file_error(char *);
void argument_error(char *);
/*----------------------------------------------------*/
#endif