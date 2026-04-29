#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no{
    int valor;
    struct no *prox;
} No;

typedef struct fila{
    int *fila;
    int ini;
    int fim;
} Fila;

No **inicializa(int vertices)
{
    No **grafo = malloc(sizeof(No*) * vertices);

    for (int i=0; i<vertices; i++)
        grafo[i] = NULL;

    return grafo;
}

//////////////////////////////////////////////////////////

void inserir(No **grafo, int u, int v) 
{
    No *noh1 = malloc(sizeof(No));
    No *noh2 = malloc(sizeof(No));

    noh1->valor = v;
    noh1->prox = grafo[u];
    grafo[u] = noh1;

    noh2->valor = u;
    noh2->prox = grafo[v];
    grafo[v] = noh2;
}

void BFS(No **grafo);

int main()
{
    int vertices, arestas;
    scanf("%d %d", &vertices, &arestas);

    No **grafo = inicializa(vertices);

    int u, v;
    for (int i=0; i<arestas; i++)
    {
        scanf("%d %d", &u, &v);
        inserir(grafo, u, v);
    }

    char *cores = malloc(sizeof(char) * vertices);
    int *predecessor = malloc(sizeof(int) * vertices);
    

    for (int i=0; i<vertices; i++)
    {
        cores[i] = 'B';
        predecessor[i] = -1;
    }    

    return 0;
}