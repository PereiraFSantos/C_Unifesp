#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *left;
    struct no *right;
}No;

// ------------------------------------------------------------- //

No *inicializa(){
    No *raiz = malloc 
}

void inserir(No *raiz, int valor){
    if(raiz->valor > valor && !raiz->left){
        No *noh = malloc(sizeof(No));
        noh->valor = valor;
        noh->left = NULL;
        noh->right = NULL;
        raiz->left = noh;
        return;
    }

    else if(raiz->valor < valor && !raiz->right){
        No *noh = malloc(sizeof(No));
        noh->valor = valor;
        noh->left = NULL;
        noh->right = NULL;
        raiz->right = noh;
        return;
    }

    if(raiz->valor < valor){
        inserir(raiz->right, valor);
        return;
    }
    
    inserir(raiz->left, valor);
}

int main(){

    int nums, valor;
    scanf("%d", &nums);

    No *raiz = malloc(sizeof(No));
    raiz->left = NULL;
    raiz->right = NULL;
    scanf("%d", &raiz->valor);

    for(int i=0; i<(nums-1); i++){
        scanf("%d", &valor);
        insere(raiz, valor);
    }
        

    return 0;
}