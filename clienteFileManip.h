#ifndef CLNT_FILE_MANIP_H_INCLUDED
#define CLNT_FILE_MANIP_H_INCLUDED

void cadastro_cliente(FILE*,int*);

void listar_clientes(FILE*);

int pesquisa_clnt_CPF(FILE*,char*);

int pesquisa_clnt_ID(FILE*,unsigned long);

void alteracao_cliente(FILE*);

void consulta_clnt_CPF(FILE *);

void consulta_clnt_ID(FILE*);

#endif //CLNT_FILE_MANIP_H_INCLUDED