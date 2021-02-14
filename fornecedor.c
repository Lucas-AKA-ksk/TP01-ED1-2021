#include <stdio.h>
#include <string.h>
#include "fornecedor.h"
#include "structDeclarations.h"
#include "utility.h"

void cadastro_fornecedor(FILE *arq, int *id){
    char cnpj[15];
    int sair = 1;
    Fornecedor new;
    
    do{
        do{
            printf("\nDigite o CNPJ do fornecedor a ser cadastrado: ");
            fgets(cnpj,sizeof(cnpj),stdin);
            check_newline(cnpj);
        }while(validarCNPJ(cnpj)==0);

        if(pesquisa_frncdr_CNPJ(arq,cnpj)==-1){
            strcpy(new.cnpj, cnpj);
            printf("\nDigite o nome do fornecedor: ");
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
            format_string(new.nome);
            printf("\nDigite o email do fornecedor: ");
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
            format_string(new.email);
            printf("\nDigite o telefone do fornecedor: ");
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(Fornecedor),1,arq);
        }
        else
            printf("\nCNPJ já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Fornecedor\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair!=2);
}

void listar_fornecedores(FILE *arq){
    Fornecedor r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Clientes");
    printf("\nID\t\tNOME\t\t\t\tCNPJ\t\tEMAIL\t\t\tTELEFONE");
    while(fread(&r,sizeof(Fornecedor),1,arq))
        printf("\n%lu\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s",r.id,r.nome,r.cnpj,r.email,r.telefone);
}

int pesquisa_frncdr_CNPJ(FILE *arq,char* cnpj){
    Fornecedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(Fornecedor),1,arq)==1){
    	if(strcmp(r.cnpj,cnpj)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

int pesquisa_frncdr_ID(FILE *arq,unsigned long id){
   	Fornecedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(Fornecedor),1,arq)==1){
    	if(r.id == id)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}

void alteracao_fornecedor(FILE *arq){
    char cnpj[15];
    int sair = 1, posicao;
    Fornecedor new;
    
    do{
        do{
            printf("\nDigite o CNPJ do fornecedor o qual o cadastro deverá ser alterado: ");
            fgets(cnpj,sizeof(cnpj),stdin);
            check_newline(cnpj);
        }while(validarCNPJ(cnpj)==0);

        posicao = pesquisa_frncdr_CNPJ(arq,cnpj);
        
        if(posicao!=-1){
            fseek(arq,posicao*sizeof(Fornecedor),SEEK_SET);
            fread(&new,sizeof(Fornecedor),1,arq);
            strcpy(new.cnpj, cnpj);
            printf("\nDigite o nome do fornecedor: ");
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
            format_string(new.nome);
            printf("\nDigite o email do fornecedor: ");
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
            format_string(new.email);
            printf("\nDigite o telefone do fornecedor: ");
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("\nValor da ID: %lu",new.id);
            fseek(arq,posicao*sizeof(Fornecedor),SEEK_SET);
            fwrite(&new,sizeof(Fornecedor),1,arq);
        }
        else
            printf("\nCNPJ não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Ateração? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_frncdr_CPF(FILE *arq){
    char cnpj[15];
    int sair = 1, posicao;
    Fornecedor search;
    
    do{
        do{
            printf("\nDigite o CNPJ do Fornecedor o qual deseja CONSULTAR: ");
            fgets(cnpj,sizeof(cnpj),stdin);
            check_newline(cnpj);
        }while(validarCNPJ(cnpj)==0);

        posicao = pesquisa_frncdr_CNPJ(arq,cnpj);
        
        if(posicao!=-1){
            printf("\nRegistro encontrado!!");

            fseek(arq,posicao*sizeof(Fornecedor),SEEK_SET);
            fread(&search,sizeof(Fornecedor),1,arq);
			
            printf("\nCNPJ do Fornecedor: %s",search.cnpj); 
			printf("\nNome do Fornecedor: %s",search.nome); 
			printf("\nEMAIL do Fornecedor: %s",search.email); 
			printf("\nTelefone do Fornecedor: %s",search.telefone); 
			printf("\nID do Fornecedor: %lu",search.id);
        }
        else
            printf("\nCNPJ não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Ateração? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_frncdr_ID(FILE *arq){
    unsigned long id;
    int sair = 1, posicao;
    Fornecedor search;
    do{
        printf("\nDigite a ID do Fornecedor o qual deseja CONSULTAR: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);

        posicao = pesquisa_frncdr_ID(arq,id);
        
        if(posicao!=-1){
            printf("\nRegistro encontrado!!");

            fseek(arq,posicao*sizeof(Fornecedor),SEEK_SET);
            fread(&search,sizeof(Fornecedor),1,arq);
			
            printf("\nCNPJ do Fornecedor: %s",search.cnpj);
			printf("\nNome do Fornecedor: %s",search.nome);
			printf("\nEMAIL do Fornecedor: %s",search.email);
			printf("\nTelefone do Fornecedor: %s",search.telefone);
			printf("\nID do Fornecedor: %lu",search.id);
        }
        else
            printf("\nID não Cadastrado no Registro, operação cancelada!!!");

        printf("\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while(sair !=1);
}

void consulta_frncdr_INI(FILE *arq){
    char ini[4];
    int sair = 1,count;
    Fornecedor search;
    
    do
    {
        printf("\nDigite as 3 primeiras letras do nome do Fornecedor \no qual deseja CONSULTAR : ");
        fgets(ini,sizeof(ini),stdin);
        check_newline(ini);
        format_string(ini);
        
        count = 0;
        fseek(arq,0,SEEK_SET);

        while(fread(&search,sizeof(Fornecedor),1,arq)==1)
        {
    	    if(strncmp(search.nome,ini,3)==0)
            {
                printf("\n\nNome do Vendedor: %s",search.nome);
                printf("\nCPF do Vendedor: %s",search.cnpj); 
			    printf("\nEMAIL do Vendedor: %s",search.email); 
			    printf("\nTelefone do Vendedor: %s",search.telefone);
			    printf("\nID do Vendedor: %lu",search.id);
                count++;
            }
        }
        if(count==0)
            printf("\n\nNão existem Fornecedores que possuem esse prefixo...");
        printf("\n\nDeseja Sair da Consulta? 1-Sim 2-Não");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=1);
    
}

