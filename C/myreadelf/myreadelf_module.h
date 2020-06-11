#ifndef MYREADELF_MODULE_H
#define MYREADELF_MODULE_H
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
#include "debug.h"
#include "error.h"
//
char* get_elf_class(int);
char* get_elf_data_encoding(int);
char* get_elf_version(int);
char* get_elf_os_abi(int);
char* get_elf_type(int);
char* get_elf_machine(int);
void read_elf_header(const char*);
void read_elf_header_64( Elf64_Ehdr );
void read_elf_header_32( Elf32_Ehdr );
void read_elf_section( char*, char* );
//void read_elf_section_64( Elf64_Shdr );
//void read_elf_section_32( Elf32_Shdr );
int find_section_name(char*,int,char*,int);
//
#endif