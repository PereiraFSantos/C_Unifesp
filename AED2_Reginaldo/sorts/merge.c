#include <stdio.h>
#include <stdlib.h>

void Merge(int *lista, int ini, int fim)
{
    int meio = (fim + ini) / 2;

    int tamanho_A = meio - ini + 1;
    int tamanho_B = fim - meio;

    int A[tamanho_A];
    int B[tamanho_B];

    for (int i=0; i<tamanho_A; i++)
        A[i] = lista[ini + i];

    for (int i=0; i<tamanho_B; i++)
        B[i] = lista[meio + 1 + i];

    int ind_A = 0, ind_B = 0;
    for (int i=ini; i <= fim; i++)
    {
        if (ind_A < tamanho_A)
        {
            if (ind_B == tamanho_B || A[ind_A] <= B[ind_B])
            {
                lista[i] = A[ind_A];
                ind_A++;
                continue;
            }

            lista[i] = B[ind_B];
            ind_B++;
            continue;
        }    

        lista[i] = B[ind_B];
        ind_B++;
    }
}


void MergeSort(int *lista, int ini, int fim)
{
    if (fim == ini)
        return;
    
    int meio = (fim + ini) / 2;

    MergeSort(lista, ini, meio);
    MergeSort(lista, meio + 1, fim);    
    Merge(lista, ini, fim);
}

int main ()
{
    int num;
    scanf("%d", &num);

    int *lista = malloc(sizeof(int) * num);
    
    for (int i=0; i<num; i++)
        scanf("%d", &lista[i]);

    MergeSort(lista, 0, num-1);

    for (int i=0; i<num; i++)
        printf("%d ", lista[i]);


    free(lista);
    return 0;
}