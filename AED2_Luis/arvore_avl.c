#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    int fb; //fator de balanceamento
    struct no *esq;
    struct no *dir;
}  No;

////////////////////////////////////////////////////////////

int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}

int altura_noh(No *noh)
{
    if (!noh)
        return -1;

    return max(altura_noh(noh->esq), altura_noh(noh->dir)) + 1;
}

int fator_balanceamento(No *noh)
{
    return altura_noh(noh->esq) - altura_noh(noh->dir);
}

////////////////////////////////////////////////////////////

No *LL(No *X)
{
    No *ptr = X->esq->dir;
    No *Y = X->esq;

    Y->dir = X;
    X->esq = ptr;

    X->fb = fator_balanceamento(X);
    Y->fb = fator_balanceamento(Y);

    return Y;
}

No *RR(No *X)
{
    No *ptr = X->dir->esq;
    No *Y = X->dir;

    Y->esq = X;
    X->dir = ptr;

    X->fb = fator_balanceamento(X);
    Y->fb = fator_balanceamento(Y);

    return Y;
}

No *LR(No *X)
{
    X->esq = RR(X->esq);
    return LL(X);
}

No *RL(No *X)
{
    X->dir = LL(X->dir);
    return RR(X);
}

No *rotacao(No *raiz)
{
    if (raiz->fb == 2)
    {
        if (raiz->esq->fb == -1)
        {
            raiz = LR(raiz);
            return raiz;
        }

        return LL(raiz);
    }

    if (raiz->fb == -2)
    {
        if (raiz->dir->fb == 1)
        {
            raiz = RL(raiz);
            return raiz;
        }

        return RR(raiz);
    }

    return raiz;
}

No *inserir(No *raiz, int info)
{
    if (!raiz)
    {
        No *ptr = malloc(sizeof(No));
        
        ptr->dir = NULL;
        ptr->esq = NULL;
        ptr->fb = 0;
        ptr->valor = info;

        return ptr;
    }

    if (info < raiz->valor)
        raiz->esq = inserir(raiz->esq, info);
    else
        raiz->dir = inserir(raiz->dir, info);

    raiz->fb = fator_balanceamento(raiz);

    return raiz;
}

void remover(No *raiz, int info)
{
    
}

int main()
{
    int n;
    scanf("%d", &n);

    // Arvore *arv;
    // arv->raiz = NULL;
    No *raiz = NULL;
    int info;

    for (int i=0; i<n; i++)
    {
        scanf("%d", &info);
        raiz = inserir(raiz, info);
        raiz = rotacao(raiz);
    }
    
    return 0;
}