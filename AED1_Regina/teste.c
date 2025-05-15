#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    float dinheiro;
    int livros_interesse;
    float *livros_comprar; // por ordem de preferência do cliente
}Cliente;

int main(){

    // int contador = 0;
    // char frase[10];
    // FILE *f = fopen("teste.txt", "r");   
    // while(fgets(frase, 10, f) != NULL)
    //     contador++;

    // printf("%d", contador);

    // fclose(f);

    char a[10] = "aaaa\0aa";
    char b[20] = "aaaa\0";
    // int n = strcmp(a, b);
    int n = strcmp(a, "aaaa");
    printf("%d", n);
    // isso é 0

    return 0;
}