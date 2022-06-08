#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"
#include "utils.h"

void swap(bignum *a, bignum *b) {
    bignum temp = *a;
    *a = *b;
    *b = temp;
}

bignum copy(bignum *n) {
    bignum n2 = *n;
    n2.values = NULL;
    n2.values = (int *) malloc(sizeof(int) * n2.size);
    for (int i = 0; i < n->size; i++) {
        *(n2.values + i) = *(n->values + i);
    }
    return n2;
}

int greater_abs(bignum a, bignum b) {
    if (a.size > b.size)
        return 1;
    else if (b.size > a.size)
        return 0;
    else if (a.size == b.size) {
        int i;
        for (i = (a.size - 1); a.values[i] == b.values[i]; i--)
            if (!i) break;
        if (a.values[i] > b.values[i])
            return 1;
        else
            return 0;
    }
}

int greater(bignum a, bignum b) {
    if (a.sign != b.sign)
        return a.sign > b.sign;
    else
        return a.sign > 0 ? greater_abs(a, b) : greater_abs(b, a);
}

int equals(bignum a, bignum b) {
    if (a.base != b.base) {
        printf("Las bases no coinciden!");
        exit(EXIT_FAILURE);
    }
    if (a.size != b.size) return 0;
    if (a.sign != b.sign) return 0;
    for (int i = 0; i < a.size; i++)
        if (*(a.values + i) != *(b.values + i))
            return 0;
    return 1;
}


bignum str2bignum(char *str, int base) {
    bignum n;
    int len = (int) strlen(str);
    n.base = base;
    n.size = len;
    n.values = (int *) malloc(sizeof(int) * n.size);

    int tmp;
    int counter = 0;
    for (int i = 0; i < len; i++) {
        if (i == 0) {
            if (*(str + i) == '-') {
                n.sign = -1;
                n.size--;
                continue;
            } else if (*(str + i) == ',' || *(str + i) == '.') {
                n.size--;
                continue;
            } else {
                n.sign = 1;
            }
        }
        if (base != 128 && (48 > (int) str[i] || (int) str[i] > 57)) {
            printf("Error parseando el número! Has introducido caracteres que no son números.");
            exit(EXIT_FAILURE);
        }

        tmp = ((int) str[i]) - (base != 128 ? '0' : 0);
        *(n.values + (n.size - counter - 1)) = tmp;
        counter++;
    }

    return prettify(n);
}

bignum int2bignum(int num, int base) {
    int c = (num / base) + 1;
    char *n = (char *) malloc(sizeof(char) * c);
    sprintf(n, "%d", num);
    return str2bignum(n, base);
}

bignum append(bignum a, bignum b) {
    a = copy(&a);
    b = copy(&b);

    a.size += b.size;
    a.values = (int *) realloc(a.values, sizeof(int) * a.size);
    for (int i = (a.size - 1); i >= 0; i--)
        *(a.values + i) = i > b.size - 1 ? *(a.values + i - b.size) : *(b.values + i);
    return prettify(a);
}

bignum prettify(bignum n) {
    int o_len = n.size - 1;
    int proceed = 0;
    for (int i = o_len; i >= 0; i--) {
        if (i == o_len || proceed) {
            if (*(n.values + i) == 0 && n.size > 1) {
                proceed = 1;
                n.size--;
                n.values = (int *) realloc(n.values, sizeof(int) * n.size);
            } else
                proceed = 0;
        }
    }
    if (n.size == 1 && *n.values == 0)
        n.sign = 1;
    return n;
}

void print(bignum n) {
    if (n.sign == -1) printf("-");
    for (int i = n.size - 1; i >= 0; i--) {
        printf(n.base != 128 ? "%d" : "%c", (n.base != 128 ? (int) n.values[i] : (char) n.values[i]));
        if (n.base == 10 && !(i % 3) && i)
            printf(",");
        else if (n.base == 2 && !(i % 4) && i)
            printf(" ");
    }
}
