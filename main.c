#include<stdio.h>
#include<locale.h>
#include "header.h"

int main(void){
    setlocale(LC_ALL,"");
    int option;
    FILE *fp_cliente,*fp_notafiscal,*fp_itemNotaFiscal,*fp_produto,*fp_vendedor,*fp_fornecedor,*fp_notaCompra,*fp_itemCompra;
    fp_cliente = fopen("cliente.dat","r+b");
    if(fp_cliente == NULL){
        printf("Arquivo inexistente, criando novo arquivo de mesmo nome.\n");
        fp_cliente = fopen("cliente.dat","w+b");
    };

    do
    {
        printf("\n####Sistema de gerenciamento de loja####");
        printf("\nSelecione qual operacao deseja realizar:");
        printf("\n01->Cadastro\t2->Alteração\n3->Consulta\t4->Listagem");
        printf("\n\nOpção selecionada: ");
        scanf("%d", &option);

        switch (option)
        {

        case 0:
            /* code, if any...*/
            break;
        case 1:
            /* code */
            break;
        
        case 2:
            /* code */
            break;

        case 3:
            /* code */
            break;

        case 4:
            /*code*/
            break;

        default:
            printf("\nDigite um valor valido para realizar uma operação.\n");
            break;
        }
    } while (option != 0);
    fclose(fp_cliente);
    return 0;
}