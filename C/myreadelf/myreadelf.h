#ifndef MYREADELF_H
#define MYREADELF_H
/*-----------------------------------------------------------------*/
#include "myreadelf_module.h"
/*-----------------------------------------------------------------*/
enum flag_num{
FLAG_H,
FLAG__help,
FLAG_h,
FLAG__file_header,
FLAG_x,
FLAG__hex_dump,
FLAG_FILE
};
//
typedef struct flag_arg{
    enum flag_num num;
    char*    str;
}flag_arg;
//
typedef struct arg_action{
    enum flag_num num;
    char* option;
    struct arg_action* next;
}arg_action;
/*-----------------------------------------------------------------*/
char USAGE[] = "Usage: readelf <option(s)> fichier(s)-elf\n"
" Afficher les informations à propos du contenu du format des fichiers ELF\n"
" Options are:\n"
"  -H --help              Afficher l'aide-mémoire\n"
"  -h --file-header       Display the ELF file header\n"
"  -x --hex-dump=<number|name>\n"
"                         Dump the contents of section <number|name> as bytes\n";
char** ELF_FILES;
int count_files = 0;
flag_arg flag_H            = {FLAG_H,"-H"};
flag_arg flag_help         = {FLAG__help,"--help"};
flag_arg flag_h            = {FLAG_h,"-h"};
flag_arg flag__file_header = {FLAG__file_header,"--file-header"};
flag_arg flag_x            = {FLAG_x,"-x"};
flag_arg flag__hex_dump    = {FLAG__hex_dump,"--hex-dump"};
/*-----------------------------------------------------------------*/
arg_action* parse_arg(int , char** );
arg_action* new_action();
/*-----------------------------------------------------------------*/
#endif
