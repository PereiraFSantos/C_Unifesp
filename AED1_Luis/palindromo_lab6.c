#include <stdio.h>
#include <stdlib.h>

int palindro(char str[], int fim, int ini, int cont){

    if(str[0] == '\n')
        return -1;

    if(str[ini] == '\0')
        return 0;

    cont += palindro(str, fim-1, ini+1, cont);

    if(str[ini] == str[fim])
        cont++;

    return cont;
}

void desaloca(char **str[], int linhas){
    for(int i = 0; i < linhas; i++)
        free(str[i]);
}

int main(int argc, char *argv[]){
    
    if(argc > 1)
        return 0;

    int linhas, size;
    scanf("%d", &linhas);
    scanf("%d", &size);
    getchar();
    // int linhas = atoi(argv[1]);
    // int size = atoi(argv[2]);

    char *palindromo = malloc(linhas + 1);
    char **str = malloc(linhas * sizeof(char *));

    for(int i = 0; i < linhas; i++)
        str[i] = malloc(size + 2);


    int tamanho, ini, n;
    for(int i = 0; i < linhas; i++){
        fgets(str[i], size+2, stdin);
        tamanho = ini = 0;

        if(str[i][0] == '\n'){
            palindromo[i] = '0';
            continue;
        }
    

        for(int p = 0; (str[i][p] != '\0') && (str[i][p] != '\n'); p++)
            tamanho++;

        n = palindro(str[i], tamanho-1, 0, 0);

        if(n == tamanho)
            palindromo[i] = '1';
        else
            palindromo[i] = '0';
    }

    palindromo[linhas] = '\0';
    printf(palindromo);

    desaloca(str, linhas);
    free(palindromo);
    return 0;
}