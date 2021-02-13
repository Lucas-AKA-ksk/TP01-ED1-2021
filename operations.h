#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

typedef struct 
{
    unsigned long idProduto;
    int quantidadeVendida;
    float valorVenda;
}Carrinho;

void realizar_venda(FILE*,FILE*,FILE*,FILE*,FILE*,int*,int*);

void realizar_compra(FILE*,FILE*,FILE*,FILE*,int*,int*);

int pesquisa_carrinho(Carrinho*,int,unsigned int);

#endif //OPERATIONS_H_INCLUDED