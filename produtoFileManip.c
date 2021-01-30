#include <stdio.h>
#include <string.h>
#include "structDeclarations.h"
#include "produtoFileManip.h"
#include "utilityFunctions.h"

void cadastro_produto(FILE* arq, int *id)
{
    int sair = 1;
    Produto new;

    do
    {
        setbuf(stdin,NULL);
        printf("\nDigite o nome do Produto que será cadastrado: ");
        fgets(new.nome,sizeof(new.nome),stdin);
        check_newline(new.nome);
        printf("\nDigite o Preco da unidade: ");
        scanf("%f",&new.precoUnitario);
        setbuf(stdin,NULL);
        new.quantidadeEstoque = 0;
        new.id = *id;
        (*id)++;
        printf("\nDeseja Sair do Cadastro de Produtos?? 1->SIM 2->NÃO ");
        scanf("%d",&sair);
    } while (sair!=1);
    

}