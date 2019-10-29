#include <stdio.h>
#include <stdlib.h>

char desc(char last, char c);


int main() {
    FILE *in;
    FILE *out;
    char c, nc, lc=0;

    in = fopen("in.txt", "r");
    out = fopen("out.txt", "wb");

    if (in == NULL || out == NULL) {
        printf("Error abriendo el archivo.\n");
        return EXIT_FAILURE;
    }

    while (1) {
        fscanf(in, "%c", &c);
        if (feof(in)!=0) break;
        nc = desc(lc, c);
        fwrite(&nc, sizeof(nc), 1, out);
        lc = nc;
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}


char desc(char last, char c) {
    int ascii = (int) c;
    int l_ascii = (int) last;
    int n_ascii = (ascii - l_ascii) + 128;
    int new_ascii = n_ascii % 128;
    char new_char = (char) new_ascii;
    return new_char;
}
