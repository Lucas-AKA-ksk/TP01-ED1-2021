#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utility.h"

/* Abre um arquivo existente para edição ou cria um arquivo caso não exista */
void open_file(FILE** fp,char* filename)
{
    *fp = fopen(filename,"r+b");
    if(*fp == NULL){
        printf("\nArquivo %s não encontrado, um novo arquivo de mesmo nome será criado.", filename);
        *fp = fopen(filename, "w+b");
    }
};

/* Substitui o newline(\n) por nul(\0) */
void newline_remover(char *s)
{
    if(s[strlen(s)-1]=='\n')
        s[strlen(s)-1]='\0';
}

/* Verifica a existencia de um newline em uma string 's',
caso não exista, consome o buffer, caso exista, chama newline_remover */
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

/* Transforma todos os caracteres da string 's' em uppercase */
void format_string(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
    {
        s[i]=toupper(s[i]);
    }
    
}

/* Verifica a validade de um CPF */
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

/* Verifica a validade de um CNPJ */
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

/* Obtem a data atual do sistema */
void get_sys_date(char *array, int size)
{
    time_t rawtime;
    
    time (&rawtime);
    struct tm  *timeinfo = localtime(&rawtime);
    strftime(array, size, "%d/%m/%Y", timeinfo);
}

/* Verifica se uma data é válida */
int verify_date(char *data)
{
    char dataF[11];
    strcpy(dataF, data);
    int dia, mes, ano, anoAtual=2021;
    if(strlen(data)!=10)
    {
        printf("Formato incorreto, caracteres insuficientes!");
        return 0;
    }
    if(data[2]!='/')
    {
        printf("formato incorreto, primeira barra faltando");
        return 0;
    }
    if(data[5]!='/')
    {
        printf("formato incorreto, segunda barra faltando!");
        return 0;
    }
    sscanf(strtok(dataF, "/"), "%d", &dia);
    sscanf(strtok(NULL, "/"), "%d", &mes);
    sscanf(strtok(NULL, "/"), "%d", &ano);
    
    if(ano>=1960 && ano<=anoAtual) //checa o ano de nascimento
    {
        
        if(mes>=1 && mes<=12) //checa mês de nascimento
        {
            //checa dia de nascimento
            if((dia>=1 && dia<=31) && (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12))
                printf("Data valida.\n");
            else if((dia>=1 && dia<=30) && (mes==4 || mes==6 || mes==9 || mes==11))
                printf("Data valida.\n");
            else if((dia>=1 && dia<=28) && (mes==2))
                printf("Data valida.\n");
            else if(dia==29 && mes==2 && (ano%400==0 ||(ano%4==0 && ano%100!=0)))
                printf("Data valida.\n");
            else{
                printf("Dia invalido.\n");
                return 0;
            }
        }
        else
        {
            printf("Mes invalido.\n");
            return 0;
        }
    }
    else
    {
        printf("Ano invalido.\n");
        return 0;
    }
    return 1;
}

/* Verifica se data1 é menor que data2 */
int smaller_date(char* date1,char* date2) 
{
    char date1_cpy[11], date2_cpy[11];
    int day1,day2,mon1,mon2,year1,year2;
    strcpy(date1_cpy,date1);
    strcpy(date2_cpy,date2);

    sscanf(strtok(date1_cpy, "/"), "%d", &day1);
    sscanf(strtok(NULL, "/"), "%d", &mon1);
    sscanf(strtok(NULL, "/"), "%d", &year1);

    sscanf(strtok(date2_cpy, "/"), "%d", &day2);
    sscanf(strtok(NULL, "/"), "%d", &mon2);
    sscanf(strtok(NULL, "/"), "%d", &year2);

    if(year1<year2) 
        return 1;
    else if(year1==year2) 
        if(mon1<mon2) 
            return 1;
        else if(mon1==mon2) 
            if(day1<=day2) 
                return 1;
            else 
                return 0;
        else 
            return 0;
    else 
        return 0;
    
}