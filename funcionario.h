#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
    int numVendas;
} TFunc;

int tamanho_arquivo(FILE *arq);

int tamanho_registro();

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario, int numVendas);

void adicionarFunc(FILE *out);

void salva(TFunc *func, FILE *out);

TFunc *le(FILE *in);

void imprime(TFunc *func);

void criarBase(FILE *out, int tam, int min);

void shuffle(int *vet,int MAX,int MIN);

void imprimirBase(FILE *out);

void removerFuncionario(FILE *arquivo, int cod);

void imprimirBaseFun(FILE *out, int n);

#endif // FUNCIONARIO_H_INCLUDED
