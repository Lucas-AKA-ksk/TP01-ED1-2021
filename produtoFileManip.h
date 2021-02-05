#ifndef PRDT_FILE_MANIP_H_INCLUDED
#define PRDT_FILE_MANIP_H_INCLUDED

void cadastro_produto(FILE*,int*);

int pesquisa_prdt(FILE*,unsigned long);

//int verificar_estoque(FILE*,int,int);

void atualizar_estoque(FILE*,int,int);

#endif //PRDT_FILE_MANIP_H_INCLUDED