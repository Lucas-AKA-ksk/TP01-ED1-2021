#ifndef FRNCDR_FILE_MANIP_H_INCLUDED
#define FRNCDR_FILE_MANIP_H_INCLUDED

void cadastro_fornecedor(FILE*,int*);

void listar_fornecedores(FILE*);

int pesquisa_frncdr_CNPJ(FILE*,char*);

void alteracao_fornecedor(FILE*);

void consulta_frncdr_CPF(FILE*);

#endif //FRNCDR_FILE_MANIP_H_INCLUDED