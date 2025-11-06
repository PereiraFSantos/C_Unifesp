#include <stdio.h>
#include <stdlib.h>

typedef struct noh {
    int valor;
    struct noh *prox;
} No;

//////////////////////////////////////////////////////////////

void liberar(No *inicio) {
    if (!inicio)
        return;

    liberar(inicio->prox);
    free(inicio);
}

void printar(No *lista) {

    while (lista) {
        printf("%d ", lista->valor);
        lista = lista->prox;
    }

}

No *meio_lista(No *inicio) {

    No *ptr = inicio;

    if (!inicio)
        return NULL;

    for (inicio; ptr; inicio = inicio->prox) {
        ptr = ptr->prox;
        if (!ptr)
            break;
        ptr = ptr->prox;
        if (!ptr)
            break;
    }

    return inicio;
}

No *merge(No *left, No *right) {

    if (!right)
        return left;

    No *inicio, *ptr;
    // *ptr_left, ptr_right

    if (left->valor < right->valor) {
        inicio = ptr = left;
        left = left->prox;
    }
    else {
        inicio = ptr = right;
        right = right->prox;
    }

    while (right && left) {
        
        if (left->valor < right->valor) {
            ptr->prox = left;
            left = left->prox;
        }
        else {
            ptr->prox = right;
            right = right->prox;
        }

        ptr = ptr->prox;
    }

    if (left) 
        ptr->prox = left;
    else 
        ptr->prox = right;
    

    return inicio;

}

No *merge_sort(No *inicio, No *meio) {

    if (inicio == meio)
        return inicio;

    meio = meio_lista(inicio);
    No *ptr = meio->prox;
    meio->prox = NULL;

    inicio = merge_sort(inicio, meio);
    ptr = merge_sort(ptr, NULL);

    return merge(inicio, ptr);
}

void inserir(No **lista, int x) {

    No *ptr = malloc(sizeof(No));
    ptr->valor = x;
    ptr->prox = NULL;

    if (!(*lista)) {
        *lista = ptr;
        return;
    }

    No *aux = *lista;
    for (aux; aux->prox; aux = aux->prox);
    aux->prox = ptr;

}

int main() {

    int n, x;
    scanf("%d", &n);
    No *lista = NULL;

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        inserir(&lista, x);
    }

    lista = merge_sort(lista, NULL);
    printar(lista);
    liberar(lista);

    return 0;
}