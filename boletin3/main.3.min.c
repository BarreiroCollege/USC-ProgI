#include <stdio.h>
#define l 256

int transformar(char palabra[l]) {
  int cambios=0, i, ascii;

  for (i=0; palabra[i]!='\0'; i++) {
    ascii = (int) palabra[i];

    if (ascii >= 65 && ascii <= 90) {
      palabra[i] = (char) (ascii + 32);
      cambios++;
    }
  }
  return cambios;
}

int main() {
  char palabra[l];

  printf("Escribe: ");
  scanf("%s", palabra);

  int cambios = transformar(palabra);

  printf("\nCambios: %d", cambios);
  printf("\nCambiado: %s", palabra);
  return 0;
}
