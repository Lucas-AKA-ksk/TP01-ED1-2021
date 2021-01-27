#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct
{
    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
}cliente;

typedef struct
{
    unsigned long id;
    unsigned long idCliente;
    char numeroNota[8];
    unsigned long idVendedor;
    char dataCompra[11];
    float valorTotal;
}notaFiscal;

typedef struct
{
    unsigned long id;
    unsigned long idNota;
    unsigned long idProduto;
    float precoUnitario;
    unsigned int quantidade;
}itemNotaFiscal;

typedef struct
{
    unsigned long id;
    char nome[100];
    unsigned int quantidadeEstoque;
    float precoUnitario;
}produto;

typedef struct
{
    unsigned long id;
    char matricula[10];
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
    char password[20];
}vendedor;

typedef struct
{
    unsigned long id;
    char cnpj[15];
    char nome[100];
    char email[50];
    char telefone[15];
}fornecedor;

typedef struct
{
    unsigned long id;
    char numeroNota[10];
    unsigned long idFornecedor;
    char dataCompra[11];
    float valorTotal;
}notaCompra;

typedef struct
{
    unsigned long id;
    unsigned long idProduto;
    unsigned long idNotacompra;
    unsigned int quantidade;
    float valorUnitario;
}itemCompra;

#endif // STRUCT_H_INCLUDED