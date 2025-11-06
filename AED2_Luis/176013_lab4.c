#include <stdio.h>
#include <stdlib.h>

typedef struct ponto {
    int X;
    int Y;
} Ponto;

//////////////////////////////////////////////////////////////

void insertion_sort(Ponto *point, int tamanho) {

    int j;
    Ponto chave;
    for (int i=1; i < tamanho; i++) {

        chave = point[i];
        j = i-1;

        while (j >= 0 && point[j].X > chave.X) {
            point[j+1] = point[j];
            j--;
        }

        point[j+1] = chave;
    }

}

int partition(Ponto *point, int inicio, int fim) {

    int pivo = point[fim].X;

    int i = inicio - 1;
    Ponto aux;
    for (int j = inicio; j < fim; j++) {

        if (point[j].X <= pivo) {
            i++;
            aux = point[j];
            point[j] = point[i];
            point[i] = aux;
        }
    }

    i++;
    aux = point[fim];
    point[fim] = point[i];
    point[i] = aux;

    return i;
}

void quick_sort(Ponto *point, int inicio, int fim, int limiar) {

    if (inicio < fim) {

        if ((fim - inicio)+1 < limiar) {
            insertion_sort(&point[inicio], (fim - inicio)+1);
            return;
        }

        int pivo = partition(point, inicio, fim);
        quick_sort(point, inicio, pivo-1, limiar);
        quick_sort(point, pivo+1, fim, limiar);
    
    }

}

int main() {

    int limiar, n;
    scanf("%d %d", &limiar, &n);

    // if (limiar == 5)
    //     exit(1);

    Ponto *point = malloc(sizeof(Ponto) * n);

    for (int i = 0; i < n; i++)
        scanf("%d", &point[i].X);

    for (int i = 0; i < n; i++)
        scanf("%d", &point[i].Y);


    quick_sort(point, 0, n-1, limiar);

    for (int i=0; i < n; i++)
        printf("(%d,%d) ", point[i].X, point[i].Y);

    free(point);

    return 0;
}