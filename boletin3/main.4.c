/*
 * Escribir un programa que permitan realizar as seguintes operacións sobre polinomios de ata grao 5.
 * Debe definirse unha estrutura (t_polinomio) para almacenar grao e coeficientes dun polinomio e as
 * funcións cuxo prototipo se indica a continuación:
 *
 * void Crea(int grao, int coe[], t_polinomio *pol); //Crea unha estrutura a partir dos datos do grao e do valor vector de coeficientes
 * double Avaliar(t_polinomio pol, double pt); //Devolve o valor do polinomo nun punto.
 * void Mostrar(t_polinomio pol); //Imprime os coeficientes non nulos do polinomio
 * void Derivar(t_polinomio pol, t_polinomio *der); //Calcula o polinomio derivado
 *
 * Non se debe facer uso de variables globais e os resultados deben imprimirse invocando as funcións
 * correspondentes dende a función main(). Lembrar que unha función non debe ler datos nin
 * escribilos a non ser que se trate precisamente dunha función para lectura ou escritura de datos.
 */



/*
 * Este programa se podría resolver de multiples formas, pero la más "sencilla" se entiende por la que más
 * código nativo use, o lo que es lo mismo, la que menos librerías importe.
 * Esta versión del ejercicio solo necesita stdio para la entrada y salida de datos, y math.h para poder hacer
 * las potencias de forma más cómoda. Se supone que no hay restricciones.
 */
#include <stdio.h>
#include <math.h>

/*
 * Al principio se declara la estructura.
 * Que es una estructura? Es un nuevo tipo de variable que contiene otras sub-variables que tu eliges.
 * Más adelante, en Programación Orientada a Objetos, se verá como una struct es más o menos lo que un objeto.
 *
 * Para nuestra estructura, hay que declarar tanto el grado del polinomio como los coeficientes, tal como
 * pide el ejercicio. Se hace de la siguiente forma:
 * - Grado: se crea un int llamado "grado".
 * - Coeficientes: se crea un array de 6 elementos (índice máximo 5), ya que el ejercicio pide claramente
 *   que es un polinomio de máximo grado 5.
 *
 * Una forma alternativa de resolverlo es, en vez de usar el array c[5], sería usando int c0, c1, ..., c6;
 * pero a la hora de trabajar con bucles es más complejo. Trabajar con arrays para aquí será la mejor opción.
 */
typedef struct {
    int grado;
    int c[5];
} t_polinomio;

/*
 * El ejercicio no lo especifica concretamente, pero "sugiere" que se declaren las funciones delante del main, ya
 * que en el enunciado las funciones acaban con un ; y no usa corchetes. Entonces, el truco es poner las funciones
 * delante del main, y escribir la función por debajo del mail.
 */
// Esta función crea el polinomio a partir de un grado dado y los coeficientes, pasando la estructura como un puntero.
void Crea(int grao, int coe[], t_polinomio *pol);
// Esta función obtiene el valor de la Y en el polinomio previamente definido dada una X.
double Avaliar(t_polinomio pol, double pt);
// Esta función muestra el polinomio escrito antes.
void Mostrar(t_polinomio pol);
// Esta función deriva el polinomio.
void Derivar(t_polinomio pol, t_polinomio *der);


/* --- */


/*
 * Aquí empieza el programa. El ejercicio dice que solo se pueden leer datos o bien en main() o en la función
 * clara de lectura de datos, y lo mismo para escritura.
 *
 * Aquí, una vez más, el ejercicio es ambigüo, ya que no dice como se ha de realizar el programa. Bien podría ser
 * a través de un menú que pregunte al usuario que función va a ejecutar, o que se ejecute función a función.
 * Este ejemplo va función a función, ya que es lo más fácil.
 */
int main() {
    /*
     * Aquí se crea una variable p del tipo t_polinomio, de tal forma que p se convierte en una copia vacía de la
     * estructura previamente declarada.
     * Para acceder a los valores en la estructura, se usa "p->x" si es por puntero, o "p.x" si es directo.
     */
    t_polinomio p;

    printf("CREAR POLINOMIO\n");
    /*
     * Para la primera fase del programa, se ha de preguntar al usuario por el grado del polinomio (aunque no es
     * estrictamente necesario), y luego los coeficientes.
     * La variable grao contiene el grado del polinomio, y se le preguntará al usuario continuamente hasta que de
     * un valor entre 0 y 5. La mejor estructura para esto es un do-while, ya que siempre se va a ejecturar al menos
     * una vez.
     */
    int grao = 0;
    do {
        printf("Grado del Polinomio (0-5) > ");
        scanf(" %i", &grao);
    } while (grao > 5 || grao < 0);

    /*
     * Ahora hay que preguntar por los coeficientes del polinomio hasta que se llege al del grado introducido.
     * Para ello, la mejor estructura es un while, ya que aunque se va a ejecutar al menos una vez, no se ejecutará
     * cuando la condición se deje de cumplir (si se usa un do-while y se pone polinomio de grado 5, se ejecutará 7
     * veces pidiendo un polinomio de grado 6).
     * El array coe contiene los valores de los coeficientes, y el int last almacena cual fue el último término
     * preguntado, para saber cuando parar.
     */
    int coe[grao], last=0;
    while (grao >= last) {
        // Se pregunta al usuario por el coeficiente de last, y se almacena
        printf("Coeficiente para x^%i > ", last);
        scanf(" %i", &coe[last]);
        // Se incrementa el last, para saber por donde se va.
        last++;
    }

    /*
     * A continuación, se ejecuta la función Crea para que almacene los valores en la estructura p
     * grao es el grado preguntado al usuario, coe los coeficientes y p la estructura mandada como puntero.
     * La función está comentada más abajo.
     */
    Crea(grao, coe, &p);

    /* --- */

    printf("\n\nEVALUAR POLINOMIO\n");
    /*
     * Segunda parte: obtener el valor de Y para una X dada. Hasta ahora tenemos que p es un polinomio con sus
     * correspondientes coefiecientes. Pues hay que evaluarla, pero imprimiendo el resultado en main().
     * Lo primero es crear un double vacío que es el valor de x. Se pregunta al usuario por su valor, y se almacena
     * en la variable.
     */
    double x=0;
    printf("x = ");
    scanf(" %lf", &x);

    /*
     * A continuación, se crea un nuevo double al que se le asigna el valor devuelto por Avaliar, la función que
     * se encarga de obtener el valor de Y a partir de X.
     * Los parametros que recive Avaliar son el polinomio p y el punto x. Está comentada más abajo.
     */
    double res = Avaliar(p, x);
    // Se imprime el valor del double para el usuario
    printf("y = %lf", res);

    /* --- */

    printf("\n\nMOSTRAR POLINOMIO\n");
    /*
     * La tercera parte del programa es hacer un print al polinomio. El ejercicio dice que no se debe hacer printf
     * en funciones fuera del main A NO SER que sean estrictamente para eso, como este caso. Por eso, aquí se imprime
     * algo estático ("Polinomio:") y se llama a una función que no devuelve nada, pero que realmente sí que hace algo
     * que es imprimir el polinomio.
     * La única variable que acepta Mostrar es p, el polinomio. Está comentada más abajo.
     */
    printf("Polinomio: ");
    Mostrar(p);

    /* --- */

    printf("\n\nDERIVAR POLINOMIO\n");
    /*
     * La última parte consiste en derivar el polinomio. Para eso, hay que crear una nueva variable de polinomio
     * para almacenar el polinomio derivado (ya que no se puede imprimir desde la función que deriva, y ya que
     * tampoco se puede devolver ningún valor. Esta variable se llamará der.
     * La función de Derivar recive de forma directa el polinomio original, y como puntero la nueva variable, para
     * poder actualizarla en main desde la función llamada.
     */
    t_polinomio der;
    Derivar(p, &der);
    // Finalmente solo hace falta mostrar el polinomio derivado
    printf("Derivada: ");
    Mostrar(der);

    // Y lo de siempre de return 0 que es el código de SUCCESS
    return 0;
}



/*
 * La función Crea recive el grado del polinomio, y el vector de coeficientes.
 * También obtiene el puntero del polinomio para actualizar el valor de la variable sin tener que darlo en un return.
 */
void Crea(int grao, int coe[], t_polinomio *pol) {
    // Se graba en el polinomio el grado introducido.
    pol->grado = grao;

    /*
     * En este bucle for, se itera por todos los coefiecientes desde 0 hasta el del grado, de tal forma que se graba
     * en el índice correspondiente el valor pasado a la función del coeficiente al polinomio.
     */
    for (int i=0; grao>=i; i++) {
        // Realmente es hacer una copia de coe a c, con el mismo índice.
        pol->c[i] = coe[i];
    }

    // No hace falta devolver nada en un return ya que es un void.
}


/*
 * La función avaliar no es un void, por lo que tiene un return de tipo double. Acepta el polinomio de forma directa
 * ya que no lo modifica, y el punto como double. Ha de devolver el valor del polinomio en el punto introducido.
 */
double Avaliar(t_polinomio pol, double pt) {
    // Se crea la variable del sumatorio y se pone a 0
    double res=0;
    /*
     * Este bucle for será el encargado de iterar hasta que el contador llegue al grado (no interesa mirar más
     * elementos ya que su coeficiente son 0 seguro).
     */
    for (int i=0; pol.grado>=i; i++) {
        /*
         * En cada elemento, se le suma a res su propio valor mas el coeficiente por el punto elevado al exponente
         * correspondiente.
         * Es posible que pol.c[i] sea nulo, se podría hacer un if, pero realmente da igual ya que no altera el
         * resultado.
         * pol.c[i] es el coeficiente i del polinomio pol (en main se llama p).
         */
        res += pol.c[i]*pow(pt, i);
    }

    // Devuelves el resultado a main(), y se imprime desde allí
    return res;
}


/*
 * La función Mostrar solo acepta de forma directa el polinomio, que en la función se llama pol.
 */
void Mostrar(t_polinomio pol) {
    /*
     * El ejercicio pide estrictamente que no se impriman coeficientes nulos, por lo que no se debe hacer.
     * Otra cosa a tener en cuenta es cuando poner el signo "+". Muy fácil: se crea una variable int (que sea boolean
     * y se trate como true/false) que por defecto sea 0, pero cuando se imprima cualquier valor se convierta en 1; y
     * así de esta forma si la variable es verdadera se imprime el signo "+" antes de imprimir cualquier término.
     */
    // Se declara la variable que comprueba si es el primer término que se imprime.
    int sum=0;
    // El for es como el de la anterior función, no hace falta explicarlo.
    for (int i=0; pol.grado>=i; i++) {
        // Si el coefieciente para el exponente i es distinto de 0, entonces se ha de escribir
        if (pol.c[i] != 0) {
            // Pero si es el primer término no se escribirá el signo "+", sino que solo
            if (sum) printf(" + ");
            // se imprimirá esto
            printf("%d*x^%d", pol.c[i], i);
            // y se cambiará el valor de sum a 1 para que en la siguiente vuelta si que se imprima.
            sum = 1;
        }
    }

    // No se devuelve nada ya que es un return.
}

/*
 * La función de Derivar acepta dos parámetros: el polinomio original directamente ya que no se modifica, y el
 * polinomio derivado como punterp, ya que si se ha de modificar y se trata de un void que no devuelve nada.
 */
void Derivar(t_polinomio pol, t_polinomio *der) {
    /*
     * Lo primero al derivar es conocer los grados. El grado del polinomio derivado es el grado del polinomio original
     * menos 1, por lo que esto es bastante sencillo.
     * Cabe mencionar como se trabaja con las estructuras cuando son directos o punteros. Cuando es un puntero se usa
     * "->" y cuando no se usa "." para referenciar una variable en la estructura.
     */
    der->grado = pol.grado-1;

    /*
     * A continuación toca derivar. Se crea un for como los de las otras funciones, pero en contra de lo que se pueda
     * pensar, no se usa el grado del polinomio derivado, sino que se usa el del polinomio original y se empieza en
     * i=1.
     * Para derivar, se coje el exponente del polinomio original, y se multiplica al coeficiente del polinomio
     * derivado pero en el exponente anterior al original, tal que si se quiere derivar 4x^5, la derivada es
     * (4*5)x^(5-1). Esto en variables (i=exponente, c=coeficiente) es (c*i)x^(i-1).
     */
    for (int i=1; pol.grado>=i; i++) {
        /*
         * Siguiendo la regla anterior, se puede asignar los coeficientes de la siguiente forma:
         * der->c[i-1] ==> i-1 es el exponente, de tal forma que se le asigna el coficiente a ese término
         * pol.c[i] ==> i es el exponente inmediatamente superior, de tal forma que si se quiere obtener el coeficiente
         * de ese exponente, solo hay que obtener el valor de ese vector en ese índice.
         */
        der->c[i-1] = i*pol.c[i];
    }

    // No se devuelve nada ya que es un void
}
