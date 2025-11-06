#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int *A;
    int tamanho;
} Lista;

void heapify(Lista *vetor, int id) 
{
    int left = (id*2)+1;
    int right = (id*2)+2;   

    int aux, maior;

    if (left <= vetor->tamanho-1 && vetor->A[left] > vetor->A[id])
        maior = left;
    else    
        maior = id;

    if (right <= vetor->tamanho-1 && vetor->A[right] > vetor->A[maior])
        maior = right;

    if (maior != id)
    {
        aux = vetor->A[id];
        vetor->A[id] = vetor->A[maior];
        vetor->A[maior] = aux;

        heapify(vetor, maior);
    }

}

void build_max_heap(Lista *vetor)
{
    for (int i = vetor->tamanho/2; i >= 0; i--)
        heapify(vetor, i);
}

void heap_sort(Lista *vetor, int tamanho) 
{
    build_max_heap(vetor);

    int aux;
    for (int i = vetor->tamanho-1; i > 0; i--)
    {
        aux = vetor->A[0];
        vetor->A[0] = vetor->A[i];
        vetor->A[i] = aux;

        vetor->tamanho--;
        heapify(vetor, 0);
    }
}

int main() 
{
    int n;
    scanf("%d", &n);

    Lista *array = malloc(sizeof(Lista));
    array->A = malloc(sizeof(int) * n);
    array->tamanho = n;

    for (int i=0; i<n; i++)
        scanf("%d", &array->A[i]);

    heap_sort(array, n);

    for (int i=0; i<n; i++)
        printf("%d ", array->A[i]);

    return 0;
}