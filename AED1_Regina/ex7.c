#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char *nome;
    long int telefone;
    struct no *left;
    struct no *right;
} No;

// -------------------------------------------- //


// se retornar 0: strings iguais
//             1: str vai a direita da raiz
//            -1:           esquerda da raiz
int compara_str(char *str, No *raiz) {

    int i;
    for (i=0; (str[i] != '\0') && (raiz->nome[i] != '\0'); i++) {
        if ((str[i] - raiz->nome[i]) != 0) {
            if ((str[i] - raiz->nome[i]) > 0) 
                return 1;

            return -1;
        }
    }

    if (str[i] == '\0' && raiz->nome[i] == '\0')
        return 0;

    if (raiz->nome[i] == '\0')
        return 1;

    return -1;
}

No *busca(No *raiz, char *nome_busca) {

    switch (compara_str(nome_busca, raiz)) {
        case 0:
            return NULL;
        case -1:
            if (raiz->left)
                return busca(raiz->left, nome_busca);

            return raiz;
        case 1:
            if (raiz->right)
                return busca(raiz->right, nome_busca);

            return raiz;
    }

}

void ADD(No **raiz) {

    char str[50];
    long int number;

    scanf("%s", str);
    scanf("%ld", &number);

    if (!(*raiz)) {
        *raiz = malloc(sizeof(No));
        (*raiz)->nome = malloc(strlen(str) + 1);

        strcpy((*raiz)->nome, str);
        (*raiz)->telefone = number;
        (*raiz)->left = NULL;
        (*raiz)->right = NULL;

        printf("Contato adicionado\n");
        return;
    }

    No *ptr = busca(*raiz, str);
    
    if (!ptr) {
        printf("Contato ja existe\n");
        return;
    }

    No *aux = malloc(sizeof(No));
    aux->nome = malloc(50);

    strcpy(aux->nome, str);
    aux->telefone = number;
    aux->left = NULL;
    aux->right = NULL;

    // printf("Contato adicionado\n");

    if (compara_str(str, ptr) == 1) {
        ptr->right = aux;
        return;
    }

    ptr->left = aux;
}

void Search(No *raiz) {

    char str[50];
    scanf("%s", str);

    if (!raiz) {
        printf("Contato nao encontrado\n");
        return;
    }

    while (raiz) {
        switch (compara_str(str, raiz)) {
            case 0:
                printf("%ld\n", raiz->telefone);
                return;
            case -1:
                if (raiz->left) {
                    raiz = raiz->left;
                    continue;
                }
                    
                printf("Contato nao encontrado\n");
                return;
            case 1:
                if (raiz->right) {
                    raiz = raiz->right;
                    continue;
                }

                printf("Contato nao encontrado\n");
                return;
        }
    }

}

void list(No *raiz) {

    if (!raiz)
        return;

    list(raiz->left);
    printf("Nome: %s - Telefone: %ld\n", raiz->nome, raiz->telefone);
    list(raiz->right);
}

void libera(No *raiz) {

    if (!raiz)
        return;

    libera(raiz->left);
    libera(raiz->right);

    free(raiz->nome);
    free(raiz);
}

int main() {

    int entradas;

    do {
        scanf("%d", &entradas);
    } while (entradas > 100 || entradas < 1);

    No *raiz = NULL;

    char comando[20];
    for (int i=0; i < entradas; i++){
        scanf("%s", comando);

        if (strcmp(comando, "ADD") == 0) {
            ADD(&raiz);
            continue;
        }
        if (strcmp(comando, "SEARCH") == 0) {
            Search(raiz);
            continue;
        }
        if (strcmp(comando, "LIST") == 0) {
            list(raiz);
            continue;
        }
    }

    libera(raiz);

    return 0;
}