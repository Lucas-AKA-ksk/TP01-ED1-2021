#include <stdio.h>
#include <string.h>
#include "fileManipulation.h"
#include "structDeclarations.h"
#include "helperFunctions.h"

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

void listar_clnts(FILE *arq){
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

void cadastro_vendedor(FILE *arq, int *id){
    char cpf[12];
    int sair = 1;
    vendedor new;
    
    do{
        do{
            printf("\nDigite o CPF do vendedor a ser cadastrado: ");
			setbuf(stdin,NULL);
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        if(pesquisa_vnddr_CPF(arq,cpf)==-1){
            strcpy(new.cpf, cpf);
			printf("valor que será inserido: %s",new.cpf); //TESTING PURPOSES
            printf("\nDigite a matricula do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.matricula, sizeof(new.matricula),stdin);
            check_newline(new.matricula);
            printf("valor que será inserido: %s",new.matricula); //TESTING PURPOSES
            printf("\nDigite o nome do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
			printf("valor que será inserido: %s",new.nome); //TESTING PURPOSES
            printf("\nDigite o email do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
			printf("valor que será inserido: %s",new.email); //TESTING PURPOSES
            printf("\nDigite o telefone do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("valor que será inserido: %s",new.telefone); //TESTING PURPOSES
            setbuf(stdin,NULL);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(vendedor),1,arq);
        }
        else
            printf("\nCPF já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Vendedor?\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
    }while(sair!=2);
}

void listar_vnddrs(FILE *arq){
    vendedor r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Vendedores");
    printf("\nID\t\tMATRICULA\t\tNOME\t\t\t\tCPF\t\tEMAIL\t\t\tTELEFONE");
    while(fread(&r,sizeof(vendedor),1,arq))
        printf("\n%lu\t\t%s\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s",r.id,r.matricula,r.nome,r.cpf,r.email,r.telefone);
}

int pesquisa_vnddr_CPF(FILE *arq,char* cpf){
   	vendedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(vendedor),1,arq)==1){
    	if(strcmp(r.cpf,cpf)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

void cadastro_fornecedor(FILE *arq, int *id){
    char cnpj[12];
    int sair = 1;
    fornecedor new;
    
    do{
        do{
            printf("\nDigite o CNPJ do fornecedor a ser cadastrado: ");
			setbuf(stdin,NULL);
            fgets(cnpj,sizeof(cnpj),stdin);
            check_newline(cnpj);
        }while(0/*validarCNPJ(cnpj)==0*/);

        if(pesquisa_frncdr_CNPJ(arq,cnpj)==-1){
            strcpy(new.cnpj, cnpj);
			printf("valor que será inserido: %s",new.cnpj); //TESTING PURPOSES
            printf("\nDigite o nome do fornecedor: ");
			setbuf(stdin,NULL);
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
			printf("valor que será inserido: %s",new.nome); //TESTING PURPOSES
            printf("\nDigite o email do fornecedor: ");
			setbuf(stdin,NULL);
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
			printf("valor que será inserido: %s",new.email); //TESTING PURPOSES
            printf("\nDigite o telefone do fornecedor: ");
			setbuf(stdin,NULL);
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("valor que será inserido: %s",new.telefone); //TESTING PURPOSES
            setbuf(stdin,NULL);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(fornecedor),1,arq);
        }
        else
            printf("\nCNPJ já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Cliente?\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
    }while(sair!=2);
}

void listar_fornecedores(FILE *arq){
    fornecedor r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Clientes");
    printf("\nID\t\tNOME\t\t\t\tCNPJ\t\tEMAIL\t\t\tTELEFONE");
    while(fread(&r,sizeof(cliente),1,arq))
        printf("\n%lu\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s",r.id,r.nome,r.cnpj,r.email,r.telefone);
}

int pesquisa_frncdr_CNPJ(FILE *arq,char* cnpj){
    fornecedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(fornecedor),1,arq)==1){
    	if(strcmp(r.cnpj,cnpj)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

