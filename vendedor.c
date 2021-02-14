#include <stdio.h>
#include <string.h>
#include "vendedor.h"
#include "structDeclarations.h"
#include "utility.h"

void cadastro_vendedor(FILE *arq, int *id)
{
    char cpf[12];
    int sair = 1;
    Vendedor new;
    
    do{
        do{
            printf("\nDigite o CPF do vendedor a ser cadastrado: ");
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        if(pesquisa_vnddr_CPF(arq,cpf)==-1){
            strcpy(new.cpf, cpf);
            printf("\nDigite a matricula do vendedor: ");
            fgets(new.matricula, sizeof(new.matricula),stdin);
            check_newline(new.matricula);
            format_string(new.matricula);
            printf("\nDigite o nome do vendedor: ");
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
            format_string(new.nome);
            printf("\nDigite o email do vendedor: ");
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
            format_string(new.email);
            printf("\nDigite o telefone do vendedor: ");
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
            printf("\nDigite a senha do vendedor: ");
            fgets(new.password, sizeof(new.password),stdin);
            check_newline(new.password);
            format_string(new.password);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(Vendedor),1,arq);
        }
        else
            printf("\nCPF já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Vendedor?\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair!=2);
}

void listar_vendedores(FILE *arq)
{
    Vendedor r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Vendedores");
    printf("\nID\t\tMATRICULA\t\tNOME\t\t\t\tCPF\t\tEMAIL\t\t\tTELEFONE\t\t\tSENHA:");
    while(fread(&r,sizeof(Vendedor),1,arq))
        printf("\n%lu\t\t%s\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s\t\t\t%s",r.id,r.matricula,r.nome,r.cpf,r.email,r.telefone,r.password);
}

int pesquisa_vnddr_CPF(FILE *arq,char* cpf)
{
   	Vendedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(Vendedor),1,arq)==1){
    	if(strcmp(r.cpf,cpf)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

int pesquisa_vnddr_ID(FILE *arq,unsigned long id)
{
   	Vendedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(Vendedor),1,arq)==1){
    	if(r.id == id)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

void alteracao_vendedor(FILE *arq){
    char cpf[12];
    int sair = 1, posicao;
    Vendedor new;
    
    do{
        do{
            printf("\nDigite o CPF do vendedor o qual o cadastro deverá ser alterado: ");
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        posicao = pesquisa_vnddr_CPF(arq,cpf);
        
        if(posicao!=-1){
            fseek(arq,posicao*sizeof(Vendedor),SEEK_SET);
            fread(&new,sizeof(Vendedor),1,arq);
            strcpy(new.cpf, cpf);
            printf("\nDigite a matricula do vendedor: ");
            fgets(new.matricula, sizeof(new.matricula),stdin);
            check_newline(new.matricula);
            format_string(new.matricula);
            printf("\nDigite o nome do vendedor: ");
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
            format_string(new.nome);
            printf("\nDigite o email do vendedor: ");
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
            format_string(new.email);
            printf("\nDigite o telefone do vendedor: ");
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
            printf("\nDigite a senha do vendedor: ");
            fgets(new.password, sizeof(new.password),stdin);
            check_newline(new.password);
            format_string(new.password);
			printf("\nValor da ID: %lu",new.id);
            fseek(arq,posicao*sizeof(Vendedor),SEEK_SET);
            fwrite(&new,sizeof(Vendedor),1,arq);
        }
        else
            printf("\nCPF não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Ateração? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_vnddr_CPF(FILE *arq){
    char cpf[12];
    int sair = 1, posicao;
    Vendedor search;
    
    do{
        do{
            printf("\nDigite o CPF do Vendedor o qual o deseja CONSULTAR: ");
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        posicao = pesquisa_vnddr_CPF(arq,cpf);
        
        if(posicao!=-1){
            printf("\nRegistro encontrado!!");

            fseek(arq,posicao*sizeof(Vendedor),SEEK_SET);
            fread(&search,sizeof(Vendedor),1,arq);
            
			printf("\nCPF do Vendedor: %s",search.cpf); 
            printf("\nMatricula do Vendedor: %s",search.matricula); 
			printf("\nNome do Vendedor: %s",search.nome); 
			printf("\nEMAIL do Vendedor: %s",search.email); 
			printf("\nTelefone do Vendedor: %s",search.telefone); 
            printf("\nSenha do Vendedor: %s",search.password); 
			printf("\nID do Vendedor: %lu",search.id);
        }
        else
            printf("\nCPF não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_vnddr_ID(FILE *arq){
    unsigned long id;
    int sair = 1, posicao;
    Vendedor search;
    do{
        printf("\nDigite a ID do Vendedor o qual deseja CONSULTAR: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);

        posicao = pesquisa_vnddr_ID(arq,id);
        
        if(posicao!=-1){
            printf("\nRegistro encontrado!!");
            
            fseek(arq,posicao*sizeof(Vendedor),SEEK_SET);
            fread(&search,sizeof(Vendedor),1,arq);
            
			printf("\nCPF do Vendedor: %s",search.cpf); 
            printf("\nMatricula do Vendedor: %s",search.matricula); 
			printf("\nNome do Vendedor: %s",search.nome); 
			printf("\nEMAIL do Vendedor: %s",search.email); 
			printf("\nTelefone do Vendedor: %s",search.telefone); 
            printf("\nSenha do Vendedor: %s",search.password); 
			printf("\nID do Vendedor: %lu",search.id);
        }
        else
            printf("\nID não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_vnddr_INI(FILE *arq){
    char ini[4];
    int sair = 1,count;
    Vendedor search;
    
    do
    {
        printf("\nDigite as 3 primeiras letras do nome do Vendedor \no qual deseja CONSULTAR : ");
        fgets(ini,sizeof(ini),stdin);
        check_newline(ini);
        format_string(ini);
        
        count = 0;
        fseek(arq,0,SEEK_SET);

        while(fread(&search,sizeof(Vendedor),1,arq)==1)
        {
    	    if(strncmp(search.nome,ini,3)==0)
            {
                printf("\n\nNome do Vendedor: %s",search.nome);
                printf("\nCPF do Vendedor: %s",search.cpf); 
			    printf("\nEMAIL do Vendedor: %s",search.email); 
			    printf("\nTelefone do Vendedor: %s",search.telefone);
                printf("\nMatricula do Vendedor: %s",search.matricula);  
			    printf("\nID do Vendedor: %lu",search.id);
                printf("\nSenha do Vendedor: %s",search.password); 
                count++;
            }
        }
        if(count==0)
            printf("\n\nNão existem Vendedores que possuem esse prefixo...");
        printf("\n\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=1);
    
}

int login_vendedor(FILE *arq,char *cpf, char* password)
{
    int posicao = pesquisa_vnddr_CPF(arq,cpf);
    Vendedor search;
    
    if(posicao!=-1){
        fseek(arq,posicao*sizeof(Vendedor),SEEK_SET);
        fread(&search,sizeof(Vendedor),1,arq);
        if(strcmp(search.password,password)==0)
            return posicao;
        else
        {
            printf("\nSenha incorreta!!");
            return posicao;
        }
    }
    else
    {
        printf("\nCPF incorreto!!");
        return posicao;
    }
}

