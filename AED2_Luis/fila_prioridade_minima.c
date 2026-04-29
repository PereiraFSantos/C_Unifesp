#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct fila {
    int *lista;
    int tamanho;
} Fila;

////////////////////////////////////////////////////////////////

int parent(int i) 
{
    if (i%2 == 1)
        return i/2;

    return (i/2)-1;
} 

void heap_increase_key(Fila *fila, int indice, int new_value)
{
    if (fila->lista[indice] < new_value)
    {
        printf("Nova chave maior q a atual, burro");
        exit(0);
    }

    fila->lista[indice] = new_value;
    int aux;
    while (indice > 0 && fila->lista[parent(indice)] > fila->lista[indice])
    {
        aux = fila->lista[parent(indice)];
        fila->lista[parent(indice)] = fila->lista[indice];
        fila->lista[indice] = aux;

        indice = parent(indice);
    }
}

void inserir(Fila *fila, int id, int n)
{
    if (fila->tamanho == n)
    {
        printf("negativo my friend");
        exit(0);
    }

    fila->tamanho++;

    int k = id;
    id = INT_MAX;
    fila->lista[fila->tamanho-1] = id;

    heap_increase_key(fila, fila->tamanho-1, k);
}

int main()
{
    int n;
    scanf("%d", &n);
    
    Fila *fila = malloc(sizeof(Fila));
    fila->lista = malloc(sizeof(int) * n);
    fila ->tamanho = 0;

    int valor;
    for (int i=0; i<n; i++)
    {
        scanf("%d", &valor);
        inserir(fila, valor, n);
    }

    for (int i=0; i<n; i++)
        printf("%d ", fila->lista[i]);

    return 0;
}