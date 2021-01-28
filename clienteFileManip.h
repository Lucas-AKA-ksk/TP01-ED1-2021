#ifndef CLNT_FILE_MANIP_H_INCLUDED
#define CLNT_FILE_MANIP_H_INCLUDED

void cadastro_cliente(FILE*,int*);

void listar_clientes(FILE*);

int pesquisa_clnt_CPF(FILE*,char*);

void alteracao_cliente(FILE*);

#endif //CLNT_FILE_MANIP_H_INCLUDED