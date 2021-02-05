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
        fseek(arq,0,SEEK_END);
        fwrite(&new,sizeof(Produto),1,arq);
        printf("\nDeseja Sair do Cadastro de Produtos?? 1->SIM 2->NÃO ");
        scanf("%d",&sair);
    } while (sair!=1);
    

}

int pesquisa_prdt(FILE *arq,unsigned long id)
{
    Produto r;
    int posicao=0;
    fseek(arq,0,SEEK_SET);

    while(fread(&r,sizeof(Produto),1,arq)==1)
    {
        if(r.id==id)
            return posicao;
        else
            posicao++;

    }
    return -1;
}

void atualizar_estoque(FILE *arq, int posicao, int qtd)
{
    Produto p;
    fseek(arq,posicao*sizeof(Produto),SEEK_SET);
    fread(&p,sizeof(Produto),1,arq);

    printf("\nEstoque atual: %d",p.quantidadeEstoque); //Testing purposes

    p.quantidadeEstoque = p.quantidadeEstoque + qtd;

    printf("\nEstoque após att: %d",p.quantidadeEstoque); //Testing purposes

    fseek(arq,posicao*sizeof(Produto),SEEK_SET);
    fwrite(&p,sizeof(Produto),1,arq);
}