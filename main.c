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

    mostrarMenuPrincipal(arqfunc, arqforn, arqclient, arqprod,logFile,p0);

    
    // Fecha os arquivos

    fclose(arqfunc);
    fclose(logFile);
    fclose(arqforn);
    fclose(arqclient);
    fclose(arqprod);
    fclose(p0);

    return 0;
}
