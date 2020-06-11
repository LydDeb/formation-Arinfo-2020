/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    utils.h

  @Description
    This file groups the declarations of the functions that implement
        the utils library (defined in utils.c).
        Include the file in the project when this library is needed.
        Use #include "utils.h" in the source files where the functions are needed.
 */
/* ************************************************************************** */

#ifndef _UTILS_H    /* Guard against multiple inclusion */
#define _UTILS_H

void DelayAprox10Us( unsigned int tusDelay );
void swap_values(uint8_t* a, uint8_t* b);
uint16_t hex_to_dec(uint8_t hex);
uint16_t prng_lfsr(uint16_t lfsr);
#endif /* _UTILS_H */

/* *****************************************************************************
 End of File
 */
