#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

void cadastro_produto(FILE*,int*);

int pesquisa_prdt(FILE*,unsigned long);

void atualizar_estoque(FILE*,int,int);

void atualizar_preco(FILE*,FILE*,int,float);

void reajuste_preco_individual(FILE*,FILE*);

void reajuste_preco_all(FILE*,FILE*);

#endif //PRODUTO_H_INCLUDED