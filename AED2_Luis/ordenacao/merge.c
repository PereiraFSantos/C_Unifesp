#include <stdio.h>
#include <stdlib.h>

void merge(int *lista, int id_ini, int id_fim, int meio) {

    int tamanhoEsq = meio - id_ini + 1;
    int tamanhoDir = id_fim - meio;

    int left[tamanhoEsq];
    int right[tamanhoDir];

    for (int i = 0; i < tamanhoEsq; i++)
        left[i] = lista[id_ini + i];

    for (int i = 0; i < tamanhoDir; i++)
        right[i] = lista[meio + 1 + i];

    int indice_E = 0, indice_D = 0;

    for (int i = id_ini; i <= id_fim; i++) {

        if (indice_E < tamanhoEsq) {
            if (indice_D < tamanhoDir) {

                if (left[indice_E] < right[indice_D]) {
                    lista[i] = left[indice_E];
                    indice_E++;
                    continue;
                }

                lista[i] = right[indice_D];
                indice_D++;
                continue;
            }

            lista[i] = left[indice_E];
            indice_E++;
            continue;
        }

        lista[i] = right[indice_D];
        indice_D++;
    }
}

// void merge(int)

void merge_sort(int *lista, int id_ini, int id_fim) {

    if (id_ini == id_fim)
        return;

    int id = (id_ini + id_fim) / 2;
    merge_sort(lista, id_ini, id);
    merge_sort(lista, id+1, id_fim);
    merge(lista, id_ini, id_fim, id);
}

int main() {

    int n;
    scanf("%d", &n);
    int *lista = malloc(sizeof(int) * n);

    for (int i=0; i < n; i++)
        scanf("%d", &lista[i]);

    merge_sort(lista, 0, n-1);

    for (int i=0; i < n; i++)
        printf("%d ", lista[i]);

    return 0;
}