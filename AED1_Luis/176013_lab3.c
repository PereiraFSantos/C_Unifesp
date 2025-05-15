#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int simbolo; // simbolo armazenado no noh
    struct No *prox; // ponteiro para o proximo noh
    struct No *ant;// ponteiro para o noh anterior
}No;

typedef struct Tambor {
    No *cabeca; // ponteiro para a cabeca da sequencia de simbolos
}Tambor;

typedef struct Maquina{
    int n_tambores; // numero de tambores na maquina
    Tambor *tambores; // ponteiro para VETOR de Tambor e NAO vetor de PONTEIROS de Tambor
}Maquina;

///----------------------------------------------------///

Maquina *cria_maquina(int num_tambores){

    Maquina *ptr = malloc(sizeof(Maquina));
    ptr->tambores = malloc(sizeof(Tambor) * num_tambores);

    ptr->n_tambores = num_tambores;
    for(int i = 0; i < num_tambores; i++)
        ptr->tambores[i].cabeca = NULL;

    return ptr;
}


//      função pra inserir um novo nó na lista
//      (no = ponteiro para o novo nó a ser inserido)
void insere_simbolo(Tambor *tambor, int valor){

    No *no = malloc(sizeof(No));
    no->simbolo = valor;

    if(!tambor->cabeca){
        tambor->cabeca = no;
        tambor->cabeca->ant = no;
        tambor->cabeca->prox = no;        
        return;
    }


    no->prox = tambor->cabeca;
    no->ant = tambor->cabeca->ant;
    tambor->cabeca->ant = no;

    if(tambor->cabeca->prox == tambor->cabeca)
        tambor->cabeca->prox = no;
}


void remove_simbolo(Tambor *tambor, int valor){
    printf("[REMOVE SIMBOLO][START]");

    No *ptr = tambor->cabeca;

    if(!tambor->cabeca)
        return;

    if(tambor->cabeca->simbolo == valor && tambor->cabeca->prox == tambor->cabeca){
        free(tambor->cabeca);
        tambor->cabeca = NULL;
        return;
    }

    if(ptr->simbolo == valor){   // 1º elemento retirado e lista não vazia

        ptr->prox->ant = ptr->ant;   // o proximo nó vai apontar para o anterior
        ptr->ant->prox = ptr->prox;  // o contrario
        tambor->cabeca = ptr->ant;

        free(ptr);
        return;
    }

    while(ptr->prox->simbolo != valor && ptr->prox != tambor->cabeca)
        ptr = ptr->prox;
    
    if(ptr->prox == ptr)         // não existe o elemento no tambor
        return;

    ptr = ptr->prox;
    ptr->prox->ant = ptr->ant;   // o proximo nó vai apontar para o anterior
    ptr->ant->prox = ptr->prox;  // o contrario

    free(ptr);
    printf("[REMOVE SIMBOLO][END]");
}

//--------------------------------------------------------//

void desaloca_tambor(Tambor *tambor){

    if(!tambor->cabeca){
        free(tambor);
        return;
    }

    No *ptr = tambor->cabeca;

    if(ptr->prox == ptr){
        free(ptr);
        free(tambor);
        return;
    }

    while(ptr->prox != tambor->cabeca){
        ptr = ptr->prox;
        free(ptr->ant);
    }

    free(ptr);
    free(tambor->cabeca);
    free(tambor);
}


void desaloca_caixas(Maquina **machine){
    for(int i=0; i< (*machine)->n_tambores; i++)
        desaloca_tambor(&(*machine)->tambores[i]);

    free(*machine);
    *machine = NULL;
}


void gira_tambor(Tambor *tambor, int giros, int sentido){

    if(!tambor->cabeca || tambor->cabeca->prox == tambor->cabeca)
        NULL;

    if(sentido == 0){
        for(int i=0; i<giros; i++)
            tambor->cabeca = tambor->cabeca->ant;

        return;
    }
    
    for(int i=0; i<giros; i++)
        tambor->cabeca = tambor->cabeca->prox;

    return;
}


int *printas(Maquina *machine, int valores){

    int *sequencia = malloc(sizeof(int) * valores);

    for(int i=0; i<machine->n_tambores; i++)
        sequencia[i] = machine->tambores[i].cabeca->simbolo;

    return sequencia;
}

int main(){

    int num_tambores, num_simbolos;
    scanf("%d", &num_tambores);
    scanf("%d", &num_simbolos);

    Maquina *maquina = cria_maquina(num_tambores);
    maquina->n_tambores = num_tambores;
    printf("[1]\n");
    int valor;
    for(int i=0; i<num_tambores; i++){
        for(int n=0; n<num_simbolos; n++){
            scanf("%d", &valor);
            insere_simbolo(&maquina->tambores[i], valor);
        }
    }
    printf("[2]\n");
    int *giros = malloc(sizeof(int) * num_tambores);
    for(int i=0; i<num_tambores; i++)
        scanf("%d", &giros[i]);
    
    printf("[3]\n");
    int *sentido = malloc(sizeof(int) * num_tambores);
    for(int i=0; i<num_tambores; i++)
        scanf("%d", &sentido[i]);
    
    printf("[4]\n");
    for(int i=0; i<num_tambores; i++)
        gira_tambor(&maquina->tambores[i], giros[i], sentido[i]);


    int *first = printas(maquina, num_simbolos);
    printf("[5]\n");

    int *remover = malloc(sizeof(int) * num_tambores);
    for(int i = 0; i < num_tambores; i++){
        scanf("%d", &remover[i]);
        remove_simbolo(&maquina->tambores[i], remover[i]);
    }
    printf("[joia2]");

    // int *second = printas(maquina, num_simbolos);

    printf("[joia3]");
    printf("-");
    for(int i=0; i<num_simbolos; i++)
        printf("%d-", first[i]);
    
    // printf("\n-");
    // for(int i=0; i<num_simbolos; i++)
    //     printf("%d-", second[i]);


    free(first);
    // free(second);
    free(remover);
    free(giros);
    free(sentido);
    desaloca_caixas(&maquina);
    return 0;
}