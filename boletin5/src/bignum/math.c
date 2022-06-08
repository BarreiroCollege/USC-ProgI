#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "library.h"
#include "utils.h"
#include "math.h"

bignum add(bignum a, bignum b) {
    bignum c;

    if (a.base != b.base) {
        printf("Las bases de los números no coinciden!");
        exit(EXIT_FAILURE);
    }
    c.base = a.base;

    if (!(greater_abs(a, b) || equals(a, b)))
        swap(&a, &b);

    c.size = a.size;
    c.values = (int *) malloc(sizeof(int) * c.size);

    c.sign = a.sign;
    if (a.sign < 0) {
        a.sign = (-1) * a.sign;
        b.sign = (-1) * b.sign;
    }

    int res, acc = 0;
    for (int i = 0; i < a.size; i++) {
        res = *(a.values + i);
        if (acc)
            res += acc * b.sign;
        if ((b.size - 1) >= i)
            res += *(b.values + i) * b.sign;

        *(c.values + i) = (res + c.base) % c.base;

        acc = 0;
        if (res < 0 || res > (c.base - 1))
            acc = 1;
    }

    if (acc) {
        c.size++;
        c.values = (int *) realloc(c.values, sizeof(int) * c.size);
        *(c.values + (c.size - 1)) = acc;
    }

    return prettify(c);
}

bignum sub(bignum a, bignum b) {
    b.sign = (-1) * b.sign;
    return add(a, b);
}

bignum mult(bignum a, bignum b, ...) {
    if (a.base != b.base) {
        printf("Las bases de los números no coinciden!");
        exit(EXIT_FAILURE);
    }

    bignum c = int2bignum(0, a.base);

    a = copy(&a);
    b = copy(&b);

    while (*(b.values) == 0 && b.size > 1) {
        a.size++;
        a.values = realloc(a.values, sizeof(int) * a.size);
        for (int i = (a.size - 1); i > 0; i--)
            *(a.values + i) = *(a.values + i - 1);
        *(a.values) = 0;

        b.size--;
        for (int i = 0; i < b.size; i++)
            *(b.values + i) = *(b.values + i + 1);
        b.values = realloc(b.values, sizeof(int) * b.size);
    }

    va_list ap;
    va_start(ap, b);
    int block = va_arg(ap, int);
    va_end(ap);

    if (!greater_abs(a, b) && block != 1)
        swap(&a, &b);

    if (b.size == 1) {
        c.size = a.size;
        c.values = (int *) malloc(sizeof(int) * c.size);

        int res, acc = 0;
        for (int i = 0; i < a.size; i++) {
            res = *(a.values + i) * *(b.values) + acc;
            *(c.values + i) = res % c.base;

            acc = 0;
            if (res < 0 || res > (c.base - 1))
                acc = res / c.base;
        }

        if (acc) {
            c.size++;
            c.values = (int *) realloc(c.values, sizeof(int) * c.size);
            *(c.values + (c.size - 1)) = acc;
        }
    } else {
        for (int i = 0; i < b.size; i++) {
            char *str = (char *) malloc(sizeof(char) * (i + 2));
            *str = '1';
            *(str + i + 1) = '\0';
            for (int k = 1; k <= i; k++)
                *(str + k) = '0';
            bignum exp = str2bignum(str, c.base);
            free(str);

            bignum b1 = int2bignum(*(b.values + i), c.base);
            bignum n1 = mult(a, b1, 1);
            bignum n2 = mult(n1, exp, 1);

            c = add(c, n2);
        }
    }

    if (a.sign != b.sign)
        c.sign = -1;

    return prettify(c);
}

bignum division(bignum a, bignum b) {
    if (a.base != b.base) {
        printf("Las bases de los números no coinciden!");
        exit(EXIT_FAILURE);
    }

    bignum c = int2bignum(0, a.base);
    bignum r = int2bignum(0, a.base);

    int negative = 0;
    if (a.sign != b.sign) {
        negative = 1;
        a.sign = 1;
        b.sign = 1;
    }

    int k;
    for (int i = (a.size - 1); i >= 0; i--) {
        r = append(r, int2bignum(*(a.values + i), a.base));
        while (greater(b, r)) {
            i--;
            if (i < 0)
                break;
            r = append(r, int2bignum(*(a.values + i), a.base));
            c = append(c, int2bignum(0, c.base));
        }
        for (k = 0; 1; k++) {
            bignum n1 = mult(b, int2bignum(k, a.base));
            bignum n11 = mult(b, int2bignum(k + 1, a.base));
            if (greater(int2bignum(0, a.base), sub(r, n11))) {
                r = sub(r, n1);
                c = append(c, int2bignum(k, a.base));
                break;
            }
        }
    }

    if (negative)
        c.sign = -1;
    return prettify(c);
}

bignum fact(bignum n) {
    if (n.sign < 0) {
        printf("No existe el factorial de números negativos");
        exit(EXIT_FAILURE);
    }

    bignum c = int2bignum(1, n.base);

    if (n.size == 1 && *(n.values) == 0)
        return int2bignum(1, n.base);

    for (int i = 0; greater_abs(n, int2bignum(1, n.base)); i++) {
        c = mult(c, n);
        n = sub(n, int2bignum(1, n.base));
    }
    return c;
}

bignum power(bignum base, bignum exp) {
    if (base.base != exp.base) {
        printf("Las bases de los números no coinciden!");
        exit(EXIT_FAILURE);
    } else if (greater(int2bignum(0, exp.base), exp)) {
        printf("No se pueden calcular potencias negativas!");
        exit(EXIT_FAILURE);
    }

    if (equals(exp, int2bignum(0, exp.base)))
        return int2bignum(1, base.base);
    else if (equals(exp, int2bignum(1, exp.base)))
        return base;
    else if (equals(exp, int2bignum(2, exp.base)))
        return mult(base, base);
    else if (equals(int2bignum(0, exp.base), mod(exp, int2bignum(2, exp.base))))
        return power(mult(base, base), division(exp, int2bignum(2, base.base)));
    else if (equals(int2bignum(1, exp.base), mod(exp, int2bignum(2, exp.base))))
        return mult(base, power(mult(base, base), division(exp, int2bignum(2, base.base))));
}

bignum powermod(bignum x, bignum p, bignum n) {
    if (x.base != p.base || x.base != n.base || p.base != n.base) {
        printf("Las bases de los números no coinciden!");
        exit(EXIT_FAILURE);
    } else if (greater(int2bignum(0, p.base), p)) {
        printf("No se pueden calcular potencias negativas!");
        exit(EXIT_FAILURE);
    }

    bignum a = int2bignum(1, x.base);
    bignum m = copy(&p);
    bignum t = copy(&x);

    while (greater(m, int2bignum(0, m.base))) {
        bignum k = division(m, int2bignum(2, m.base));
        bignum r = sub(m, mult(int2bignum(2, k.base), k));
        if (equals(r, int2bignum(1, r.base)))
            a = mod(mult(a, t), n);
        t = mod(mult(t, t), n);
        m = copy(&k);
    }
    return a;
}


bignum mod(bignum a, bignum b) {
    if (a.base != b.base) {
        printf("Las bases de los números no coinciden!");
        exit(EXIT_FAILURE);
    }

    if (equals(a, b))
        return int2bignum(0, b.base);
    else if (!greater_abs(a, b))
        return a;
    bignum c = mult(b, division(a, b));
    c.sign = 1;
    return sub(a, c);
}