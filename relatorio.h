#ifndef RELATORIO_H_INCLUDED
#define RELATORIO_H_INCLUDED

void relatorio_notaFiscal(FILE*,FILE*);

void relatorio_notaCompra(FILE*,FILE*);

void relatorio_cliente(FILE*,FILE*,FILE*);

void relatorio_vnddr_dia(FILE*,FILE*, FILE*);

void relatorio_vnddr_mes(FILE*,FILE*,FILE*);

void melhor_vnddr_mes(FILE*,FILE*,FILE*);

void melhor_vnddr_intrvl(FILE*,FILE*,FILE*);

void historico_preco(FILE*,FILE*);

int pesquisa_NF_id(FILE*, unsigned long);

int pesquisa_NC_id(FILE*,unsigned long);

#endif //RELATORIO_H_INCLUDED