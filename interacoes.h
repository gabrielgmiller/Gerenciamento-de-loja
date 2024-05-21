#ifndef INTERACOES_H_INCLUDED
#define INTERACOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


void realizarVenda(int codProduto, int codFuncionario, int codCliente, FILE *Prod, FILE *Func, FILE *Client);

void realizarCompra(int codProduto, int codFuncionario, int codCliente, FILE *Prod, FILE *Func, FILE *Client) ;

void adicionarProdutoFornecedor(FILE *Prod, FILE *For);

void alterarPrecoProdutoFornecedor(FILE *Prod, FILE *For) ;

#endif // CLIENTE_H_INCLUDED