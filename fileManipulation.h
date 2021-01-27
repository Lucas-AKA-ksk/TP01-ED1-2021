#ifndef FILE_MANIP_H_INCLUDED
#define FILE_MANIP_H_INCLUDED

void cadastro_cliente(FILE*,int*);

void listar_clnts(FILE*);

int pesquisa_clnt_CPF(FILE*,char*);

void cadastro_vendedor(FILE*,int *);

void listar_vnddrs(FILE*);

int pesquisa_vnddr_CPF(FILE*,char*);

void cadastro_fornecedor(FILE*,int*);

void listar_fornecedores(FILE*);

int pesquisa_frncdr_CNPJ(FILE*,char*);

#endif //FILE_MANIP_H_INCLUDED