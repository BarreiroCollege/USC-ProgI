#include <stdio.h>
#include <math.h>

typedef struct {
    int grado;
    int c[5];
} t_polinomio;

void Crea(int grao, int coe[], t_polinomio *pol);
double Avaliar(t_polinomio pol, double pt);
void Mostrar(t_polinomio pol);
void Derivar(t_polinomio pol, t_polinomio *der);




int main() {
    t_polinomio p;

    printf("CREAR POLINOMIO\n");
    int grao = 0;
    do {
        printf("Grado del Polinomio (0-5) > ");
        scanf(" %i", &grao);
    } while (grao > 5 || grao < 0);

    int coe[grao], last=0;
    while (grao >= last) {
        printf("Coeficiente para x^%i > ", last);
        scanf(" %i", &coe[last]);
        last++;
    }

    Crea(grao, coe, &p);


    printf("\n\nEVALUAR POLINOMIO\n");
    double x=0;
    printf("x = ");
    scanf(" %lf", &x);

    double res = Avaliar(p, x);
    printf("y = %lf", res);


    printf("\n\nMOSTRAR POLINOMIO\n");
    printf("Polinomio: ");
    Mostrar(p);


    printf("\n\nDERIVAR POLINOMIO\n");
    t_polinomio der;
    Derivar(p, &der);
    printf("Derivada: ");
    Mostrar(der);

    return 0;
}



void Crea(int grao, int coe[], t_polinomio *pol) {
    pol->grado = grao;

    for (int i=0; grao>=i; i++) {
        pol->c[i] = coe[i];
    }

}


double Avaliar(t_polinomio pol, double pt) {
    double res=0;
    for (int i=0; pol.grado>=i; i++) {
        res += pol.c[i]*pow(pt, i);
    }

    return res;
}


void Mostrar(t_polinomio pol) {
    int sum=0;
    for (int i=0; pol.grado>=i; i++) {
        if (pol.c[i] != 0) {
            if (sum) printf(" + ");
            printf("%d*x^%d", pol.c[i], i);
            sum = 1;
        }
    }

}

void Derivar(t_polinomio pol, t_polinomio *der) {
    der->grado = pol.grado-1;

    for (int i=1; pol.grado>=i; i++) {
        der->c[i-1] = i*pol.c[i];
    }

}
