#include <stdio.h>
#include <stdlib.h>

int partition(int *lista, int ini, int fim)
{
    int pivo = lista[fim];

    int i = ini-1, aux;
    for (int j=ini; j <= fim-1; j++)
    {
        if (lista[j] <= pivo)
        {
            i++;
            aux = lista[j];
            lista[j] = lista[i];
            lista[i] = aux;
        }
    }

    i++;
    aux = lista[fim];
    lista[fim] = lista[i];
    lista[i] = aux;

    return i;
}

void quicksort(int *lista, int ini, int fim)
{
    if (ini < fim)
    {    
        int p = partition(lista, ini, fim);
        quicksort(lista, ini, p-1);
        quicksort(lista, p+1, fim);
    }        
}

int main()
{
    int num;
    scanf("%d", &num);

    int *lista = malloc(sizeof(int) * num);
    for (int i=0; i<num; i++)
        scanf("%d", &lista[i]);

    quicksort(lista, 0, num-1);

    for (int i=0; i<num; i++)
        printf("%d ", lista[i]);

    return 0;
}