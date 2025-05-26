#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pilha {
    int valor;
    struct pilha *prox;
} Pilha;

typedef struct lista {
    char *nome;
    int num_elementos;
    Pilha *pilha;
    struct lista *prox;
} Lista;

// ---------------------------------------------------//
// Funções de comando:

void liberar_pilha(Pilha *pilha) {

    if (!pilha)
        return;

    liberar_pilha(pilha->prox);
    free(pilha);

}

void liberar_lista(Lista *lista) {

    if (!lista) 
        return;

    liberar_lista(lista->prox);
    liberar_pilha(lista->pilha);
    free(lista);

}

Lista *init(Lista *lista, char *nome_pilha) {

    Lista *ptr = malloc(sizeof(Lista));

    if (!lista){
        lista = ptr;
        lista->nome = nome_pilha;
        lista->num_elementos = 0;
        lista->pilha = NULL;
        lista->prox = NULL;
        return lista;
    }

    Lista *aux = lista;
    while(aux->prox)
        aux = aux->prox;

    aux->prox = ptr;

    ptr->nome = nome_pilha;
    ptr->num_elementos = 0;
    ptr->pilha = NULL;
    ptr->prox = NULL;

    return lista;
}

void push(Lista *lista, char *nome_pilha, int number) {

    while (lista && (strcmp(lista->nome, nome_pilha) != 0))
        lista = lista->prox;

    if (!lista) {
        printf("Pilha %s nao encontrada!", nome_pilha);
        liberar_lista(lista);
        exit(0);
    }

    Pilha *ptr = malloc(sizeof(Pilha));

    ptr->prox = lista->pilha;
    ptr->valor = number;
    lista->pilha = ptr;
    lista->num_elementos++;
}

// função pop, percorre a lista guardando sempre um valor anterior a pilha, 
// para o caso da pilha ficar vazia, ela será liberada
Lista *pop1(Lista *lista, char *nome_pilha) {

    Lista *ini = lista, a;
    Lista *aux = &a;
    aux->prox = NULL;

    if (lista && (strcmp(nome_pilha, lista->nome) == 0)) {

        switch (lista->num_elementos) {
        case 0:
            printf("Pilha %s vazia!", nome_pilha);
            liberar_lista(lista);
            exit(0);
        
        case 1:
            ini = lista->prox;
            break;

        default:
            break;
        }

    } else {

        // percorre a lista até achar a pilha
        do {
            aux = lista;
            lista = lista->prox;
        } while (lista && (strcmp(lista->nome, nome_pilha) != 0));
    
        if (!lista) {
            printf("Pilha %s nao encontrada!", nome_pilha);
            liberar_lista(lista);
            exit(0);
        }
    }
        
    Pilha *ptr = lista->pilha;
    lista->pilha = lista->pilha->prox;
    lista->num_elementos--;
    free(ptr);

    if (lista->num_elementos == 0) {
        aux->prox = lista->prox;
        free(lista);
    }

    return ini;
}

void top(Lista *lista, char *nome_pilha) {

    while (lista && (strcmp(lista->nome, nome_pilha) != 0))
        lista = lista->prox;

    if (!lista) {
        printf("Pilha %s nao encontrada!", nome_pilha);
        liberar_lista(lista);
        exit(0);
    }

    if (lista->num_elementos == 0){
        printf("Pilha %s vazia!", nome_pilha);
        liberar_lista(lista);
        exit(0);
    }

    printf("%s: [%d]\n", nome_pilha, lista->pilha->valor);
}

void printar(Lista *lista, char *nome_pilha) {

    while (lista && (strcmp(lista->nome, nome_pilha) != 0))
        lista = lista->prox;

    if (!lista) {
        printf("Pilha %s nao encontrada!", nome_pilha);
        liberar_lista(lista);
        exit(0);
    }    

    Pilha *ptr = lista->pilha;
    if (lista->nome == 0) {
        printf("[]\n");
        return;
    }


    printf("[%d", ptr->valor);

    for (int i = 1; i < lista->num_elementos; i++){
        ptr = ptr->prox;
        printf(", %d", ptr->valor);
    }

    printf("]\n");
}

void show(Lista *lista) {

    Pilha *ptr;

    while (lista) {

        if (lista->num_elementos == 0) {
            printf("%s: []\n", lista->nome);
            lista = lista->prox;
            continue;
        }

        ptr = lista->pilha;
        printf("%s: [%d", lista->nome, ptr->valor);

        for (int i = 1; i < lista->num_elementos; i++){
            ptr = ptr->prox;
            printf(", %d", ptr->valor);
        }

        printf("]\n");
        lista = lista->prox;
    }

}

// recebe a pilha B e o nome da pilha, o nó da lista em que se encontra
// e o nome da pilha A, para dar dar o merge e liberar a memoria
void merge_recursivo(Pilha *pilha, Lista *lista, char *nome_A) {

    if (!pilha) 
        return;

    merge_recursivo(pilha->prox, lista, nome_A);

    push(lista, nome_A, pilha->valor);
    free(pilha);

}

Lista *merge(Lista *lista, char *nome_A, char *nome_B) {

    Lista *ini = lista, *aux = NULL;
    
    if (lista && strcmp(nome_B, lista->nome) == 0) 
        ini = ini->prox;
    

    if (!lista) {
        printf("Erro: pilhas nao encontradas!");
        liberar_lista(lista);
        exit(0);
    }

    Lista *pilhaA = lista, *pilhaB = lista;

    do {
        aux = pilhaB;
        pilhaB = pilhaB->prox;
    } while (pilhaB && (strcmp(pilhaB->nome, nome_B) != 0));
    
    while (pilhaA && (strcmp(pilhaA->nome, nome_A) != 0))
        pilhaA = pilhaA->prox;
    
    if ((!pilhaA) || (!pilhaB)) {
        printf("Erro: pilhas nao encontradas!");
        liberar_lista(lista);
        exit(0);
    }

    aux->prox = aux->prox->prox; // sempre terá um prox elemento, pois ele anda atrás da pilha B

    // if (pilhaB->num_elementos == 0)

    merge_recursivo(pilhaB->pilha, lista, pilhaA->nome);
    free(pilhaB);

    return ini;
}

void split_complete(Pilha *pilha, char *novo_nome, int k, Lista *lista) {

    if (k == 0) 
        return;

    split_complete(pilha->prox, novo_nome, k--, lista);

    push(lista, novo_nome, pilha->valor);
    free(pilha);    

}

Lista *split(Lista *lista, char *nome, char *nome_novo, int k) {

    Lista *ptr = lista, *aux = NULL, *ini = lista, *percorre = lista;

    if (!lista) {
        printf("Pilha %s nao encontrada!", nome);
        liberar_lista(lista);
        exit(0);
    }

    do {
        aux = percorre;
        percorre = percorre->prox;
    } while (percorre && (strcmp(percorre->nome, nome) != 0));
    
    if (!percorre) {
        printf("Pilha %s nao encontrada!", nome);
        liberar_lista(lista);
        exit(0);
    }

    // while (ptr && (strcmp(ptr->nome, nome) != 0))
    //     ptr = ptr->prox;

    // if (!ptr) {
    //     printf("Pilha %s nao encontrada!", nome);
    //     // liberar memoria
    //     exit(0);
    // }

    lista = init(lista, nome_novo);

    if (strcmp(ini->nome, nome) == 0) {
        if (k > ini->num_elementos) {
            ini = ini->prox->prox;
            split_complete(lista->pilha, nome_novo, lista->num_elementos, lista); 
            free(lista);
            return ini;   
        }

    }

    if (k > percorre->num_elementos){
        split_complete(percorre->pilha, nome_novo, percorre->num_elementos, lista);
        aux->prox = percorre->prox;
        free(percorre);
        return ini;
    }

    split_complete(percorre->pilha, nome_novo, k, lista);

    return ini;

}

// ---------------------------------------------------//

char *coleta_nome() {

    char *str = calloc(31, 1);
    int i = -1;
    do {
        str[++i] = getchar();
    } while ((str[i] != ':') && (str[i] != '\n') && (str[i] != ' '));

    str[i] = '\0';

    return str;
}

// função pra limpar o buffer e deixar a leitura da primeira palavra 
// do comando limpa, isso em casos de espaço ou \n. Codigo da uma leve
// bugada se digitar algo que não seja algum dos comandos, mas é só
// ninguém fazer isso :D
void flush_buffer() {
    char ch;
    do {
        ch = getchar();
    } while ((ch == ' ') || (ch == '\n'));

    if (ch == EOF)
        return;
    
    ungetc(ch, stdin);
    return;
}

void inputs(int entradas) {

    char *str;
    Lista *lista = NULL;

    for (int i=0; i < entradas; i++) {

        flush_buffer();
        str = coleta_nome();

        if (strcmp(str, "MERGE") == 0) {
            
            char *nomeA, *nomeB;
        
            flush_buffer();
            nomeA = coleta_nome();

            flush_buffer();
            nomeB = coleta_nome();

            lista = merge(lista, nomeA, nomeB);
            continue;
        }

        if (strcmp(str, "SPLIT") == 0) {
            
            char *nome_novo, *nome;
            int k;

            flush_buffer();
            nome = coleta_nome();

            flush_buffer();
            nome_novo = coleta_nome();

            scanf("%d", &k);
            split(lista, nome, nome_novo, k);

            continue;
        }

        if (strcmp(str, "SHOW") == 0) {
            show(lista);
            continue;
        }

        char comando[6];
        scanf("%s", comando);

        if (strcmp(comando, "INIT") == 0) {
            lista = init(lista, str);
            continue;
        }

        if (strcmp(comando, "PUSH") == 0) {
            int n;
            scanf("%d", &n);
            push(lista, str, n);
            continue;
        }

        if (strcmp(comando, "POP") == 0) {
            lista = pop1(lista, str);
            continue;
        }

        if (strcmp(comando, "TOP") == 0) {
            top(lista, str);
            continue;
        }

        if (strcmp(comando, "PRINT") == 0) {
            printar(lista, str);
            continue;
        }

    }    

}

int main() {

    // codigo feito muito as pressas, ta muito feio
    // que Deus ajude a pessoa que está lendo isso

    int entradas;
    do {
        scanf("%d", &entradas);
    } while ((entradas < 1) || (entradas > 100));

    inputs(entradas);

    return 0;
}