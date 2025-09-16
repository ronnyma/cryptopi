#include "aes.h"

void expand_key(const uint8_t key[32]) {
    uint32_t w[60];

    int i;
    for (i = 0; i < 8; i++) {
        w[i] = (uint32_t) key[4 * i] << 24 | (uint32_t) key[4 * i + 1] << 16
               | (uint32_t) key[4 * i + 2] << 8 | key[4 * i + 3];
    }

    for (i = 8; i < 60; i++) {
        uint32_t temp = w[i - 1];

        if (i % 8 == 0) {
            temp = subst_word(rot_word(temp)) ^ rcon[i / 8];
        } else if (i % 8 == 4) {
            temp = subst_word(temp);
        }

        w[i] = w[i - 8] ^ temp;
    }
}


static uint32_t subst_word(uint32_t word) {
    uint8_t *bytes = (uint8_t *) &word;
    bytes[0] = sbox[bytes[0]];
    bytes[1] = sbox[bytes[1]];
    bytes[2] = sbox[bytes[2]];
    bytes[3] = sbox[bytes[3]];
    return word;
}

static uint32_t rot_word(uint32_t word) {
    return word << 8 | word >> 24;
}
