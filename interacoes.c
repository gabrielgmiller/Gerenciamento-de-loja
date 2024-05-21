#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"
#include "produto.h"
#include "fornecedor.h"
#include "cliente.h"
#include "buscaSequencia.h"
#include "interface.h"
#include "interacoes.h"

void realizarVenda(int codProduto, int codFuncionario, int codCliente, FILE *Prod, FILE *Func, FILE *Client) {
    TProd *produto = buscaSequencialProd(codProduto, Prod);
    if (produto != NULL) {
        TFunc *funcionario = buscaSequencial(codFuncionario, Func);
        if (funcionario != NULL) {
            TClient *cliente = buscaSequencialClient(codCliente, Client);
            if (cliente != NULL) {
                if (produto->numVendas > 0) {
                    produto->numVendas++;
                    
                    cliente->numCompras++;

                    funcionario->numVendas++;

                    fseek(Prod, -tamanho_registroProd(), SEEK_CUR);
                    salvaProd(produto,  Prod);
                    fseek(Prod, 0, SEEK_END);  // Move o ponteiro para o final do arquivo

                    fseek(Func, -tamanho_registro(), SEEK_CUR);
                    salva(funcionario, Func);
                    fseek(Func, 0, SEEK_END);  // Move o ponteiro para o final do arquivo

                    fseek(Client, -tamanho_registroClient(), SEEK_CUR);
                    salvaClient(cliente, Client);
                    fseek(Client, 0, SEEK_END);

                    printf("Venda realizada com sucesso!\n");
                    printf("Os numeros de vendas foram alterados!\n\n");
                    printf("Recibo de venda:\n");
                    printf("Produto: %s\n", produto->nome);
                    printf("Funcionário: %s\n", funcionario->nome);
                    printf("Cliente: %s\n", cliente->nome);

                    free(produto);
                    free(funcionario);
                    free(cliente);
                } else {
                    printf("Desculpe, o produto está fora de estoque.\n");
                }
            } else {
                printf("Cliente não encontrado.\n");
            }
        } else {
            printf("Funcionário não encontrado.\n");
        }
    } else {
        printf("Produto não encontrado.\n");
    }
}


void realizarCompra(int codProduto, int codFuncionario, int codCliente, FILE *Prod, FILE *Func, FILE *Client) {
    TProd *produto = buscaSequencialProd(codProduto, Prod);
    if (produto != NULL) {
        TFunc *funcionario = buscaSequencial(codFuncionario, Func);
        if (funcionario != NULL) {
            TClient *cliente = buscaSequencialClient(codCliente, Client);
            if (cliente != NULL) {
                if (produto->numVendas > 0) {
                    produto->numVendas++;
                    
                    cliente->numCompras++;
                    
                    funcionario->numVendas++;

                    fseek(Prod, -tamanho_registroProd(), SEEK_CUR);
                    salvaProd(produto,  Prod);
                    fseek(Prod, 0, SEEK_END);  // Move o ponteiro para o final do arquivo

                    fseek(Func, -tamanho_registro(), SEEK_CUR);
                    salva(funcionario, Func);
                    fseek(Func, 0, SEEK_END);  // Move o ponteiro para o final do arquivo

                    fseek(Client, -tamanho_registroClient(), SEEK_CUR);
                    salvaClient(cliente, Client);
                    fseek(Client, 0, SEEK_END);

                    printf("Compra realizada com sucesso!\n");
                    printf("Os numeros de vendas foram alterados!\n\n");
                    printf("Recibo de Compra:\n");
                    printf("Produto: %s\n", produto->nome);
                    printf("Funcionário: %s\n", funcionario->nome);
                    printf("Cliente: %s\n", cliente->nome);

                    free(produto);
                    free(funcionario);
                    free(cliente);
                } else {
                    printf("Desculpe, o produto está fora de estoque.\n");
                }
            } else {
                printf("Cliente não encontrado.\n");
            }
        } else {
            printf("Funcionário não encontrado.\n");
        }
    } else {
        printf("Produto não encontrado.\n");
    }
}

void adicionarProdutoFornecedor(FILE *Prod, FILE *For) {
    int cod, numVendas, codForn;
    char nome[50];
    double preco;
    TProd *novoProd;

    printf("Qual o codigo do produto: ");
    scanf("%d", &cod);

    printf("Qual o nome do produto: ");
    getchar(); // Limpar o buffer de entrada
    fgets(nome, sizeof(nome), stdin);

    printf("Qual o preco do produto: ");
    scanf("%lf", &preco);

    printf("Qual o num de vendas do produto: ");
    scanf("%d", &numVendas);

    novoProd = produto(cod, nome, preco, numVendas);
    salvaProd(novoProd, Prod);

    printf("Qual o fornecedor que realizou a venda do produto: ");
    scanf("%d", &codForn);

    TFor *fornecedor = buscaSequencialFor(codForn, For);

    if (fornecedor != NULL) {
        fornecedor->comissao += preco*0.1;

        fseek(For, -tamanho_registroFor(), SEEK_CUR);
        salvaFor(fornecedor, For);
        fseek(For, 0, SEEK_END);

        limparTela();
        printf("\nProduto adicionado ao estoque e venda registrada para o fornecedor com sucesso!\n\n");
        printf("Recibo de Venda:\n");
        printf("Produto: %s\n", novoProd->nome);
        printf("Fornecedor: %s\n", fornecedor->nome);
        printf("A comissao foi adicionada automaticamente ao fornecedor!\n");

        free(novoProd);
        free(fornecedor);
    } else {
        printf("\nFornecedor não encontrado para o produto.\n");
    }
}

void alterarPrecoProdutoFornecedor(FILE *Prod, FILE *For) {
    int cod;
    double novoPreco;

    printf("Qual o codigo do produto: ");
    scanf("%d", &cod);

    TProd *produto = buscaSequencialProd(cod, Prod);

    if (produto != NULL) {
        TFor *fornecedor = buscaSequencialFor(cod, For);

        if (fornecedor != NULL) {
            printf("Qual o novo preco do produto: ");
            scanf("%lf", &novoPreco);

            produto->preco = novoPreco;

            fseek(Prod, -tamanho_registroProd(), SEEK_CUR);
            salvaProd(produto, Prod);
            fseek(Prod, 0, SEEK_END);

            printf("\nPreco do produto atualizado com sucesso!\n");
            printf("Recibo de alteracao:\n");
            printf("Produto: %s\n", produto->nome);
            printf("Fornecedor: %s\n", fornecedor->nome);

            free(produto);
            free(fornecedor);
        } else {
            printf("\nFornecedor não encontrado para o produto.\n");
            free(produto);
        }
    } else {
        printf("\nProduto não encontrado.\n");
    }
}




