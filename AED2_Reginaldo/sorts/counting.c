#include <stdio.h>
#include <stdlib.h>

int *counting(int *lista, int *frequencia, int maior, int num)
{
    for (int i=0; i<num; i++)
    {
        scanf("%d", &lista[i]);
        frequencia[lista[i]] += 1;
    }

    for (int i=1; i<=maior; i++)
        frequencia[i] += frequencia[i-1];

    int *saida = malloc(sizeof(int) * num);

    for (int i=num-1; i>=0; i--)
    {
        frequencia[lista[i]] -= 1;
        saida[frequencia[lista[i]]] = lista[i]; 
    }

    return saida;
}

int main()
{
    int num, maior;
    scanf("%d %d", &num, &maior);    

    int *lista = malloc(sizeof(int) * num);
    int *frequencia = calloc(maior+1, sizeof(int));    

    lista = counting(lista, frequencia, maior, num);

    for (int i=0; i<num; i++)
        printf("%d ", lista[i]);

    return 0;
}