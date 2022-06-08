#include <stdio.h>
#include <stdlib.h>

#include "bignum/library.h"
#include "bignum/utils.h"
#include "bignum/math.h"
#include "rsa.h"


bignum gcd(bignum a, bignum h) {
    if (a.base != h.base) {
        printf("Las bases no coinciden!");
        exit(EXIT_FAILURE);
    }

    bignum temp;
    while (1) {
        temp = mod(a, h);
        if (equals(temp, int2bignum(0, a.base)))
            return h;
        a = h;
        h = temp;
    }
}

void keypair(bignum p, bignum q) {
    bignum n = mult(p, q);

    bignum phi = mult(sub(p, int2bignum(1, BASE)), sub(q, int2bignum(1, BASE)));

    bignum e = int2bignum(2, BASE);
    while (greater_abs(phi, e)) {
        // e must be co-prime to phi and
        // smaller than phi.
        if (equals(gcd(e, phi), int2bignum(1, BASE)) && !equals(e, p) && !equals(e, q))
            break;
        e = add(e, int2bignum(1, BASE));
    }

    row *table = (row *) malloc(sizeof(row) * 2);
    (*(table + 0)).a = int2bignum(1, BASE);
    (*(table + 0)).b = int2bignum(0, BASE);
    (*(table + 0)).d = phi;
    (*(table + 0)).k = int2bignum(0, BASE);
    (*(table + 1)).a = int2bignum(0, BASE);
    (*(table + 1)).b = int2bignum(1, BASE);
    (*(table + 1)).d = e;
    (*(table + 1)).k = division(phi, e);

    int i;
    for (i = 2; !equals((*(table + i - 1)).d, int2bignum(1, BASE)); i++) {
        table = realloc(table, sizeof(row) * (i + 1));
        (*(table + i)).a = sub((*(table + i - 2)).a, mult((*(table + i - 1)).a, (*(table + i - 1)).k));
        (*(table + i)).b = sub((*(table + i - 2)).b, mult((*(table + i - 1)).b, (*(table + i - 1)).k));
        (*(table + i)).d = sub((*(table + i - 2)).d, mult((*(table + i - 1)).d, (*(table + i - 1)).k));
        (*(table + i)).k = division((*(table + i - 1)).d, (*(table + i - 0)).d);
    }

    i--;
    bignum d = (*(table + i)).b;
    if (greater(d, phi))
        d = mod(d, phi);
    else if (greater(int2bignum(0, d.base), d))
        d = add(d, phi);

    printf("Clave Pública (e | n) = (");
    print(e);
    printf(" | ");
    print(n);
    printf(")\n");

    printf("Clave Privada (d | n) = (");
    print(d);
    printf(" | ");
    print(n);
    printf(")\n");
}

void encrypt(bignum e, bignum n, bignum msg) {
    bignum c = powermod(msg, e, n);
    printf("Encriptado [(msg ^ e) %% n] = ");
    print(c);
    printf("\n");
}

void decrypt(bignum d, bignum n, bignum msg) {
    bignum m = powermod(msg, d, n);
    printf("Desencriptado [(msg ^ d) %% n] = ");
    print(m);
    printf("\n");
}
