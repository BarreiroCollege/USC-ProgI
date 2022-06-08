#ifndef BIGNUM_UTILS_H
#define BIGNUM_UTILS_H

#include "library.h"

/**
 * Function to swap two big numbers.
 * @param a pointer to first bignum
 * @param b pointer to second bignum
 */
void swap(bignum *a, bignum *b);

/**
 * Function to create a copy the bignum content (and not mem address).
 * @param n pointer to the bignum
 * @return copied bignum
 */
bignum copy(bignum *n);

/**
 * Function to check if the magnitude of a given number is bigger than the other.
 * @param a first bignumb
 * @param b second bignum
 * @return {@code abs(a) > abs(b)}
 */
int greater_abs(bignum a, bignum b);

/**
 * Function to check if the a given number is bigger than the other.
 * @param a first bignumb
 * @param b second bignum
 * @return {@code a > b}
 */
int greater(bignum a, bignum b);

/**
 * Function to compare two bignumbers
 * @param a first bignum
 * @param b second bignum
 * @return {@code a == b}
 */
int equals(bignum a, bignum b);

/**
 * Function to parse string to a bignum. Will stop execution if non-numeric char is passed.
 * @param str raw number as string
 * @param base base in which number is stored
 * @return parsed bignum
 */
bignum str2bignum(char *str, int base);

/**
 * Function to parse a normal int to a bignum.
 * @param num integer to be converted
 * @param base base in which number is stored
 * @return parsed bignum
 */
bignum int2bignum(int num, int base);

/**
 * Function to append a bignumber at the end of another.
 * @param a bignum to the left
 * @param b bignum to the right
 * @return {@code "a"+"b"}
 */
bignum append(bignum a, bignum b);

/**
 * Function to remove left-padding zero's.
 * @param n bignum to beautify
 * @return formatted bignum
 */
bignum prettify(bignum n);

/**
 * Function to print a big number.
 * @param n bignum to print
 */
void print(bignum n);

#endif //BIGNUM_UTILS_H
