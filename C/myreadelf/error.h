#ifndef ERROR
#define ERROR
#include <stdio.h>
#include <stdlib.h>
/*----------------------------------------------------*/
static const int SYNTAX_ERROR = -1;
static const int FILE_ERROR = -2;
/*----------------------------------------------------*/
void syntax_error();
void json_syntax_error(char*);
void file_error(char*);
/*----------------------------------------------------*/
#endif