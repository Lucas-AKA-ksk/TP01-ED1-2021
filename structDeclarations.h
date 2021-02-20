#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct
{
    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
}Cliente;

typedef struct
{
    unsigned long id;
    unsigned long idCliente;
    unsigned long idVendedor;
    char dataCompra[11];
    float valorTotal;
}NotaFiscal;

typedef struct
{
    unsigned long id;
    unsigned long idNota;
    unsigned long idProduto;
    float precoUnitario;
    unsigned int quantidade;
}ItemNotaFiscal;

typedef struct
{
    unsigned long id;
    char nome[100];
    unsigned int quantidadeEstoque;
    float precoUnitario;
}Produto;

typedef struct
{
    unsigned long id;
    /*char matricula[10];*/
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
    char password[20];
}Vendedor;

typedef struct
{
    unsigned long id;
    char cnpj[15];
    char nome[100];
    char email[50];
    char telefone[15];
}Fornecedor;

typedef struct
{
    unsigned long id;
    unsigned long idFornecedor;
    char dataCompra[11];
    float valorTotal;
}NotaCompra;

typedef struct
{
    unsigned long id;
    unsigned long idProduto;
    unsigned long idNotaCompra;
    unsigned int quantidade;
    float valorUnitario;
}ItemNotaCompra;

typedef struct
{
    unsigned long idProduto;
    char dataAlteracao[11];
    float valor;
}historicoPreco;

#endif // STRUCT_H_INCLUDED