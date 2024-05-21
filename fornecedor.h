#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Fornecedor {
    int cod;
    char nome[50];
    char cnpj[15];
    int comissao;
} TFor;

int tamanho_arquivoFor(FILE *arq);

int tamanho_registroFor();

TFor *fornecedor(int cod, char *nome, char *cnpj, int comissao);

void salvaFor(TFor *forn, FILE *out);

TFor *leFor(FILE *in);

void imprimeFor(TFor *forn);

void adicionarForn(FILE *out);

void criarBaseFor(FILE *out, int tam, int min);

void shuffleFor(int *vet,int MAX,int MIN);

void imprimirBaseFor(FILE *out);

void removerFornecedor(FILE *arquivo, int cod);

void imprimirBaseFo(FILE *out, int n);

#endif // FORNECEDOR_H_INCLUDED