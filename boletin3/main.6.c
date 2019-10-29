/*
 * Escribir un programa que lea un arquivo de texto e que garde noutro arquivo ese texto encriptado
 * da seguinte forma: o primeiro carácter imprímeo tal como foi lido, nos demais casos, cada carácter é
 * substituído polo carácter na posición da táboa ASCII que corresponde ao módulo 128 da suma do
 * código ASCII do carácter actual máis o do carácter lido previamente. Exemplo: Se tivésemos no
 * arquivo orixe:
 * 35 Abacates
 * entón debe aparecer no arquivo de saída:
 * 3hUa#CDDUYX
 * Empregar unha función para o encriptado
 */

/*
 * Una vez más, el ejercicio tiene múltiples soluciones. Este caso solo es una de las muchas posibles.
 * Lo primero es importar las librerías, y declarar que vamos a usar una función (esto se puede saltar
 * si se escribe la función delante del main().
 */
#include <stdio.h>
#include <stdlib.h>

char encr(char last, char c);


int main() {
    /*
     * Para las variables de inicio, debemos tener en cuenta que se trabajará con dos archivos diferentes:
     * uno de entrada de salida, por lo que se necesitan dos FILE's diferentes.
     * Además, se han de usar una serie de variables para almacenar los siguientes datos: caracter actual, caracter
     * anterior y caracter cambiado.
     */
    FILE *in;
    FILE *out;
    char c, nc, lc=0;
    /*
     * c = current char
     * nc = new char
     * lc = last char
     */

    /*
     * Se abren ambos archivos en su modo correspondiente: el de lectura en read only, y el de escritura en write
     */
    in = fopen("in.txt", "r");
    out = fopen("out.txt", "w");

    /*
     * Y se comprueba como en el ejercicio anterior que ambos archivos existan.
     * Cabe destacar aquí que out nunca va a ser NULL, ya que el programa creará el archivo si existe.
     */
    if (in == NULL || out == NULL) {
        printf("Error abriendo el archivo.\n");
        return EXIT_FAILURE;
    }

    /*
     * El bucle aquí es el mismo que en el ejercicio anterior. Se rompe cuando se llega al final del archivo, pero se
     * rompe manualmente con un break dentro del mismo.
     * Esto es lo que se denomina "bucle infinito" si no tuviese ningún break dentro.
     */
    while (1) {
        /*
         * La función fscanf es la misma que en el ejercicio anterior, con la diferencia de que aquí buscará por
         * caracteres en vez de por int. Se guarda lo que encuentra en la variable c.
         */
        fscanf(in, "%c", &c);
        /*
         * Cuando se llega al final del archivo el while se ha de romper. Esto ocurre cuando feof deja de valer 0
         * por lo que solo hay que ejecutar el comando break.
         */
        if (feof(in)!=0) break;
        /*
         * A continuación se encripta en la función escrita más abajo (tiene comentarios). En la primera vuelta, lc
         * será 0, de tal forma que el caracter no cambiará.
         * nc se convierte en el caracter encriptado
         */
        nc = encr(lc, c);
        /*
         * Ahora hay que ir escribiendo caracter a caracter el archivo nuevo. Para esto se puede usar fwrite, que
         * necesita un puntero a la variable del char, el tamaño de tal variable, "una constante", y el archivo
         * a escribir.
         */
        fwrite(&nc, sizeof(nc), 1, out);
        /*
         * Y finalmente se actualiza el último caracter al insertado justo ahora pero sin encriptar.
         */
        lc = c;
    }

    /*
     * Y para terminar se cierran ambos archivos y se devuelve el código de error de éxito = 0
     */
    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}


/*
 * En esta función se va a hacer la función de encriptado. Como se depende del caracter anterior, va a recibir
 * dos parámetros: el anterior y el actual/current. Devolverá el nuevo caracter cambiado.
 */
char encr(char last, char c) {
    // Primer paso: convertir de char al código ascii correspondiente, tanto del actual como del anterior.
    int ascii = (int) c;
    int l_ascii = (int) last;
    // Segundo paso: realizar la suma de ambos caracteres
    int n_ascii = ascii + l_ascii;
    // Tercer paso: como ascii es aritmética modular, se realiza el módulo 128
    int new_ascii = n_ascii % 128;
    // Cuarto paso: convertir el código ascii a char de vuelta
    char new_char = (char) new_ascii;
    // Y finalmente se devuelve
    return new_char;

    /*
     * Lo anterior se puede poner en una línea de código:
     * return (char) ((((int) c)+last) % 128);
     */
}
