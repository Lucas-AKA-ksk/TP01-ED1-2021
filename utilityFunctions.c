#include <stdio.h>
#include <string.h>
#include "utilityFunctions.h"

void open_file(FILE** fp,char* filename)
{
    *fp = fopen(filename,"r+b");
    if(*fp == NULL){
        printf("\nArquivo %s não encontrado, um novo arquivo de mesmo nome será criado.", filename);
        *fp = fopen(filename, "w+b");
    }
};

void newline_remover(char *s)
{
    if(s[strlen(s)-1]=='\n')
        s[strlen(s)-1]='\0';
}

void check_newline(char *s)
{
    if(strchr(s,'\n')==NULL) /* Se \n  não for encontrado*/
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else 
        newline_remover(s);
}

int validarCPF(char *cpf)
{
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11){
        printf("\tCPF inválido!!\n\n");
        return 0;
    }///Se cpf não possuir 11 caracteres (excluindo 0 "\0") ele é inválido. 
        
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0)){
            printf("\tCPF inválido!!\n\n");
            return 0;
    }///se o CPF tiver todos os números iguais ele é inválido.
         
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1){
            printf("\tCPF inválido!!\n\n");
            return 0;///se o digito 1 não for o mesmo que o da validação CPF é inválido
        }     
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2){
            printf("\tCPF inválido!!\n\n");
            return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }    
        }
    }
    return 1;
} 

int validarCNPJ(char *cnpj)
{
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cnpj) != 14){
        printf("\tCNPJ inválido!!\n\n");
        return 0;
    }///Se CNPJ não possuir 14 caracteres (excluindo 0 "\0") ele é inválido. 
        
    else if((strcmp(cnpj,"0000000000000") == 0) || (strcmp(cnpj,"1111111111111") == 0) || (strcmp(cnpj,"2222222222222") == 0) ||
            (strcmp(cnpj,"3333333333333") == 0) || (strcmp(cnpj,"4444444444444") == 0) || (strcmp(cnpj,"5555555555555") == 0) ||
            (strcmp(cnpj,"6666666666666") == 0) || (strcmp(cnpj,"7777777777777") == 0) || (strcmp(cnpj,"8888888888888") == 0) ||
            (strcmp(cnpj,"9999999999999") == 0)){
            printf("\tCPF inválido!!\n\n");
            return 0;
    }///se o CNPJ tiver todos os números iguais ele é inválido.
         
    else
    {
        for(i = 11, j = 2; i>=0 ;i--, j++)
        {
            if(j>9)
                j=2;
            digito1 += (cnpj[i]-48) * j;
        }
        digito1 %= 11;
        if (digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cnpj[12]-48) != digito1)
        {
            printf("\nCNPJ inválido!!\n\n");
            return 0;///se o digito 1 não for o mesmo que o da validação CNPJ é inválido
        }
        else
        {
            for(i = 12, j = 2; i>=0 ;i--, j++)
            {
                if(j>9)
                    j=2;
                digito2 += (cnpj[i]-48) * j;
            }
            digito2 %= 11;
            if (digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if((cnpj[13]-48) != digito2)
            {
                printf("\tCNPJ inválido!!\n\n");
                return 0;///se o digito 1 não for o mesmo que o da validação CNPJ é inválido
            }
        }
        
    }
    return 1;
} 