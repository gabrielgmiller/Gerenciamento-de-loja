#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "funcionario.h"
#include "fornecedor.h"
#include "cliente.h"
#include "interacoes.h"
#include "interface.h"
#include "produto.h"
#include "buscaBinaria.h"
#include "hash.h"

int main() {
    FILE *arqfunc, *logFile, *arqforn, *arqclient, *arqprod, *p0;
    TFunc *f;
    TFor *forn;
    TClient *client;
    TProd *prod;
    const char *fh;

    arqfunc = fopen("arquivo_funcionario.dat", "w+");
    if (arqfunc == NULL) {
        printf("Erro ao abrir o arquivo de funcionário.\n");
        return 1;
    }

    logFile = fopen("log.txt", "w+");
    if (logFile == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    arqforn = fopen("arquivo_fornecedor.dat", "w+");
    if (arqforn == NULL) {
        printf("Erro ao abrir o arquivo de fornecedor.\n");
        return 1;
    }

    arqclient = fopen("arquivo_cliente.dat", "w+");
    if (arqclient == NULL) {
        printf("Erro ao abrir o arquivo de cliente.\n");
        return 1;
    }

    arqprod = fopen("arquivo_produto.dat", "w+");
    if (arqprod == NULL) {
        printf("Erro ao abrir o arquivo de produto.\n");
        return 1;
    }

    p0 = fopen("particao0.dat", "w+");
    if (p0 == NULL) {
        printf("Erro ao abrir o arquivo de produto.\n");
        return 1;
    }

    //mostrarMenuPrincipal(arqfunc, arqforn, arqclient, arqprod,logFile,p0);

    const char *hash_file_name = "hash.dat";
    const char *data_file_name = "data.dat";
    int hash_size = 100; // Escolha um tamanho adequado para sua tabela hash

    FILE *data_file = fopen(data_file_name, "a+b");

    if (data_file == NULL) {
        printf("Erro ao abrir o arquivo de dados\n");
        return 1;
    }


    // Cria a tabela hash
    creates_hash(hash_file_name, hash_size);

    // Cria uma base de dados aleatória
    criarBaseHash(data_file, hash_file_name, data_file_name, hash_size, 10, 1);
    
    FILE *hash_file = fopen(hash_file_name, "r+b");
    if (hash_file == NULL) {
        printf("Erro ao abrir o arquivo hash\n");
        return 1;
    }

    int searchResult = search(5, hash_file, data_file_name, hash_size);

    


    // ... (outras operações)

    // Fecha os arquivos
    fclose(data_file);
    fclose(hash_file);


    fclose(arqfunc);
    fclose(logFile);
    fclose(arqforn);
    fclose(arqclient);
    fclose(arqprod);
    fclose(p0);

    return 0;
}
