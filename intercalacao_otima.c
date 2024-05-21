#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "intercalacao_otima.h"
#include "funcionario.h"
#include "cliente.h"
#include "produto.h"
#include "fornecedor.h"

typedef struct {
    TFunc *funcionario;
    FILE *arquivo;
    int posicao;
} TVetorF;

void intercalacaoF(FILE *out, char *nome, int totalParticoes, int F) {
    TVetorF *vetor = (TVetorF *)malloc(F * sizeof(TVetorF));
    int particoesLidas = 0;
    int particoesGeradas = 0;
    int particoesAtualizadas = 1;
    int particoesProcessadas = F - 1;
    int numParticoes = totalParticoes;
    char nomeParticao[20];

    while (numParticoes > 1) {
        for (int i = 0; i < particoesProcessadas; i++) {
            snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, particoesLidas);
            vetor[i].arquivo = fopen(nomeParticao, "rb");
            vetor[i].posicao = 0;

            if (vetor[i].arquivo != NULL) {
                fseek(vetor[i].arquivo, vetor[i].posicao * tamanho_registro(), SEEK_SET);
                TFunc *f = le(vetor[i].arquivo);

                if (f != NULL) {
                    vetor[i].funcionario = f;
                } else {
                    vetor[i].funcionario = funcionario(INT_MAX, "", "", "", 0.0, 0);
                }
            }
            particoesLidas++;
        }

        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes + particoesGeradas);
        particoesGeradas++;
        vetor[particoesProcessadas].arquivo = fopen(nomeParticao, "w+b");

        if (vetor[particoesProcessadas].arquivo == NULL) {
            perror("Erro ao abrir novo arquivo de saida.");
            exit(EXIT_FAILURE);
        }

        vetor[particoesProcessadas].posicao = 0;

        while (1) {
            int menorISBN = INT_MAX;
            int indiceMenor = -1;

            for (int i = 0; i < particoesProcessadas; i++) {
                if (vetor[i].funcionario->cod < menorISBN) {
                    menorISBN = vetor[i].funcionario->cod;
                    indiceMenor = i;
                }
            }

            if (menorISBN == INT_MAX) {
                break;
            }

            fseek(vetor[particoesProcessadas].arquivo, vetor[particoesProcessadas].posicao * tamanho_registro(), SEEK_SET);
            salva(vetor[indiceMenor].funcionario, vetor[particoesProcessadas].arquivo);
            vetor[particoesProcessadas].posicao++;
            vetor[indiceMenor].posicao++;
            fseek(vetor[indiceMenor].arquivo, vetor[indiceMenor].posicao * tamanho_registro(), SEEK_SET);

            TFunc *proximoRegistro = le(vetor[indiceMenor].arquivo);

            if (proximoRegistro != NULL) {
                vetor[indiceMenor].funcionario = proximoRegistro;
            } else {
                vetor[indiceMenor].funcionario = funcionario(INT_MAX, "", "", "", 0.0, 0);
            }
        }

        numParticoes += particoesAtualizadas - particoesProcessadas;
    }

    sobrescreverArquivoF(out, vetor[particoesProcessadas].arquivo, tamanho_registro());

    for (int i = 0; i < particoesProcessadas; i++) {
        fclose(vetor[i].arquivo);
        free(vetor[i].funcionario);
    }
    free(vetor);
}

void sobrescreverArquivoF(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro) {
    for (int i = 0; i < tamanho_arquivo(arquivoOriginal); i++) {
        fseek(arquivoOriginal, i * tamanhoRegistro, SEEK_SET);
        fseek(novoArquivo, i * tamanhoRegistro, SEEK_SET);
        TFunc *f = le(novoArquivo);
        if (f != NULL) {
            salva(f, arquivoOriginal);
        }
    }
}

// Estrutura TClient
typedef struct {
    TClient *cliente;
    FILE *arquivo;
    int posicao;
} TVetorClient;

void intercalacaoClient(FILE *out, char *nome, int totalParticoes, int F) {
    TVetorClient *vetor = (TVetorClient *)malloc(F * sizeof(TVetorClient));
    int particoesLidas = 0;
    int particoesGeradas = 0;
    int particoesAtualizadas = 1;
    int particoesProcessadas = F - 1;
    int numParticoes = totalParticoes;
    char nomeParticao[20];

    while (numParticoes > 1) {
        int todosArquivosVazios = 1;

        for (int i = 0; i < particoesProcessadas; i++) {
            snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, particoesLidas);
            vetor[i].arquivo = fopen(nomeParticao, "rb");
            vetor[i].posicao = 0;

            if (vetor[i].arquivo != NULL) {
                fseek(vetor[i].arquivo, vetor[i].posicao * tamanho_registroClient(), SEEK_SET);
                TClient *c = leClient(vetor[i].arquivo);

                if (c != NULL) {
                    vetor[i].cliente = c;
                    todosArquivosVazios = 0;
                } else {
                    vetor[i].cliente = client(INT_MAX, "", "", "", 0);
                }
            }
            particoesLidas++;
        }

        if (todosArquivosVazios) {
            break;
        }

        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes + particoesGeradas);
        particoesGeradas++;
        vetor[particoesProcessadas].arquivo = fopen(nomeParticao, "w+b");

        if (vetor[particoesProcessadas].arquivo == NULL) {
            perror("Erro ao abrir novo arquivo de saida.");
            exit(EXIT_FAILURE);
        }

        vetor[particoesProcessadas].posicao = 0;

        while (1) {
            int menorCodigo = INT_MAX;
            int indiceMenor = -1;

            for (int i = 0; i < particoesProcessadas; i++) {
                if (vetor[i].cliente->cod < menorCodigo) {
                    menorCodigo = vetor[i].cliente->cod;
                    indiceMenor = i;
                }
            }

            if (menorCodigo == INT_MAX) {
                break;
            }

            fseek(vetor[particoesProcessadas].arquivo, vetor[particoesProcessadas].posicao * tamanho_registroClient(), SEEK_SET);
            salvaClient(vetor[indiceMenor].cliente, vetor[particoesProcessadas].arquivo);
            vetor[particoesProcessadas].posicao++;
            vetor[indiceMenor].posicao++;
            fseek(vetor[indiceMenor].arquivo, vetor[indiceMenor].posicao * tamanho_registroClient(), SEEK_SET);

            TClient *proximoRegistro = leClient(vetor[indiceMenor].arquivo);

            if (proximoRegistro != NULL) {
                vetor[indiceMenor].cliente = proximoRegistro;
            } else {
                vetor[indiceMenor].cliente = client(INT_MAX, "", "", "", 0);
            }
        }

        numParticoes += particoesAtualizadas - particoesProcessadas;
    }

    sobrescreverArquivoClient(out, vetor[particoesProcessadas].arquivo, tamanho_registroClient());

    for (int i = 0; i < particoesProcessadas; i++) {
        fclose(vetor[i].arquivo);
        free(vetor[i].cliente);
    }
    free(vetor);
}

void sobrescreverArquivoClient(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro) {
    for (int i = 0; i < tamanho_arquivoClient(arquivoOriginal); i++) {
        fseek(arquivoOriginal, i * tamanhoRegistro, SEEK_SET);
        fseek(novoArquivo, i * tamanhoRegistro, SEEK_SET);
        TClient *c = leClient(novoArquivo);
        if (c != NULL) {
            salvaClient(c, arquivoOriginal);
        }
    }
}
// Estrutura TFor
typedef struct {
    TFor *fornecedor;
    FILE *arquivo;
    int posicao;
} TVetorFor;

void intercalacaoFor(FILE *out, char *nome, int totalParticoes, int F) {
    TVetorFor *vetor = (TVetorFor *)malloc(F * sizeof(TVetorFor));
    int particoesLidas = 0;
    int particoesGeradas = 0;
    int particoesAtualizadas = 1;
    int particoesProcessadas = F - 1;
    int numParticoes = totalParticoes;
    char nomeParticao[20];

    while (numParticoes > 1) {
        int todosArquivosVazios = 1;

        for (int i = 0; i < particoesProcessadas; i++) {
            snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, particoesLidas);
            vetor[i].arquivo = fopen(nomeParticao, "rb");
            vetor[i].posicao = 0;

            if (vetor[i].arquivo != NULL) {
                fseek(vetor[i].arquivo, vetor[i].posicao * tamanho_registroFor(), SEEK_SET);
                TFor *f = leFor(vetor[i].arquivo);

                if (f != NULL) {
                    vetor[i].fornecedor = f;
                    todosArquivosVazios = 0;
                } else {
                    vetor[i].fornecedor = fornecedor(INT_MAX, "", "", 0);
                }
            }
            particoesLidas++;
        }

        if (todosArquivosVazios) {
            break;
        }

        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes + particoesGeradas);
        particoesGeradas++;
        vetor[particoesProcessadas].arquivo = fopen(nomeParticao, "w+b");

        if (vetor[particoesProcessadas].arquivo == NULL) {
            perror("Erro ao abrir novo arquivo de saida.");
            exit(EXIT_FAILURE);
        }

        vetor[particoesProcessadas].posicao = 0;

        while (1) {
            int menorCodigo = INT_MAX;
            int indiceMenor = -1;

            for (int i = 0; i < particoesProcessadas; i++) {
                if (vetor[i].fornecedor->cod < menorCodigo) {
                    menorCodigo = vetor[i].fornecedor->cod;
                    indiceMenor = i;
                }
            }

            if (menorCodigo == INT_MAX) {
                break;
            }

            fseek(vetor[particoesProcessadas].arquivo, vetor[particoesProcessadas].posicao * tamanho_registroFor(), SEEK_SET);
            salvaFor(vetor[indiceMenor].fornecedor, vetor[particoesProcessadas].arquivo);
            vetor[particoesProcessadas].posicao++;
            vetor[indiceMenor].posicao++;
            fseek(vetor[indiceMenor].arquivo, vetor[indiceMenor].posicao * tamanho_registroFor(), SEEK_SET);

            TFor *proximoRegistro = leFor(vetor[indiceMenor].arquivo);

            if (proximoRegistro != NULL) {
                vetor[indiceMenor].fornecedor = proximoRegistro;
            } else {
                vetor[indiceMenor].fornecedor = fornecedor(INT_MAX, "", "", 0);
            }
        }

        numParticoes += particoesAtualizadas - particoesProcessadas;
    }

    sobrescreverArquivoFor(out, vetor[particoesProcessadas].arquivo, tamanho_registroFor());

    for (int i = 0; i < particoesProcessadas; i++) {
        fclose(vetor[i].arquivo);
        free(vetor[i].fornecedor);
    }
    free(vetor);
}

void sobrescreverArquivoFor(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro) {
    for (int i = 0; i < tamanho_arquivoFor(arquivoOriginal); i++) {
        fseek(arquivoOriginal, i * tamanhoRegistro, SEEK_SET);
        fseek(novoArquivo, i * tamanhoRegistro, SEEK_SET);
        TFor *f = leFor(novoArquivo);
        if (f != NULL) {
            salvaFor(f, arquivoOriginal);
        }
    }
}

// Estrutura TProd
typedef struct {
    TProd *produto;
    FILE *arquivo;
    int posicao;
} TVetorProd;

void intercalacaoProd(FILE *out, char *nome, int totalParticoes, int F) {
    TVetorProd *vetor = (TVetorProd *)malloc(F * sizeof(TVetorProd));
    int particoesLidas = 0;
    int particoesGeradas = 0;
    int particoesAtualizadas = 1;
    int particoesProcessadas = F - 1;
    int numParticoes = totalParticoes;
    char nomeParticao[20];

    while (numParticoes > 1) {
        for (int i = 0; i < particoesProcessadas; i++) {
            snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, particoesLidas);
            vetor[i].arquivo = fopen(nomeParticao, "rb");
            vetor[i].posicao = 0;

            if (vetor[i].arquivo != NULL) {
                fseek(vetor[i].arquivo, vetor[i].posicao * tamanho_registroProd(), SEEK_SET);
                TProd *p = leProd(vetor[i].arquivo);

                if (p != NULL) {
                    vetor[i].produto = p;
                } else {
                    vetor[i].produto = produto(INT_MAX, "", 0.0, 0);
                }
            }
            particoesLidas++;
        }

        snprintf(nomeParticao, sizeof(nomeParticao), "%s%d.dat", nome, totalParticoes + particoesGeradas);
        particoesGeradas++;
        vetor[particoesProcessadas].arquivo = fopen(nomeParticao, "w+b");

        if (vetor[particoesProcessadas].arquivo == NULL) {
            perror("Erro ao abrir novo arquivo de saida.");
            exit(EXIT_FAILURE);
        }

        vetor[particoesProcessadas].posicao = 0;

        while (1) {
            int menorCodigo = INT_MAX;
            int indiceMenor = -1;

            for (int i = 0; i < particoesProcessadas; i++) {
                if (vetor[i].produto->cod < menorCodigo) {
                    menorCodigo = vetor[i].produto->cod;
                    indiceMenor = i;
                }
            }

            if (menorCodigo == INT_MAX) {
                break;
            }

            fseek(vetor[particoesProcessadas].arquivo, vetor[particoesProcessadas].posicao * tamanho_registroProd(), SEEK_SET);
            salvaProd(vetor[indiceMenor].produto, vetor[particoesProcessadas].arquivo);
            vetor[particoesProcessadas].posicao++;
            vetor[indiceMenor].posicao++;
            fseek(vetor[indiceMenor].arquivo, vetor[indiceMenor].posicao * tamanho_registroProd(), SEEK_SET);

            TProd *proximoRegistro = leProd(vetor[indiceMenor].arquivo);

            if (proximoRegistro != NULL) {
                vetor[indiceMenor].produto = proximoRegistro;
            } else {
                vetor[indiceMenor].produto = produto(INT_MAX, "", 0.0, 0);
            }
        }

        numParticoes += particoesAtualizadas - particoesProcessadas;
    }

    sobrescreverArquivoProd(out, vetor[particoesProcessadas].arquivo, tamanho_registroProd());

    for (int i = 0; i < particoesProcessadas; i++) {
        fclose(vetor[i].arquivo);
        free(vetor[i].produto);
    }
    free(vetor);
}

void sobrescreverArquivoProd(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro) {
    for (int i = 0; i < tamanho_arquivoProd(arquivoOriginal); i++) {
        fseek(arquivoOriginal, i * tamanhoRegistro, SEEK_SET);
        fseek(novoArquivo, i * tamanhoRegistro, SEEK_SET);
        TProd *p = leProd(novoArquivo);
        if (p != NULL) {
            salvaProd(p, arquivoOriginal);
        }
    }
}
