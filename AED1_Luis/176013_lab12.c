#include <stdio.h>
#include <stdlib.h>

typedef struct grafo{
    int n_vert;
    int **matriz;
}Grafo;

typedef struct no{
    int rotulo;
    int arestas_incidentes;
}No;

// ------------------------------------------------- //

Grafo *inicializa(int num_vertices){
    Grafo *graph = malloc(sizeof(Grafo));
    graph->matriz = malloc(sizeof(int *) * num_vertices);
    graph->n_vert = num_vertices;
    // *graph = {0};

    for(int i=0; i<num_vertices; i++){
        graph->matriz[i] = malloc(sizeof(int) * num_vertices);
        for(int n=0; n<num_vertices; n++)
            graph->matriz[i][n] = 0;
    }    

    return graph;
}

void inserir(Grafo *graph, int vertice1, int vertice2){
    if(graph->matriz[vertice1][vertice2] == 0){
        graph->matriz[vertice1][vertice2] = 1;
        graph->matriz[vertice2][vertice1] = 1;
    }
}

// int acesso(int *visitados, int vertice){
//     if(visitados[vertice] == 1)
//         return 0;

//     return 1;
// }

int busca(Grafo *graph, int vert1, int vert2, int *visitados){
    if(graph->matriz[vert1][vert2] == 1)
        return 1;

    visitados[vert1] = 1;

    for(int i=0; i<graph->n_vert; i++){
        if(graph->matriz[vert1][i] == 0)
            continue;
        if(visitados[i] == 1)
            continue;
     
        if(busca(graph, i, vert2, visitados))
            return 1;
    }
    return 0;
}

int grau_minimo(Grafo *graph){
    No noh;
    noh.arestas_incidentes = graph->n_vert + 1;
    noh.rotulo = 0;
    int aux;

    for(int i=0; i<graph->n_vert; i++){
        aux = 0;

        for(int n=0; n<graph->n_vert; n++)
            if(graph->matriz[i][n] == 1)
                aux++;

        if(noh.arestas_incidentes > aux){
            noh.arestas_incidentes = aux;
            noh.rotulo = i;
        }
    }
    
    return noh.rotulo;
}

int grau_maximo(Grafo *graph){
    No noh;
    noh.arestas_incidentes = -1;
    noh.rotulo = 0;
    int aux;

    for(int i=0; i<graph->n_vert; i++){
        aux = 0;

        for(int n=0; n<graph->n_vert; n++)
            if(graph->matriz[i][n] == 1)
                aux++;
                
        if(noh.arestas_incidentes < aux){
            noh.arestas_incidentes = aux;
            noh.rotulo = i;
        }
    }

    return noh.rotulo;
}

int main(){

    int num_vertice, num_aresta, arg1, arg2;
    scanf("%d %d", &num_vertice, &num_aresta);
    Grafo *graph = inicializa(num_vertice);
    int *visitados = calloc(num_vertice, sizeof(int));
    
    for(int i=0; i<num_aresta; i++){
        scanf("%d %d", &arg1, &arg2);
        inserir(graph, arg1, arg2);
    }

    scanf("%d %d", &arg1, &arg2);
    int caminho = busca(graph, arg1, arg2, visitados);
    arg1 = grau_minimo(graph); 
    arg2 = grau_maximo(graph);

    printf("%d %d %d", caminho, arg1, arg2);

    return 0;
}