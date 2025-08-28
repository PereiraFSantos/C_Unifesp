#include <stdio.h>
#include <stdlib.h>

typedef struct noh {
    char simbolo;
    struct noh *left;
    struct noh *right;
} Noh;

// ------------------------------------------------------ //

// void inserir_arvore(Noh *raiz, Noh *ptr) {

//     if (!raiz)
//         return;
    
//     if (raiz->simbolo - ptr->simbolo > 0)
//         inserir_arvore(ptr->simbolo, raiz->left);
//     else 
//         inserir_arvore(ptr->simbolo, raiz->right);


//     if (raiz->simbolo - ptr->simbolo > 0 && !raiz->left)
//         raiz->left = ptr;
//     else if (raiz->simbolo - ptr->simbolo < 0 && !raiz->right)
//         raiz->right = ptr;
    
// }

// void inserir(char caractere, Noh **raiz) {

//     Noh *ptr = malloc(sizeof(Noh));
//     ptr->simbolo = caractere;
//     ptr->right = NULL;
//     ptr->left = NULL;

//     if (!(*raiz)) {
//         *raiz = ptr;
//         return;
//     }

//     inserir_arvore(*raiz, ptr);
// }

int indice(char simbolo, char *em_ordem, int tamanho) {
    int n;
    for (n=0; n < tamanho; n++)
        if (em_ordem[n] == simbolo)
            return n;

    return -1;
}

Noh *construir_ABB(char *pre_ordem, char *em_ordem, int tamanho) {

    if (tamanho == 0)
        return NULL;

    Noh *ptr = malloc(sizeof(Noh));
    ptr->simbolo = *pre_ordem;
    ptr->left = NULL;
    ptr->right = NULL;

    int ind = indice(*pre_ordem, em_ordem, tamanho);

    ptr->left = construir_ABB(pre_ordem+1, em_ordem, ind);
    ptr->right = construir_ABB(pre_ordem+1+ind, em_ordem+1+ind, tamanho-1-ind);

    return ptr;
}

void printar(Noh *raiz) {
    if (!raiz)
        return;

    printar(raiz->left);
    printar(raiz->right);
    printf("%c", raiz->simbolo);
}

void liberar(Noh *raiz) {
    if (!raiz)
        return;

    liberar(raiz->left);
    liberar(raiz->right);
    free(raiz);
}

// ------------------------------------------------------ //

int main() {

    int tamanho;
    do {
        scanf("%d", &tamanho);
    } while (tamanho > 81 || tamanho < 0);

    char str1[82], str2[82];
    scanf("%s", str1);
    scanf("%s", str2);

    Noh *raiz = construir_ABB(str1, str2, tamanho);
    printar(raiz);
    liberar(raiz);
}