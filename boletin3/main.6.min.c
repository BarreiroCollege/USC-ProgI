#include <stdio.h>
#include <stdlib.h>

char encr(char last, char c);


int main() {
    FILE *in;
    FILE *out;
    char c, nc, lc=0;

    in = fopen("in.txt", "r");
    out = fopen("out.txt", "w");

    if (in == NULL || out == NULL) {
        printf("Error abriendo el archivo.\n");
        return EXIT_FAILURE;
    }

    while (!feof(in)) {
        fscanf(in, "%c", &c);
        nc = encr(lc, c);
        fwrite(&nc, sizeof(nc), 1, out);
        lc = c;
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}


char encr(char last, char c) {
    int ascii = (int) c;
    int l_ascii = (int) last;
    int n_ascii = ascii + l_ascii;
    int new_ascii = n_ascii % 128;
    char new_char = (char) new_ascii;
    return new_char;
}
