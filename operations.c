#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "structDeclarations.h"
#include "utilityFunctions.h"
#include "produtoFileManip.h"
#include "clienteFileManip.h"
#include "vendedorFileManip.h"

void realizar_venda(FILE *arqVnddr,FILE *arqClnt,FILE *arqProd, FILE *arqNF, FILE *arqINF, int *idNota, int *idItem)
{
    char cpf[12], password[20];
    int sair, mudarCliente,fecharVenda, posicaoV, posicaoC, posicaoP;
    unsigned long id;
    Vendedor login;
    
    do
    {
        printf("\nDigite o CPF do VENDEDOR: ");
		setbuf(stdin,NULL);
        fgets(cpf,sizeof(cpf),stdin);
        check_newline(cpf);
        printf("\nDigite a SENHA do VENDEDOR: ");
		setbuf(stdin,NULL);
        fgets(password,sizeof(password),stdin);
        check_newline(password);
        
        posicaoV = login_vendedor(arqVnddr,cpf,password);
    
        if (posicaoV!=-1) /* Caso o cadastro(CPF) exista e a senha esteja correta */
        {
            printf("\nLogin efetuado com sucesso!!");
            fseek(arqVnddr,posicaoV*sizeof(Vendedor),SEEK_SET);
            fread(&login,sizeof(Vendedor),1,arqVnddr);
            do
            {
                printf("\nDigite a ID do CLIENTE: ");
		        setbuf(stdin,NULL);
                scanf("%lu",&id);
                
                posicaoC = pesquisa_clnt_ID(arqClnt,id);

                if (posicaoC!=-1) /* Caso o Cliente esteja cadastrado */
                {
                    NotaFiscal NF;
                    ItemNotaFiscal INF;
                    Produto p;
                    Carrinho *C;
                    int cartPos = 0, cIndex, i, dateChoice, auxQTD;
                    unsigned long idOut;
                    float auxVT;

                    C = (Carrinho*)malloc(sizeof(Carrinho));
                    
                    do /* Menu de operações do carrinho */
                    {
                        printf("\n\n\tSelecione qual tipo de operação deseja realizar:");
                        printf("\n\t1->Adicionar item ao carrinho\t2->Remover item do carrinho\n\t3->Alterar quantidade\t4->Concluir a venda\n\t0->Cancelar a venda atual");
                        printf("\n\nOpção selecionada: ");
                        scanf("%d", &fecharVenda);


                        switch (fecharVenda)
                        {
                        case 0: /* Cancelamento da venda */
                            printf("\nCOMPRA CANCELADA!!!");
                            free(C);
                            break;
                        
                        case 1:/* Adicionar Produto ao carrinho */

                            if(cartPos>0)
                                C = (Carrinho*)realloc(C,(cartPos+1)*sizeof(Carrinho));
                                
                            printf("\nDigite a id do Produto a ser vendido: ");
                            setbuf(stdin,NULL);
                            scanf("%lu",&C[cartPos].idProduto);

                            posicaoP = pesquisa_prdt(arqProd,C[cartPos].idProduto);

                            if(posicaoP!=-1) /* Caso o produto esteja Cadastrado */
                            {
                                if (pesquisa_carrinho(C,cartPos,C[cartPos].idProduto)==-1) /* Caso o produto não esteja no carrinho */
                                {
                                    fseek(arqProd,posicaoP*sizeof(Produto),SEEK_SET);
                                    fread(&p,sizeof(Produto),1,arqProd);

                                    printf("\nDigite a quantidade a ser vendido: ");
                                    setbuf(stdin,NULL);
                                    scanf("%d",&C[cartPos].quantidadeVendida);

                                    if (p.quantidadeEstoque>=C[cartPos].quantidadeVendida) /* Caso exista estoque o suficiente de dado Produto */
                                    {
                                        C[cartPos].valorVenda = C[cartPos].quantidadeVendida*p.precoUnitario;
                                        atualizar_estoque(arqProd,posicaoP,-C[cartPos].quantidadeVendida);
                                        cartPos++;
                                    }
                                    else
                                        printf("\nEstoque insuficiente para a quantidade desejada!!");
                                }
                                else
                                    printf("\nEste produto já está no carrinho...\nCaso queira, altere a quantidade do mesmo...");   
                            }
                            else
                                printf("\nNenhum produto corresponde a ID fornecida!!");

                            break;
                        
                        case 2: /* Remoção de itens do carrinho */
                            
                            if(cartPos==0)
                            {
                                printf("\nO carrinho está vazio!!");
                                break;
                            }
                            else
                            {
                                printf("\nDigite a id do Produto a ser removido: ");
                                setbuf(stdin,NULL);
                                scanf("%lu",&idOut);

                                cIndex = pesquisa_carrinho(C,cartPos,idOut);

                                if (cIndex!=-1 && idOut!=0)
                                {
                                    atualizar_estoque(arqProd,C[cIndex].idProduto-1,C[cIndex].quantidadeVendida);
                                    C[cIndex].idProduto=0;
                                    printf("\nProduto Removido!");
                                }
                                    
                                else
                                    printf("\nNão há Produtos deste tipo no carrinho...");
                                
                            }    
                            break;
                        
                        case 3: /* Alterar quantidade */
                            if(cartPos==0)
                            {
                                printf("\nO carrinho está vazio!!");
                                break;
                            }
                            else
                            {
                                printf("\nDigite a id do Produto o qual queira alterar a qtde: ");
                                setbuf(stdin,NULL);
                                scanf("%lu",&idOut);
                                
                                posicaoP = pesquisa_prdt(arqProd,idOut);

                                if (posicaoP!=-1) /* Se a ID está cadastrada */
                                {
                                    cIndex = pesquisa_carrinho(C,cartPos,idOut);

                                    if (cIndex!=-1 && idOut!=0) /* Se o produto correspondente a ID fornecida está no carrinho */
                                    {
                                        fseek(arqProd,posicaoP*sizeof(Produto),SEEK_SET);
                                        fread(&p,sizeof(Produto),1,arqProd);
                                    
                                        printf("\nDigite a nova quantidade a ser vendida: ");
                                        setbuf(stdin,NULL);
                                        scanf("%d",&auxQTD);

                                        if ((p.quantidadeEstoque+C[cIndex].quantidadeVendida)>=auxQTD) /* Caso exista estoque o suficiente de dado Produto */
                                        {
                                            C[cIndex].valorVenda = auxQTD*p.precoUnitario;
                                            if(auxQTD>C[cIndex].quantidadeVendida)
                                                atualizar_estoque(arqProd,posicaoP,-(auxQTD-C[cIndex].quantidadeVendida));
                                            else if (auxQTD<=C[cIndex].quantidadeVendida)
                                                atualizar_estoque(arqProd,posicaoP,(C[cIndex].quantidadeVendida-auxQTD));
                                            C[cIndex].quantidadeVendida=auxQTD;
                                            
                                        }
                                        else
                                            printf("\nEstoque insuficiente para a quantidade desejada!!");

                                    }
                                    else
                                        printf("\nNão há Produtos deste tipo no carrinho...");
                                }
                                else
                                    printf("\nNenhum produto corresponde a ID fornecida!!");
                            } 
                            break;


                        case 4: /* Fechamento da venda */
                            
                            if(cartPos>0) /* O fechamento só pode ocorrer se houver ao menos um item no carrinho */
                            {
                                    i = 0;
                                auxVT = 0;

                                while(i<=cartPos){
                                    if(C[i].idProduto!=0) /* Se o idProduto não for 0 (valor que representa item removido)*/
                                    {
                                        INF.id = *idItem;
                                        (*idItem)++;
                                        INF.idNota = *idNota;
                                        INF.idProduto = C[i].idProduto;
                                        INF.precoUnitario = C[i].valorVenda/C[i].quantidadeVendida;
                                        INF.quantidade = C[i].quantidadeVendida;
                                        auxVT+=C[i].valorVenda;
                                        fseek(arqINF,0,SEEK_END);
                                        fwrite(&INF,sizeof(ItemNotaFiscal),1,arqINF); 
                                    }
                                    i++;
                                }

                                NF.id = *idNota;
                                (*idNota)++;
                                NF.idCliente = id;
                                NF.idVendedor = login.id;
                                NF.valorTotal = auxVT;
                                do
                                {
                                    printf("\nDeseja Digitar a Data da compra manualmente ou pega-la do sistema?\n\n1->Digitar manualmente\t2->Obter data do sistema\n\nEscolha: ");
                                    setbuf(stdin,NULL);
                                    scanf("%d",&dateChoice);

                                    switch (dateChoice)
                                    {
                                    case 1: /* Digitar a data manualmente */
                                        /* code */
                                        break;
                            
                                    case 2: /* Obter data do sistema */
                                        /* code */
                                        break;

                                    default:
                                        printf("\nDigite um valor Valido!!\n");
                                        break;
                                    }

                                }while(dateChoice!=1 && dateChoice!=2);


                                fseek(arqNF,0,SEEK_END);
                                fwrite(&NF,sizeof(NotaFiscal),1,arqNF);

                                free(C);
                                fecharVenda = 0;
                            }
                            else
                                printf("\nImpossivel finalizar a compra de um carrinho que esta vazio.\nAdicione itens ou cancele a compra...");
                                
                            break;

                        default:
                            printf("\nDigite um valor valido para realizar uma operação.\n");
                            break;
                        }
                    
                    } while (fecharVenda!=0);
                    
                }
                
                printf("\nDeseja Realizar outra venda? 1->SIM\t2->NÃO");
                setbuf(stdin,NULL);
                scanf("%d",&mudarCliente);
            } while (mudarCliente!=2);
            
        }
        else
            printf("\nInformações incorretas!! Operação Cancelada...");
        
        printf("\nDeseja Logar como outro vendedor ou retornar ao menu? 1->Logar novamente\t2->Sair");
        setbuf(stdin,NULL);
        scanf("%d", &sair);
    } while (sair!=2);
}

int pesquisa_carrinho(Carrinho *c, int size, unsigned int id){
    
    int i = 0;

    while(i<size)
    {
        if(c[i].idProduto==id)
        {
            return i;
        }
        i++;
    }
    return -1;
}