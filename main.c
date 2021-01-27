#include<stdio.h>
#include<locale.h>
#include "structDeclarations.h"
#include "fileManipulation.h"

void open_file(FILE**, char*); /* Opens a file with given filename or creates one if none exists */

int main(void){
    setlocale(LC_ALL,"");
    int option, subOption, last_clnt_id, last_vnddr_id, last_frncdr_id;
    FILE *fp_cliente,*fp_notaFiscal,*fp_itemNotaFiscal,*fp_produto,*fp_vendedor,*fp_fornecedor,*fp_notaCompra,*fp_itemCompra;
    open_file(&fp_cliente,"record-files/cliente.dat");
    open_file(&fp_notaFiscal,"record-files/notaFiscal.dat");
    open_file(&fp_itemNotaFiscal,"record-files/itemNotaFiscal.dat");
    open_file(&fp_produto,"record-files/produto.dat");
    open_file(&fp_vendedor,"record-files/vendedor.dat");
    open_file(&fp_fornecedor,"record-files/fornecedor.dat");
    open_file(&fp_notaCompra,"record-files/notaCompra.dat");
    open_file(&fp_itemCompra,"record-files/itemCompra.dat");

    /* Gets first available ID based on number of entries in file(won't work if delete function is implemented) */
    last_clnt_id = (ftell(fp_cliente)/sizeof(cliente)); 
    last_vnddr_id = (ftell(fp_vendedor)/sizeof(vendedor));
    last_frncdr_id = (ftell(fp_fornecedor)/sizeof(fornecedor));

    if (fp_cliente != NULL && fp_notaFiscal != NULL && fp_itemNotaFiscal != NULL && fp_produto != NULL && fp_vendedor != NULL && fp_fornecedor != NULL && fp_notaCompra != NULL && fp_itemCompra != NULL) /* If all files were sucessfully opened */
    {
        do
        {
            printf("\n####Sistema de gerenciamento de loja####");
            printf("\nSelecione qual operacao deseja realizar:");
            printf("\n1->Cadastros\t2->Alterações\n3->Consultas\t4->Listagens\n0->Fechar o programa");
            printf("\n\nOpção selecionada: ");
            scanf("%d", &option);

            switch (option)
            {

            case 0:
                /* code, if any...*/
                break;
            
            case 1: /*Sub-menu de cadastros */
                do
                {
                    printf("\n\tSelecione qual tipo de cadastro deseja REALIZAR:");
                    printf("\n\t1->Cadastro de Clientes\t2->Cadastro de Vendedores\n\t3->Cadastro de Fornecedores\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        cadastro_cliente(fp_cliente, &last_clnt_id);
                        break;

                    case 2:
                        cadastro_vendedor(fp_vendedor, &last_vnddr_id);
                        break;

                    case 3:
                        cadastro_fornecedor(fp_vendedor, &last_frncdr_id);
                        break;

                    default:
                        printf("\nDigite um valor valido para realizar uma operação.\n");
                        break;
                    }
                } while (subOption!=0);
                break;
        
            case 2: /* Sub-menu de ALTERAÇÃO de cadastros */
                do
                {
                    printf("\n\tSelecione qual tipo de cadastro deseja ALTERAR:");
                    printf("\n\t1->Cadastro de Clientes\t2->Cadastro de Vendedores\n\t3->Cadastro de Fornecedores\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        /* Função de ALTERAÇÃO de cadastro de clientes aqui */
                        break;

                    case 2:
                        /* função de ALTERAÇÃO de cadastro de vendedores aqui */
                        break;

                    case 3:
                        /* função de ALTERAÇÃO de cadastro de fornecedores aqui */
                        break;

                    default:
                        printf("\nDigite um valor valido para realizar uma operação.\n");
                        break;
                    }
                } while (subOption!=0);
                break;

            case 3: /* Sub-menu de Consultas */
                do
                {
                    printf("\n\tSelecione qual tipo de cadastro deseja CONSULTAR:");
                    printf("\n\t1->Consulta de Clientes\t2->Consulta de Vendedores\n\t3->Consulta de Fornecedores\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        /* Função de CONSULTA de clientes aqui */
                        break;

                    case 2:
                        /* função de CONSULTA de vendedores aqui */
                        break;

                    case 3:
                        /* função de CONSULTA de fornecedores aqui */
                        break;

                    default:
                        printf("\nDigite um valor valido para realizar uma operação.\n");
                        break;
                    }
                } while (subOption!=0);
                break;

            case 4: /* Sub-menu de Listagens */
                do
                {
                    printf("\n\tSelecione qual tipo de cadastro deseja LISTAR:");
                    printf("\n\t1->Listagem de Clientes\t2->Listagem de Vendedores\n\t3->Listagem de Fornecedores\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        listar_clnts(fp_cliente);
                        break;

                    case 2:
                        listar_vnddrs(fp_vendedor);
                        break;

                    case 3:
                        /* função de LISTAGEM de fornecedores aqui */
                        break;

                    default:
                        printf("\nDigite um valor valido para realizar uma operação.\n");
                        break;
                    }
                } while (subOption!=0);
                break;

            default:
                printf("\nDigite um valor valido para realizar uma operação.\n");
                break;
            }
        } while (option != 0);
    }
    fclose(fp_cliente);
    fclose(fp_notaFiscal);
    fclose(fp_itemNotaFiscal);
    fclose(fp_produto);
    fclose(fp_vendedor);
    fclose(fp_fornecedor);
    fclose(fp_notaCompra);
    fclose(fp_itemCompra);
    return 0;
}

void open_file(FILE** fp,char* filename)
{
    *fp = fopen(filename,"r+b");
    if(*fp == NULL){
        printf("\nArquivo %s não encontrado, um novo arquivo de mesmo nome será criado.", filename);
        *fp = fopen(filename, "w+b");
    }
};