#ifndef BIGNUM_LIBRARY_H
#define BIGNUM_LIBRARY_H

#define BASE 10

/**
 * Structure to work with big numbers, avoiding the int size. A big number is split into its digits, and then stored
 * in an array. Both length and sign are stored into variables.
 */
typedef struct {
    int base; /** base in which number is stored at */
    int sign; /** 1 for positive number, -1 for negative number */
    int size; /** number of stored digits */
    int *values; /** array of digits on number, being index 0 the less significative */
} bignum;

#endif //BIGNUM_LIBRARY_H