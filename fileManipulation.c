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
            printf("Digite o CPF do cliente a ser cadastrado: ");
            fgets(cpf,sizeof(cpf),stdin);
            newline_remover(cpf);
            setbuf(stdin,NULL);
        }while(validarCPF(cpf)==0);
    
        if(1/* Função consulta/pesquisa CPF aqui no lugar do "1" */){
            strcpy(new.cpf, cpf);
            printf("\nDigite o nome do cliente: ");
            fgets(new.nome, sizeof(new.nome),stdin);
            newline_remover(new.nome);
            setbuf(stdin,NULL);
            printf("\nDigite o email do cliente: ");
            fgets(new.email, sizeof(new.email),stdin);
            newline_remover(new.email);
            setbuf(stdin,NULL);
            printf("\nDigite o telefone do cliente");
            fgets(new.telefone, sizeof(new.telefone),stdin);
            newline_remover(new.telefone);
            setbuf(stdin,NULL);
            new.id = id;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(cliente),1,arq);
        }
        else
            printf("\nCPF já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Cliente?\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
    }while(sair!=2);
}
