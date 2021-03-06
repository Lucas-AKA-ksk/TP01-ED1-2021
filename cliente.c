#include <stdio.h>
#include <string.h>
#include "structDeclarations.h"
#include "cliente.h"
#include "utility.h"

void cadastro_cliente(FILE *arq, int *id){
    char cpf[12];
    int sair = 1;
    Cliente new;
    
    do{
        do{
            printf("\nDigite o CPF do cliente a ser cadastrado: ");
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        if(pesquisa_clnt_CPF(arq,cpf)==-1){
            strcpy(new.cpf, cpf);
            printf("\nDigite o nome do cliente: ");
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
            format_string(new.nome);
            printf("\nDigite o email do cliente: ");
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
            format_string(new.email);
            printf("\nDigite o telefone do cliente: ");
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(Cliente),1,arq);
        }
        else
            printf("\nCPF já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Cliente?\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair!=2);
}

void listar_clientes(FILE *arq){
    Cliente r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Clientes");
    printf("\nID\t\tNOME\t\t\t\tCPF\t\tEMAIL\t\t\tTELEFONE");
    while(fread(&r,sizeof(Cliente),1,arq))
        printf("\n%lu\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s",r.id,r.nome,r.cpf,r.email,r.telefone);
}

int pesquisa_clnt_CPF(FILE *arq,char* cpf){
   	Cliente r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(Cliente),1,arq)==1){
    	if(strcmp(r.cpf,cpf)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

int pesquisa_clnt_ID(FILE *arq,unsigned long id){
   	Cliente r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(Cliente),1,arq)==1){
    	if(r.id == id)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

void alteracao_cliente(FILE *arq){
    char cpf[12];
    int sair = 1, posicao;
    Cliente new;
    
    do{
        do{
            printf("\nDigite o CPF do cliente o qual o cadastro deverá ser alterado: ");
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        posicao = pesquisa_clnt_CPF(arq,cpf);
        
        if(posicao!=-1){
            fseek(arq,posicao*sizeof(Cliente),SEEK_SET);
            fread(&new,sizeof(Cliente),1,arq);
            strcpy(new.cpf, cpf);
            printf("\nDigite o nome do cliente: ");
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
            format_string(new.nome);
            printf("\nDigite o email do cliente: ");
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
            format_string(new.email);
            printf("\nDigite o telefone do cliente: ");
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("\nValor da ID: %lu",new.id);
            fseek(arq,posicao*sizeof(Cliente),SEEK_SET);
            fwrite(&new,sizeof(Cliente),1,arq);
        }
        else
            printf("\nCPF não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Ateração? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_clnt_CPF(FILE *arq){
    char cpf[12];
    int sair = 1, posicao;
    Cliente search;
    do{
        do{
            printf("\nDigite o CPF do cliente o qual deseja CONSULTAR: ");
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        posicao = pesquisa_clnt_CPF(arq,cpf);
        
        if(posicao!=-1){
            printf("\nRegistro encontrado!!");
            
            fseek(arq,posicao*sizeof(Cliente),SEEK_SET);
            fread(&search,sizeof(Cliente),1,arq);
			
            printf("\nCPF do Cliente: %s",search.cpf); 
			printf("\nNome do Cliente: %s",search.nome); 
			printf("\nEMAIL do Cliente: %s",search.email); 
			printf("\nTelefone do cliente: %s",search.telefone); 
			printf("\nID do Cliente: %lu",search.id);
        }
        else
            printf("\nCPF não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_clnt_ID(FILE *arq){
    unsigned long id;
    int sair = 1, posicao;
    Cliente search;
    do{
        printf("\nDigite a ID do Cliente o qual deseja CONSULTAR: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);

        posicao = pesquisa_clnt_ID(arq,id);
        
        if(posicao!=-1){
            printf("\nRegistro encontrado!!");
            
            fseek(arq,posicao*sizeof(Cliente),SEEK_SET);
            fread(&search,sizeof(Cliente),1,arq);
			
            printf("\nCPF do Cliente: %s",search.cpf); 
			printf("\nNome do Cliente: %s",search.nome); 
			printf("\nEMAIL do Cliente: %s",search.email); 
			printf("\nTelefone do cliente: %s",search.telefone); 
			printf("\nID do Cliente: %lu",search.id);
        }
        else
            printf("\nID não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_clnt_INI(FILE *arq){
    char ini[4];
    int sair = 1,count;
    Cliente search;
    
    do
    {
        printf("\nDigite as 3 primeiras letras do nome do cliente \no qual deseja CONSULTAR : ");
        fgets(ini,sizeof(ini),stdin);
        check_newline(ini);
        format_string(ini);
        
        count = 0;
        fseek(arq,0,SEEK_SET);

        while(fread(&search,sizeof(Cliente),1,arq)==1)
        {
    	    if(strncmp(search.nome,ini,3)==0)
            {
                printf("\n\nNome do Cliente: %s",search.nome);
                printf("\nCPF do Cliente: %s",search.cpf); 
			    printf("\nEMAIL do Cliente: %s",search.email); 
			    printf("\nTelefone do cliente: %s",search.telefone); 
			    printf("\nID do Cliente: %lu",search.id);
                count++;
            }
        }
        if(count==0)
            printf("\n\nNão existem Clientes que possuem esse prefixo...");
        printf("\n\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=1); 
}

