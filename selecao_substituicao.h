#ifndef SELECAO_SUBSTITUICAO_H_
#define SELECAO_SUBSTITUICAO_H_

#include <stdio.h>
#include "funcionario.h"
#include "cliente.h"
#include "fornecedor.h"
#include "produto.h"

int selecaoSubstituicaoF(FILE *in, char *nome, int M);

int existemNaoCongelados(int *congelados, int n);

void liberarRegistros(TFunc **func, int M);

int selecaoSubstituicaoClient(FILE *in, char *nome, int M);

int selecaoSubstituicaoFor(FILE *in, char *nome, int M);

int selecaoSubstituicaoProd(FILE *in, char *nome, int M);

int existemNaoCongelados(int *congelados, int n);

void liberarRegistrosClient(TClient **clients, int M);

void liberarRegistrosFor(TFor **forn, int M);

void liberarRegistrosProd(TProd **prods, int M);

#endif /* SELECAO_SUBSTITUICAO_H_ */
