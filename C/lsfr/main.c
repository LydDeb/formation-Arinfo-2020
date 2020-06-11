#include <stdio.h>
#include "module.h"

int main (int argc,char** argv) {
    unsigned int n   = 0xACE1;
    unsigned int m   = n;
    unsigned int m_f = n;
    printf("0x%04X\n",n);
    for(int i=0; i<10; i++) {
        m = lfsr(m);
        m_f = lfsr_bit_field(m_f);
        printf("0x%04X 0x%04X\n", m, m_f);
    }
    
    return 0;
}