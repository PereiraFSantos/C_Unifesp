#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct chamado{
    struct chamado *prox;
    int id;
    char msg[51];
}Chamado;

typedef struct fila{
    Chamado *ini;
    Chamado *fim;
}Fila;

// ---------------------------------------------------- //

void liberar(Fila *fila);

void add(Fila *fila){

    Chamado *ptr = malloc(sizeof(Chamado));
    scanf("%d", &ptr->id);
    getchar();
    fgets(ptr->msg, 51, stdin);
    ptr->prox = NULL;

    if(!(fila->fim)){
        fila->fim = fila->ini = ptr;
        return;
    }

    fila->fim->prox = ptr;
    fila->fim = ptr;
}

void remover(Fila *fila){

    if(!(fila->ini)){
        printf("Fila vazia!");
        liberar(fila);
        exit(0);
    }

    Chamado *ptr = fila->ini;

    if(fila->ini == fila->fim){
        fila->ini = fila->fim = NULL;
        free(ptr);
        return;
    }

    fila->ini = fila->ini->prox;
    free(ptr);
}

void printar(Fila *fila){

    if(!(fila->ini)){
        printf("\n");
        return;
    }

    // printf("ID: %d - %s", fila->ini->id, fila->ini->msg);
    
    for(Chamado *ptr = fila->ini; ptr; ptr = ptr->prox)
        printf("ID: %d - %s", ptr->id, ptr->msg);

}

void clear(Fila *fila){

    if(!(fila->ini))
        return;
    

    while(fila->ini)
        remover(fila);

}

void liberar(Fila *fila){

    Chamado *ptr;
    while(fila->ini){
        ptr = fila->ini;
        fila->ini = fila->ini->prox;
        free(ptr);
    }

    free(fila);
}

void inputs(int entradas){

    char str[8];
    Fila *fila = malloc(sizeof(Fila));
    fila->fim = fila->ini = NULL;
    
    for(int i=0; i < entradas; i++){
        
        scanf("%s", str);
        
        if(strcmp(str, "ENQUEUE") == 0){
            add(fila);
            continue;
        }

        if(strcmp(str, "DEQUEUE") == 0){
            remover(fila);
            continue;
        }

        if(strcmp(str, "PRINT") == 0){
            printar(fila);
            continue;
        }

        if(strcmp(str, "CLEAR") == 0){
            clear(fila);
            continue;
        }
    }

    liberar(fila);
}

int main(){

    int entradas;
    do{
        scanf("%d", &entradas);
    }while((entradas < 1) || (entradas > 100));

    inputs(entradas);

    return 0;
}