#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;           // valor armazenado no noh
    struct no *prox;    // ponteiro para o proximo noh
} No;

typedef struct cx {
    No **caixa;         // ponteiro para as caixas
    int N;              // numero de caixas
} Caixa;

/////////////////////////////////////////////////////////////

No *inicializa(){
    return NULL;
}

Caixa *aloca_caixas(int n){

    Caixa *ptr = malloc(sizeof(Caixa));
    ptr->caixa = malloc(sizeof(No *) * n);

    ptr->N = n;

    for(int i = 0; i < n; i++){
        ptr->caixa[i] = inicializa();
    }

    return ptr;
}

int h(int k, int N){    // retorna qual caixa vai o item
    return k % N;
}

/////////////////////////////////////////////////////////////

void insere(Caixa *caixa, int item){

    int indice = h(item, caixa->N);
    No **cabeca = &caixa->caixa[indice];    
    No *elemento = malloc(sizeof(No));

    elemento->prox = NULL;
    elemento->info = item;

    if(!*cabeca){
        *cabeca = elemento;
        return;
    }

    elemento->prox = *cabeca;
    *cabeca = elemento;

}

No *retira(Caixa *caixa, int item){

    int indice = h(item, caixa->N);
    No **lista = &caixa->caixa[indice]; //cabeça
    No *ptr = *lista;

    if(!ptr)
        return NULL;

    if(ptr->info == item){ // primeiro valor
        *lista = ptr->prox;
        return ptr;
    }

    while(ptr->prox && (ptr->prox->info != item))
        ptr = ptr->prox;    

    if(!ptr->prox)
        return NULL;

    No *tirar = ptr->prox;
    ptr->prox = ptr->prox->prox;

    return tirar;
}

void desaloca_lista(No **cabeca){
    while(*cabeca){              //primeiro valor nao nulo

        No *ptr = *cabeca;
        *cabeca = ptr->prox;

        free(ptr);
    }
}

void desaloca_caixas(Caixa *caixa){
    for(int i = 0; i < caixa->N; i++)
        desaloca_lista(&caixa->caixa[i]);

    free(caixa);
}

void imprime(Caixa *caixa){

    for(int i = 0; i < caixa->N; i++){

        No *ptr = caixa->caixa[i];

        if(!ptr)
            continue;

        printf("%d", ptr->info);
        ptr = ptr->prox;

        while(ptr){
            printf(" %d", ptr->info);
            ptr = ptr->prox;
        }
        printf("\n");
    }
}

int main(){

    int n; // num caixas
    scanf("%d", &n);

    Caixa *caixas = aloca_caixas(n);

    int m; // num inserts
    scanf("%d", &m);

    for(int i = 0; i < m; i++){        
        int item;
        scanf("%d", &item);        

        insere(caixas, item);
    }

    int eliminar;
    scanf("%d", &eliminar);

    No *retirar = retira(caixas, eliminar);

    if(retirar){
        printf("%d\n", eliminar);
        free(retirar);
    }
    else
        printf("-1\n");

    imprime(caixas);
    desaloca_caixas(caixas);

    return 0;
}