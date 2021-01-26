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
			printf("Valor da ID: %lu",new.id);
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