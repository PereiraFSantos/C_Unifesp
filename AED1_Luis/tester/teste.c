#include <stdio.h>
#include <stdlib.h>
#define stdin stdin

// void ler(){
//     FILE *file;
//     file = fopen("text.txt", "r");

//     if(!file){
//         perror("Deu merda pra abrir");
//         return;
//     }

//     char str[100];
//     // fgets(str, 100, file);
//     fread(str, 4, 4, file);
//     printf(str);

//     int close = fclose(file);
// }

// void escrever(char caractere){
//     FILE *file;
//     file = fopen("text.txt", "r+");

//     if(!file){
//         perror("Deu merda pra abrir");
//         return;
//     }

//     fputc(caractere, file);
//     // fwrite()
//     int i = fclose(file);
// }

// void escreveFInal(char caractere){
//     FILE *file;
//     file = fopen("text.txt", "a+");

//     if(!file){
//         perror("Deu merda pra escrever no final\n");
//     }

//     // fputc(caractere, file);

//     char buffer[10];

//     fgets(buffer, 5, stdin);
//     fwrite(buffer, 4, 1, file);
//     fclose(file);
// }

// int main(){

//     // escrever('A');
//     escreveFInal('U');
//     ler();

//     return 0;
// }

int palindro(char str[], int ind, int tamanho, int condi){

    if(str[ind] == ' ' || ind == -1)
        return 0;

    condi += palindro(str, ind-1, tamanho+1, 0);

    if(str[ind] == str[ind + tamanho])
        return 0;

    return condi-1;
}

int palindros(char str[], int fim, int ind, int cont){

    if(str[ind] == ' ' || ind == -1)
        return 0;

    cont += palindro(str, fim+1, ind-1, cont);

    if(str[ind] == str[fim])
        cont--;

    return cont;
}

int main(int argc, char *argv[]){

    char a[10] = "ja buti";

    int pop = palindro(a, 8, 0, 0);
    printf("%d\n", pop);

    return 0;
}