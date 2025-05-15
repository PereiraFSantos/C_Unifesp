#include <stdio.h>
#include <stdlib.h>

// typedef struct sequencia{
//     int tamanho;
//     int *sequencia;
// }sequencia;

// ----------------------------- //

int intervalo(int *sequencia, int x, int indice, int tamanho){

    // verificação do ultimo elemento da busca
    if(tamanho <= 3 || indice == 0){
        if(sequencia[indice] > x && sequencia[indice-1] < x)
            return indice;
        else if(sequencia[indice] < x && sequencia[indice+1] > x)
            return indice;

        return -1;
    }

    // early return
    if(indice == -1)
        return indice;

    // verificação caso o elemento do meio for menor que x
    if(sequencia[indice] < x){
        if(sequencia[indice+1] > x)
            return indice;


        tamanho /= 2;
        indice += ((tamanho - 1) / 2) + 1;
        indice = intervalo(sequencia, x, indice+1, tamanho); 
        return indice;
    }

    if(sequencia[indice-1] < x)
        return indice;

    tamanho /= 2;
    indice -= tamanho / 2;
    indice = intervalo(sequencia, x, indice, tamanho);

    return indice;
}

void start(int *sequencia, int x, int nums){
    
    int tamanho = 0;
    for(int i = 0; i < nums; i++){
        scanf("%d", &sequencia[i]);
        tamanho++;
    }

    int indice = (tamanho - 1) / 2;
    indice = intervalo(sequencia, x, indice, tamanho);

    if(indice == -1)
        printf("nao ha intervalo valido");
    else if(sequencia[indice] > x)
        printf("%d %d", sequencia[indice-1], sequencia[indice]);
    else    
        printf("%d %d", sequencia[indice], sequencia[indice+1]);
    
}

int main(){

    int x, nums;
    scanf("%d %d", &x, &nums);
    int *sequencia = malloc(nums * sizeof(int));;

    start(sequencia, x, nums);
    return 0;
}