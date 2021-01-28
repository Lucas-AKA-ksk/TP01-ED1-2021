#include <stdio.h>
#include <string.h>
#include "structDeclarations.h"
#include "clienteFileManip.h"
#include "utilityFunctions.h"

void cadastro_cliente(FILE *arq, int *id){
    char cpf[12];
    int sair = 1;
    cliente new;
    
    do{
        do{
            printf("\nDigite o CPF do cliente a ser cadastrado: ");
			setbuf(stdin,NULL);
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        if(pesquisa_clnt_CPF(arq,cpf)==-1){
            strcpy(new.cpf, cpf);
			printf("valor que será inserido: %s",new.cpf); //TESTING PURPOSES
            printf("\nDigite o nome do cliente: ");
			setbuf(stdin,NULL);
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
			printf("valor que será inserido: %s",new.nome); //TESTING PURPOSES
            printf("\nDigite o email do cliente: ");
			setbuf(stdin,NULL);
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
			printf("valor que será inserido: %s",new.email); //TESTING PURPOSES
            printf("\nDigite o telefone do cliente: ");
			setbuf(stdin,NULL);
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("valor que será inserido: %s",new.telefone); //TESTING PURPOSES
            setbuf(stdin,NULL);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(cliente),1,arq);
        }
        else
            printf("\nCPF já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Cliente?\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
    }while(sair!=2);
}

void listar_clientes(FILE *arq){
    cliente r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Clientes");
    printf("\nID\t\tNOME\t\t\t\tCPF\t\tEMAIL\t\t\tTELEFONE");
    while(fread(&r,sizeof(cliente),1,arq))
        printf("\n%lu\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s",r.id,r.nome,r.cpf,r.email,r.telefone);
}

int pesquisa_clnt_CPF(FILE *arq,char* cpf){
   	cliente r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(cliente),1,arq)==1){
    	if(strcmp(r.cpf,cpf)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

void alteracao_cliente(FILE *arq){
    char cpf[12];
    int sair = 1, posicao;
    cliente new/*,old*/;
    
    do{
        do{
            printf("\nDigite o CPF do cliente o qual o cadastro deverá ser alterado: ");
			setbuf(stdin,NULL);
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        posicao = pesquisa_clnt_CPF(arq,cpf);
        
        if(posicao!=-1){
            fseek(arq,posicao*sizeof(cliente),SEEK_SET);
            fread(&new,sizeof(cliente),1,arq);
            strcpy(new.cpf, cpf);
			printf("valor que será inserido: %s",new.cpf); //TESTING PURPOSES
            printf("\nDigite o nome do cliente: ");
			setbuf(stdin,NULL);
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
			printf("valor que será inserido: %s",new.nome); //TESTING PURPOSES
            printf("\nDigite o email do cliente: ");
			setbuf(stdin,NULL);
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
			printf("valor que será inserido: %s",new.email); //TESTING PURPOSES
            printf("\nDigite o telefone do cliente: ");
			setbuf(stdin,NULL);
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("valor que será inserido: %s",new.telefone); //TESTING PURPOSES
            setbuf(stdin,NULL);
			printf("\nValor da ID: %lu",new.id);
            fseek(arq,posicao*sizeof(cliente),SEEK_SET);
            fwrite(&new,sizeof(cliente),1,arq);
        }
        else
            printf("\nCPF não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Ateração? 1-Sim 2-Não");
        scanf("%d",&sair);
    }while(sair !=1);
}

