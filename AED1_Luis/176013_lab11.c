#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int vertice;
    int verificacao;
    struct no *prox;
}No;

typedef struct grafo{
    int n_vert;
    No **adj;
}Grafo;

// ------------------------------------------------------------------------- //

Grafo *cria_grafo(int vertices){
    Grafo *graph = malloc(sizeof(Grafo));
    graph->adj = malloc(sizeof(No *) * vertices);
    graph->n_vert = vertices;

    for(int i=0; i<vertices; i++){
        graph->adj[i] = malloc(sizeof(No));
        graph->adj[i]->vertice = i;
        graph->adj[i]->verificacao = 0;
        graph->adj[i]->prox = NULL;
    }
    
    return graph;
}

void insere(Grafo *graph, int no1, int no2){
    No *indice = graph->adj[no1];
    No *ptr = malloc(sizeof(No));
    ptr->vertice = no2;
    ptr->verificacao = 0;

    if(!indice->prox){
        indice->prox = ptr;
        ptr->prox = NULL;
        return;
    }

    ptr->prox = indice->prox;
    indice->prox = ptr;
}

int busca(Grafo *graph, No *no1, int no2){
    if(no1->vertice == no2)
        return 1;

    if(no1->verificacao == 1)
        return 0;

    no1->verificacao = 1;
    int ind = 0;
    while(no1){
        no1 = no1->prox;
        if(!no1)
            break;

        ind += busca(graph, graph->adj[no1->vertice], no2);
    }

    return ind;
}

void libera_no(No *noh){
    if(!noh)
        return;

    libera_no(noh->prox);
    free(noh);
}

void libera(Grafo *graph){
    for(int i=0; i<graph->n_vert; i++)
        libera_no(graph->adj[i]);

    free(graph->adj);
    free(graph);
}

int main(){

    // ordem: vertice e aresta
    int vert, aresta, no1, no2;
    scanf("%d %d", &vert, &aresta);
    
    Grafo *graph = cria_grafo(vert);
    for(int i=0; i<aresta; i++){
        scanf("%d %d", &no1, &no2);
        insere(graph, no1, no2);
        insere(graph, no2, no1);
    }

    scanf("%d %d", &no1, &no2);
    int ind = busca(graph, graph->adj[no1], no2);

    if(ind){
        printf("1");
        return 0;
    }
    printf("0");

    libera(graph);
    return 0;
}