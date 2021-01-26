#include <stdio.h>
#include <string.h>
#include "helperFunctions.h"

void newline_remover(char *s){
    if(s[strlen(s)-1]=='\n')
        s[strlen(s)-1]='\0';
}

void check_newline(char *s){
    if(strchr(s,'\n')==NULL){
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