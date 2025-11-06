#include <stdio.h>
#include <stdlib.h>

int busca_binaria(int *sequencia, int tamanho, int x) {

    int id, indice_inicial = 0, indice_final = tamanho - 1;

    if (sequencia[0] >= x) {
        for (id = 0; sequencia[id] == x && id < tamanho; id++);
        return id;
    }

    if (sequencia[indice_final] <= x) 
        return tamanho;

    id = (indice_final - indice_inicial) / 2;

    while (!(sequencia[id] >= x && x >= sequencia[id-1]) && !(sequencia[id] <= x && x <= sequencia[id+1])) {

        if (sequencia[id] == x) {
            for (id; sequencia[id] == x && id < tamanho; id++);
            return id + 1;
        }

        if (sequencia[id] > x) 
            indice_final = id + 1;        
        else    
            indice_inicial = id + 1;
    
        id = (indice_final - indice_inicial) / 2;
    }

    if (sequencia[id] == x) {
        for (id; sequencia[id] == x && id < tamanho; id++);
        return id + 1;
    }

    if (sequencia[id] <= x)
        return id + 1;

    return id;
}

void insertion_sort(int *sequencia, int id_chaves, int tamanho, int tamanho_organizado) {

    if (id_chaves == 0)
        return;

    insertion_sort(sequencia, id_chaves-1, tamanho, tamanho_organizado-1);

    int chave = sequencia[id_chaves];
    int id = busca_binaria(sequencia, tamanho_organizado, chave);
    printf("[%d %d] ", chave, id);

    for (int i = id_chaves; i > id; i--) {
        sequencia[i] = sequencia[i-1];   
    }

    sequencia[id] = chave;

    for (int i=0; i<tamanho; i++)
        printf("%d ", sequencia[i]);
    
    printf("\n");

}

int main() {

    int tamanho;
    scanf("%d", &tamanho);

    int *sequencia = malloc(sizeof(int) * tamanho);

    for (int i=0; i < tamanho; i++) 
        scanf("%d", &sequencia[i]);
    
    getchar();
    insertion_sort(sequencia, tamanho-1, tamanho, tamanho-1);

    // for (int i=0; i<tamanho; i++)
    //     printf("%d ", sequencia[i]);
    
    // printf("\n");

    return 0;
}