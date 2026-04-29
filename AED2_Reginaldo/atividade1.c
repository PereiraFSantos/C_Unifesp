#include <stdio.h>
#include <stdlib.h>

typedef struct eleitor 
{
    int voto[3];
    int valido;
} 
Eleitor;

///////////////////////////////////////////////////////////////////////

void segundo_turno(Eleitor *eleitores, int *candidatos, int V, int primeiro, int segundo)
{
    int validos = 0;
    candidatos[primeiro] = 0;
    candidatos[segundo] = 0;

    for (int i=0; i<V; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (eleitores[i].voto[j] == primeiro + 1)
            {
                candidatos[primeiro] += 1;
                validos += 1;
                break;
            }
            else if (eleitores[i].voto[j] == segundo + 1)
            {
                candidatos[segundo] += 1;
                validos += 1;
                break;
            }
        }
    }

    if (candidatos[primeiro] > candidatos[segundo] || (candidatos[primeiro] == candidatos[segundo] && primeiro < segundo))
        printf("\n%d %.2f", primeiro + 1, (candidatos[primeiro] / (validos * 1.0)) * 100);
    else 
        printf("\n%d %.2f", segundo + 1, (candidatos[segundo] / (validos * 1.0)) * 100);
    

}

void primeiro_turno(Eleitor *eleitores, int *candidatos, int V, int C)
{
    for (int i=0; i<C; i++) candidatos[i] = 0;
    int validos = 0;

    for (int i=0; i<V; i++) // contagem dos votos
    {
        scanf("%d %d %d", &eleitores[i].voto[0], &eleitores[i].voto[1], &eleitores[i].voto[2]);

        if (eleitores[i].voto[0] >= 1 && eleitores[i].voto[0] <= C) // validar o voto
        {
            candidatos[eleitores[i].voto[0] - 1] += 1;
            eleitores[i].valido = 1;
            validos += 1;
        }
        else
            eleitores[i].valido = 0;
    }

    if (validos == 0)
    {
        printf("0");
        return;
    }

    int primeiro = -1, segundo = -1;

    for (int i = 0; i < C; i++) 
    {
        if (primeiro == -1 || candidatos[i] > candidatos[primeiro]) 
        {
            segundo = primeiro;
            primeiro = i;
        } 
        else if (segundo == -1 || candidatos[i] > candidatos[segundo]) 
        {
            segundo = i;
        }
    }

    float percentual = (candidatos[primeiro] / (validos * 1.0)) * 100;
    
    printf("%d %.2f", primeiro + 1, percentual);

    if (percentual >= 50.0)
        return;

    segundo_turno(eleitores, candidatos, V, primeiro, segundo);
}

int main()
{
    int V, C;
    scanf("%d %d", &V, &C);

    Eleitor *eleitores = malloc(sizeof(Eleitor) * V);
    int *candidatos = malloc(sizeof(int) * C);

    primeiro_turno(eleitores, candidatos, V, C);

    free(eleitores);
    free(candidatos);
    return 0;
}