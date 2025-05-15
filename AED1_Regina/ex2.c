#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pilha{
    struct pilha *prox;
    int info;
}Pilha;

typedef struct system{
    Pilha *main;
    int size;
}System;

void push(System *system, int valor){
    Pilha *ptr = malloc(sizeof(Pilha));

    ptr->info = valor;
    ptr->prox = system->main;
    system->main = ptr;
    system->size++;
}

int pop(System *system){

    if(system->size == 0){
        printf("Erro: Pilha vazia!");
        exit(0);
    }

    Pilha *ptr = system->main;
    system->main = system->main->prox;
    system->size--;

    int n = ptr->info;

    free(ptr);
    return n;
}

// ------------------------------------------------------ //

void math(System *system, int operacao){

    if(system->size < 2){
        printf("Erro: Elementos insuficiente para operacao!");
        exit(0);
    }

    int n[2];
    n[0] = pop(system);
    n[1] = pop(system);

    switch(operacao){
    case 1: // soma
        push(system, n[1] + n[0]);
        break;
    
    case 2: // subtração
        push(system, n[1] - n[0]);
        break;

    case 3: // divisão
        if(n[0] == 0){
            printf("Erro: Divisao por zero!");
            // printf("Erro: Divisão por zero!");
            exit(0);
        }

        push(system, n[1] / n[0]);
        break;

    case 4: // multiplicação
        push(system, n[1] * n[0]);
        break;

    }
}

void duplica(System *system){
    if(system->size == 0){
        printf("Erro: Pilha vazia para DUP!");
        exit(0);
    }

    push(system, system->main->info);
}

void troca_elementos(System *system){
    if(system->size < 2){
        printf("Erro: Pilha insuficiente para SWAP!");
        exit(0);
    }    

    int n1, n2;
    n1 = pop(system);
    n2 = pop(system);

    push(system, n1);
    push(system, n2);
}

void roll(System *system, int number){

    if(system->size < number){
        printf("Erro: Posicao invalida!");
        // printf("Erro: n fora dos limites!");
        exit(0);
    }

    int aux[number - 1];
    for(int i=0; i < (number - 1); i++)
        aux[i] = pop(system);
    
    int n = pop(system);

    for(int i = number - 2; i > -1; i--)
        push(system, aux[i]);

    push(system, n);
}

void clear(System *system){

    if(system->size == 0){
        printf("Erro: Pilha vazia!");
        exit(0);
    }

    int n, t = system->size;
    for(int i=0; i < t; i++)
        n = pop(system);
    
}

void printar(System *system){

    if(system->size == 0){
        printf("\n");
        return;
    }

    printf("%d", system->main->info);
    Pilha *ptr = system->main->prox;

    for(int i=1; i < system->size; i++){
        printf(" %d", ptr->info);
        ptr = ptr->prox;
    }

    printf("\n");
}

void liberar(System *system){

    if(system->size != 0){
        int n;
        for(int i=0; i < system->size; i++)
            n = pop(system);
    }
    
    free(system);
}

void inputs(int entradas){

    char str[6];
    int number, n = 0;

    System *system = malloc(sizeof(System));
    system->main = NULL;
    system->size = 0;

    for(int i=0; i<entradas; i++){

        scanf("%s", str);
        // fgets(str, 6, stdin);

        if(strcmp(str, "PUSH") == 0){
            scanf("%d", &number);
            push(system, number);
            continue;
        }
        
        if(strcmp(str, "POP") == 0){
            number = pop(system);
            continue;
        }
        
        if(strcmp(str, "ADD") == 0){
            math(system, 1);
            continue;
        }
        
        if(strcmp(str, "SUB") == 0){
            math(system, 2);
            continue;
        }

        if(strcmp(str, "DIV") == 0){
            math(system, 3);
            continue;
        }

        if(strcmp(str, "MUL") == 0){
            math(system, 4);
            continue;
        }

        if(strcmp(str, "DUP") == 0){
            duplica(system);
            continue;
        }

        if(strcmp(str, "SWAP") == 0){
            troca_elementos(system);
            continue;
        }

        if(strcmp(str, "ROLL") == 0){
            scanf("%d", &number);
            roll(system, number);
            continue;
        }

        if(strcmp(str, "CLEAR") == 0){
            clear(system);
            continue;
        }

        if(strcmp(str, "PRINT") == 0){
            printar(system);
            n++;
            continue;
        }
    }

    if(n == 0)
        printar(system);

    liberar(system);

}


int main(){

    int entradas;
    // scanf("%d", &entradas);
    // getchar();
    do{
        scanf("%d", &entradas);
    }while((entradas < 1) || (entradas > 100));

    inputs(entradas);
    return 0;
}