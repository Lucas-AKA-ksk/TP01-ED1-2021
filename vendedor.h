#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

void cadastro_vendedor(FILE*,int *);

void listar_vendedores(FILE*);

int pesquisa_vnddr_CPF(FILE*,char*);

int pesquisa_vnddr_ID(FILE*,unsigned long);

int pesquisa_vnddr_EMAIL(FILE*,char*);

void alteracao_vendedor(FILE*);

void consulta_vnddr_CPF(FILE*);

void consulta_vnddr_ID(FILE*);

void consulta_vnddr_INI(FILE*);

int login_vendedor(FILE*,char*,char*);

#endif //VENDEDOR_H_INCLUDED