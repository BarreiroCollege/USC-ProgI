#include <stdio.h>
#include <string.h>


char desc(char last, char c);
int Hamming(char string1[], char string2[]);


int main() {
    char contra[128];
    printf("Contraseña > ");
    scanf(" %[^\n]s", contra);


    FILE *f = fopen("chaves.dat", "r");

    if (f == NULL) {
        printf("Error abriendo el archivo.\n");
        return 1;
    }

    char archivo[128];
    while (fscanf(f, " %[^\n]s", archivo) > 0) {
        char nc, lc=0;
        for (int i=0; i<strlen(archivo); i++) {
            nc = desc(lc, archivo[i]);
            archivo[i] = nc;
            lc = archivo[i];
        }
        archivo[strlen(archivo)-1] = '\0';

        if (!Hamming(contra, archivo)) {
            printf("Contraseña Correcta");
            return 0;
        }
    }

    printf("Contraseña Incorrecta");
    return 1;
}



char desc(char last, char c) {
    return (char) (((c - last) + 128) % 128);
}


int Hamming(char string1[], char string2[]) {
    int len1 = strlen(string1);
    int len2 = strlen(string2);
    if (len1 != len2) {
        return -1;
    }

    int c = 0;
    for (int i=0; i<len1; i++) {
        if (string1[i] != string2[i]) c++;
    }
    return c;
}
