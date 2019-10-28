// Importas la librería
#include <stdio.h>
// Aquí defines la longitud de la cadena, porque así lo declaras una vez y te ahorrras tener que escribir el mismo número muchas
// veces. Y como vas a trabajar con diferentes variables, así le pones a todas la misma longitud
#define l 256

// Declaras la función de transformar, que devuelve la variable "cambios" que es el contador de cambios. La función recibe una
// variable: palabra, que es la palabra que lees en el programa.
int transformar(char palabra[l]) {
  // Declaras las variables de inicio, que son cambios (el contador) e "i", que es el contador del for. La variable ascii trabaja
  // dentro del for.
  int cambios=0, i, ascii;

  // Aquí empieza lo bueno, es el loop for que se encarga de mapear la palabra comprobando caracter a caracter. Solo para cuando
  // el caracter es \0, o el fin de palabra.
  for (i=0; palabra[i]!='\0'; i++) {
    // Asignas el código ascii a la variable ascii. Le puse (int) al principio solo por mero protocolo, para que se entienda
    // mejor, pero funcionaría también como ascii = palabra[i]
    // palabra[i] es el caracter en la posición i
    ascii = (int) palabra[i];

    // En código ascii, si el código está entre 65 y 90 es una letra mayúscula, entonces si es así se convierte a minúscula
    if (ascii >= 65 && ascii <= 90) {
      // Para convertirlo a minúscula solo hay que sumarle 32 al código, o lo que es lo mismo, cambiar el valor del bit
      // menos significativo en la posición 5. Aquí lo mismo que antes, ponerle (char) es protocolo para que se entienda mejor
      // pero funcionaría solo con palabra[i] = ascii + 32;
      palabra[i] = (char) (ascii + 32);
      // Y se aumenta el contador en 1.
      cambios++;
    // Si no se cumple el if, el caracter no se cambia, por lo que no hace falta cambiar nada.
    }
  }
  // Y se devuelve el valor de cambios.
  return cambios;
}

// Función main()
int main() {
  // La variable palabra es lo que se escribe, y también la palabra cambiada.
  char palabra[l];

  // Lectura de datos.
  printf("Escribe: ");
  scanf("%s", palabra);

  // Se ejecuta la función transformar, y el valor que devuelve es el número de cambios.
  int cambios = transformar(palabra);
  // Pero C tiene lo que se llama paso de valor por referencia, de tal forma que si una variable se modifica en una función, se
  // cambia en la función padre (en este caso main).

  // Se imprimen los resultados.
  printf("\nCambios: %d", cambios);
  printf("\nCambiado: %s", palabra);
  return 0;
}
