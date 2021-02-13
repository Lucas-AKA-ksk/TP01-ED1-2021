#include <stdio.h>
#include <string.h>
#include "structDeclarations.h"
#include "produto.h"
#include "utility.h"

void cadastro_produto(FILE* arq, int *id)
{
    int sair = 1;
    Produto new;

    do
    {
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
        setbuf(stdin,NULL);
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

void atualizar_preco(FILE *arqC, FILE *arqH, int posicao, float mult)
{
    historicoPreco h;
    Produto p;

    fseek(arqC,posicao*sizeof(Produto),SEEK_SET);
    fread(&p,sizeof(Produto),1,arqC);

    h.idProduto = p.id;
    get_sys_date(h.dataAlteracao,sizeof(h.dataAlteracao));
    h.valor = p.precoUnitario;
    fseek(arqH,0,SEEK_END);
    fwrite(&h,sizeof(historicoPreco),1,arqH);

    printf("\nPreço antes da alteração: %.2f",p.precoUnitario); //Testing purposes
    p.precoUnitario += p.precoUnitario*mult;
    printf("\nPreço depois da alteração: %.2f",p.precoUnitario); //Testing purposes

    fseek(arqC,posicao*sizeof(Produto),SEEK_SET);
    fwrite(&p,sizeof(Produto),1,arqC);
}

void reajuste_preco_individual(FILE *arqC,FILE *arqH)
{
    int sair, posicao;
    unsigned long id;
    float mult;
    do
    {
        printf("\nDigite a ID do produto: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);

        posicao = pesquisa_prdt(arqC,id);

        if(posicao!=-1)
        {
            printf("\nDigite a porcentagem do reajuste(EX: 0,1 = 10%%): ");
            scanf("%f",&mult);
            setbuf(stdin,NULL);
            atualizar_preco(arqC,arqH,posicao,mult);
        }
        else
            printf("\nNenhum produto corresponde a ID fornecida!!");
        printf("\nDeseja Sair da Att de Produtos?? 1->SIM 2->NÃO ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=1);
    
}

void reajuste_preco_all(FILE *arqC, FILE *arqH)
{
    float mult;
    int id = 1, posicao;
    printf("\nDigite a porcentagem do reajuste(EX: 0,1 = 10%%): ");
    scanf("%f",&mult);
    setbuf(stdin,NULL);
    while ((posicao=pesquisa_prdt(arqC,id))!=-1)
    {
        atualizar_preco(arqC,arqH,posicao,mult);
        id++;
    }
}