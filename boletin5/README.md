# Boletín 5

- [Ejercicio](#descrición)
- [Entrega](#entrega)

## Descrición
O obxectivo deste exercicio é implentar unha biblioteca en C para o traballo con números enteiros grandes e
implementar o algoritmo RSA bseándose en dita biblioteca.  
A representación de números enteiros nun ordenador está limitada polo número de bits da representación.
Non obstabte hai certas operacións matemáticas de interese que precisan manexar enteiros cun tamaño
maior. Nese caso é preciso recorrer a outro tipo de representacións, e definir tamén novas operacións
aritméticas para traballar con eles.  
Un enteiro grande pode representarse usando un vector de díxitos en base B, usando unha estrutura coma
a seguinte:
```c
typedef struct {
int sign;
int tam;
int *val;
} bignum;
```
onde `signo` é o signo do enteiro, e `tam` é o tamaño do vector dinámico val.

Pídese implementar as seguintes funcións para ocaso de B=10:

```
bignum str2bignum(char *str) //convierte unha cadea a bignum.
```
> Hai que decidir se o primeiro elemento do vector se corresponde coa cifra máis significativa ou coa menos
significativa, e telo en conta no resto das operacións


```
bignum add(bignum a, bignum b) //devolve a suma de dous enteiros grandes.
```
> A idea é percorrer os dous vectores sumando elemento a elemento tendo conta do acarreo:
> 1) Comezar pola posición da cifra menos significativa.  
> 2) Ir sumando o acarreo previo e as cifras elemento a elemento ata o outro extremo dos vectores, gardando
na mesma posición do vector resultante o valor suma % 10 e tomando como acarreo o valor suma/10.

```
bignum sub(bignum a,bignum b) //resta dous enteiros grandes.
```
> 1) Comezar pola posición da cifra menos significativa.  
> 2) Súmaselle ao subtraendo o acarreo previo, despois faise a resta dos elementos correspondentes ata o
outro extremo dos vectores, gardando na mesma posición do vector resultante. Se a diferenza é negativa
súmaselle 10 e ponse o acarreo a 1, senón o acarreo é cero.

```
bignum mult(bignum a,bignum b) //devolve o produto de dos enteiros grandes
```
> ![](https://i.imgur.com/5kZr6T8.png)

```
bignum remainder(bignum a,bignum n) //devolve o resto da division enteira a/n
                                    //usando o algoritmo descrito en [1].
```

```
bignum fact(bignum n) //devolve n!.
```

```
bignum div(bignum a,bignum b,bignum n) //devolve a * b módulo n.
```

En todas as operacións hai que ter en conta o signo dos enteiros, e o efecto que teñen no resultado. No
traballo con números grandes pódense empregar os algoritmos básicos aprendidos na escola, aínda que
existen outros máis eficientes. Para o caso da división o algoritmo descríbese aquí:  
[División larga](https://es.wikipedia.org/wiki/Divisi%C3%B3n_larga)

### Instruccións para entrega
1. Tedes que usar unha estrutura para representar un enteiro grande, e memoria dinámica para crear
cada vector segundo o tamaño que sexa necesario.
2. Hai que crear un arquivo .h coas definición e un arquivo .c coa implementación da biblioteca.
3. Hai que escribir un programa para probar os algoritmo da biblioteca. Podedes comprobar o seu
funcionamento con números pequenos.
4. Cada función debe especificarse debidamente coa precondición e a poscondición.
5. Noutro arquivo hai que indicar os diferentes casos de proba e as saídas que vai ofrecendo o
programa.
6. O programa debe compilar nunha máquina Linux usando o compilador gcc.

## Entrega
Para realizar este ejercicio es (muy) recomendable usar Linux debido a que es necesario
enlazar librerías, y debido a eso se debe usar `gcc`. Si se tine Windows, se puede usar una
Virtual Machine o activar el Subsistema de Linux en Windows. En Mac, se puede [instalar gcc muy
fácilmente](https://www.mkyong.com/mac/how-to-install-gcc-compiler-on-mac-os-x/).  
Para compilar el ejercicio y enlazar las librerías, se usará la siguiente estructura de archivos:

```
boletin5                   - Carpeta del proyecto
├── bin                    - Carpeta donde se generarán los archivos compilados .o
│   ├── main.o             
│   ├── rsa.o
│   └── static             - Carpeta donde se generarán los archivos de la librería estática .a
│       ├── libbignum.a
│       ├── library.o
│       ├── math.o
│       └── utils.o
├── boletin5                - Ejercicio compilado con las librerías enlazadas
└── src                     - Código fuente del ejercicio
    ├── bignum              - Carpeta con el código fuente de la librería
    │   ├── library.c
    │   ├── library.h
    │   ├── math.c
    │   ├── math.h
    │   ├── utils.c
    │   └── utils.h
    ├── main.c
    ├── rsa.c
    └── rsa.h
```

_Tener en cuenta que el ejercicio aquí se separó en main.c y rsa.c. Si solo se usa un archivo (main.c), se pueden saltar
los pasos del mismo y compilar solo main.c._
_Lo mismo ocurre con la librería, que se separó en varios archivos. Sí solo se usa uno, sólo se compila uno._

Se ha de tener en cuenta como se estructurará la librería. De tal forma que, aun sin tener el código fuente de la librería,
si se quiere usar se ha de realizar `#include "bignum/archivo.h"`.
Esto permite trabajar con librerías compiladas sin conocer el código fuente, sólo conociendo su documentación.

### Compilar
El primer paso es compilar todos los archivos que se han escrito. Para esto, se ejecutarán los siguientes comandos:

```
gcc -c src/main.c -o bin/main.o
gcc -c src/rsa.c -o bin/rsa.o

gcc -c src/bignum/library.c -o bin/static/library.o
gcc -c src/bignum/utils.c -o bin/static/utils.o
gcc -c src/bignum/math.c -o bin/static/math.o
```

Lo que se hace ahí es generar individualmente los archivos de los source files y sus cabeceras, independientemente de
los includes utilizados. Estos archivos .o no tienen ninguna librería enlazada, por lo que no se pueden ejecutar a no
ser que los archivos de los que dependen estén en las carpetas correctas.  

### Librería
Ahora hay que compilar la librería al formato .a para que se pueda enlazar a un ejecutable sin que dependa de los
archivos y su directorio.

```
ar rcs bin/static/libbignum.a bin/static/library.o bin/static/utils.o bin/static/math.o
```

El comando generará el archivo `bin/static/libbignum.a`, que viene siendo la librería que se puede enlazar a los archivos
compilados para utilizar independientemente de la carpeta.

### Enlazado
El último paso es enlazar los archivos de nuestro programa (`main.c` y `rsa.c`, compiados son `.o`) a la librería. Para
esto, se usa el comando:

```
gcc bin/main.o bin/rsa.o -Lbin/static -lbignum -o boletin5
``` 

Lo que ese comando hace es juntar el `main` y el `rsa` en un archivo único, y enlazarle la librería de forma estática.  
El parámetro `-L` especifica en que carpeta se encuentran las librerías compiladas, y el `-l` el nombre de la librería (sin
_lib_ ni extensión).  
Se genera un archivo llamado `boletin5` que ya puede ser ejecutado a través de `./boletin5` sin importar las librerías de
las que dependa, porque todas están "dentro" suya.

![](https://i.imgur.com/9atTsb5.png)
