#ifndef VNDDR_FILE_MANIP_H_INCLUDED
#define VNDDR_FILE_MANIP_H_INCLUDED

void cadastro_vendedor(FILE*,int *);

void listar_vendedores(FILE*);

int pesquisa_vnddr_CPF(FILE*,char*);

int pesquisa_vnddr_ID(FILE*,unsigned long);

void alteracao_vendedor(FILE*);

void consulta_vnddr_CPF(FILE*);

void consulta_vnddr_ID(FILE*);

void consulta_vnddr_INI(FILE*);

#endif //VNDDR_FILE_MANIP_H_INCLUDED