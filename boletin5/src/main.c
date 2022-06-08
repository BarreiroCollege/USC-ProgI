#include <stdio.h>
#include <stdlib.h>

#include "bignum/library.h"
#include "bignum/utils.h"
#include "bignum/math.h"
#include "rsa.h"


char *inputString(FILE *fp, size_t size) {
    char *str = NULL;
    int ch;
    size_t len = 0;
    str = malloc(sizeof(char) * 1);
    if (!str)
        return str;
    while (EOF != (ch = fgetc(fp)) && ch != '\n') {
        str[len++] = (char) ch;
        if (len == size) {
            str = realloc(str, sizeof(char) * (size += 16));
            if (!str)
                return str;
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}


int main() {
    bignum menu;
    while (1) {
        printf("---------- BOLETÍN 5 ----------\n");
        printf("1. Probar librería de BigNum\n");
        printf("2. Encriptación RSA\n");
        printf("0. Salir\n");
        printf("\n");
        printf("> ");
        menu = str2bignum(inputString(stdin, 10), 10);
        printf("\n");
        if (equals(menu, int2bignum(0, 10)))
            break;
        else if (equals(menu, int2bignum(1, 10))) {
            bignum a = int2bignum(0, BASE);
            bignum b = int2bignum(0, BASE);
            while (1) {
                printf("---------- MODO BIGNUM ----------\n");
                printf("a = ");
                print(a);
                printf("\n");
                printf("b = ");
                print(b);
                printf("\n");
                printf("\n");
                printf("1. Modificar números\n");
                printf("2. Suma (a+b)\n");
                printf("3. Resta (a-b)\n");
                printf("4. Multiplicación (a*b)\n");
                printf("5. División (a/b)\n");
                printf("6. Factorial (a!)\n");
                printf("7. Exponente (a^b)\n");
                printf("8. Módulo (a%%b)\n");
                printf("9. Potencia modular (a^b %% %d)\n", BASE);
                printf("0. Volver\n");
                printf("\n");
                printf("> ");
                menu = str2bignum(inputString(stdin, 10), 10);
                printf("\n");
                if (equals(menu, int2bignum(0, 10)))
                    break;
                else if (equals(menu, int2bignum(1, 10))) {
                    printf("Número a > ");
                    char *in1 = inputString(stdin, 10);
                    a = str2bignum(in1, BASE);
                    printf("Número b > ");
                    char *in2 = inputString(stdin, 10);
                    b = str2bignum(in2, BASE);
                } else if (equals(menu, int2bignum(2, 10))) {
                    printf("= ");
                    print(add(a, b));
                    printf("\n");
                } else if (equals(menu, int2bignum(3, 10))) {
                    printf("= ");
                    print(sub(a, b));
                    printf("\n");
                } else if (equals(menu, int2bignum(4, 10))) {
                    printf("= ");
                    print(mult(a, b));
                    printf("\n");
                } else if (equals(menu, int2bignum(5, 10))) {
                    printf("= ");
                    print(division(a, b));
                    printf("\n");
                } else if (equals(menu, int2bignum(6, 10))) {
                    printf("= ");
                    print(fact(a));
                    printf("\n");
                } else if (equals(menu, int2bignum(7, 10))) {
                    printf("= ");
                    print(power(a, b));
                    printf("\n");
                } else if (equals(menu, int2bignum(8, 10))) {
                    printf("= ");
                    print(mod(a, b));
                    printf("\n");
                } else if (equals(menu, int2bignum(9, 10))) {
                    printf("= ");
                    print(powermod(a, b, int2bignum(BASE, BASE)));
                    printf("\n");
                }
                if (greater(menu, int2bignum(1, BASE)) && greater(int2bignum(10, BASE), menu)) {
                    printf("Pulsa [enter] para continuar...");
                    getchar();
                }
                printf("\n");
            }
        } else if (equals(menu, int2bignum(2, 10))) {
            while (1) {
                printf("---------- MODO RSA ----------\n");
                printf("1. Generar claves\n");
                printf("2. Encriptar\n");
                printf("3. Desencriptar\n");
                printf("0. Volver\n");
                printf("\n");
                printf("> ");
                menu = str2bignum(inputString(stdin, 10), 10);
                printf("\n");
                if (equals(menu, int2bignum(0, 10)))
                    break;
                else if (equals(menu, int2bignum(1, 10))) {
                    printf("Introduce los números primos p y q\n");
                    printf("p > ");
                    bignum p = str2bignum(inputString(stdin, 10), BASE);
                    printf("q > ");
                    bignum q = str2bignum(inputString(stdin, 10), BASE);
                    keypair(p, q);
                } else if (equals(menu, int2bignum(2, 10))) {
                    printf("Introduce la clave pública\n");
                    printf("e > ");
                    bignum e = str2bignum(inputString(stdin, 10), BASE);
                    printf("n > ");
                    bignum n = str2bignum(inputString(stdin, 10), BASE);
                    printf("Introduce el mensaje a encriptar\n");
                    printf("> ");
                    bignum msg = str2bignum(inputString(stdin, 10), BASE);
                    encrypt(e, n, msg);
                } else if (equals(menu, int2bignum(3, 10))) {
                    printf("Introduce la clave privada\n");
                    printf("d > ");
                    bignum d = str2bignum(inputString(stdin, 10), BASE);
                    printf("n > ");
                    bignum n = str2bignum(inputString(stdin, 10), BASE);
                    printf("Introduce el mensaje a desencriptar\n");
                    printf("> ");
                    bignum msg = str2bignum(inputString(stdin, 10), BASE);
                    decrypt(d, n, msg);
                }
                if (greater(menu, int2bignum(0, BASE)) && greater(int2bignum(4, BASE), menu)) {
                    printf("Pulsa [enter] para continuar...");
                    getchar();
                }
                printf("\n");
            }
        }
        printf("\n\n");
    }
    return EXIT_SUCCESS;
}