#include <stdio.h>
#include <stdlib.h>

void insertion(int *sequencia, int tamanho) {

    int j, chave;
    for(int i = 1; i < tamanho; i++) {
        chave = sequencia[i];
        j = i-1;

        while (j >= 0 && sequencia[j] > chave) {
            sequencia[j+1] = sequencia[j];
            j = j-1;
        }

        sequencia[j+1] = chave;

        for(int n=0; n<tamanho; n++)
            printf("%d ", sequencia[n]);

        printf("\n");
    }
    
}

int main() {

    int tamanho;
    scanf("%d", &tamanho);

    int *sequencia = malloc(sizeof(int) * tamanho);
    for(int i=0; i<tamanho; i++)
        scanf("%d", &sequencia[i]);

    insertion(sequencia, tamanho);

    printf("\n");

    for(int i=0; i<tamanho; i++)
        printf("%d ", sequencia[i]);

    printf("\n");

    return 0;
}