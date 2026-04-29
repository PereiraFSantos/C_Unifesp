#include <stdio.h>
#include <stdlib.h>

int parent(int id)
{
    if (id == 0)
        return 0;

    if (id%2 == 1)
        return id/2;
    return (id/2)-1;
}

int son(int id, int num) { return (id*2)+1; }

//------------------------------------------------------------------------//

void heapify(int *lista, int num, int id)
{
    int esq, dir;
    esq = son(id, num);
    dir = son(id, num) + 1;

    int maior = id, aux;

    if (esq < num && lista[maior] < lista[esq])
        maior = esq;

    if (dir < num && lista[maior] < lista[dir])
        maior = dir;

    if (maior != id)
    {
        aux = lista[id];
        lista[id] = lista[maior];
        lista[maior] = aux;

        heapify(lista, num, maior);
    }
}

void build_max_heapify(int *lista, int num)
{
    for (int i=(num/2); i>=0; i--)
        heapify(lista, num, i);
} 
                       
void heapsort(int *lista, int num)
{
    build_max_heapify(lista, num);

    int aux;
    for (int i=1; i < num; i++)
    {
        aux = lista[0];
        lista[0] = lista[num-i];
        lista[num-i] = aux;

        heapify(lista, num-i, 0);
    }
}

int main()
{
    int num;
    scanf("%d", &num);

    int *lista = malloc(sizeof(int) * num);

    for (int i=0; i<num; i++)
        scanf("%d", &lista[i]);

    heapsort(lista, num);

    for (int i=0; i<num; i++)
        printf("%d ", lista[i]);

    return 0;
}