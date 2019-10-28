#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f;
    int count=0, n[512];

    f = fopen("file.txt", "r");

    if (f == NULL) {
        printf("Error abriendo el archivo.\n");
        return EXIT_FAILURE;
    }

    while (!feof(f)) {
        fscanf(f, "%d", &n[count]);
        count++;
    }

    int suma=0;
    for (int i=0; i<count; i++) {
        suma += n[i];
    }

    printf("Media = %lf\n", (double) suma/count);
    fclose(f);

    return EXIT_SUCCESS;
}
