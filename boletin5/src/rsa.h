#ifndef BOLETIN5_RSA_H
#define BOLETIN5_RSA_H

#include "bignum/library.h"

/**
 * Structure to calculate the RSA private key.
 */
typedef struct {
    bignum a;
    bignum b;
    bignum d;
    bignum k;
} row;

/**
 * Get the great common divisor of two bignumbers
 * @param a first bignum
 * @param b second bignum
 * @return {@code gcd(a, b)}
 */
bignum gcd(bignum a, bignum b);

/**
 * Function to generate a RSA keypair
 */
void keypair(bignum p, bignum q);

/**
 * Function to encrypt with RSA.
 */
void encrypt(bignum p, bignum q, bignum msg);

/**
 * Function to decrypt with RSA.
 */
void decrypt(bignum d, bignum n, bignum msg);

#endif //BOLETIN5_RSA_H
