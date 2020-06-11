#ifndef MODULE_H
#define MODULE_H
#include <stdlib.h>
//
typedef struct bit_field{
    unsigned int bf : 1;
    unsigned int be : 1;
    unsigned int bd : 1;
    unsigned int bc : 1;
    unsigned int bb : 1;
    unsigned int ba : 1;
    unsigned int b9 : 1;
    unsigned int b8 : 1;
    unsigned int b7 : 1;
    unsigned int b6 : 1;
    unsigned int b5 : 1;
    unsigned int b4 : 1;
    unsigned int b3 : 1;
    unsigned int b2 : 1;
    unsigned int b1 : 1;
    unsigned int b0 : 1;
    unsigned int op : 1;
} bit_field;
//
unsigned int lfsr(unsigned int n);
void uint_to_bit_field(unsigned int n, bit_field* bf);
unsigned int bit_field_to_uint(bit_field* bf);
unsigned int lfsr_bit_field(unsigned int n);
bit_field* new_bit_field();
#endif