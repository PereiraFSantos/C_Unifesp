#include <stdio.h>
#include <stdlib.h>

typedef struct vetor {
    int *lista_ordenada;
    int indice_final;
    int indice_inicial;
    int tamanho;
} Vetor;

Vetor *inicializa(int tamanho) {

    Vetor *ptr = malloc(sizeof(Vetor));
    ptr->indice_final = tamanho - 1;
    ptr->indice_inicial = 0;
    ptr->tamanho = tamanho;
    ptr->lista_ordenada = calloc(tamanho, sizeof(int));
    
    return ptr;
}

void liberar(Vetor *lista) {
    free(lista->lista_ordenada);
    free(lista);
}

// --------------------------------------------------------- //

void busca_binaria(Vetor *lista, int x) {

    int id = (lista->indice_final + lista->indice_inicial) / 2;

    if (x > lista->lista_ordenada[id]) {
        if (x < lista->lista_ordenada[id+1]) {
            printf("%d %d", lista->lista_ordenada[id], lista->lista_ordenada[id+1]);
            return;
        }

        lista->indice_inicial = id + 1;
        return busca_binaria(lista, x);
    } else {
        if (x > lista->lista_ordenada[id-1]) {
            printf("%d %d", lista->lista_ordenada[id-1], lista->lista_ordenada[id]);
            return;
        }

        lista->indice_final = id - 1;
        return busca_binaria(lista, x);
    }        

}

int main() {
    int x, tamanho;
    scanf("%d %d", &x, &tamanho);

    Vetor *lista = inicializa(tamanho);

    for (int i=0; i < tamanho; i++) 
        scanf("%d", &lista->lista_ordenada[i]);

    if (x > lista->lista_ordenada[tamanho-1] || x < lista->lista_ordenada[0]) {
        printf("nao ha intervalo valido");
        liberar(lista);
        return 0;
    }

    busca_binaria(lista, x);
    liberar(lista);

    return 0;
}