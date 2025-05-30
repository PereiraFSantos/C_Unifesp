#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int codigo;
    char *descricao;
    struct no *prox;
    struct no *ant;
}No;

No *encontra_no(No *lista, int id);
void liberar(No *lista);

// ---------------------------------------------------- //
// funções de comando:

No *add(No *lista, int id, char *str) {

    No *ptr = encontra_no(lista, id);

    if (ptr) {
        printf("Codigo ja existente!\n");
        return lista;
    }
    
    ptr = malloc(sizeof(No));
    ptr->codigo = id;
    ptr->descricao = str;

    if (!lista) {
        lista = ptr;
        lista->ant = lista;
        lista->prox = lista;
        
        return lista;
    }

    ptr->ant = lista->ant;
    ptr->prox = lista;
    lista->ant->prox = ptr;
    lista->ant = ptr;
    
    return lista;
}

No *remover(No *lista, int id) {

    No *ptr = encontra_no(lista, id);

    if (!ptr) {
        printf("Codigo nao encontrado!\n");
        return lista;
    }
    
    ptr->ant->prox = ptr->prox;
    ptr->prox->ant = ptr->ant;

    if (ptr == lista) {
        if (lista->prox == lista) {
            free(lista);
            return NULL;
        }

        lista = lista->prox;
    }

    free(ptr);
    return lista;
}

void printar(No *lista, int type) {
    
    if (!lista) {
        printf("Lista vazia!\n");
        return;
    }

    No *ptr = lista;

    if (type == 1) {
        ptr = ptr->ant;
        do {
            printf("Codigo: %d - %s", ptr->codigo, ptr->descricao);
            ptr = ptr->ant;
        } while (ptr != lista->ant);

        return;
    }

    do {
        printf("Codigo: %d - %s", ptr->codigo, ptr->descricao);
        ptr = ptr->prox;
    } while (ptr != lista);

}

void search(No *lista, int id) {

    No *ptr = encontra_no(lista, id);

    if (!ptr) {
        printf("Codigo nao encontrado!\n");
        return;
    }

    printf("Codigo: %d - %s", ptr->codigo, ptr->descricao);
}

// ---------------------------------------------------- //

// retorna o endereço do nó que eu busco, caso o nó
// nao exista, retorna NULL
No *encontra_no(No *lista, int id) {

    if (!lista) 
        return NULL;

    if (lista->codigo == id)
        return lista;

    No *ptr = lista;

    do {
        ptr = ptr->prox;
    } while ((ptr != lista) && (ptr->codigo != id));

    if (lista == ptr)
        return NULL;

    return ptr;
}

void flush_buffer(No *lista) {
    char a;
    do {
        a = getchar();
    } while ((a == ' ') || (a == '\n'));

    if (a == EOF) {
        printf("N superior ao numero de comandos!\n");
        liberar(lista);
        exit(0);
    }

    ungetc(a, stdin);
}

void liberar(No *lista) {

    if (!lista)
        return;

    No *ptr = lista->prox;
    No *aux = lista->prox;

    if (lista == lista->prox) {
        free(lista->descricao);
        free(lista);
        return;
    }

    do {
        aux = aux->prox;
        free(ptr->descricao);
        free(ptr);
        ptr = aux;
    } while (aux != lista);

    free(lista);
}

void inputs(int entradas) {

    char comando[14], *str;
    int id;
    No *lista = NULL;

    for (int i=0; i < entradas; i++) {
        
        flush_buffer(lista);
        scanf("%s", comando);

        if (strcmp(comando, "ADD") == 0) {

            scanf("%d", &id);
            getchar();

            str = malloc(sizeof(char) * 51);
            fgets(str, 51, stdin);

            lista = add(lista, id, str);

            continue;
        }
            
        if (strcmp(comando, "REMOVE") == 0) {

            scanf("%d", &id);
            lista = remover(lista, id);

            continue;
        }

        if (strcmp(comando, "PRINT_FORWARD") == 0) {

            printar(lista, 0);

            continue;
        }

        if (strcmp(comando, "PRINT_REVERSE") == 0) {

            printar(lista, 1);

            continue;
        }

        if (strcmp(comando, "SEARCH") == 0) {

            scanf("%d", &id);
            search(lista, id);

            continue;
        }
    }

    free(lista);
}

int main() {

    int n;
    scanf("%d", &n);

    if ((n < 1) || (n > 100)) {
        printf("N nao e valido!\n");
        return 0;
    }

    inputs(n);

    return 0;
}