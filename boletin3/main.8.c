/*
 * BOLETÍN 3 | EJERCICIO 8
 * -----------------------
 * Dados dous vectores U e V, defínese a distancia de Hamming, d(U,V), coma o número de posicións
 * nas que difiren os vectores. Por exemplo, se U = 20001 e V = 10103, d(U,V) = 3, xa que existen
 * tres posicións nas cales os vectores teñen diferente valor. Escribide unha función, denominada
 * Hamming, que reciba como parámetros dúas cadeas de caracteres e devolva un enteiro que indique
 * a distancia Hamming entre elas. Se as cadeas non teñen lonxitudes iguais a función devolverá -1.
 *
 * Empregar esa función dentro dun programa en C que pida ao usuario unha chave de paso (cadea
 * de caracteres), e que a compare coas almacenadas nun arquivo denominado chaves.dat xa
 * existente e que, despois de chamar á función Hamming, amose por pantalla unha mensaxe
 * indicando se a cadea dada polo usuario coincide ou non con algunha das almacenadas no arquivo
 * chaves.dat. Considerar que as chaves de paso do arquivo están encriptadas segundo o método
 * anterior e que por tanto fai falta desencriptalas para facer a comparación.
 */

/*
 * Lo que este ejercicio pide es basicamente comprobar una cadena escrita por el usuario contra
 * un archivo de claves encriptadas. Pero pide estrictamente que para comparar la cadena se use la
 * función Hamming, por lo que hay que trabajar con esta. Las cadenas estarán encriptadas por mod 128,
 * tal como se hizo en los ejercicios 6 y 7.
 * Antes de nada, comentar que hay dos soluciones válidas a este ejercicio: una en la que se encripta
 * la cadena escrita, y otra en la que se desencriptan las cadenas del archivo de claves. En este caso se
 * desencriptarán las cadenas en el archivo y se comparará con la escrita.
 */

/*
 * Primer paso es importar las librerías. Hará falta la clásica stdio para lectura y escritura, pero además
 * para hacer el ejercicio más sencillo la de string.h, ya que se usará la función de strlen para facilitar
 * el trabajo más adelante.
 */
#include <stdio.h>
#include <string.h>


/*
 * A continuación se declaran las cabeceras de las funciones. En este caso la función desencriptar del
 * ejercicio 7 y la función Hamming, que viene especificada en las directrices del ejercicio.
 * La función Hamming es un int que devuelve el número de caracteres que no coinciden en dos cadenas que
 * son pasadas por parámetros, pero antes comprueba si su longitud son iguales (sino devuelve -1).
 */
char desc(char last, char c);
int Hamming(char string1[], char string2[]);


/*
 * Se declara la función main(), en la que se preguntará al usuario por la contraseña, y se desencriptarán las
 * contraseñas de los archivos.
 */
int main() {
    // Esta variable es la contraseña introducida por el usuario. 128 es un valor arbitrario.
    char contra[128];
    printf("Contraseña > ");
    /*
     * Para leer una cadena de texto, se usa scanf("%s"), pero el problema de hacer esto es que para de leer
     * en el primer espacio. Para arreglar esto, se usa RegEx (Regular Expression, o Expresión Regular),
     * que lo que hace es leer en base a un filtro personalizado. En este caso, se usa %[^\n]s
     * El % indica que es lectura de una variable
     * El [] indica que se introduce una expresión regular, en la cual ^ significa "no" y \n es salto de linea,
     * o "intro".
     * La s significa que se va a guardar en una cadena de texto (vector de char).
     * De tal forma, la expresión %[^\n]s quiere decir que se lee como una cadena de texto hasta que se encuentra
     * un salto de linea, de tal forma que los espacios quedan incluidos.
     * El espacio delante de % quiere decir que evitamos coger lo que previamente está escrito
     */
    scanf(" %[^\n]s", contra);


    /*
     * A continuación hay que leer el archivo. Se usa el modo "r" de solo lectura, ya que no interesa escribir
     * nada. Aquí en la propia definición ya se le asigna el archivo al FILE *f
     * El archivo chaves.dat ha de estar en el mismo directorio que el .exe compilado.
     */
    FILE *f = fopen("chaves.dat", "r");

    // Comprobar que se abre correctamente el archivo
    if (f == NULL) {
        printf("Error abriendo el archivo.\n");
        // return 1 quiere decir "devolver error". 0 es para éxito, 1 para error.
        return 1;
    }

    /*
     * Aquí comienza la lectura de todas las contraseñas del archivo. Se declara una nueva variable char (que
     * recomendablemente debe ser del mismo tamaño que la anterior) a la que se le va a ir asignando el valor
     * que se va leyendo.
     * char archivo será la variable donde almacenemos las contraseñas del archivo
     */
    char archivo[128];
    /*
     * El loop while es lo interesante. Para la lectura de archivos, se usa fscanf, que significa "file scanf".
     * Los parámetros que acepta son: (FILE *), (char *), ...
     * Siendo (FILE *) el archivo a leer, (char *) el formato de datos a leer y (...) la variable donde escribir
     * los datos. fscanf es exactamente igual que scanf, pero que acepta el (FILE *) para que en vez de leer
     * en la consola lea en un archivo.
     * Por este motivo, se vuelve a usar la expresión regular, ya que en el archivo hay una contraseña por línea
     *
     * fscanf devuelve un int, que equivale al número de elemntos restantes que quedan por leer, y devuelve -1
     * si no queda ninguno más o llegó al final del archivo.
     * De esta forma, se puede hacer un while para que lea todos los datos mientras el valor de fscanf sea mayor
     * que 0 (ya que en este caso no interesa saber cuantos quedan por leer, solo leer hasta que no quede ninguno
     */
    while (fscanf(f, " %[^\n]s", archivo) > 0) {
        /*
         * El primer paso ahora es desencriptar las contraseñas del archivo. Para hacer esto, como en el ejercicio
         * 7 se iba caracter a caracter, pues aquí lo mismo. Hacen falta dos caracteres: el nc que es el "new char"
         * y el lc que es el "last char".
         * Fijarse que en last char se inicia en 0, ya que el primer caracter no se encripta, así se mantiene igual
         */
        char nc, lc=0;
        /*
         * "Para cada i, desde 0 hasta la longitud de la contraseña en el archivo incrementando i por uno en cada
         * vuelta..."
         */
        for (int i=0; i<strlen(archivo); i++) {
            /*
             * Se asigna a "new char" el valor del caracter en la posición i desencriptado. En la primera vuelta lc
             * vale 0, por lo que no cambia.
             * A la función se le pasa el caracter anterior desencriptado, y el caracter actual encriptado
             */
            nc = desc(lc, archivo[i]);
            // Se actualiza el caracter en la posición i al caracter equivalente desencriptado
            archivo[i] = nc;
            // A lc se le guarda el valor del caracter en la posición i para utilizarlo en la siguiente vuelta.
            lc = archivo[i];
        }
        /*
         * Finalmente hay que añadir el final de cadena a archivo desencriptado. Pero se añade en la última posición
         * con caracter, osea la longitud de archivo menos 1
         */
        archivo[strlen(archivo)-1] = '\0';

        /*
         * A continuación se aplica la función Hamming, a la que se le manda la contraseña introducida por el usuario
         * y la contraseña desencriptada del archivo.
         * Como la contraseña es correcta cuando Hamming devuelve 0, entonces solo hace falta mirar su valor
         * !Hamming(contra, archivo) es equivalente a Hamming(contra, archivo)==0, se usa el ! para hacelro más corto
         */
        if (!Hamming(contra, archivo)) {
            printf("Contraseña Correcta");
            // Y como la contraseña es correcta, no hace falta mirar ninguna más porque ya hay una que es verdadera
            return 0;
        }

        // Se repite el mismo procedimiento para todas las contraseñas en el archivo
    }

    /*
     * Si ninguna contraseña es correcta, entonces el while saldrá sin detener el programa, por lo que ninguna
     * contraseña es correcta.
     */
    printf("Contraseña Incorrecta");
    return 1;
}


/*
 * La función desencriptar es la misma que esta:
 * https://github.com/barreeeiroo/Programacion-I/blob/master/boletin3/main.7.min.c#L35
 * Lo único que está "minimizada" para que ocupe menos
 */
char desc(char last, char c) {
    return (char) (((c - last) + 128) % 128);
}


/*
 * La función Hamming acepta las dos cadenas, y devuelve un valor que significa en cuantas posiciones difieren ambas
 * cadenas, y -1 si tienen longitudes diferentes
 */
int Hamming(char string1[], char string2[]) {
    /*
     * El primer paso es comprobar la longitud de ambas cadenas, ya que si no miden lo mismo no hace falta comprobar
     * el resto
     * Se usa la función strlen de string.h
     */
    int len1 = strlen(string1);
    int len2 = strlen(string2);
    if (len1 != len2) {
        // Se devuelve -1, de tal forma que el resto de la función no se ejecuta
        return -1;
    }

    /*
     * Si se llega hasta aquí, es porque ambas cadenas tienen la misma longitud. Entonces, hace falta inciiar un
     * contador para mirar el número de caracteres que no coinciden.
     * La mejor forma de hacerlo es con un for ya que así ya se tiene el contador de la posición del caracter,
     * sin tener que iniciar otro fuera del mismo.
     */
    int c = 0;
    for (int i=0; i<len1; i++) {
        // Si los caracteres no coinciden, se incrementa c que es el contador de diferencias
        if (string1[i] != string2[i]) c++;
    }
    // Y se devuelve c, que vale 0 si son iguales
    return c;
}
