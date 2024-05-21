#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    int numCompras;
} TClient;

int tamanho_arquivoClient(FILE *arq);

int tamanho_registroClient();

TClient *client(int cod, char *nome, char *cpf, char *data_nascimento, int numCompras);

void salvaClient(TClient *client, FILE *out);

TClient *leClient(FILE *in);

void imprimeClient(TClient *client);

void adicionarClient(FILE *out);

void criarBaseClient(FILE *out, int tam, int min);

void shuffleClient(int *vet,int MAX,int MIN);

void imprimirBaseClient(FILE *out);

void removerCliente(FILE *arquivo, int cod);

void imprimirBaseCli(FILE *out, int n);

#endif // CLIENTE_H_INCLUDED