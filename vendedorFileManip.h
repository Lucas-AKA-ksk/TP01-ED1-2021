#ifndef VNDDR_FILE_MANIP_H_INCLUDED
#define VNDDR_FILE_MANIP_H_INCLUDED

void cadastro_vendedor(FILE*,int *);

void listar_vendedores(FILE*);

int pesquisa_vnddr_CPF(FILE*,char*);

void alteracao_vendedor(FILE*);

#endif //VNDDR_FILE_MANIP_H_INCLUDED