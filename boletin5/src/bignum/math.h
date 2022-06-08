#ifndef BIGNUM_MATH_H
#define BIGNUM_MATH_H

#include "library.h"

/**
 * Function to sum two bignum structs.
 * @param a first operand
 * @param b second operand
 * @return {@code a + b}
 */
extern bignum add(bignum a, bignum b);

/**
 * Function to substract two bignum structs.
 * @see add()
 * @param a first operand
 * @param b substract operand
 * @return {@code a - b}
 */
extern bignum sub(bignum a, bignum b);

/**
 * Function to multiply two bignum structs.
 * @param a first operand
 * @param b second operand
 * @return {@code a * b}
 */
extern bignum mult(bignum a, bignum b, ...);

/**
 * Returns the division result without decimals.
 * @param a dividend
 * @param b divisor
 * @return {@code a/b}
 */
extern bignum division(bignum a, bignum b);

/**
 * Function to calculate the factorial of a given number.
 * @param n bignum
 * @return {@code n!}
 */
extern bignum fact(bignum n);

/**
 * Function to calculate the power of a given number.
 * @param base base of power
 * @param exp exponent of power
 * @return {@code base^exp}
 */
extern bignum power(bignum base, bignum exp);

/**
 * Function to calculate the modular power of a given number.
 * @param x base of power
 * @param p exponent of power
 * @param n module
 * @return {@code base^exp % n}
 */
extern bignum powermod(bignum x, bignum p, bignum n);

/**
 * Function to calculate the remainder of a division.
 * @param a dividend
 * @param b divisor
 * @return {@code a%b}
 */
extern bignum mod(bignum a, bignum b);

#endif //BIGNUM_MATH_H
