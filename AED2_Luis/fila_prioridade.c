#include <stdio.h>
#include <stdlib.h>

typedef struct noh {
    int id;
    int valor;
} No;

typedef struct fila {
    No *lista;
    int tamanho;
} Lista;

/////////////////////////////////////////////////////////////////

void heap_inserir(No *A, int *B, No *x, int prioridade)
{
    if (x->id > prioridade)
    {
        printf("Não é possível diminuir a prioridade do objeto.\n");
        return;
    }

    x->id = prioridade;

}

int main()
{
    int n;
    scanf("%d", &n);
    
    No *A = malloc(sizeof(No) * n);
    int *B = malloc(sizeof(int) * n);



    return 0;
}