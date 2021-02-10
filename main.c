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
    int option, subOption, subOption2, last_clnt_id, last_vnddr_id, last_frncdr_id, last_prdt_id,last_nf_id,last_inf_id,last_nc_id,last_inc_id;
    FILE *fp_cliente,*fp_notaFiscal,*fp_itemNotaFiscal,*fp_produto,*fp_vendedor,*fp_fornecedor,*fp_notaCompra,*fp_itemNotaCompra,*fp_historicoPreco;
    open_file(&fp_cliente,"record-files/cliente.dat");
    open_file(&fp_notaFiscal,"record-files/notaFiscal.dat");
    open_file(&fp_itemNotaFiscal,"record-files/itemNotaFiscal.dat");
    open_file(&fp_produto,"record-files/produto.dat");
    open_file(&fp_vendedor,"record-files/vendedor.dat");
    open_file(&fp_fornecedor,"record-files/fornecedor.dat");
    open_file(&fp_notaCompra,"record-files/notaCompra.dat");
    open_file(&fp_itemNotaCompra,"record-files/itemCompra.dat");
    open_file(&fp_historicoPreco,"record-files/historicoPreco.dat");
    
    /* Gets first available ID based on number of entries in the file
    (won't work if delete function is implemented) */
    last_clnt_id = (ftell(fp_cliente)/sizeof(Cliente))+1;
    last_nf_id = (ftell(fp_notaFiscal)/sizeof(NotaFiscal))+1;
    last_inf_id = (ftell(fp_itemNotaFiscal)/sizeof(ItemNotaFiscal))+1;
    last_prdt_id = (ftell(fp_produto)/sizeof(Produto))+1;
    last_vnddr_id = (ftell(fp_vendedor)/sizeof(Vendedor))+1;
    last_frncdr_id = (ftell(fp_fornecedor)/sizeof(Fornecedor))+1;
    last_nc_id = (ftell(fp_notaCompra)/sizeof(NotaCompra))+1;
    last_inc_id = (ftell(fp_itemNotaCompra)/sizeof(ItemNotaCompra))+1;

    if (fp_cliente != NULL && fp_notaFiscal != NULL && fp_itemNotaFiscal != NULL && fp_produto != NULL && fp_vendedor != NULL && fp_fornecedor != NULL && fp_notaCompra != NULL && fp_itemNotaCompra != NULL) /* If all files were sucessfully opened */
    {
        do
        {
            printf("\n####Sistema de gerenciamento de loja####");
            printf("\nSelecione qual operacao deseja realizar:");
            printf("\n1->Cadastros\n2->Alterações\n3->Consultas\n4->Listagens\n5->Compras e Vendas\n0->Fechar o programa");
            printf("\n\nOpção selecionada: ");
            scanf("%d", &option);
            setbuf(stdin,NULL);

            switch (option)
            {

            case 0:
                printf("\n\nFechando arquivos e encerrando o programa...");
                break;
            
            case 1: /* Sub-menu de cadastros */
                do
                {
                    printf("\n\n\tSelecione qual tipo de cadastro deseja REALIZAR:");
                    printf("\n\t1->Cadastro de Clientes\n\t2->Cadastro de Vendedores\n\t3->Cadastro de Fornecedores\n\t4->Cadastro de Produtos\n\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    setbuf(stdin,NULL);

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
        
            case 2: /* Sub-menu de Alterações */
                do
                {
                    printf("\n\n\tSelecione qual tipo de ALTERAÇÃO deseja realizar:");
                    printf("\n\t1->Cadastro de Clientes\n\t2->Cadastro de Vendedores\n\t3->Cadastro de Fornecedores\n\t4->Alt. de preço indv.\n\t5->Alt. de preço global\n\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    setbuf(stdin,NULL);

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

                    case 4:
                        reajuste_preco_individual(fp_produto,fp_historicoPreco);
                        break;
                
                    case 5:
                        reajuste_preco_all(fp_produto,fp_historicoPreco);
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
                    printf("\n\t1->Consulta de Clientes\n\t2->Consulta de Vendedores\n\t3->Consulta de Fornecedores\n\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    setbuf(stdin,NULL);

                    switch (subOption)
                    {
                    case 0:
                        break;
                
                    case 1:
                        do
                        {
                            printf("\n\n\tSelecione por qual campo deseja CONSULTAR:");
                            printf("\n\t1->Consulta por CPF\n\t2->Consulta por ID\n\t3->Consulta por INICIAIS\n\t0->Voltar ao Menu de Consultas");
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
                            printf("\n\t1->Consulta por CPF\n\t2->Consulta por ID\n\t3->Consulta por INICIAIS\n\t0->Voltar ao Menu de Consultas");
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
                            printf("\n\t1->Consulta por CNPJ\n\t2->Consulta por ID\n\t3->Consulta por INICIAIS\n\t0->Voltar ao Menu de Consultas");
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
                    printf("\n\t1->Listagem de Clientes\n\t2->Listagem de Vendedores\n\t3->Listagem de Fornecedores\n\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    setbuf(stdin,NULL);

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
                do
                {
                    printf("\n\n\tDeseja realizar qual operação:");
                    printf("\n\t1->Venda(p/um cliente)\n\t2->Compra(de um fornecedor)\n\t0->Voltar ao Menu Principal");
                    printf("\n\nOpção selecionada: ");
                    scanf("%d", &subOption);
                    setbuf(stdin,NULL);

                    switch (subOption)
                    {
                    case 1: /* Vendas (p/ um cliente) */
                        realizar_venda(fp_vendedor,fp_cliente,fp_produto,fp_notaFiscal,fp_itemNotaFiscal,&last_nf_id,&last_inf_id);
                        break;
                
                    case 2: /* Comprar(de um fornecedor) */
                        realizar_compra(fp_fornecedor,fp_produto,fp_notaCompra,fp_itemNotaCompra,&last_nc_id,&last_inc_id);
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
    fclose(fp_itemNotaCompra);
    fclose(fp_historicoPreco);
    return 0;
}
