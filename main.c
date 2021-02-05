#include <stdio.h>
#include <locale.h>
#include "structDeclarations.h"
#include "clienteFileManip.h"
#include "vendedorFileManip.h"
#include "fornecedorFileManip.h"
#include "utilityFunctions.h"
#include "produtoFileManip.h"
#include "operations.h"

int main(void){
    setlocale(LC_ALL,"");
    int option, subOption, subOption2, last_clnt_id, last_vnddr_id, last_frncdr_id, last_prdt_id,last_nf_id,last_inf_id;
    FILE *fp_cliente,*fp_notaFiscal,*fp_itemNotaFiscal,*fp_produto,*fp_vendedor,*fp_fornecedor,*fp_notaCompra,*fp_itemCompra;
    open_file(&fp_cliente,"record-files/cliente.dat");
    open_file(&fp_notaFiscal,"record-files/notaFiscal.dat");
    open_file(&fp_itemNotaFiscal,"record-files/itemNotaFiscal.dat");
    open_file(&fp_produto,"record-files/produto.dat");
    open_file(&fp_vendedor,"record-files/vendedor.dat");
    open_file(&fp_fornecedor,"record-files/fornecedor.dat");
    open_file(&fp_notaCompra,"record-files/notaCompra.dat");
    open_file(&fp_itemCompra,"record-files/itemCompra.dat");

    /* Gets first available ID based on number of entries in the file
    (won't work if delete function is implemented) */
    last_clnt_id = (ftell(fp_cliente)/sizeof(Cliente))+1; 
    last_vnddr_id = (ftell(fp_vendedor)/sizeof(Vendedor))+1;
    last_frncdr_id = (ftell(fp_fornecedor)/sizeof(Fornecedor))+1;
    last_prdt_id = (ftell(fp_produto)/sizeof(Produto))+1;
    last_nf_id = (ftell(fp_notaFiscal)/sizeof(NotaFiscal))+1;
    last_inf_id = (ftell(fp_itemNotaFiscal)/sizeof(ItemNotaFiscal))+1;

    if (fp_cliente != NULL && fp_notaFiscal != NULL && fp_itemNotaFiscal != NULL && fp_produto != NULL && fp_vendedor != NULL && fp_fornecedor != NULL && fp_notaCompra != NULL && fp_itemCompra != NULL) /* If all files were sucessfully opened */
    {
        do
        {
            printf("\n####Sistema de gerenciamento de loja####");
            printf("\nSelecione qual operacao deseja realizar:");
            printf("\n1->Cadastros\t2->Alterações\n3->Consultas\t4->Listagens\n5->Compras e Vendas\t0->Fechar o programa");
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
                    printf("\n\n\tSelecione qual tipo de cadastro deseja REALIZAR:");
                    printf("\n\t1->Cadastro de Clientes\t2->Cadastro de Vendedores\n\t3->Cadastro de Fornecedores\t4->Cadastro de Produtos\n\t0->Voltar ao Menu Principal");
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
                        cadastro_fornecedor(fp_fornecedor, &last_frncdr_id);
                        break;

                    case 4:
                        cadastro_produto(fp_produto, &last_prdt_id);
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
                    printf("\n\n\tSelecione qual tipo de cadastro deseja ALTERAR:");
                    printf("\n\t1->Cadastro de Clientes\t2->Cadastro de Vendedores\n\t3->Cadastro de Fornecedores\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        alteracao_cliente(fp_cliente);
                        break;

                    case 2:
                        alteracao_vendedor(fp_vendedor);
                        break;

                    case 3:
                        alteracao_fornecedor(fp_vendedor);
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
                    printf("\n\n\tSelecione qual tipo de cadastro deseja CONSULTAR:");
                    printf("\n\t1->Consulta de Clientes\t2->Consulta de Vendedores\n\t3->Consulta de Fornecedores\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        do
                        {
                            printf("\n\n\tSelecione por qual campo deseja CONSULTAR:");
                            printf("\n\t1->Consulta por CPF\t2->Consulta por ID\n\t3->Consulta por INICIAIS\t0->Voltar ao Menu de Consultas");
                            printf("\n\nOpção selecionada: ");
                            scanf("%d", &subOption2);
                            switch (subOption2)
                            {
                            case 0:
                                break;
                
                            case 1:
                                consulta_clnt_CPF(fp_cliente);/* Função de CONSULTA de clientes por CPF aqui */
                                break;

                            case 2:
                                consulta_clnt_ID(fp_cliente);/* Função de CONSULTA de clientes por ID aqui */
                                break;

                            case 3:
                                consulta_clnt_INI(fp_cliente);/* Função de CONSULTA de clientes por INICIAIS aqui */
                                break;

                            default:
                                printf("\nDigite um valor valido para realizar uma operação.\n");
                                break;
                            }
                        } while (subOption2!=0);
                        break;

                    case 2:
                        do
                        {
                            printf("\n\n\tSelecione por qual campo deseja CONSULTAR:");
                            printf("\n\t1->Consulta por CPF\t2->Consulta por ID\n\t3->Consulta por INICIAIS\t0->Voltar ao Menu de Consultas");
                            printf("\n\nOpção selecionada: ");
                            scanf("%d", &subOption2);
                            switch (subOption2)
                            {
                            case 0:
                                break;
                
                            case 1:
                                consulta_vnddr_CPF(fp_vendedor);/* Função de CONSULTA de clientes por CPF aqui */
                                break;

                            case 2:
                                consulta_vnddr_ID(fp_vendedor);/* Função de CONSULTA de vendedores por ID aqui */
                                break;

                            case 3:
                                consulta_vnddr_INI(fp_vendedor);/* Função de CONSULTA de vendedores por INICIAIS aqui */
                                break;

                            default:
                                printf("\nDigite um valor valido para realizar uma operação.\n");
                                break;
                            }
                        } while (subOption2!=0);
                        break;

                    case 3:
                        do
                        {
                            printf("\n\n\tSelecione por qual campo deseja CONSULTAR:");
                            printf("\n\t1->Consulta por CNPJ\t2->Consulta por ID\n\t3->Consulta por INICIAIS\t0->Voltar ao Menu de Consultas");
                            printf("\n\nOpção selecionada: ");
                            scanf("%d", &subOption2);
                            switch (subOption2)
                            {
                            case 0:
                                break;
                
                            case 1:
                                consulta_frncdr_CPF(fp_fornecedor);/* Função de CONSULTA de clientes por CPF aqui */
                                break;

                            case 2:
                                consulta_frncdr_ID(fp_fornecedor);/* Função de CONSULTA de vendedores por ID aqui */
                                break;

                            case 3:
                                consulta_frncdr_INI(fp_fornecedor);/* Função de CONSULTA de vendedores por INICIAIS aqui */
                                break;

                            default:
                                printf("\nDigite um valor valido para realizar uma operação.\n");
                                break;
                            }
                        } while (subOption2!=0);
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
                    printf("\n\n\tSelecione qual tipo de cadastro deseja LISTAR:");
                    printf("\n\t1->Listagem de Clientes\t2->Listagem de Vendedores\n\t3->Listagem de Fornecedores\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        listar_clientes(fp_cliente);
                        break;

                    case 2:
                        listar_vendedores(fp_vendedor);
                        break;

                    case 3:
                        listar_fornecedores(fp_fornecedor);
                        break;

                    default:
                        printf("\nDigite um valor valido para realizar uma operação.\n");
                        break;
                    }
                } while (subOption!=0);
                break;

            case 5:/* Sub-menu de Compras e vendas */
                printf("\n\n\tDeseja realizar qual operação:");
                printf("\n\t1->Venda(p/um cliente)\t2->Compra(de um fornecedor)\n\t0->Voltar ao Menu Principal");
                printf("\n\nOpção selecionada: ");
                scanf("%d", &subOption);
                switch (subOption)
                {
                case 1: /* Vendas (p/ um cliente) */
                    realizar_venda(fp_vendedor,fp_cliente,fp_produto,fp_notaFiscal,fp_itemNotaFiscal,&last_nf_id,&last_inf_id);
                    break;
                
                case 2: /* Comprar(de um fornecedor) , implementação temporaria */
                    atualizar_estoque(fp_produto,0,15);
                    atualizar_estoque(fp_produto,1,15);
                    atualizar_estoque(fp_produto,2,15);
                    atualizar_estoque(fp_produto,3,15);
                    atualizar_estoque(fp_produto,4,15);
                    break;

                default:
                    break;
                }
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
