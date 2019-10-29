/**
 * Copyright (c) 2019    Diego Barreiro | diego@barreiro.xyz
 *
 *
 * Programa que pregunta por nombres hasta que se escribe FIN.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[256] = "";

    while (strcmp(input, "FIN")) {
        printf("%s\n", input);
        printf("Introduza un nome: ");
        scanf(" %s", input);
    }

    printf("\nRematei");

    return EXIT_SUCCESS;
}
