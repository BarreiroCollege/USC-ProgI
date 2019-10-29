/*
 * Escribir un programa que lea un texto almacenado nun arquivo, encriptado de acordo ca técnica
 * descrita antes, descifre tal texto e o presente descifrado por pantalla. Empregar unha función para o
 * desencriptado. Para desencriptar hai que sumarlle 128 á resta de códigos e despois cacular o
 * módulo 128.
 */

/*
 * Lo mismo: este ejercicio tiene múltiples soluciones. Esta es solo una de ellas. Se importan las librerías al
 * principio y se le dice al compilador que hay una función que ha de leer más abajo.
 */

#include <stdio.h>
#include <stdlib.h>

char desc(char last, char c);

int main() {
    /*
     * Exactamente lo mismo que en el ejercicio anterior.
     *
     * """Para las variables de inicio, debemos tener en cuenta que se trabajará con dos archivos diferentes:
     * uno de entrada de salida, por lo que se necesitan dos FILE's diferentes.
     * Además, se han de usar una serie de variables para almacenar los siguientes datos: caracter actual, caracter
     * anterior y caracter cambiado."""
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
    out = fopen("out.txt", "wb");

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
         * A continuación se desencripta en la función escrita más abajo (tiene comentarios). En la primera vuelta, lc
         * será 128, de tal forma que el caracter no cambiará.
         * nc se convierte en el caracter desencriptado
         */
        nc = desc(lc, c);
        /*
         * Ahora hay que ir escribiendo caracter a caracter el archivo nuevo. Para esto se puede usar fwrite, que
         * necesita un puntero a la variable del char, el tamaño de tal variable, "una constante", y el archivo
         * a escribir.
         */
        fwrite(&nc, sizeof(nc), 1, out);
        /*
         * Y finalmente se actualiza el último caracter al insertado justo ahora pero sin encriptar.
         */
        lc = nc;
    }

    /*
     * Y para terminar se cierran ambos archivos y se cierra la ejecución
     */
    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}


char desc(char last, char c) {
    // Primer paso: convertir de char al código ascii correspondiente, tanto del actual como del anterior.
    int ascii = (int) c;
    int l_ascii = (int) last;
    // Segundo paso: realizar la resta de ambos caracteres, aplicando la correción de 128 ya que puede dar negativo
    // Sumar y restar 128 no cambia el resultado, ya que es mod 128
    int n_ascii = (ascii - l_ascii) + 128;
    // Tercer paso: como ascii es aritmética modular, se realiza el módulo 128
    int new_ascii = n_ascii % 128;
    // Cuarto paso: convertir el código ascii a char de vuelta
    char new_char = (char) new_ascii;
    // Y finalmente se devuelve
    return new_char;
}
