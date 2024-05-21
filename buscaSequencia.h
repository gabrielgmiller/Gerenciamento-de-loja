#ifndef BUSCASEQUENCIA_H_INCLUDED
#define BUSCASEQUENCIA_H_INCLUDED

#include "funcionario.h"
#include "produto.h"
#include "fornecedor.h"
#include "cliente.h"

TFunc *buscaSequencial(int chave, FILE *in);

TClient *buscaSequencialClient(int chave, FILE *in);

TFor *buscaSequencialFor(int chave, FILE *in);

TProd *buscaSequencialProd(int chave, FILE *in);

#endif 