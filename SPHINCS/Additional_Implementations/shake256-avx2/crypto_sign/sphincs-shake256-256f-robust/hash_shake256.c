#include <stdint.h>
#include <string.h>

#include "address.h"
#include "utils.h"
#include "params.h"
#include "hash.h"
#include "fips202.h"

#define SPX_TREE_HEIGHT 10 // Replace with the actual value
#define SPX_D 2 // Replace with the actual value
#define SPX_N 32 // Replace with the actual value
#define SPX_PK_BYTES 64 // Replace with the actual value
#define SPX_FORS_MSG_BYTES 32 // Replace with the actual value

uint64_t bytes_to_ull(const unsigned char *bytes, size_t len)
{
    uint64_t result = 0;
    for (size_t i = 0; i < len; i++) {
        result |= (uint64_t)bytes[i] << (8 * i);
    }
    return result;
}

void shake256_inc_absorb(shake256_inc_state *state, const unsigned char *input, size_t inlen)
{
    shake256_inc_absorb(state, input, inlen);
}

void shake256_inc_finalize(shake256_inc_state *state)
{
    shake256_inc_finalize(state);
}

void shake256_inc_squeeze(unsigned char *output, size_t outlen, shake256_inc_state *state)
{
    shake256_inc_squeeze(output, outlen, state);
}

void shake256(unsigned char *output, size_t outlen, const unsigned char *input, size_t inlen)
{
    shake256(output, outlen, input, inlen);
}

void initialize_hash_function(const unsigned char *pub_seed,
                              const unsigned char *sk_seed)
{
    (void)pub_seed; /* Suppress an 'unused parameter' warning. */
    (void)sk_seed; /* Suppress an 'unused parameter' warning. */
}

void prf_addr(unsigned char *out, const unsigned char *key,
             const uint32_t addr[8])
{
    unsigned char buf[SPX_N + SPX_ADDR_BYTES];

    memcpy(buf, key, SPX_N);
    memcpy(buf + SPX_N, addr, SPX_ADDR_BYTES);

    shake256(out, SPX_N, buf, SPX_N + SPX_ADDR_BYTES);
}

void gen_message_random(unsigned char *R, const unsigned char *sk_prf,
                       const unsigned char *optrand,
                       const unsigned char *m, unsigned long long mlen)
{
    uint64_t s_inc[26];

    shake256_inc_init(s_inc);
    shake256_inc_absorb(s_inc, sk_prf, SPX_N);
    shake256_inc_absorb(s_inc, optrand, SPX_N);
    shake256_inc_absorb(s_inc, m, mlen);
    shake256_inc_finalize(s_inc);
    shake256_inc_squeeze(R, SPX_N, s_inc);
}

void hash_message(unsigned char *digest, uint64_t *tree, uint32_t *leaf_idx,
                 const unsigned char *R, const unsigned char *pk,
                 const unsigned char *m, unsigned long long mlen)
{
    unsigned char buf[SPX_FORS_MSG_BYTES + SPX_TREE_BYTES + SPX_LEAF_BYTES];
    unsigned char *bufp = buf;
    uint64_t s_inc[26];

    if (!digest ||!tree ||!leaf_idx ||!R ||!pk ||!m) {
        // Handle error
    }

    shake256_inc_init(s_inc);
    shake256_inc_absorb(s_inc, R, SPX_N);
    shake256_inc_absorb(s_inc, pk, SPX_PK_BYTES);
    shake256_inc_absorb(s_inc, m, mlen);
    shake256_inc_finalize(s_inc);
    shake256_inc_squeeze(buf, SPX_FORS_MSG_BYTES + SPX_TREE_BYTES + SPX_LEAF_BYTES, s_inc);

    memcpy(digest, bufp, SPX_FORS_MSG_BYTES);
    bufp += SPX_FORS_MSG_BYTES;

    *tree = bytes_to_ull(bufp, SPX_TREE_BYTES);
    *tree &= (~(uint64_t)0) >> (64 - SPX_TREE_BITS);
    bufp += SPX_TREE_BYTES;

    *leaf_idx = bytes_to_ull(bufp, SPX_LEAF_BYTES);
    *leaf_idx &= (~(uint32_t)0) >> (32 - SPX_LEAF_BITS);
}
