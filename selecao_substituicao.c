#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#include "funcionario.h"
#include "selecao_substituicao.h"
#include "cliente.h"
#include "fornecedor.h"
#include "produto.h"


int selecaoSubstituicaoF(FILE *in, char *nome, int M) {
    rewind(in);
    FILE *out;
    char nomeParticao[20];
    int totalParticoes = 0;
    int totalRegistrosLidos = 0;
    int ultimaChaveGravada = 0;
    int totalRegistros = tamanho_arquivo(in);
    int congelados[M];

    memset(congelados, 0, sizeof(congelados));

    TFunc *func[M];

    while (!feof(in)) {
        fseek(in, totalRegistrosLidos * tamanho_arquivo(in), SEEK_SET);
        func[totalRegistrosLidos] = le(in);
        totalRegistrosLidos++;
        if (totalRegistrosLidos >= M) {
            break;
        }
    }

    snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);

    while (totalRegistrosLidos < totalRegistros) {
        if (existemNaoCongelados(congelados, M)) {
            out = fopen(nomeParticao, "w+b");
            if (out == NULL) {
                perror("Erro ao abrir novo arquivo de saida.");
                exit(EXIT_FAILURE);
            }
        } else {
            continue;
        }

        int temNaoCongelados = 1;

        while (temNaoCongelados && !feof(in)) {
            TFunc *registro = NULL;
            int menorCod = INT_MAX;
            int indice = 0;

            for (int i = 0; i < M; i++) {
                if (congelados[i]) {
                    continue;
                }
                if (func[i]->cod < menorCod) {
                    menorCod = func[i]->cod;
                    registro = func[i];
                    indice = i;
                }
            }

            salva(registro, out);

            ultimaChaveGravada = menorCod;

            fseek(in, totalRegistrosLidos * tamanho_registro(), SEEK_SET);

            TFunc *proximoRegistro = le(in);

            if (proximoRegistro != NULL) {
                func[indice] = proximoRegistro;
            } else {
                func[indice] = NULL;
            }

            totalRegistrosLidos++;

            if (func[indice] == NULL || func[indice]->cod < ultimaChaveGravada) {
                congelados[indice] = 1;
            }

            temNaoCongelados = existemNaoCongelados(congelados, M);
        }

        if (out != NULL) {
            fclose(out);
        }

        for (int i = 0; i < M; i++) {
            if (func[i] != NULL) {
                congelados[i] = 0;
            }
        }

        totalParticoes++;
        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);
    }

    fflush(in);

    liberarRegistros(func, M);

    return totalParticoes;
}

int existemNaoCongelados(int *congelados, int n) {
    for (int i = 0; i < n; i++) {
        if (!congelados[i]) {
            return 1;
        }
    }
    return 0;
}

void liberarRegistros(TFunc **func, int M) {
    for (int i = 0; i < M; i++) {
        if (func[i] != NULL) {
            free(func[i]);
        }
    }
}



int selecaoSubstituicaoClient(FILE *in, char *nome, int M) {
    rewind(in);
    FILE *out;
    char nomeParticao[20];
    int totalParticoes = 0;
    int totalRegistrosLidos = 0;
    int ultimaChaveGravada = 0;
    int totalRegistros = tamanho_arquivoClient(in);
    int congelados[M];

    memset(congelados, 0, sizeof(congelados));

    TClient *clients[M];

    while (!feof(in)) {
        fseek(in, totalRegistrosLidos * tamanho_arquivoClient(in), SEEK_SET);
        clients[totalRegistrosLidos] = leClient(in);
        totalRegistrosLidos++;
        if (totalRegistrosLidos >= M) {
            break;
        }
    }

    snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);

    while (totalRegistrosLidos < totalRegistros) {
        if (existemNaoCongelados(congelados, M)) {
            out = fopen(nomeParticao, "w+b");
            if (out == NULL) {
                perror("Erro ao abrir novo arquivo de saida.");
                exit(EXIT_FAILURE);
            }
        } else {
            continue;
        }

        int temNaoCongelados = 1;

        while (temNaoCongelados && !feof(in)) {
            TClient *registro = NULL;
            int menorCod = INT_MAX;
            int indice = 0;

            for (int i = 0; i < M; i++) {
                if (congelados[i]) {
                    continue;
                }
                if (clients[i]->cod < menorCod) {
                    menorCod = clients[i]->cod;
                    registro = clients[i];
                    indice = i;
                }
            }

            salvaClient(registro, out);

            ultimaChaveGravada = menorCod;

            fseek(in, totalRegistrosLidos * tamanho_registroClient(), SEEK_SET);

            TClient *proximoRegistro = leClient(in);

            if (proximoRegistro != NULL) {
                clients[indice] = proximoRegistro;
            } else {
                clients[indice] = NULL;
            }

            totalRegistrosLidos++;

            if (clients[indice] == NULL || clients[indice]->cod < ultimaChaveGravada) {
                congelados[indice] = 1;
            }

            temNaoCongelados = existemNaoCongelados(congelados, M);
        }

        if (out != NULL) {
            fclose(out);
        }

        for (int i = 0; i < M; i++) {
            if (clients[i] != NULL) {
                congelados[i] = 0;
            }
        }

        totalParticoes++;
        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);
    }

    fflush(in);

    liberarRegistrosClient(clients, M);

    return totalParticoes;
}

int selecaoSubstituicaoFor(FILE *in, char *nome, int M) {
    rewind(in);
    FILE *out;
    char nomeParticao[20];
    int totalParticoes = 0;
    int totalRegistrosLidos = 0;
    int ultimaChaveGravada = 0;
    int totalRegistros = tamanho_arquivoFor(in);
    int congelados[M];

    memset(congelados, 0, sizeof(congelados));

    TFor *forn[M];

    while (!feof(in)) {
        fseek(in, totalRegistrosLidos * tamanho_arquivoFor(in), SEEK_SET);
        forn[totalRegistrosLidos] = leFor(in);
        totalRegistrosLidos++;
        if (totalRegistrosLidos >= M) {
            break;
        }
    }

    snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);

    while (totalRegistrosLidos < totalRegistros) {
        if (existemNaoCongelados(congelados, M)) {
            out = fopen(nomeParticao, "w+b");
            if (out == NULL) {
                perror("Erro ao abrir novo arquivo de saida.");
                exit(EXIT_FAILURE);
            }
        } else {
            continue;
        }

        int temNaoCongelados = 1;

        while (temNaoCongelados && !feof(in)) {
            TFor *registro = NULL;
            int menorCod = INT_MAX;
            int indice = 0;

            for (int i = 0; i < M; i++) {
                if (congelados[i]) {
                    continue;
                }
                if (forn[i]->cod < menorCod) {
                    menorCod = forn[i]->cod;
                    registro = forn[i];
                    indice = i;
                }
            }

            salvaFor(registro, out);

            ultimaChaveGravada = menorCod;

            fseek(in, totalRegistrosLidos * tamanho_registroFor(), SEEK_SET);

            TFor *proximoRegistro = leFor(in);

            if (proximoRegistro != NULL) {
                forn[indice] = proximoRegistro;
            } else {
                forn[indice] = NULL;
            }

            totalRegistrosLidos++;

            if (forn[indice] == NULL || forn[indice]->cod < ultimaChaveGravada) {
                congelados[indice] = 1;
            }

            temNaoCongelados = existemNaoCongelados(congelados, M);
        }

        if (out != NULL) {
            fclose(out);
        }

        for (int i = 0; i < M; i++) {
            if (forn[i] != NULL) {
                congelados[i] = 0;
            }
        }

        totalParticoes++;
        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);
    }

    fflush(in);

    liberarRegistrosFor(forn, M);

    return totalParticoes;
}

int selecaoSubstituicaoProd(FILE *in, char *nome, int M) {
    rewind(in);
    FILE *out;
    char nomeParticao[20];
    int totalParticoes = 0;
    int totalRegistrosLidos = 0;
    int ultimaChaveGravada = 0;
    int totalRegistros = tamanho_arquivoProd(in);
    int congelados[M];

    memset(congelados, 0, sizeof(congelados));

    TProd *prods[M];

    while (!feof(in)) {
        fseek(in, totalRegistrosLidos * tamanho_arquivoProd(in), SEEK_SET);
        prods[totalRegistrosLidos] = leProd(in);
        totalRegistrosLidos++;
        if (totalRegistrosLidos >= M) {
            break;
        }
    }

    snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);

    while (totalRegistrosLidos < totalRegistros) {
        if (existemNaoCongelados(congelados, M)) {
            out = fopen(nomeParticao, "w+b");
            if (out == NULL) {
                perror("Erro ao abrir novo arquivo de saida.");
                exit(EXIT_FAILURE);
            }
        } else {
            continue;
        }

        int temNaoCongelados = 1;

        while (temNaoCongelados && !feof(in)) {
            TProd *registro = NULL;
            int menorCod = INT_MAX;
            int indice = 0;

            for (int i = 0; i < M; i++) {
                if (congelados[i]) {
                    continue;
                }
                if (prods[i]->cod < menorCod) {
                    menorCod = prods[i]->cod;
                    registro = prods[i];
                    indice = i;
                }
            }

            salvaProd(registro, out);

            ultimaChaveGravada = menorCod;

            fseek(in, totalRegistrosLidos * tamanho_registroProd(), SEEK_SET);

            TProd *proximoRegistro = leProd(in);

            if (proximoRegistro != NULL) {
                prods[indice] = proximoRegistro;
            } else {
                prods[indice] = NULL;
            }

            totalRegistrosLidos++;

            if (prods[indice] == NULL || prods[indice]->cod < ultimaChaveGravada) {
                congelados[indice] = 1;
            }

            temNaoCongelados = existemNaoCongelados(congelados, M);
        }

        if (out != NULL) {
            fclose(out);
        }

        for (int i = 0; i < M; i++) {
            if (prods[i] != NULL) {
                congelados[i] = 0;
            }
        }

        totalParticoes++;
        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes);
    }

    fflush(in);

    liberarRegistrosProd(prods, M);

    return totalParticoes;
}



void liberarRegistrosClient(TClient **clients, int M) {
    for (int i = 0; i < M; i++) {
        if (clients[i] != NULL) {
            free(clients[i]);
        }
    }
}

void liberarRegistrosFor(TFor **forn, int M) {
    for (int i = 0; i < M; i++) {
        if (forn[i] != NULL) {
            free(forn[i]);
        }
    }
}

void liberarRegistrosProd(TProd **prods, int M) {
    for (int i = 0; i < M; i++) {
        if (prods[i] != NULL) {
            free(prods[i]);
        }
    }
}
