/*
 * Escribir un programa cunha función que determine a media dos valores dunha secuencia de
 * enteiros almacenada nun arquivo. Lede os datos do arquivo e ideos gardando nun vector. Facede a
 * lectura ata chegar ao final o arquivo (nese momento feof(ptf)!=0). No arquivo cabeceira stdlib.h
 * está definida a función de formato int feof(FILE *ptf), que ten coma argumento o punteiro a arquivo
 * e devolve un valor distinto de cero cando chega ao final do arquivo e cero noutro caso.
 */

/*
 * Hay múltiples formas de resolver este ejercicio; esta es sólo una de ellas. Simplemente hay que ceñirse
 * a lo que el ejercicio especifica. Lo demás, lo que no pide concretamente algo se puede hacer como se
 * quiera (usar una función o no, etc.).
 */

// Para empezar se importan las librerías básicas.
#include <stdio.h>
#include <stdlib.h>

// En este caso no se usará ninguna función, se hará en el main.
int main() {
    /*
     * Lo primero es declarar las variables. Se hará una variable tipo archivo para poder leer los datos,
     * y luego otras tantas. En este caso, se creará una para almacenar los datos que se leen (el array) y
     * una para contar cuantos elemtos se encuentran.
     */
    FILE *f;
    // 512 es un valor arbitrario
    int count=0, n[512];

    /*
     * Esta línea lo que hace es darle a la variable f (el archivo) la función de trabajar con el archivo
     * que contiene los datos. Se pasa el nombre del archivo con la extensión y el modo de lectura (en este
     * caso r que significa read only).
     */
    f = fopen("file.txt", "r");

    /*
     * Es importante comprobar que se ha abierto/leido correctamente el archivo. Para esto simplemente hay
     * que comprobar si la variable del archivo está definida. Si no lo está (es NULL), quiere decir que hay
     * algún error y no se puede seguir trabajando.
     */
    if (f == NULL) {
        printf("Error abriendo el archivo.\n");
        // EXIT_FAILURE = 1
        return EXIT_FAILURE;
    }

    /*
     * A continuación se lee el contenido del archivo en un bucle. Para romper el bucle hay muchas formas de
     * hacerlo, una de las cuales es con feof. Cuando se llega al final del archivo, feof (End Of File) obtendrá
     * un valor distinto de 0, rompiendo el while.
     */
    while (!feof(f)) {
        /*
         * Lo que hace fscanf es lo mismo que scanf, pero con un archivo. Hay que pasarle el archivo previamente
         * abierto, el formato/patrón/"regex" que queremos (en este caso int %d), y finalmente la variable en la que
         * queremos guardarla (la cual se pasa como puntero para poder actualizarla).
         * Es necesario usar un contador, ya que hay que saber cuantos elementos se pasan al array.
         */
        fscanf(f, "%d", &n[count]);
        count++;
    }

    /*
     * Finalmente, solo hay que hacer otro bucle para sumar los elementos de un vector. Y como sabemos el último
     * índice que contiene algún valor, solo hay que incrementarlo hasta el mismo, y sumarlo a un int que contiene
     * toda la suma.
     */
    int suma=0;
    for (int i=0; i<count; i++) {
        suma += n[i];
    }

    /*
     * Finalmente se imprime el resultado. Solo hay que tener cuidado que una divisón de int puede dar decimal (deja
     * de ser un int), por lo qe hay que convertirlo a double o float.
     */
    printf("Media = %lf\n", (double) suma/count);
    // Y hay que cerrar el archivo antes de cerrar el programa.
    fclose(f);

    return EXIT_SUCCESS;
}
