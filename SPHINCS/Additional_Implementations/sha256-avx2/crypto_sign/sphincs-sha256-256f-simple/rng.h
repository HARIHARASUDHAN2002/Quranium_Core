//
//  rng.h
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//

#ifndef rng_h
#define rng_h

#include <stdbool.h>
#include <stdint.h>

// Error codes
typedef enum {
    RNG_SUCCESS = 0,
    RNG_BAD_MAXLEN = -1,
    RNG_BAD_OUTBUF = -2,
    RNG_BAD_REQ_LEN = -3,
    RNG_BAD_ENTROPY = -4,
    RNG_BAD_PERSONALIZATION = -5,
    RNG_BAD_SECURITY_STRENGTH = -6,
    RNG_INTERNAL_ERROR = -7,
} rng_error_t;

// Seed expander context
typedef struct {
    uint8_t buffer[16];
    int buffer_pos;
    uint32_t length_remaining;
    uint8_t key[32];
    uint8_t ctr[16];
} AES_XOF_ctx_t;

// CTR_DRBG context
typedef struct {
    uint8_t Key[32];
    uint8_t V[16];
    int reseed_counter;
} AES256_CTR_DRBG_ctx_t;

// Function prototypes
void AES256_CTR_DRBG_Update(uint8_t *provided_data, uint8_t *Key, uint8_t *V);
rng_error_t seedexpander_init(AES_XOF_ctx_t *ctx, const uint8_t *seed, const uint8_t *diversifier, uint32_t maxlen);
rng_error_t seedexpander(AES_XOF_ctx_t *ctx, uint8_t *x, uint32_t xlen);
rng_error_t randombytes_init(const uint8_t *entropy_input, const uint8_t *personalization_string, int security_strength);
rng_error_t randombytes(uint8_t *x, uint64_t xlen);

#endif /* rng_h */
