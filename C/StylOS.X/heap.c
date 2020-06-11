#include "heap.h"
#include <stdbool.h>
#include <stdint.h>

#define BLOCK_SIZE (16) /* must be power of two */
#define BLOCK_NB (1024) /* must be less than 2^16 */

static bool free_block[BLOCK_NB];
static uint8_t data[BLOCK_NB * BLOCK_SIZE];

void heap_init(void) {
    uint16_t block_index;
    uint32_t byte_index;

    /* for each block */
    for (block_index = 0; block_index < BLOCK_NB; block_index++)
        free_block[block_index] = true;

    /* for each byte in data */
    for (byte_index = 0; byte_index < BLOCK_SIZE * BLOCK_NB; byte_index++)
        data[byte_index] = 0xFF;
}

void *heap_malloc(int nb_bytes) {
    uint16_t nb_wanted_blocks = (nb_bytes + BLOCK_SIZE - 1) / BLOCK_SIZE;
    uint16_t block_index;
    uint16_t nb_free_blocks;
    for (block_index = 0; block_index < BLOCK_NB; block_index++) {
        for (nb_free_blocks = 0; nb_free_blocks < nb_wanted_blocks &&
                                 block_index + nb_free_blocks < BLOCK_NB;
             nb_free_blocks++) {
            /* if already reserved */
            if (free_block[block_index + nb_free_blocks] == false) {
                /* jump at that block */
                block_index += nb_free_blocks;
                break;
            }
        }
        if (nb_free_blocks == nb_wanted_blocks) {
            for (nb_free_blocks = 0; nb_free_blocks < nb_wanted_blocks;
                 nb_free_blocks++)
                free_block[block_index + nb_free_blocks] = false;
            return &data[block_index * BLOCK_SIZE];
        }
    }
    return NULL;
}

void heap_free(void *pointer, int nb_bytes) {
    if (pointer) {
        uint16_t start_block_index = ((uint8_t *)pointer - data) / BLOCK_SIZE;
        uint16_t nb_blocks = (nb_bytes + BLOCK_SIZE - 1) / BLOCK_SIZE;
        uint16_t block_index;
        for (block_index = start_block_index;
             block_index < start_block_index + nb_blocks; block_index++) {
            free_block[block_index] = true;
        }
    }
}