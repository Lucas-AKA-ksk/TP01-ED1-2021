#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

void cadastro_fornecedor(FILE*,int*);

void listar_fornecedores(FILE*);

int pesquisa_frncdr_CNPJ(FILE*,char*);

int pesquisa_frncdr_ID(FILE*,unsigned long);

void alteracao_fornecedor(FILE*);

void consulta_frncdr_CPF(FILE*);

void consulta_frncdr_ID(FILE*);

void consulta_frncdr_INI(FILE*);

#endif //FORNECEDOR_H_INCLUDED