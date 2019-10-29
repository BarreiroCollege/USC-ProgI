/**
 * Copyright (c) 2019    Diego Barreiro | diego@barreiro.xyz
 *
 *
 * Programa que genera una pirámide del tipo [1, 12, 123, 1234, ...]
 *
 * Este programa se basa en crear un array vació de strings al inicio cuyo índice máximo es el dado por el usuario
 * (de tal forma que el número total de entradas en el array es n+1 por el 0 también ser un elemento). De esta forma,
 * se crea un loop while con un contador que a cada vuelta obtiene el valor del elemento anterior en el array y le
 * concatena el valor en string del contador.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read();



int main() {
    int m = read(); // = Lineas solicitadas
    char o[m][m]; // = Array que contiene la pirámide
    int l = 0; // = Último índice mapeado

    strcpy(o[0], "");
    while (m > l) {
        l++;
        // char t[128];
        // snprintf(t, sizeof(t), "%s%d", o[l-1], l);
        // strcpy(o[l], t);
        snprintf(o[l], sizeof(o[l])+1, "%s%d", o[l-1], l);
    }

    for (int i = 1; i <= m; i++) {
        printf("%s\n", o[i]);
    }

    return EXIT_SUCCESS;
}


int read() {
    int i;
    printf("Número de filas (mayor que 0): ");
    scanf("%i", &i);

    while (i <= 0) {
        printf("Introduce un número mayor que 0: ");
        scanf("%i", &i);
    }
    printf("\n");
    return i;
}
