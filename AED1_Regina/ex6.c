#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int coluna;
    int valor;
    struct no *prox;
}No;

// ---------------------------------------------------- //

void liberar(No *noh) {
    if (!noh)
        return;

    liberar(noh->prox);
    free(noh);
}

void add(No **matriz, int linhas) {

    No *ptr, *aux;
    int number;

    for (int i=0; i < linhas; i++) {
        for (int k=1; k <= linhas; k++) {

            scanf("%d", &number);
            
            if (number != 0) {

                ptr = malloc(sizeof(No));
                ptr->coluna = k;
                ptr->valor = number;
                ptr->prox = NULL;

                if (!matriz[i]) {
                    matriz[i] = ptr;

                } else {
                    for (aux = matriz[i]; aux->prox; aux = aux->prox);
                    aux->prox = ptr;

                }
            }
        }
    }
}

No **soma(No **matriz_1, No **matriz_2, int linhas) {

    No **matriz_soma = calloc(linhas, sizeof(No*));
    No *ptr, *aux, *noh;


    for (int i=0; i<linhas; i++) {
        ptr = matriz_1[i];
        aux = matriz_2[i];

        for (int k=1; k<=linhas; k++) {

            noh = malloc(sizeof(No));
            noh->valor = 0;
            noh->coluna = k;
            noh->prox = NULL;

            if (ptr) {                
                if (ptr->coluna == k) {
                    noh->valor += ptr->valor;
                    ptr = ptr->prox;
                }
            }
            if (aux) {
                if (aux->coluna == k) {
                    noh->valor += aux->valor;
                    aux = aux->prox;
                }
            }
            if (noh->valor != 0) {
                No *percorre = matriz_soma[i];

                if (!matriz_soma[i]) {
                    matriz_soma[i] = noh;

                } else {
                    for(percorre; percorre->prox; percorre = percorre->prox);
                    percorre->prox = noh;

                }
            }
        }

        liberar(matriz_1[i]);
        liberar(matriz_2[i]);
    }

    free(matriz_1);
    free(matriz_2);

    return matriz_soma;
}

No **subtracao(No **matriz_1, No **matriz_2, int linhas) {

    No **matriz_sub = calloc(linhas, sizeof(No*));
    No *ptr, *aux, *noh;

    for (int i=0; i<linhas; i++) {
        ptr = matriz_1[i];
        aux = matriz_2[i];

        for (int k=1; k<=linhas; k++) {

            noh = malloc(sizeof(No));
            noh->valor = 0;
            noh->coluna = k;
            noh->prox = NULL;

            if (ptr) {
                if (ptr->coluna == k) {
                    noh->valor += ptr->valor;
                    ptr = ptr->prox;
                }
            }
            if (aux) {
                if (aux->coluna == k) {
                    noh->valor -= aux->valor;
                    aux = aux->prox;
                }
            }
            if (noh->valor != 0) {
                No *percorre = matriz_sub[i];

                if (!matriz_sub[i]) {
                    matriz_sub[i] = noh;

                } else {
                    for(percorre; percorre->prox; percorre = percorre->prox);
                    percorre->prox = noh;

                }
            }
        }

        liberar(matriz_1[i]);
        liberar(matriz_2[i]);
    }

    free(matriz_1);
    free(matriz_2);

    return matriz_sub;
}

No **multiplica(No **matriz_1, No **matriz_2, int linhas) {

    No **matriz_mult = calloc(linhas, sizeof(No*));
    No *ptrA, *ptrB, *noh, *percorre;
    int valor;

    for (int i = 0; i < linhas; i++) {
        for (int j = 1; j <= linhas; j++) {

            valor = 0;
            ptrA = matriz_1[i];

            while (ptrA) {
                int colunaA = ptrA->coluna;
                int valorA = ptrA->valor;

                ptrB = matriz_2[colunaA - 1];
                while (ptrB) {
                    if (ptrB->coluna == j) 
                        valor += valorA * ptrB->valor;
                    
                    ptrB = ptrB->prox;
                }

                ptrA = ptrA->prox;
            }

            if (valor != 0) {
                
                noh = malloc(sizeof(No));
                noh->coluna = j;
                noh->valor = valor;
                noh->prox = NULL;

                if (!matriz_mult[i]) {
                    matriz_mult[i] = noh;
                } else {
                    percorre = matriz_mult[i];

                    while (percorre->prox)
                        percorre = percorre->prox;

                    percorre->prox = noh;
                }
            }
        }

        liberar(matriz_1[i]);
    }

    for (int i = 0; i < linhas; i++)
        liberar(matriz_2[i]);

    free(matriz_1);
    free(matriz_2);

    return matriz_mult;
}


void printar(No **matriz, int linhas) {

    No *ptr;

    for (int i=0; i<linhas; i++) {

        if (!matriz[i]) {
            printf("0");

            for (int k=1; k<linhas; k++)
                printf(" 0");

        } else {
            ptr = matriz[i];

            for (int k=1; k<=linhas; k++) {
                if (ptr) {
                    if (ptr->coluna == k) {
                        if (k == 1)
                            printf("%d", ptr->valor);
                        else 
                            printf(" %d", ptr->valor);

                        ptr = ptr->prox;

                    } else {
                        if (k == 1)
                            printf("0");
                        else
                            printf(" 0");
                    }

                } else {
                    if (k == 1)
                        printf("0");
                    else
                        printf(" 0");
                }

            }
        }

        printf("\n");
    }
}

// ---------------------------------------------------- //

int main() {

    int operacao, linhas;
    scanf("%d", &operacao);
    scanf("%d", &linhas);

    No **matriz_1 = calloc(linhas, sizeof(No*));
    No **matriz_2 = calloc(linhas, sizeof(No*));

    add(matriz_1, linhas);
    add(matriz_2, linhas);

    No **matriz_resultante;

    if (operacao == 1)
        matriz_resultante = soma(matriz_1, matriz_2, linhas);
    else if (operacao == 2)
        matriz_resultante = subtracao(matriz_1, matriz_2, linhas);
    else if (operacao == 3)
        matriz_resultante = multiplica(matriz_1, matriz_2, linhas);

    printar(matriz_resultante, linhas);

    for (int i=0; i < linhas; i++)
        liberar(matriz_resultante[i]);

    return 0;
}