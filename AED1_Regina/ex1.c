#include <stdio.h>
#include <stdlib.h>

typedef struct cliente{
    float dinheiro;
    int livros_interesse;
    float *livros_comprar; // por ordem de preferência do cliente
}Cliente;

typedef struct venda{
    int *livros_comprados;
    float *troco;
}Venda;

//-------------------------------------------------------------------

void liberar(Cliente **clientes, Venda *vendas, int num_clientes){
    
    for(int i=0; i<num_clientes; i++){
        free(clientes[i]->livros_comprar);
        free(clientes[i]);
    }

    free(vendas->livros_comprados);
    free(vendas->troco);

    free(clientes);
    free(vendas);
}

void leitura_clientes(Cliente **clientes, int num_clientes){
    for(int i=0; i<num_clientes; i++){

        clientes[i] = malloc(sizeof(Cliente));

        do{
            scanf("%f", &clientes[i]->dinheiro); // verificação do dinheiro do cliente

        }while(clientes[i]->dinheiro < 0);

        do{
            scanf("%d", &clientes[i]->livros_interesse); // verificação dos livros de interesse

        }while((clientes[i]->livros_interesse < 0) || (clientes[i]->livros_interesse > 100));


        clientes[i]->livros_comprar = malloc(sizeof(float) * clientes[i]->livros_interesse);


        for(int n=0; n<clientes[i]->livros_interesse; n++){

            do{
                scanf("%f", &clientes[i]->livros_comprar[n]); // verificação do preço dos livros

            }while(clientes[i]->livros_comprar[n] < 0);

        }
    }
}

void calculo_venda(Cliente **clientes, Venda *vendas, int num_clientes){

    vendas->livros_comprados = malloc(sizeof(int) * num_clientes);
    vendas->troco = malloc(sizeof(float) * num_clientes);

    for(int i=0; i<num_clientes; i++){

        vendas->livros_comprados[i] = 0;
        vendas->troco[i] = clientes[i]->dinheiro;

        for(int n=0; n<clientes[i]->livros_interesse; n++){

            if(vendas->troco[i] < clientes[i]->livros_comprar[n])
                continue;
            
            vendas->troco[i] -= clientes[i]->livros_comprar[n];
            vendas->livros_comprados[i]++;

        }
    }
}

int main(){

    int num_clientes;

    do{
        scanf("%d", &num_clientes);

    }while((num_clientes > 100) || (num_clientes < 1));


    Cliente **clientes = malloc(sizeof(Cliente *) * num_clientes);
    Venda *vendas = malloc(sizeof(Venda));

    leitura_clientes(clientes, num_clientes);
    calculo_venda(clientes, vendas, num_clientes);

    
    printf("%d %0.2f", vendas->livros_comprados[0], vendas->troco[0]);

    for(int i=1; i<num_clientes; i++)
        printf("\n%d %0.2f", vendas->livros_comprados[i], vendas->troco[i]);

    liberar(clientes, vendas, num_clientes);

    return 0;
}