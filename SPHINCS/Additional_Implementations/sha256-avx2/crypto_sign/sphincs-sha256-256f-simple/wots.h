#ifndef SPX_WOTS_H
#define SPX_WOTS_H

#include <stdint.h>
#include "params.h"

/**
 * WOTS key generation. Takes a 32-byte seed for the private key, expands it to
 * a full WOTS private key and computes the corresponding public key.
 * It requires the seed pub_seed (used to generate bitmasks and hash keys)
 * and the address of this WOTS key pair.
 *
 * Writes the computed public key to 'pk'.
 *
 * @param pk Pointer to the buffer where the public key will be written.
 * @param seed Pointer to the 32-byte seed for the private key.
 * @param pub_seed Pointer to the seed used to generate bitmasks and hash keys.
 * @param addr Pointer to the 8-element array representing the address of this WOTS key pair.
 *
 * @return void
 */
void wots_gen_pk(unsigned char *pk, const unsigned char *seed,
                 const unsigned char *pub_seed, uint32_t addr[8]);

/**
 * Takes a n-byte message and the 32-byte seed for the private key to compute a
 * signature that is placed at 'sig'.
 *
 * @param sig Pointer to the buffer where the signature will be written.
 * @param msg Pointer to the n-byte message to be signed.
 * @param seed Pointer to the 32-byte seed for the private key.
 * @param pub_seed Pointer to the seed used to generate bitmasks and hash keys.
 * @param addr Pointer to the 8-element array representing the address of this WOTS key pair.
 *
 * @return void
 */
void wots_sign(unsigned char *sig, const unsigned char *msg,
               const unsigned char *seed, const unsigned char *pub_seed,
               uint32_t addr[8]);

/**
 * Takes a WOTS signature and an n-byte message, computes a WOTS public key.
 *
 * Writes the computed public key to 'pk'.
 *
 * @param pk Pointer to the buffer where the public key will be written.
 * @param sig Pointer to the WOTS signature.
 * @param msg Pointer to the n-byte message.
 * @param pub_seed Pointer to the seed used to generate bitmasks and hash keys.
 * @param addr Pointer to the 8-element array representing the address of this WOTS key pair.
 *
 * @return void
 */
void wots_pk_from_sig(unsigned char *pk,
                      const unsigned char *sig, const unsigned char *msg,
                      const unsigned char *pub_seed, uint32_t addr[8]);

#endif
