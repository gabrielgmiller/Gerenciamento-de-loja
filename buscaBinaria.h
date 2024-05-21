#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

#include "funcionario.h"
#include "cliente.h"
#include "fornecedor.h"
#include "produto.h"
//Realiza uma busca binaria por um funcionario na base de dados

TFunc *busca_binaria(int chave, FILE *in, int inicio, int fim);

TFor *busca_binaria_forn(int chave, FILE *in, int inicio, int fim);

TClient *busca_binaria_client(int chave, FILE *in, int inicio, int fim);

TProd *busca_binaria_prod(int chave, FILE *in, int inicio, int fim);

#endif // BUSCABINARIA_H_INCLUDED