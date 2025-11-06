#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

int main()
{
    int tamanho;
    scanf("%d", &tamanho);

    No **lista = malloc(sizeof(No *) * 10);
    for (int i=0; i<10; i++)
        lista[i] = NULL;

    

    return 0;
}