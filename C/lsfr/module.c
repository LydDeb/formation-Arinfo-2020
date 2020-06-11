#include "module.h"
//
unsigned int lfsr(unsigned int n){
    unsigned int m = n;
    unsigned int b = 1 & ((n>>5)^(n>>3)^(n>>2)^(n>>0));
    m = (m>>1) | (b<<15);
    return m;
}
//
void uint_to_bit_field(unsigned int n, bit_field* bf){
    bf->b0 = 1 & (n >> 0x00);
    bf->b1 = 1 & (n >> 0x01);
    bf->b2 = 1 & (n >> 0x02);
    bf->b3 = 1 & (n >> 0x03);
    bf->b4 = 1 & (n >> 0x04);
    bf->b5 = 1 & (n >> 0x05);
    bf->b6 = 1 & (n >> 0x06);
    bf->b7 = 1 & (n >> 0x07);
    bf->b8 = 1 & (n >> 0x08);
    bf->b9 = 1 & (n >> 0x09);
    bf->ba = 1 & (n >> 0x0a);
    bf->bb = 1 & (n >> 0x0b);
    bf->bc = 1 & (n >> 0x0c);
    bf->bd = 1 & (n >> 0x0d);
    bf->be = 1 & (n >> 0x0e);
    bf->bf = 1 & (n >> 0x0f);
}
//
unsigned int bit_field_to_uint(bit_field* bf){
    unsigned int n = 0;
    n = (bf->b0 << 0x00) | (bf->b1 << 0x01) | (bf->b2 << 0x02) | (bf->b3 << 0x03) | 
        (bf->b4 << 0x04) | (bf->b5 << 0x05) | (bf->b6 << 0x06) | (bf->b7 << 0x07) |
        (bf->b8 << 0x08) | (bf->b9 << 0x09) | (bf->ba << 0x0a) | (bf->bb << 0x0b) |
        (bf->bc << 0x0c) | (bf->bd << 0x0d) | (bf->be << 0x0e) | (bf->bf << 0x0f);
    return n;    
}
//
bit_field* new_bit_field(){
    bit_field* field = malloc(sizeof(bit_field));
    field->b0 = 0;
    field->b1 = 0;
    field->b2 = 0;
    field->b3 = 0;
    field->b4 = 0;
    field->b5 = 0;
    field->b6 = 0;
    field->b7 = 0;
    field->b8 = 0;
    field->b9 = 0;
    field->ba = 0;
    field->bb = 0;
    field->bc = 0;
    field->bd = 0;
    field->be = 0;
    field->bf = 0;
    field->op = 0;
    return field;
}
//
unsigned int lfsr_bit_field(unsigned int n){
    bit_field* field = new_bit_field();
    uint_to_bit_field(n, field);
    field->op = field->b5 ^ field->b3 ^ field->b2 ^ field->b0;    
    field->b0 = field->b1;
    field->b1 = field->b2;
    field->b2 = field->b3;
    field->b3 = field->b4;
    field->b4 = field->b5;
    field->b5 = field->b6;
    field->b6 = field->b7;
    field->b7 = field->b8;
    field->b8 = field->b9;
    field->b9 = field->ba;
    field->ba = field->bb;
    field->bb = field->bc;
    field->bc = field->bd;
    field->bd = field->be;
    field->be = field->bf;
    field->bf = field->op;
    unsigned int m = bit_field_to_uint(field);
    return m;
}