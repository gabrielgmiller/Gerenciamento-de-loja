#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Produto {
    int cod;
    char nome[50];
    double preco;
    int numVendas;
} TProd;

int tamanho_arquivoProd(FILE *arq);

int tamanho_registroProd();

TProd *produto(int cod, char *nome, double preco,int numVendas);

void salvaProd(TProd *prod, FILE *out);

TProd *leProd(FILE *in);

void imprimeProd(TProd *prod);

void adicionarProd(FILE *out);

void criarBaseProd(FILE *out, int tam, int min);

void shuffleProd(int *vet,int MAX,int MIN);

void imprimirBaseProd(FILE *out);

void removerProduto(FILE *arquivo, int cod);

void imprimirBasePr(FILE *out, int n);

#endif // PRODUTO_H_INCLUDED