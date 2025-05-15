#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char caractere;
    struct no *prox;
}No;

// ------------------------------------------------------------

void push(No **pilha, char caractere){

    No *ptr = malloc(sizeof(No));
    ptr->caractere = caractere;

    if(!(*pilha)){
        ptr->prox = NULL;
        *pilha = ptr;
        return;
    }

    ptr->prox = *pilha;
    *pilha = ptr;
}

void esvazia(No **pilha){

    while(*pilha){
        printf("%c", (*pilha)->caractere);
        No *ptr = *pilha;
        *pilha = (*pilha)->prox;
        free(ptr);
    }
    printf(" ");
}


int main(){
    // é um código que vc vai receber um número de caracteres máximo de uma
    // frase e vai retornar as palavras invertidas, porém na mesma ordem

    No *pilha = malloc(sizeof(No));
    pilha = NULL;

    int num_char;
    scanf("%d", &num_char);
    getchar();

    char frase[num_char + 1];
    fgets(frase, num_char+1, stdin);

    for(int i=0; i<num_char; i++){
        if((frase[i] == ' ') || (frase[i] == '\0')){
            esvazia(&pilha);
            continue;
        }

        push(&pilha, frase[i]);
    }

    return 0;
}