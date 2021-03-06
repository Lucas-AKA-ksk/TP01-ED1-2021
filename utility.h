#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

void open_file(FILE**, char*); /* Opens a file with given filename or creates one if none exists */

void newline_remover(char*);

void check_newline(char*);

void format_string(char*);

int validarCPF(char*);

int validarCNPJ(char*);

void get_sys_date(char*,int);

int verify_date(char*);

int smaller_date(char*,char*);

#endif //UTILITY_H_INCLUDED