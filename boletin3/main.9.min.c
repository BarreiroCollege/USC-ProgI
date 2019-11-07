#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define archivo "invent.dat"

typedef struct {
    int codigo;
    char nome[30];
    int prezo;
    int cantidade;
} Item;


void gravar_datos();
void leer_datos(Item datos[]);
int venta_item(int codigo, int cantidad, Item datos[]);


int ultimo() {
    FILE *f = fopen(archivo, "rb");
    if (f == NULL) {
        printf("Error abriendo el archivo!");
        exit(1);
    }
    Item temporal;
    int last = 0;

    while (fread(&temporal, sizeof(Item), 1, f)) {
        if (temporal.codigo > last) {
            last = temporal.codigo;
        }
    }
    fclose(f);
    return last;
}


int main() {
    int menu=1, u=0; 
    int v_code=0, v_amount=0; 

    while (menu != 0) {
        printf("\n1. Leer Datos\n");
        printf("2. Gravar Datos\n");
        printf("3. Venta Item\n");
        printf("0. Salir\n\n");
        printf("# ");
        scanf(" %d", &menu);

        u = ultimo();
        Item datos[u];

        printf("\n");
        switch (menu) {
            case 1:
                leer_datos(datos);
                if (u == 0) {
                    printf("No hay items");
                } else {
                    for (int i=0; i<u; i++) {
                        printf("ID: %d -> '%s' %d€ x%d\n", datos[i].codigo, datos[i].nome, datos[i].prezo, datos[i].cantidade);
                    }
                }
                break;
            case 2:
                gravar_datos();
                printf("Añadido");
                break;
            case 3:
                printf("Código (venta) > ");
                scanf(" %d", &v_code);
                printf("Cantidad (venta) > ");
                scanf(" %d", &v_amount);
                leer_datos(datos);
                if (venta_item(v_code, v_amount, datos) == 1) {
                    printf("Vendido!");
                }
            default:
                break;
        }
    }

    return 0;
}


void leer_datos(Item datos[]) {
    FILE *f = fopen(archivo, "rb");
    if (f == NULL) {
        printf("Error abriendo el archivo!");
        exit(1);
    }

    Item temporal;
    for (int i=0; fread(&temporal, sizeof(Item), 1, f); i++) {
        datos[i] = temporal;
    }
    fclose(f);
}


void gravar_datos() {
    char nombre[30];
    int precio;
    int cantidad;

    printf("Nombre (max 30) > ");
    getchar();
    scanf(" %[^\n]s", nombre);
    printf("Precio (entero) > ");
    scanf(" %d", &precio);
    printf("Cantidad (entero) > ");
    scanf(" %d", &cantidad);

    Item nuevo;
    nuevo.codigo = ultimo()+1;
    strcpy(nuevo.nome, nombre);
    nuevo.prezo = precio;
    nuevo.cantidade = cantidad;

    FILE *f = fopen(archivo, "ab");
    if (f == NULL) {
        printf("Error abriendo el archivo!");
        exit(1);
    }
    fwrite(&nuevo, sizeof(Item), 1, f);

    fclose(f);
}


int venta_item(int codigo, int cantidad, Item datos[]) {
    int c = ultimo();
    for (int i=0; i<c; i++) {
        if (datos[i].codigo == codigo) {
            if (datos[i].cantidade > cantidad) {
                datos[i].cantidade = datos[i].cantidade-cantidad;
            } else if (datos[i].cantidade == cantidad) {
                datos[i].codigo = 0;
            } else {
                printf("No hay unidades suficientes!\n");
                return 0;
            }

            FILE *f = fopen(archivo, "wb");
            if (f == NULL) {
                printf("Error abriendo el archivo!");
                exit(1);
            }

            int arreglo=0;
            for (int j=0; j<c; j++) {
                if (datos[j].codigo != 0) {
                    datos[j].codigo += arreglo;
                    fwrite(&datos[j], sizeof(Item), 1, f);
                } else {
                    arreglo -= 1;
                }
            }
            fclose(f);
            return 1;
        }
    }

    printf("El elemento no está en el inventario!\n");
    return 0;
}
