#include <stdio.h>
#include <stdlib.h>

int *Counting_Sort(int *lista, int tamanho, int k)
{
    int *lista_final = malloc(sizeof(int) * tamanho),
        *frequencia = calloc(k+1, sizeof(int));

    for (int i=0; i<tamanho; i++)
        frequencia[lista[i]]++;

    for (int i=1; i<=k; i++)
        frequencia[i] += frequencia[i-1];

    for (int i=tamanho-1; i >= 0; i--)
    {
        lista_final[frequencia[lista[i]] - 1] = lista[i];
        frequencia[lista[i]]--;
    }

    free(lista);
    free(frequencia);
    return lista_final;
}

int main()
{
    int tamanho, k;
    scanf("%d %d", &tamanho, &k);

    int *lista = malloc(sizeof(int) * tamanho);

    for (int i=0; i<tamanho; i++)
        scanf("%d", &lista[i]);

    lista = Counting_Sort(lista, tamanho, k);

    for (int i=0; i<tamanho; i++)
        printf("%d ", lista[i]);

    return 0;
}