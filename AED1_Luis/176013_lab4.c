#include <stdio.h>
#include <stdlib.h>

typedef struct Operacao {
    char tipo; // ’I’ para inserir, ’R’ para remover
    char caractere; // caractere inserido ou removido
    int posicao; // posicao no texto onde a operacao ocorreu
    struct Operacao *prox; // ponteiro para a proxima operacao na pilha
} Operacao;

typedef struct Editor {
    int num_caracter;
    Operacao *undo; // desfazer
    Operacao *redo; // refazer
    char str[100];
}Editor;

//---------------------------------------------------------//

Editor *Inicializa(){

    Editor *edicao = malloc(sizeof(Editor));

    edicao->num_caracter = 0;
    edicao->redo = NULL;
    edicao->undo = NULL;
    
    for(int i=0; i<100; i++)
        edicao->str[i] = '\0';

    return edicao;
}

void Add_desfaz(Editor *editor, char valor, int posicao, char tipo){

    Operacao *ptr = malloc(sizeof(Operacao));

    ptr->caractere = valor;
    ptr->posicao = posicao;
    ptr->tipo = tipo;

    if(!editor->undo){
        editor->undo = ptr;
        ptr->prox = NULL;
        return;
    }

    ptr->prox = editor->undo;
    editor->undo = ptr;

}

void Add_refaz(Editor *editor, char valor, int posicao, char tipo){

    Operacao *ptr = malloc(sizeof(Operacao));

    ptr->caractere = valor;
    ptr->posicao = posicao;
    ptr->tipo = tipo;

    if(!editor->redo){
        editor->redo = ptr;
        ptr->prox = NULL;
        return;
    }

    ptr->prox = editor->redo;
    editor->redo = ptr;

}

//---------------------------------------------------------//

void Inserir(Editor *editor, char valor, int posicao){

    if(posicao < 0)
        return;

    if(posicao >= editor->num_caracter){
        editor->str[editor->num_caracter] = valor;
        editor->num_caracter++;
        
        editor->str[editor->num_caracter] = '\0';
        Add_desfaz(editor, valor, posicao, 'I');
        return;
    }

    char auxilio[100];

    for(int i = 0; i < editor->num_caracter; i++)
        auxilio[i] = editor->str[i];

    editor->str[posicao] = valor;

    for(int i = posicao; i<100; i++)
        editor->str[i+1] = auxilio[i];

    editor->num_caracter++;
    editor->str[editor->num_caracter] = '\0';
    Add_desfaz(editor, valor, posicao, 'I');

}

void Remover(Editor *editor, int posicao){

    if(posicao >= editor->num_caracter || !editor->str || posicao < 0)
        return;

    Add_desfaz(editor, editor->str[posicao], posicao, 'R');

    for(int i = posicao; i < editor->num_caracter; i++){
        editor->str[i] = editor->str[i+1];
    }

    editor->num_caracter--;
}

/**
 * esta função vai criar uma replica do primeiro nó da pilha de desfazer,
 * pegar as informações dela para criar um nó na pilha de refazer, para então
 * apagar os dois nós iguais do topo da pilha de desfazer
 * 
 * para saber se remove ou insere, está sendo usado o tipo inverso da edição
*/
void Desfazer(Editor *editor){

    if(!editor->undo)
        return;

    if(editor->undo->tipo == 'I'){
        Remover(editor, editor->undo->posicao);
        Add_refaz(editor, editor->undo->caractere, editor->undo->posicao, editor->undo->tipo);

        Operacao *ptr = editor->undo; // primeiro nó

        if(!ptr->prox->prox){
            editor->undo = NULL;

            free(ptr->prox);
            free(ptr);

            return;
        }

        editor->undo = ptr->prox->prox;
        free(ptr->prox);
        free(ptr);

        return;
    }

    Inserir(editor, editor->undo->caractere, editor->undo->posicao);
    Add_refaz(editor, editor->undo->caractere, editor->undo->posicao, editor->undo->tipo);
    
    Operacao *ptr = editor->undo; // primeiro nó

    if(!ptr->prox->prox){
        editor->undo = NULL;

        free(ptr->prox);
        free(ptr);

        return;
    }

    editor->undo = ptr->prox->prox;
    free(ptr->prox);
    free(ptr);

    return;
}

void Refazer(Editor *editor){

    if(!editor->redo)
        return;

    Operacao *ptr; // primeiro nó

    if(editor->redo->tipo == 'I'){

        Remover(editor, editor->redo->posicao);
        
        if(!editor->redo->prox){
            ptr = editor->redo;
            editor->redo = NULL;

            free(ptr);    
            return;
        }

        ptr = editor->redo;
        editor->redo = ptr->prox;

        free(ptr);
        return;
    }

    Inserir(editor, editor->redo->caractere, editor->redo->posicao);

    if(!editor->redo->prox){
        ptr = editor->redo;
        editor->redo = NULL;

        free(ptr);    
        return;
    }    

    ptr = editor->redo;
    editor->redo = ptr->prox;

    free(ptr);
    return;
}


int main(){

    Editor *editor = Inicializa();

    int tamanho_texto;
    scanf("%d", &tamanho_texto);
    getchar();

    char txt[tamanho_texto + 1];
    fgets(txt, tamanho_texto + 1, stdin);
    getchar();

    for(int i = 0; i < tamanho_texto; i++)
        Inserir(editor, txt[i], i);
    

    int num_operacoes;
    scanf("%d", &num_operacoes);
    getchar();

    for(int i=0; i<num_operacoes; i++){

        char operacao;
        scanf("%c", &operacao);
        getchar();

        if(operacao == 'U') {
            Desfazer(editor);
        }

        if(operacao == 'E') {
            Refazer(editor);
        }

        if(operacao == 'R') {
            int posicao;
            scanf("%d", &posicao);

            Remover(editor, posicao);

            getchar();
        }

        if(operacao == 'I') {
            char ch;
            scanf("%c", &ch);

            int posicao;
            scanf("%d", &posicao);

            Inserir(editor, ch, posicao);
            
            getchar();
        }
        
        printf("%s\n", editor->str);
    }

    return 0;
}

// 
