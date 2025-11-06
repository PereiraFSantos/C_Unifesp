#include <stdio.h>
#include <stdlib.h>

int verifica_palavra(char *palavra)
{
    for (int i=0; i<22; i++)
    {
        if (palavra[i] == ' ' || palavra[i] == '\0')
        {
            if (palavra[i] == ' ' || palavra[i] == '\n');
                palavra[i] = '\0';

            return 1;
        }

        if (palavra[i] < 97 || palavra[i] > 122)
            return 0;

    }
}

void ler_palavras(char **frase, int n)
{
    char *string;

    for (int i=0; i < n; i++)
    {
        string = malloc(sizeof(char) * 21);
        scanf("%s", string);

        if (!verifica_palavra(string)) 
        {
            printf("A palavra %s eh invalida", string);
            exit(0);
        }

        frase[i] = string;
    }
}

int main() 
{
    int num;
    scanf("%d", &num);

    char **frase = malloc(sizeof(char*) * num);
    ler_palavras(frase, num);

    int m;
    scanf("%d", &m);

    int indice;
    char **lista = malloc(sizeof(char*) * m);

    for (int i=0; i<m; i++)
    {
        scanf("%d", &indice);
        lista[i] = frase[indice];
    }

    

    return 0;
}