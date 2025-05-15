#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 11

typedef struct no {
    char info[TAM];
    struct no *irmao;
    struct no *filho;
} no;

no *inicializa(char info[TAM]) {
    no *noh = malloc(sizeof(no));
    noh->irmao = NULL;
    noh->filho = NULL;
    strcpy(noh->info, info);
    return noh;
}

void excluir(no *noh) {
    if (!noh) 
        return;

    excluir(noh->irmao);
    excluir(noh->filho);
    free(noh);
}

no *busca(no *noh, char pasta[TAM]) {
    while (noh) {
        if (strcmp(noh->info, pasta) == 0) 
            return noh;

        no *ptr = busca(noh->filho, pasta);

        if (ptr) 
            return ptr;
        noh = noh->irmao;
    }
    return NULL;
}

no *buscaProx(no *noh, char pasta[TAM]) {
    if (!noh) 
        return NULL;

    while (noh) {
        if (noh->filho && strcmp(noh->filho->info, pasta) == 0) 
            return noh;
        if (noh->irmao && strcmp(noh->irmao->info, pasta) == 0) 
            return noh;

        no *ptr = buscaProx(noh->irmao, pasta);

        if (ptr) return ptr;
        noh = noh->filho;
    }
    return NULL;
}

void inserir(no *root, char arquivo1[TAM], char pasta[TAM]) {
    no *noh = inicializa(arquivo1);
    no *local = busca(root, pasta);
    if (!local) return;
    if (!local->filho) {
        local->filho = noh;
    } else {
        no *temp = local->filho;
        while (temp->irmao) temp = temp->irmao;
        temp->irmao = noh;
    }
}

void mover(no *root, char arquivo[TAM], char pasta[TAM]) {
    no *arqv = buscaProx(root, arquivo);
    no *pst = busca(root, pasta);

    if (!arqv || !pst) return;
        no *ptr;
    if (arqv->irmao && strcmp(arqv->irmao->info, arquivo) == 0) {
        ptr = arqv->irmao;
        arqv->irmao = ptr->irmao;
    }else{
        ptr = arqv->filho;
        arqv->filho = ptr->irmao;
    }
    ptr->irmao = NULL;
    inserir(pst, ptr->info, pst->info);
    free(ptr);
}

void remover(no *root, char arquivo[TAM]) {
    no *arqv = buscaProx(root, arquivo);
    if (!arqv) return;
        no *ptr;

    if (arqv->irmao && strcmp(arqv->irmao->info, arquivo) == 0) {
        ptr = arqv->irmao;
        arqv->irmao = ptr->irmao;
    } else {
        ptr = arqv->filho;
        arqv->filho = ptr->irmao;
    }
    excluir(ptr);
}

int main() {
    no *root = inicializa("root");
    int num;
    scanf("%d", &num);
    getchar();

    for (int i = 0; i < num; i++) {
        char operacao[3], arg1[TAM], arg2[TAM];
        scanf("%s", operacao);
        if (strcmp(operacao, "-i") == 0) {
            scanf("%s %s", arg1, arg2);
            inserir(root, arg1, arg2);
        } else if (strcmp(operacao, "-m") == 0) {
            scanf("%s %s", arg1, arg2);
            mover(root, arg1, arg2);
        } else {
            scanf("%s", arg1);
            remover(root, arg1);
        }
    }
    char arg1[TAM];
    scanf("%s", arg1);
    if (!busca(root, arg1)) {
        printf("Arquivo nao encontrado\n");
        return 0;
    }
    printf("root");
    return 0;
}
