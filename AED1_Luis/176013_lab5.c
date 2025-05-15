#include <stdio.h>
#include <stdlib.h>

typedef struct Tarefa{
    int ID;
    int num_paginas;
    char prioridade;
    struct Tarefa *prox;
}Tarefa;

typedef struct Fila{
    int num_elementos;
    Tarefa *ini;
    Tarefa *fim;
}Fila;

//---------------------------------------//

void Exibir_Inverso();

Fila *inicializa(){

    Fila *ptr = malloc(sizeof(Fila));

    ptr->fim = NULL;
    ptr->ini = NULL;
    ptr->num_elementos = 0;

    return ptr;
}

//---------------------------------------//


void Adicionar_Tarefa(Fila *fila, int id, int paginas, char prioridade){

    Tarefa *ptr = malloc(sizeof(Tarefa));

    ptr->ID = id;
    ptr->num_paginas = paginas;
    ptr->prioridade = prioridade;
    ptr->prox = NULL;

    if(!fila->ini){
        fila->ini = ptr;
        fila->fim = ptr;
        fila->num_elementos++;
        return;
    }

    Tarefa *auxilio = fila->ini;
    while(auxilio){
        if(auxilio->ID == id){
            printf("\n");
            return;
        }
        auxilio = auxilio->prox;
    }

    fila->num_elementos++;

    if(prioridade == 'U'){

        ptr->prox = fila->ini;
        fila->ini = ptr;

        return;
    }

    fila->fim->prox = ptr;
    fila->fim = ptr;
}

// imprime a primeira tarefa da lista, se a lista n existe
void Processar_Tarefa(Fila *fila){

    if(!fila->ini){
        printf("\n");
        return;
    }

    Tarefa *ptr = fila->ini;

    printf(
        "%d %d %c\n",
        ptr->ID,
        ptr->num_paginas,
        ptr->prioridade
    );

    fila->num_elementos--;

    if(!ptr->prox){
        fila->ini = NULL;
        fila->fim = NULL;

        free(ptr);
        return;
    }

    fila->ini = ptr->prox;
    free(ptr);
}

// verifica se a fila está vazia, é o primeiro ou ultimo elemento a ser 
// retirado, e também elementos no meio da lista
void Cancelar_Tarefa(Fila *fila, int id){

    if(!fila->ini){
        printf("\n");
        return;
    }

    Tarefa *ptr = fila->ini;

    if(ptr->ID == id){
        fila->ini = ptr->prox;

        printf(
            "%d %d %c\n",
            ptr->ID,
            ptr->num_paginas,
            ptr->prioridade
        );

        fila->num_elementos--;
        free(ptr);
        return;
    }

    while(ptr->prox && ptr->prox->ID != id)
        ptr = ptr->prox;
    
    if(!ptr->prox){
        printf("\n");
        return;
    }
    
    if(!ptr->prox->prox)
        fila->fim = ptr;

    printf(
        "%d %d %c\n",
        ptr->prox->ID,
        ptr->prox->num_paginas,
        ptr->prox->prioridade
    );

    Tarefa *aux = ptr->prox;

    ptr->prox = ptr->prox->prox;

    fila->num_elementos--;
    free(aux);
}

void Exibir(Fila *fila, int ordem){

    if(!fila->ini){
        printf("\n");
        return;
    }

    if(ordem == 0){

        Tarefa *ptr = fila->ini;

        do{
        printf(
            "%d %d %c\n",
            ptr->ID,
            ptr->num_paginas,
            ptr->prioridade
        );

        ptr = ptr->prox;
          
        }while(ptr);
        
        return;
    }    

    Exibir_Inverso(fila->ini);
}


// exibe a fila de maneira inversa por recursividade, se a lista for 
// bem bem grande pode dar stack overflow, mas pra tarefa deve bastar
void Exibir_Inverso(Tarefa *tarefa){

    if(!tarefa)
        return;

    Exibir_Inverso(tarefa->prox);
    
    printf(
        "%d %d %c\n",
        tarefa->ID,
        tarefa->num_paginas,
        tarefa->prioridade
    );

}

//---------------------------------------//

void Desaloca(Fila *fila){

    Tarefa *no;

    while(fila->ini){
        no = fila->ini;
        fila->ini = no->prox;
        free(no);
    }
    free(fila);
}

//---------------------------------------//

int main(){
    
    Fila *fila = inicializa();

    int operacoes;
    scanf("%d", &operacoes);
    getchar();


    int id, paginas, ordem;
    char prioridades, operacao;
    for(int i = 0; i < operacoes; i++){
        
        scanf(" %c", &operacao);
        getchar();

        switch (operacao) {
        case 'P':
            Processar_Tarefa(fila);
            break;
        case 'C':
            scanf("%d", &id);
            Cancelar_Tarefa(fila, id);
            break;
        case 'E':
            scanf("%d", &ordem);
            Exibir(fila, ordem);
            break;
        case 'A':
            scanf("%d %d", &id, &paginas);
            getchar();
            scanf(" %c", &prioridades);
            Adicionar_Tarefa(fila, id, paginas, prioridades);
            break;
        default:
            // Caso inválido
            printf("\n");
            break;
        }
    }

    Desaloca(fila);

    return 0;
}