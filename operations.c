#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "structDeclarations.h"
#include "utility.h"
#include "produto.h"
#include "cliente.h"
#include "vendedor.h"
#include "fornecedor.h"

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
                scanf("%lu",&id);
                setbuf(stdin,NULL);
                
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
                        setbuf(stdin,NULL);


                        switch (fecharVenda)
                        {
                        case 0: /* Cancelamento da venda */
                            printf("\nVENDA CANCELADA!!!");
                            free(C);
                            break;
                        
                        case 1:/* Adicionar Produto ao carrinho */

                            if(cartPos>0)
                                C = (Carrinho*)realloc(C,(cartPos+1)*sizeof(Carrinho));
                                
                            printf("\nDigite a id do Produto a ser vendido: ");
                            scanf("%lu",&C[cartPos].idProduto);
                            setbuf(stdin,NULL);

                            posicaoP = pesquisa_prdt(arqProd,C[cartPos].idProduto);

                            if(posicaoP!=-1) /* Caso o produto esteja Cadastrado */
                            {
                                if (pesquisa_carrinho(C,cartPos,C[cartPos].idProduto)==-1) /* Caso o produto não esteja no carrinho */
                                {
                                    fseek(arqProd,posicaoP*sizeof(Produto),SEEK_SET);
                                    fread(&p,sizeof(Produto),1,arqProd);

                                    printf("\nDigite a quantidade a ser vendido: ");
                                    scanf("%d",&C[cartPos].quantidadeVendida);
                                    setbuf(stdin,NULL);

                                    if (p.quantidadeEstoque>=C[cartPos].quantidadeVendida) /* Caso exista estoque o suficiente de dado Produto */
                                    {
                                        C[cartPos].valorVenda = C[cartPos].quantidadeVendida*p.precoUnitario;
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
                                scanf("%lu",&idOut);
                                setbuf(stdin,NULL);

                                cIndex = pesquisa_carrinho(C,cartPos,idOut);

                                if (cIndex!=-1 && idOut!=0)
                                {
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
                                scanf("%lu",&idOut);
                                setbuf(stdin,NULL);
                                
                                posicaoP = pesquisa_prdt(arqProd,idOut);

                                if (posicaoP!=-1) /* Se a ID está cadastrada */
                                {
                                    cIndex = pesquisa_carrinho(C,cartPos,idOut);

                                    if (cIndex!=-1 && idOut!=0) /* Se o produto correspondente a ID fornecida está no carrinho */
                                    {
                                        fseek(arqProd,posicaoP*sizeof(Produto),SEEK_SET);
                                        fread(&p,sizeof(Produto),1,arqProd);
                                    
                                        printf("\nDigite a nova quantidade a ser vendida: ");
                                        scanf("%d",&auxQTD);
                                        setbuf(stdin,NULL);

                                        if (p.quantidadeEstoque>=auxQTD) /* Caso exista estoque o suficiente de dado Produto */
                                        {
                                            C[cIndex].valorVenda = auxQTD*p.precoUnitario;
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

                                while(i<cartPos){
                                    if(C[i].idProduto!=0) /* Se o idProduto não for 0 (valor que representa item removido)*/
                                    {
                                        INF.id = *idItem;
                                        (*idItem)++;
                                        INF.idNota = *idNota;
                                        INF.idProduto = C[i].idProduto;
                                        INF.precoUnitario = C[i].valorVenda/C[i].quantidadeVendida;
                                        INF.quantidade = C[i].quantidadeVendida;
                                        auxVT+=C[i].valorVenda;
                                        atualizar_estoque(arqProd,C[i].idProduto-1,-C[i].quantidadeVendida);
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
                                    scanf("%d",&dateChoice);
                                    setbuf(stdin,NULL);

                                    switch (dateChoice)
                                    {
                                    case 1: /* Digitar a data manualmente */
                                        printf("\nDigite uma data válida no formato \"dd/mm/aaaa\": ");
                                        fgets(NF.dataCompra,sizeof(NF.dataCompra),stdin);
                                        check_newline(NF.dataCompra);
                                        if(verify_date(NF.dataCompra)==0)
                                            dateChoice = 0;

                                        break;
                            
                                    case 2: /* Obter data do sistema */
                                        get_sys_date(NF.dataCompra,sizeof(NF.dataCompra));
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
                scanf("%d",&mudarCliente);
                setbuf(stdin,NULL);
            } while (mudarCliente!=2);
            
        }
        else
            printf("\nInformações incorretas!! Operação Cancelada...");
        
        printf("\nDeseja Logar como outro vendedor ou retornar ao menu? 1->Logar novamente\t2->Sair");
        scanf("%d", &sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
}

void realizar_compra(FILE *arqForn,FILE *arqProd, FILE *arqNC, FILE *arqINC, int *idNota, int *idItem)
{
    int posicaoF,posicaoP;
    unsigned long id;
    
    printf("\nDigite a ID do FORNECEDOR: ");
    scanf("%lu",&id);
    setbuf(stdin,NULL);
                
    posicaoF = pesquisa_frncdr_ID(arqForn,id);

    if (posicaoF!=-1) /* Caso o Fornecedor esteja cadastrado */
    {
        NotaCompra NC;
        ItemNotaCompra INC;
        Produto p;
        Carrinho *C;
        int cartPos = 0, pIndex, i, dateChoice, auxQTD, fecharVenda;
        unsigned long idOut;
        float auxVT;

        C = (Carrinho*)malloc(sizeof(Carrinho));
                    
        do /* Menu de operações do carrinho */
        {
            printf("\n\n\tSelecione qual tipo de operação deseja realizar:");
            printf("\n\t1->Adicionar item ao carrinho\t2->Remover item do carrinho\n\t3->Alterar quantidade\t4->Concluir a compra\n\t0->Cancelar a compra atual");
            printf("\n\nOpção selecionada: ");
            scanf("%d", &fecharVenda);


            switch (fecharVenda)
            {
            case 0: /* Cancelamento da compra */
                printf("\nCOMPRA CANCELADA!!!");
                free(C);
                break;
                        
            case 1:/* Adicionar Produto ao carrinho */

                if(cartPos>0)
                    C = (Carrinho*)realloc(C,(cartPos+1)*sizeof(Carrinho));
                    
                printf("\nDigite a id do Produto a ser vendido: ");
                scanf("%lu",&C[cartPos].idProduto);
                setbuf(stdin,NULL);

                posicaoP = pesquisa_prdt(arqProd,C[cartPos].idProduto);

                if(posicaoP!=-1) /* Caso o produto esteja Cadastrado */
                {
                    if (pesquisa_carrinho(C,cartPos,C[cartPos].idProduto)==-1) /* Caso o produto não esteja no carrinho */
                    {
                        fseek(arqProd,posicaoP*sizeof(Produto),SEEK_SET);
                        fread(&p,sizeof(Produto),1,arqProd);

                        printf("\nDigite a quantidade a ser comprado: ");
                        scanf("%d",&C[cartPos].quantidadeVendida);
                        setbuf(stdin,NULL);

                        C[cartPos].valorVenda = C[cartPos].quantidadeVendida*p.precoUnitario;
                        cartPos++;

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
                    scanf("%lu",&idOut);
                    setbuf(stdin,NULL);

                    pIndex = pesquisa_carrinho(C,cartPos,idOut);

                    if (pIndex!=-1 && idOut!=0)
                    {
                        C[pIndex].idProduto=0;
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
                    scanf("%lu",&idOut);
                    setbuf(stdin,NULL);
                                
                    posicaoP = pesquisa_prdt(arqProd,idOut);

                    if (posicaoP!=-1) /* Se a ID está cadastrada */
                    {
                        pIndex = pesquisa_carrinho(C,cartPos,idOut);

                        if (pIndex!=-1 && idOut!=0) /* Se o produto correspondente a ID fornecida está no carrinho */
                        {
                            fseek(arqProd,posicaoP*sizeof(Produto),SEEK_SET);
                            fread(&p,sizeof(Produto),1,arqProd);
                                    
                            printf("\nDigite a nova quantidade a ser comprada: ");
                            scanf("%d",&auxQTD);
                            setbuf(stdin,NULL);

                            C[pIndex].valorVenda = auxQTD*p.precoUnitario;
                            C[pIndex].quantidadeVendida=auxQTD;
                                            
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

                    while(i<cartPos){
                        if(C[i].idProduto!=0) /* Se o idProduto não for 0 (valor que representa item removido)*/
                        {
                            INC.id = *idItem;
                            (*idItem)++;
                            INC.idNotaCompra = *idNota;
                            INC.idProduto = C[i].idProduto;
                            INC.valorUnitario = C[i].valorVenda/C[i].quantidadeVendida;
                            INC.quantidade = C[i].quantidadeVendida;
                            auxVT+=C[i].valorVenda;
                            atualizar_estoque(arqProd,C[i].idProduto-1,C[i].quantidadeVendida);
                            fseek(arqINC,0,SEEK_END);
                            fwrite(&INC,sizeof(ItemNotaCompra),1,arqINC); 
                        }
                        i++;
                    }

                    NC.id = *idNota;
                    (*idNota)++;
                    NC.idFornecedor = id;
                    NC.valorTotal = auxVT;
                    do
                    {
                        printf("\nDeseja Digitar a Data da compra manualmente ou pega-la do sistema?\n\n1->Digitar manualmente\t2->Obter data do sistema\n\nEscolha: ");
                        scanf("%d",&dateChoice);
                        setbuf(stdin,NULL);

                        switch (dateChoice)
                        {
                        case 1: /* Digitar a data manualmente */
                            printf("\nDigite uma data válida no formato \"dd/mm/aaaa\": ");
                            fgets(NC.dataCompra,sizeof(NC.dataCompra),stdin);
                            check_newline(NC.dataCompra);
                            if(verify_date(NC.dataCompra)==0)
                                dateChoice = 0;

                            break;
                            
                        case 2: /* Obter data do sistema */
                            get_sys_date(NC.dataCompra,sizeof(NC.dataCompra));
                            break;

                        default:
                            printf("\nDigite um valor Valido!!\n");
                            break;
                        }

                    }while(dateChoice!=1 && dateChoice!=2);


                    fseek(arqNC,0,SEEK_END);
                    fwrite(&NC,sizeof(NotaCompra),1,arqNC);

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
}

int pesquisa_carrinho(Carrinho *c, int size, unsigned int id)
{
    int i = 0;
    while(i<size)
    {
        if(c[i].idProduto==id)
            return i;
        i++;
    }
    return -1;
}