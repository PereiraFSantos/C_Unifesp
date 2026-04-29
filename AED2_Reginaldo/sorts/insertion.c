#include <stdio.h>
#include <stdlib.h>

void insertion(int *lista, int num)
{
    int aux, j;
    for (int i=1; i < num; i++)
    {
        aux = lista[i];
        j = i-1;
        while(j >= 0 && lista[j] > aux)
        {
            lista[j+1] = lista[j];
            j--;
        }

        j++;        
        lista[j] = aux;
    }
}

int main()
{
    int num;
    scanf("%d", &num);

    int *lista = malloc(sizeof(int) * num);

    for (int i=0; i<num; i++)
        scanf("%d", &lista[i]);

    insertion(lista, num);

    for (int i=0; i<num; i++)
        printf("%d ", lista[i]);

    return 0;
}