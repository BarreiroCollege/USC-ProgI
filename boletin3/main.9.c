/*
 * BOLETÍN 3 | EJERCICIO 9 (Enunciado)
 * -----------------------------------
 * Nun almacén precísase gardar os datos necesarios para os distintos artigos dispoñibles nun
 * ficheiro chamado invent.dat. Para cada elemento deben rexistrarse os seguintes datos:
 * codigo (enteiro)
 * nome (cadea de ata 30 caracteres)
 * prezo (número real),
 * cantidade (enteiro que indica a cantidade de unidades existente).
 *
 * Escribir unha función chamada gravar_datos que poida gardar os datos de varios artigos no
 * arquivo invent.dat. A escritura debe facerse en binario, gardando unha estrutura en cada
 * operación. O código para cada artigo será xerado secuencialmente a partir do 1 e os restantes
 * datos serán tecleados polo usuario, mentres que desexe continuar coa gravación de máis artigos.
 * Ao final, a función devolve o número de elementos inseridos.
 *
 * Escribir unha función chamada ler_datos que cargue todos os datos do arquivo de inventario nun
 * vector de estruturas, que se lle pase como argumento.
 *
 * Escribir un procedemento, co nome venta_item que reciba tres parámetros: o código dun elemento,
 * o número de unidades a seren vendidas e o vector de estruturas co inventario. Este procedemento
 * debe acceder no vector de estruturas ao artigo que se quere vender e amosar na pantalla o valor
 * total da venda. Se a cantidade de artigos existentes é menor ca cantidade esixida para a venda,
 * debe mostrar unha mensaxe indicando que non se pode realizar a venda; noutro caso debe
 * actualizar o número de unidades do artigo correspondente.
 *
 * Escribir un programa en C para probar o funcionamento das tres funcións. Antes de rematar o
 * programa debe actualizarse o arquivo invent.dat.
 */

/*
 * BOLETÍN 3 | EJERCICIO 9 (Explicación)
 * -------------------------------------
 * Este ejercicio es el más completo de todos, ya que hay que usar practicamente todo lo que ya usó en
 * ejercicios anteriores.
 * Lo primero que el ejercicio da son especificaciones: como ha de ser la estructura con la que trabajar,
 * y luego las tres funciones. Cada una de las funciones están comentadas. Finalmente se pide hacer un main()
 * que ejecute las tres funciones. De esta forma, el ejercicio pide hacer un "menú" en un bucle infinito que
 * pregunte que función ejecutar.
 * El ejercicio también dice que "antes de rematar", se ha de escribir el archivo. Pero es mucho más sencillo
 * si ya se escribe en la función de gravar datos y vender, ya que en caso de multiples procesos a la vez, se
 * trabajaría con archivos desactualizados.
 */


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


/*
 * RESUMEN CORTO: Hacer una base de datos sin ningún motor como MySQL o PostgreSQL
 * El primer paso es importar las librerías. Se usa stdio para lectura y escritura de los datos, stdlib para poder usar
 * la función exit() (comentado más abajo) y string.h para poder copiar cadenas (también comentado más abajo).
 * Además, como hay que abrir el archivo varias veces, es recomendable definir una variable global para almacenar
 * el nombre del archivo, para así en caso de cambiarse que solo haya que cambiarlo en un sitio.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define archivo "invent.dat"

/*
 * Aquí queda definida la estructura Item, que tiene 4 sub-variables: un int para el código (que se incrementa
 * automaticamente, no se pregunta al usuario para guardarlo), una cadena de longitud máxima de 30 caracteres para
 * el nombre, y otros dos int para el precio y la cantidad.
 * Definiendo la estructura como typedef nos ahorra tener que escribir "struct Item" todo el rato, y simplemente se
 * usa "Item".
 */
typedef struct {
    int codigo;
    char nome[30];
    int prezo;
    int cantidade;
} Item;


/*
 * Aquí quedan definidas las tres funciones para el ejercicio.
 * gravar_datos() no recive ningún parámetro ya que se pregunta al usuario en la propia función
 * leer_datos() recibe el array donde almacenar los datos leídos, ya que el ejercicio pide específicamente guardarlos
 * en una array
 * venta_item() es un int en vez de un void, ya que es útil mandar a main() si el elemento fue vendido o no. Recibe
 * tres parámetros: el código, la cantidad y el array de los Items disponibles
 */
void gravar_datos();
void leer_datos(Item datos[]);
int venta_item(int codigo, int cantidad, Item datos[]);


/*
 * Además, es útil declarar una función de conteo para saber cuál es el último código que hay en el archivo. La
 * función ultimo() devuelve el mayor código encontrado en la base de datos.
 */
int ultimo() {
    // El primer paso es abrir el archivo en modo lectura binario
    FILE *f = fopen(archivo, "rb");
    // Comprobar que el archivo no sea nulo; que el archivo exista
    if (f == NULL) {
        printf("Error abriendo el archivo!");
        /*
         * Si no se puede abrir el archivo, hay que detener el programa. El problema es que un return en una función
         * no detiene el programa, sino que devuelve ese valor. Entonces, se usa la función exit() con el coódigo de
         * error 1, que fuerza la detención de la ejecución.
         */
        exit(1);
    }
    // Se inicializa una variable "temporal" de Item donde almacenar el último elemento leído
    Item temporal;
    // Se inicia un int para almacenar el mayor código encontrado
    int last = 0;

    /*
     * Se hace un bucle infinito con fread(). fread() es como fscanf(), pero en vez de aceptar un "formato" lo que
     * hace es leer estructuras en el archivo. Los parámetros que acepta son:
     * . variable donde almacenar la lectura como puntero
     * . tamaño de la estructura (fijarse de mandar el nombre de la estructura y no la variable de la estructura)
     * . número de elementos (de estructuras) a leer cada vez
     * . archivo del que leer
     * El bucle se ejecuta mientras fread no sea nulo. Cuando fread sea nulo, quiere decir que ya no queda nada más
     * por leer.
     */
    while (fread(&temporal, sizeof(Item), 1, f)) {
        /*
         * Aunque tal como se hace esta solución no es posible, es recomendable usar esta condición para almacenar el
         * mayor código. Como en este ejemplo los elementos siempre van a estar ordenados, no importa incluirlo o no,
         * pero realmente es recomendable comparar si el código que estamos leyendo es mayor que el que ya teníamos
         * almacenado.
         */
        if (temporal.codigo > last) {
            // Se le pasa a la variable de devolver el código el elemento actual, que es mayor que el que ya teníamos
            last = temporal.codigo;
        }
    }
    // Cerramos el archivo
    fclose(f);
    // Devolvemos el mayor código
    return last;
}


/*
 * En la función main() solo va a haber un menú que pregunte que función quiere ejecutar, y hará printf a algunos
 * datos para algunas funciones.
 */
int main() {
    /*
     * Se inicializan las variables. Se ha de iniciar un int para el menú, para la selección; otro int para el último
     * código almacenado, y otros dos ints para el código y la cantidad de la función de venta.
     * Cada una de las variables está comentada más abajo.
     */
    int menu=1, u=0; // u = último
    int v_code=0, v_amount=0; // v_ = venta_

    /*
     * Hay que crear un bucle que ejecuté la función de preguntar el menú mientras la selección del menú no sea 0,
     * ya que el 0 es salir.
     * Como más abajo se usa un switch, el resto de valores lo que harán será volver a preguntar.
     */
    while (menu != 0) {
        // Se imprime el menú para las funciones
        printf("\n1. Leer Datos\n");
        printf("2. Gravar Datos\n");
        printf("3. Venta Item\n");
        printf("0. Salir\n\n");
        printf("# ");
        // Se espera a la entrada del usuario
        scanf(" %d", &menu);

        /*
         * A continuación, se obtiene el último código en el archivo. Además, como están ordenados, este último valor
         * es el número de elementos que hay en el archivo. De esta forma, se puede iniciar el array de Items con su
         * longitud para almacenar los datos leídos. Este array se destruye y crea en cada vuelta, ya que el número
         * de elementos puede variar en cada ejecución debido a gravar_datos() y vender_item(),
         */
        u = ultimo();
        Item datos[u];

        printf("\n");
        /*
         * Se usa un switch para llamar a las funciones en función de la selección, ya que así si la selección no es
         * ninguna pregunta de nuevo sin hacer nada, y si es 0 el while se rompe.
         */
        switch (menu) {
            // Opción 1 = leer_datos()
            case 1:
                /*
                 * Se llama a la función de leer_datos() para guardar en el array de Items los datos del archivo. Esta
                 * función está comentada más abajo.
                 */
                leer_datos(datos);
                // Si u=0 quiere decir que no hay elementos, ya que el mayor código sería 0
                if (u == 0) {
                    // Se dice que no hay inventario
                    printf("No hay items");
                } else {
                    /*
                     * Sino, se hace un bucle for que imprima cada Item en el array de Items mientras no se llege al
                     * último elemento
                     */
                    for (int i=0; i<u; i++) {
                        // Se imprime siguiendo un formato, y tener en cuenta que es una estructura (accede con puntos)
                        printf("ID: %d -> '%s' %d€ x%d\n", datos[i].codigo, datos[i].nome, datos[i].prezo, datos[i].cantidade);
                    }
                }
                break;
            // Opción 2 = gravar_datos()
            case 2:
                /*
                 * En esta opción se hace todo en la propia función, ya que el ejercicio no pone que la función tome
                 * argumentos para preguntar al usuario desde main().
                 */
                gravar_datos();
                // Se le dice al usuario que se  ha guardado su selección
                printf("Añadido");
                break;
            // Opción 3 = venta_item()
            case 3:
                /*
                 * En esta opción lo que hay que hacer es preguntar en el main() el código del producto y la cantidad
                 * a vender, para luego pasarla a la función y comprobar si realmente se ha venvido o no se pudo
                 * por cualquier motivo.
                 */
                printf("Código (venta) > ");
                scanf(" %d", &v_code);
                printf("Cantidad (venta) > ");
                scanf(" %d", &v_amount);
                /*
                 * Como la función de venta hay que pasarle un array de Items, es necesario leer primero los datos
                 * en el archivo sin imprimirlos, ya que sino datos estaría vació (se crea uno nuevo en cada vuelta
                 * del while)
                 */
                leer_datos(datos);
                /*
                 * Tal como está hecha y comentada la función de venta item más abajo, devolverá un 1 si se ha vendido
                 * el elemento, y un 0 sino (la propia función escribirá el error). Así podemos decirle al usuario si
                 * se pudo vender.
                 */
                if (venta_item(v_code, v_amount, datos) == 1) {
                    printf("Vendido!");
                }
            // Resto de opciones
            default:
                // Para el resto de números simplemente se ignoran y se vuelve a mostrar el menú
                break;
        }
    }

    return 0;
}


/*
 * La función leer_datos() lo que hace es recibir como argumento un array de Items en el que se insertarán todos los
 * Items que hay en el archivo, actualizándolo en el main()
 */
void leer_datos(Item datos[]) {
    // El primer paso es abrir el archivo en modo lectura binario
    FILE *f = fopen(archivo, "rb");
    // Comprobar que el archivo no sea nulo; que el archivo exista
    if (f == NULL) {
        printf("Error abriendo el archivo!");
        /*
         * Si no se puede abrir el archivo, hay que detener el programa. El problema es que un return en una función
         * no detiene el programa, sino que devuelve ese valor. Entonces, se usa la función exit() con el coódigo de
         * error 1, que fuerza la detención de la ejecución.
         */
        exit(1);
    }

    // Se inicia una variable temporal para almacenar los datos que fread va leyendo
    Item temporal;
    /*
     * Arriba, en la función ultimo() se usa un while para comprobar que se puede seguir leyendo. Pero aquí hace falta
     * un contador para saber en que posición del array de Items asignar el elemento.
     * Un for es un while pero con un contador, así se ahorra tener que declarar uno fuera. La condición es la misma
     * que en el while de arriba.
     */
    for (int i=0; fread(&temporal, sizeof(Item), 1, f); i++) {
        // Se copia el Item temporal al array de Items en la posición i
        datos[i] = temporal;
    }
    // Se cierra el archivo
    fclose(f);
    // No se devuelve nada ya que es un void, pero realmente la variable datos se está actualizando en la función padre
}


/*
 * La función gravar_datos() no recibe ningún argumento ni devuelve nada. Simplemente pregunta al usuario por el nombre
 * del Item, el precio y la cantidad que hay, y lo añade al archivo.
 */
void gravar_datos() {
    /*
     * Lo primero es declarar las variables donde scanf() escribirá lo que lea. Luego, el contenido de estas variables
     * se pasará a una estructura que se escribirá al archivo.
     */
    char nombre[30];
    int precio;
    int cantidad;

    // Se pregunta al usuario por todos los valores
    printf("Nombre (max 30) > ");
    /*
     * Es necesario escribir este getchar() aquí ya que sino scanf cogería todo lo que hay antes del mismo. Lo que hace
     * es forzar una entrada nueva limpia del usuario.
     */
    getchar();
    // Función RegEx explicada en el Ejercicio 8
    scanf(" %[^\n]s", nombre);
    printf("Precio (entero) > ");
    scanf(" %d", &precio);
    printf("Cantidad (entero) > ");
    scanf(" %d", &cantidad);

    /*
     * Se inicia una nueva estructura vacía a la que se le copian los valores leídos anteriormente uno a uno, para luego
     * escribir al archivo.
     */
    Item nuevo;
    /*
     * El código del artículo no se pregunta, sino que es el mayor código que hay en el archivo +1, ya que se ha de
     * incrementar automaticamente.
     */
    nuevo.codigo = ultimo()+1;
    /*
     * Un array de chars es una cadena, y en C no se puede "pasar" como se pasa un int, sino que hay que usar la función
     * strcpy para poder copiar el valor de una cadena.
     */
    strcpy(nuevo.nome, nombre);
    nuevo.prezo = precio;
    nuevo.cantidade = cantidad;

    // Abrir el archivo en modo "append" (escribir/añadir al final) binario
    FILE *f = fopen(archivo, "ab");
    // Comprobar que el archivo no sea nulo; que el archivo exista
    if (f == NULL) {
        printf("Error abriendo el archivo!");
        /*
         * Si no se puede abrir el archivo, hay que detener el programa. El problema es que un return en una función
         * no detiene el programa, sino que devuelve ese valor. Entonces, se usa la función exit() con el coódigo de
         * error 1, que fuerza la detención de la ejecución.
         */
        exit(1);
    }
    /*
     * A continuación se escribe el nuevo Item al archivo usando fwrite(). Esta función es como fread(), pero en vez
     * de leer, escribe al archivo. Los 4 argumentos que recibe son
     * . estructura como puntero
     * . tamaño de la estructura (cuidado con escribir una variable y no la estructura)
     * . número de elementos a escribir
     * . archivo
     */
    fwrite(&nuevo, sizeof(Item), 1, f);

    // Se cierra el archivo para aplicar los cambios
    fclose(f);
}


/*
 * La función venta_item() se encarga de vender un Item. Para eso, primero es necesario comprobar si el elemento
 * existe en el archivo, "buscando" por su código. Si existe, luego hay que comprobar que el número de unidades sea
 * menor o igual al de unidades a vender. Si esto se cumple, hay que actualizar la cantidad de elementos a n-v, siendo
 * n la cantidad antigua y v la cantidad a vender. Además, es necesario tener en cuenta que si la cantidad a vender
 * es igual a la cantidad disponible, el elemento se ha de eliminar del archivo porque ya no quedan unidades.
 * La función acepta tres argumentos: el código a vender, la cantidad y el array de Items disponibles.
 * La función devuelve un 1 si se ha vendido correctamente, y un 0 si no.
 */
int venta_item(int codigo, int cantidad, Item datos[]) {
    // Se inicia un int para saber cuantos elementos hay, y así cuantas veces hay que iterar
    int c = ultimo();
    for (int i=0; i<c; i++) {
        // Para cada Item en el array de Items se comprueba si el código coincide con el introducido
        if (datos[i].codigo == codigo) {
            // Si coincide, se comprueba si la cantidad disponible es mayor a la cantidad a vender
            if (datos[i].cantidade > cantidad) {
                // Si es así, se actualiza en el array la cantidad del Item una vez vendidos
                datos[i].cantidade = datos[i].cantidade-cantidad;
            // Sino, se comprueba si la cantidad disponible es igual a la cantidad a vender
            } else if (datos[i].cantidade == cantidad) {
                // Si es así, se actualiza el código a 0. Se pone 0 ya que se va a utlizar más abajo para borrarlo
                datos[i].codigo = 0;
            // Sino, quiere decir que no hay unidades suficientes
            } else {
                // Se devuelve un 0 y se imprime un mensaje
                printf("No hay unidades suficientes!\n");
                return 0;
            }

            // Abrir el archivo en modo escritura (sobreescribir) binario
            FILE *f = fopen(archivo, "wb");
            // Comprobar que el archivo no sea nulo; que el archivo exista
            if (f == NULL) {
                printf("Error abriendo el archivo!");
                /*
                 * Si no se puede abrir el archivo, hay que detener el programa. El problema es que un return en una función
                 * no detiene el programa, sino que devuelve ese valor. Entonces, se usa la función exit() con el coódigo de
                 * error 1, que fuerza la detención de la ejecución.
                 */
                exit(1);
            }

            /*
             * Si se llega hasta aquí es porque se puede vender el elemento, ya haya más unidades o las mismas. Pero
             * hay que tener en cuenta que hay que eliminar el elemento si no quedan unidades, y entonces actualizar
             * todos los códigos de los siguientes productos.
             * Para ello, se inicia una variable de correción que restará 1 a todos los códigos siguientes al elemento
             * eliminado si es que se elimina alguno.
             */
            int arreglo=0;
            // Se inicia una variable diferente a i para iterar hasta el número de elementos
            for (int j=0; j<c; j++) {
                // Si el código no es 0, es porque existen unidades, por lo que se puede esribir al archivo
                if (datos[j].codigo != 0) {
                    /*
                     * Hay que aplicarle la corrección al código. Será 0 para todos los elementos anteriores al de
                     * venta, y -1 para los siguientes si el código del de venta es 0 (que no quedan unidades)
                     */
                    datos[j].codigo += arreglo;
                    // Se escribe al archivo el Item. La función fwrite está explicada más arriba
                    fwrite(&datos[j], sizeof(Item), 1, f);
                // Sino, la correción se convierte en -1 para sumárselo al código de los elementos siguientes
                } else {
                    arreglo -= 1;
                }
            }
            // Se cierra el archivo, y se devuelve 1 ya que se pudo vender el elemento
            fclose(f);
            return 1;
        }
    }

    // Si se llega hasta aquí es porque el elemento no existe, por lo tanto se devuelve un 0 y se imprime un mensaje
    printf("El elemento no está en el inventario!\n");
    return 0;
}
