#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "relatorio.h"
#include "structDeclarations.h"
#include "utility.h"
#include "produto.h"
#include "cliente.h"
#include "vendedor.h"
//#include "fornecedorFileManip.h"

void relatorio_notaFiscal(FILE *arqNF, FILE *arqINF)
{
    FILE *fp_relatorio;
    NotaFiscal NF;
    ItemNotaFiscal INF;
    int sair, posicao, escolha;
    unsigned long id;
    do
    {
        printf("\nDigite a ID da Nota Fiscal: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);

        posicao = pesquisa_NF_id(arqNF,id);

        if(posicao!=-1)
        {
            fseek(arqNF,posicao*sizeof(NotaFiscal),SEEK_SET);
            fread(&NF,sizeof(NotaFiscal),1,arqNF);

            /* escolha entre print na tela e fprintf */
            printf("\nVoce deseja os relatório na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
            scanf("%d",&escolha);
            setbuf(stdin,NULL);
            switch (escolha)
            {
            case 1:
                printf("\n\n#### ~Dados da nota %lu~####",NF.id);
                printf("\nVendedor numero: %lu",NF.idVendedor);
                printf("\nCliente numero: %lu",NF.idCliente);
                printf("\nData da Compra: %s",NF.dataCompra);
                printf("\nValor Total da nota: %.2f",NF.valorTotal);
                fseek(arqINF,0,SEEK_SET);
                while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                {
                    if(INF.idNota==NF.id)
                    {
                        printf("\n~~~~~~~~~~~~~~~");
                        printf("\nProduto numero: %lu",INF.idProduto);
                        printf("\nPreco(UN.): %.2f",INF.precoUnitario);
                        printf("\nQuantidade: %u",INF.quantidade);
                        printf("\n~~~~~~~~~~~~~~~\n");
                    }
                }
                break;
            
            case 2:
                fp_relatorio = fopen("relatorio.txt","w");
                if(fp_relatorio!=NULL)
                {
                    fprintf(fp_relatorio,"\n\n#### ~Dados da nota %lu~####",NF.id);
                    fprintf(fp_relatorio,"\nVendedor numero: %lu",NF.idVendedor);
                    fprintf(fp_relatorio,"\nCliente numero: %lu",NF.idCliente);
                    fprintf(fp_relatorio,"\nData da Compra: %s",NF.dataCompra);
                    fprintf(fp_relatorio,"\nValor Total da nota: %.2f",NF.valorTotal);
                    fseek(arqINF,0,SEEK_SET);
                    while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                    {
                        if(INF.idNota==NF.id)
                        {
                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~");
                            fprintf(fp_relatorio,"\nProduto numero: %lu",INF.idProduto);
                            fprintf(fp_relatorio,"\nPreco(UN.): %.2f",INF.precoUnitario);
                            fprintf(fp_relatorio,"\nQuantidade: %u",INF.quantidade);
                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~\n");
                        }
                    }
                    fclose(fp_relatorio);
                    printf("\nDados do relatorio salvos no arquivo relatorio.txt");
                }
                else
                    printf("\nERRO: Não foi possível abrir o arquivo...");
                break;

            default:
                printf("\nDigite um valor valido para realizar uma operação.\n");
                break;
            }
        }
        else
            printf("\nA id digitada não corresponde a nenhuma Nota cadastrada no registro...");
        printf("\nDeseja gerar outro relatório??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while (sair!=2);
}

void relatorio_notaCompra(FILE *arqNC, FILE *arqINC)
{
    FILE *fp_relatorio;
    NotaCompra NC;
    ItemNotaCompra INC;
    int sair, posicao,escolha;
    unsigned long id;
    do
    {
        printf("\nDigite a ID da Nota Compra: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);

        posicao = pesquisa_NC_id(arqNC,id);

        if(posicao!=-1)
        {
            fseek(arqNC,posicao*sizeof(NotaCompra),SEEK_SET);
            fread(&NC,sizeof(NotaCompra),1,arqNC);

            printf("\nVoce deseja os relatório na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
            scanf("%d",&escolha);
            setbuf(stdin,NULL);
            switch (escolha)
            {
            case 1:
                printf("\n\n#### ~Dados da Compra %lu~####",NC.id);
                printf("\nFornecedor numero: %lu",NC.idFornecedor);
                printf("\nData da Compra: %s",NC.dataCompra);
                printf("\nValor Total da Compra: %.2f",NC.valorTotal);
                fseek(arqINC,0,SEEK_SET);
                while(fread(&INC,sizeof(ItemNotaCompra),1,arqINC))
                {
                    if(INC.idNotaCompra==NC.id)
                    {
                        printf("\n~~~~~~~~~~~~~~~");
                        printf("\nProduto numero: %lu",INC.idProduto);
                        printf("\nPreco(UN.): %.2f",INC.valorUnitario);
                        printf("\nQuantidade: %u",INC.quantidade);
                        printf("\n~~~~~~~~~~~~~~~\n");
                    }
                }
                break;
            
            case 2:
                fp_relatorio = fopen("relatorio.txt","w");
                if(fp_relatorio!=NULL)
                {
                    fprintf(fp_relatorio,"\n\n#### ~Dados da Compra %lu~####",NC.id);
                    fprintf(fp_relatorio,"\nFornecedor numero: %lu",NC.idFornecedor);
                    fprintf(fp_relatorio,"\nData da Compra: %s",NC.dataCompra);
                    fprintf(fp_relatorio,"\nValor Total da Compra: %.2f",NC.valorTotal);
                    fseek(arqINC,0,SEEK_SET);
                    while(fread(&INC,sizeof(ItemNotaCompra),1,arqINC))
                    {
                        if(INC.idNotaCompra==NC.id)
                        {
                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~");
                            fprintf(fp_relatorio,"\nProduto numero: %lu",INC.idProduto);
                            fprintf(fp_relatorio,"\nPreco(UN.): %.2f",INC.valorUnitario);
                            fprintf(fp_relatorio,"\nQuantidade: %u",INC.quantidade);
                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~\n");
                        }
                    }
                    fclose(fp_relatorio);
                    printf("\nDados do relatorio salvos no arquivo relatorio.txt");
                }
                else
                    printf("\nERRO: Não foi possível abrir o arquivo...");
                break;

            default:
                printf("\nDigite um valor valido para realizar uma operação.\n");
                break;
            }
        }
        else
            printf("\nA id digitada não corresponde a nenhuma Nota cadastrada no registro...");
        printf("\nDeseja gerar outro relatório??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    }while (sair!=2);
}

void relatorio_cliente(FILE *arqClnt, FILE *arqNF, FILE *arqINF)
{
    FILE *fp_relatorio;
    NotaFiscal NF;
    ItemNotaFiscal INF;
    int sair, escolha;
    unsigned long id;
    char dataInicial[11], dataFinal[11];
    do
    {
        printf("\nDigite a ID do Cliente: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);
        if(pesquisa_clnt_ID(arqClnt,id)!=-1)
        {
            do
            {
                printf("\nDigite o inicio do intervalo de datas (formato \"dd/mm/aaaa\"): ");
                fgets(dataInicial,sizeof(dataInicial),stdin);
                check_newline(dataInicial);
            } while (!verify_date(dataInicial));
            do
            {
                printf("\nDigite o fim do intervalo de datas (formato \"dd/mm/aaaa\"): ");
                fgets(dataFinal,sizeof(dataFinal),stdin);
                check_newline(dataFinal);
            } while (!verify_date(dataFinal));
            if(smaller_date(dataInicial,dataFinal))
            {
                printf("\nVoce deseja os relatório na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
                scanf("%d",&escolha);
                setbuf(stdin,NULL);
                switch (escolha)
                {
                case 1:
                    fseek(arqNF,0,SEEK_SET);
                    while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                    {
                        if (NF.idCliente==id && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                        {
                            printf("\n\n#### ~Dados da nota %lu~####",NF.id);
                            printf("\nVendedor numero: %lu",NF.idVendedor);
                            printf("\nCliente numero: %lu",NF.idCliente);
                            printf("\nData da Compra: %s",NF.dataCompra);
                            printf("\nValor Total da nota: %.2f",NF.valorTotal);
                            fseek(arqINF,0,SEEK_SET);
                            while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                            {
                                if(INF.idNota==NF.id)
                                {
                                    printf("\n~~~~~~~~~~~~~~~");
                                    printf("\nProduto numero: %lu",INF.idProduto);
                                    printf("\nPreco(UN.): %.2f",INF.precoUnitario);
                                    printf("\nQuantidade: %u",INF.quantidade);
                                    printf("\n~~~~~~~~~~~~~~~\n");
                                }
                            }
                        }
                    }
                    break;
            
                case 2:
                    fp_relatorio = fopen("relatorio.txt","w");
                    if(fp_relatorio!=NULL)
                    {
                        fseek(arqNF,0,SEEK_SET);
                        while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                        {
                            if (NF.idCliente==id && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                            {
                                fprintf(fp_relatorio,"\n\n#### ~Dados da nota %lu~####",NF.id);
                                fprintf(fp_relatorio,"\nVendedor numero: %lu",NF.idVendedor);
                                fprintf(fp_relatorio,"\nCliente numero: %lu",NF.idCliente);
                                fprintf(fp_relatorio,"\nData da Compra: %s",NF.dataCompra);
                                fprintf(fp_relatorio,"\nValor Total da nota: %.2f",NF.valorTotal);
                                fseek(arqINF,0,SEEK_SET);
                                while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                                {
                                    if(INF.idNota==NF.id)
                                    {
                                        fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~");
                                        fprintf(fp_relatorio,"\nProduto numero: %lu",INF.idProduto);
                                        fprintf(fp_relatorio,"\nPreco(UN.): %.2f",INF.precoUnitario);
                                        fprintf(fp_relatorio,"\nQuantidade: %u",INF.quantidade);
                                        fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~\n");
                                    }
                                }
                            } 
                        }
                        fclose(fp_relatorio);
                        printf("\nDados do relatorio salvos no arquivo relatorio.txt");
                    }
                    else
                    printf("\nERRO: Não foi possível abrir o arquivo...");
                    break;

                default:
                    printf("\nDigite um valor valido para realizar uma operação.\n");
                    break;
                }
            }
            else
                printf("\nIntervalo de datas invalido...");
            
        }
        else
            printf("\nA id digitada não corresponde a nenhum Cliente cadastrado no registro...");
        printf("\nDeseja gerar outro relatório??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void relatorio_vnddr_dia(FILE *arqVnddr,FILE *arqNF, FILE *arqINF)
{
    FILE *fp_relatorio;
    NotaFiscal NF;
    ItemNotaFiscal INF;
    int sair, escolha;
    unsigned long id;
    char data[11];
    do
    {
        printf("\nDigite a ID do Vendedor: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);
        if(pesquisa_vnddr_ID(arqVnddr,id)!=-1)
        {
            do
            {
                printf("\nDigite a data das vendas (formato \"dd/mm/aaaa\"): ");
                fgets(data,sizeof(data),stdin);
                check_newline(data);
            } while (!verify_date(data));
            
            printf("\nVoce deseja os relatorio na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
            scanf("%d",&escolha);
            setbuf(stdin,NULL);
            
            switch (escolha)
            {
            case 1:
                fseek(arqNF,0,SEEK_SET);
                while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                {
                    if (NF.idVendedor==id && strncmp(data,NF.dataCompra,sizeof(data))==0)
                    {
                        printf("\n\n#### ~Dados da nota %lu~####",NF.id);
                        printf("\nVendedor numero: %lu",NF.idVendedor);
                        printf("\nCliente numero: %lu",NF.idCliente);
                        printf("\nData da Compra: %s",NF.dataCompra);
                        printf("\nValor Total da nota: %.2f",NF.valorTotal);
                        fseek(arqINF,0,SEEK_SET);
                        while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                        {
                            if(INF.idNota==NF.id)
                            {
                                printf("\n~~~~~~~~~~~~~~~");
                                printf("\nProduto numero: %lu",INF.idProduto);
                                printf("\nPreco(UN.): %.2f",INF.precoUnitario);
                                printf("\nQuantidade: %u",INF.quantidade);
                                printf("\n~~~~~~~~~~~~~~~\n");
                            }
                        }
                    }
                }
                break;
            
            case 2:
                fp_relatorio = fopen("relatorio.txt","w");
                if(fp_relatorio!=NULL)
                {
                    fseek(arqNF,0,SEEK_SET);
                    while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                    {
                        if (NF.idVendedor==id && strncmp(data,NF.dataCompra,sizeof(data))==0)
                        {
                            fprintf(fp_relatorio,"\n\n#### ~Dados da nota %lu~####",NF.id);
                            fprintf(fp_relatorio,"\nVendedor numero: %lu",NF.idVendedor);
                            fprintf(fp_relatorio,"\nCliente numero: %lu",NF.idCliente);
                            fprintf(fp_relatorio,"\nData da Compra: %s",NF.dataCompra);
                            fprintf(fp_relatorio,"\nValor Total da nota: %.2f",NF.valorTotal);
                            fseek(arqINF,0,SEEK_SET);
                            while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                            {
                                if(INF.idNota==NF.id)
                                {
                                    fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~");
                                    fprintf(fp_relatorio,"\nProduto numero: %lu",INF.idProduto);
                                    fprintf(fp_relatorio,"\nPreco(UN.): %.2f",INF.precoUnitario);
                                    fprintf(fp_relatorio,"\nQuantidade: %u",INF.quantidade);
                                    fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~\n");
                                }
                            }
                        } 
                    }
                    fclose(fp_relatorio);
                    printf("\nDados do relatorio salvos no arquivo relatorio.txt");
                }
                else
                printf("\nERRO: Não foi possível abrir o arquivo...");
                break;

            default:
                printf("\nDigite um valor valido para realizar uma operação.\n");
                break;
            }  
        }
        else
            printf("\nA id digitada nao corresponde a nenhum Vendedor cadastrado no registro...");
        printf("\nDeseja gerar outro relatorio??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void relatorio_vnddr_mes(FILE *arqVnddr,FILE *arqNF,FILE *arqINF)
{
    FILE *fp_relatorio;
    NotaFiscal NF;
    ItemNotaFiscal INF;
    int sair, escolha;
    unsigned long id;
    char dataInicial[11];
    char dataFinal[11];
    char monYear[8];
    do
    {
        
        printf("\nDigite a ID do Vendedor: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);
        if(pesquisa_vnddr_ID(arqVnddr,id)!=-1)
        {
            do
            {
                strcpy(dataInicial,"01/");
                strcpy(dataFinal,"31/");
                printf("\nDigite a mes das vendas (formato \"mm/aaaa\"): ");
                fgets(monYear,sizeof(monYear),stdin);
                check_newline(monYear);
                strcat(dataInicial,monYear);
            } while (!verify_date(dataInicial));
            
            strcat(dataFinal,monYear);

            printf("\nVoce deseja os relatório na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
            scanf("%d",&escolha);
            setbuf(stdin,NULL);

            switch (escolha)
            {
            case 1:
                fseek(arqNF,0,SEEK_SET);
                while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                {
                    if (NF.idVendedor==id && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                    {
                        printf("\n\n#### ~Dados da nota %lu~####",NF.id);
                        printf("\nVendedor numero: %lu",NF.idVendedor);
                        printf("\nCliente numero: %lu",NF.idCliente);
                        printf("\nData da Compra: %s",NF.dataCompra);
                        printf("\nValor Total da nota: %.2f",NF.valorTotal);
                        fseek(arqINF,0,SEEK_SET);
                        while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                        {
                            if(INF.idNota==NF.id)
                            {
                                printf("\n~~~~~~~~~~~~~~~");
                                printf("\nProduto numero: %lu",INF.idProduto);
                                printf("\nPreco(UN.): %.2f",INF.precoUnitario);
                                printf("\nQuantidade: %u",INF.quantidade);
                                printf("\n~~~~~~~~~~~~~~~\n");
                            }
                        }
                    }
                }
                break;
        
            case 2:
                fp_relatorio = fopen("relatorio.txt","w");
                if(fp_relatorio!=NULL)
                {
                    fseek(arqNF,0,SEEK_SET);
                    while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                    {
                        if (NF.idVendedor==id && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                        {
                            fprintf(fp_relatorio,"\n\n#### ~Dados da nota %lu~####",NF.id);
                            fprintf(fp_relatorio,"\nVendedor numero: %lu",NF.idVendedor);
                            fprintf(fp_relatorio,"\nCliente numero: %lu",NF.idCliente);
                            fprintf(fp_relatorio,"\nData da Compra: %s",NF.dataCompra);
                            fprintf(fp_relatorio,"\nValor Total da nota: %.2f",NF.valorTotal);
                            fseek(arqINF,0,SEEK_SET);
                            while(fread(&INF,sizeof(ItemNotaFiscal),1,arqINF))
                            {
                                if(INF.idNota==NF.id)
                                {
                                    fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~");
                                    fprintf(fp_relatorio,"\nProduto numero: %lu",INF.idProduto);
                                    fprintf(fp_relatorio,"\nPreco(UN.): %.2f",INF.precoUnitario);
                                    fprintf(fp_relatorio,"\nQuantidade: %u",INF.quantidade);
                                    fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~\n");
                                }
                            }
                        } 
                    }
                    fclose(fp_relatorio);
                    printf("\nDados do relatorio salvos no arquivo relatorio.txt");
                }
                else
                printf("\nERRO: Não foi possível abrir o arquivo...");
                break;

            default:
                printf("\nDigite um valor valido para realizar uma operação.\n");
                break;
            }
        }
        else
            printf("\nA id digitada nao corresponde a nenhum Vendedor cadastrado no registro...");
        printf("\nDeseja gerar outro relatorio??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void melhor_vnddr_mes(FILE *arqVnddr,FILE *arqNF,FILE *arqINF)
{
    FILE *fp_relatorio;
    NotaFiscal NF;
    Vendedor V;
    int sair, escolha, posicaoV;
    char dataInicial[11],dataFinal[11];
    char monYear[8];
    float maiorValor;
    do
    {
        maiorValor = 0;
        do
        {
            strcpy(dataInicial,"01/");
            strcpy(dataFinal,"31/");
            printf("\nDigite o mes das vendas (formato \"mm/aaaa\"): ");
            fgets(monYear,sizeof(monYear),stdin);
            check_newline(monYear);
            strcat(dataInicial,monYear);
        } while (!verify_date(dataInicial));
            
        strcat(dataFinal,monYear);

        fseek(arqNF,0,SEEK_SET);
        while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
            if(NF.valorTotal>maiorValor && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                maiorValor = NF.valorTotal;

        printf("\nVoce deseja os relatório na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
        scanf("%d",&escolha);
        setbuf(stdin,NULL);

        switch (escolha)
        {
        case 1:
            printf("\nMaior(es) vendedor(es) e vendas do mes %s:",monYear);
            fseek(arqNF,0,SEEK_SET);
            while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
            {
                if (NF.valorTotal==maiorValor && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                {
                    posicaoV = pesquisa_vnddr_ID(arqVnddr,NF.idVendedor);
                    fseek(arqVnddr,posicaoV*sizeof(Vendedor),SEEK_SET);
                    fread(&V,sizeof(Vendedor),1,arqVnddr);

                    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                    printf("\nNome do Vendedor: %s",V.nome);
                    printf("\n\n#### ~Dados da nota %lu~####",NF.id);
                    printf("\nVendedor numero: %lu",NF.idVendedor);
                    printf("\nCliente numero: %lu",NF.idCliente);
                    printf("\nData da Compra: %s",NF.dataCompra);
                    printf("\nValor Total da nota: %.2f",NF.valorTotal);
                    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
            }
            break;
        
        case 2:
            fp_relatorio = fopen("relatorio.txt","w");
            if(fp_relatorio!=NULL)
            {
                fprintf(fp_relatorio,"\nMaior(es) vendedor(es) e vendas do mes %s:",monYear);
                fseek(arqNF,0,SEEK_SET);
                while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                {
                    if (NF.valorTotal==maiorValor && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                    {
                        posicaoV = pesquisa_vnddr_ID(arqVnddr,NF.idVendedor);
                        fseek(arqVnddr,posicaoV*sizeof(Vendedor),SEEK_SET);
                        fread(&V,sizeof(Vendedor),1,arqVnddr);

                        fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                        fprintf(fp_relatorio,"\nNome do Vendedor: %s",V.nome);
                        fprintf(fp_relatorio,"\n\n#### ~Dados da nota %lu~####",NF.id);
                        fprintf(fp_relatorio,"\nVendedor numero: %lu",NF.idVendedor);
                        fprintf(fp_relatorio,"\nCliente numero: %lu",NF.idCliente);
                        fprintf(fp_relatorio,"\nData da Compra: %s",NF.dataCompra);
                        fprintf(fp_relatorio,"\nValor Total: %.2f",NF.valorTotal);
                        fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    } 
                }
                fclose(fp_relatorio);
                printf("\nDados do relatorio salvos no arquivo relatorio.txt");
            }
            else
            printf("\nERRO: Não foi possível abrir o arquivo...");
            break;

        default:
            printf("\nDigite um valor valido para realizar uma operação.\n");
            break;
        }
        
        printf("\nDeseja gerar outro relatorio??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
}

void melhor_vnddr_intrvl(FILE *arqVnddr,FILE *arqNF,FILE *arqINF)
{
    FILE *fp_relatorio;
    NotaFiscal NF;
    Vendedor V;
    int sair, escolha, posicaoV;
    char dataInicial[11],dataFinal[11];
    float maiorValor;
    do
    {
        do
        {
                printf("\nDigite o inicio do intervalo de datas (formato \"dd/mm/aaaa\"): ");
                fgets(dataInicial,sizeof(dataInicial),stdin);
                check_newline(dataInicial);
        } while (!verify_date(dataInicial));
        do
        {
            printf("\nDigite o fim do intervalo de datas (formato \"dd/mm/aaaa\"): ");
            fgets(dataFinal,sizeof(dataFinal),stdin);
            check_newline(dataFinal);
        } while (!verify_date(dataFinal));
        if(smaller_date(dataInicial,dataFinal))
        {
            fseek(arqNF,0,SEEK_SET);
            while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                if(NF.valorTotal>maiorValor && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                    maiorValor = NF.valorTotal;

            printf("\nVoce deseja os relatório na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
            scanf("%d",&escolha);
            setbuf(stdin,NULL);

            switch (escolha)
            {
            case 1:
                printf("\nMaior(es) vendedor(es) e vendas entre os dias %s e %s:",dataInicial,dataFinal);
                fseek(arqNF,0,SEEK_SET);
                while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                {
                    if (NF.valorTotal==maiorValor && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                    {
                        posicaoV = pesquisa_vnddr_ID(arqVnddr,NF.idVendedor);
                        fseek(arqVnddr,posicaoV*sizeof(Vendedor),SEEK_SET);
                        fread(&V,sizeof(Vendedor),1,arqVnddr);

                        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                        printf("\nNome do Vendedor: %s",V.nome);
                        printf("\n\n#### ~Dados da nota %lu~####",NF.id);
                        printf("\nVendedor numero: %lu",NF.idVendedor);
                        printf("\nCliente numero: %lu",NF.idCliente);
                        printf("\nData da Compra: %s",NF.dataCompra);
                        printf("\nValor Total da nota: %.2f",NF.valorTotal);
                        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    }
                }
                break;
        
            case 2:
                fp_relatorio = fopen("relatorio.txt","w");
                if(fp_relatorio!=NULL)
                {
                    fprintf(fp_relatorio,"\nMaior(es) vendedor(es) e vendas entre os dias %s e %s:",dataInicial,dataFinal);
                    fseek(arqNF,0,SEEK_SET);
                    while (fread(&NF,sizeof(NotaFiscal),1,arqNF))
                    {
                        if (NF.valorTotal==maiorValor && smaller_date(dataInicial,NF.dataCompra) && smaller_date(NF.dataCompra,dataFinal))
                        {
                            posicaoV = pesquisa_vnddr_ID(arqVnddr,NF.idVendedor);
                            fseek(arqVnddr,posicaoV*sizeof(Vendedor),SEEK_SET);
                            fread(&V,sizeof(Vendedor),1,arqVnddr);

                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                            fprintf(fp_relatorio,"\nNome do Vendedor: %s",V.nome);
                            fprintf(fp_relatorio,"\n\n#### ~Dados da nota %lu~####",NF.id);
                            fprintf(fp_relatorio,"\nVendedor numero: %lu",NF.idVendedor);
                            fprintf(fp_relatorio,"\nCliente numero: %lu",NF.idCliente);
                            fprintf(fp_relatorio,"\nData da Compra: %s",NF.dataCompra);
                            fprintf(fp_relatorio,"\nValor Total: %.2f",NF.valorTotal);
                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                        } 
                    }
                    fclose(fp_relatorio);
                    printf("\nDados do relatorio salvos no arquivo relatorio.txt");
                }
                else
                printf("\nERRO: Não foi possível abrir o arquivo...");
                break;

            default:
                printf("\nDigite um valor valido para realizar uma operação.\n");
                break;
            }
        }
        else
            printf("\nIntervalo de datas invalido...");
        printf("\nDeseja gerar outro relatorio??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void historico_preco(FILE *arqProd,FILE *arqHist)
{
    FILE *fp_relatorio;
    historicoPreco H;
    int sair, escolha;
    unsigned long id;
    do
    {
        printf("\nDigite a ID do Produto: ");
        scanf("%lu",&id);
        setbuf(stdin,NULL);
        if (pesquisa_prdt(arqProd,id)!=-1)
        {
            printf("\nVoce deseja os relatório na tela ou em arquivo?\n1->TELA 2->ARQUIVO\nEscolha: ");
            scanf("%d",&escolha);
            setbuf(stdin,NULL);

            switch (escolha)
            {
            case 1:
                fseek(arqHist,0,SEEK_SET);
                while (fread(&H,sizeof(historicoPreco),1,arqHist))
                {
                    if(H.idProduto==id)
                    {
                        printf("\n~~~~~~~~~~~~~~~");
                        printf("\n\n####~Alteracao feita em %s~####",H.dataAlteracao);
                        printf("\nProduto numero: %lu",H.idProduto);
                        printf("\nPreco antes da alteracao: %.2f",H.valor);
                        printf("\n~~~~~~~~~~~~~~~\n");
                    }
                }
                break;
            
            case 2:
                fp_relatorio = fopen("relatorio.txt","w");
                if(fp_relatorio!=NULL)
                {
                    fseek(arqHist,0,SEEK_SET);
                    while (fread(&H,sizeof(historicoPreco),1,arqHist))
                    {
                        if(H.idProduto==id)
                        {
                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~");
                            fprintf(fp_relatorio,"\n\n####~Alteracao feita em %s~####",H.dataAlteracao);
                            fprintf(fp_relatorio,"\nProduto numero: %lu",H.idProduto);
                            fprintf(fp_relatorio,"\nPreco: %.2f",H.valor);
                            fprintf(fp_relatorio,"\n~~~~~~~~~~~~~~~\n");
                        }
                    }
                    fclose(fp_relatorio);
                    printf("\nDados do relatorio salvos no arquivo relatorio.txt");
                }
                else
                    printf("\nERRO: Não foi possível abrir o arquivo...");
                break;

            default:
                printf("\nDigite um valor valido para realizar uma operação.\n");
                break;
            }
        }
        else
            printf("\nA id digitada nao corresponde a nenhum Produto cadastrado no registro...");
        printf("\nDeseja gerar outro relatorio??\n1->SIM 2->NAO\nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

int pesquisa_NF_id(FILE *arq, unsigned long id)
{
    NotaFiscal r;
    int posicao=0;
    fseek(arq,0,SEEK_SET);
    while(fread(&r,sizeof(NotaFiscal),1,arq)==1)
    {
        if(r.id==id)
            return posicao;
        else
            posicao++;
    }
    return -1;
}

int pesquisa_NC_id(FILE *arq, unsigned long id)
{
    NotaCompra r;
    int posicao=0;
    fseek(arq,0,SEEK_SET);
    while(fread(&r,sizeof(NotaCompra),1,arq)==1)
    {
        if(r.id==id)
            return posicao;
        else
            posicao++;
    }
    return -1;
}