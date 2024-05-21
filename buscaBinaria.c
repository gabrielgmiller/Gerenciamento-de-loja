#include "buscaBinaria.h"
#include "funcionario.h"
#include "produto.h"
#include "cliente.h"
#include "fornecedor.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

//Realiza uma busca binaria por um funcionario na base de dados

TFunc *busca_binaria(int chave, FILE *in, int inicio, int fim) {
    TFunc *f = NULL;
    int cod = -1;

    while (inicio <= fim) {
        int meio = (int)((inicio + fim) / 2);

        // Verifica se a posição do arquivo foi ajustada corretamente
        if (fseek(in, (meio - 1) * tamanho_registro(), SEEK_SET) == 0) {
            f = le(in);

            // Verifica se a leitura foi bem-sucedida
            if (f != NULL) {
                cod = f->cod;

                // Verifica se o código foi encontrado
                if (cod == chave) {
                    return f;
                } else if (cod > chave) {
                    fim = meio - 1;
                } else {
                    inicio = meio + 1;
                }
            } else {
                // Trata o erro de leitura
                printf("Erro ao ler os dados.\n");
                break;
            }
        } else {
            // Trata o erro de posicionamento do arquivo
            printf("Erro ao posicionar o arquivo.\n");
            break;
        }
    }

    // Libera a memória alocada se a busca não foi bem-sucedida
    free(f);
    return NULL;
}

TProd *busca_binaria_prod(int chave, FILE *in, int inicio, int fim) {
    TProd *p = NULL;
    int cod = -1;

    while (inicio <= fim) {
        int meio = (int)((inicio + fim) / 2);

        if (fseek(in, (meio - 1) * tamanho_registroProd(), SEEK_SET) == 0) {
            p = leProd(in);

            if (p != NULL) {
                cod = p->cod;

                if (cod == chave) {
                    return p;
                } else if (cod > chave) {
                    fim = meio - 1;
                } else {
                    inicio = meio + 1;
                }
            } else {
                printf("Erro ao ler os dados.\n");
                break;
            }
        } else {
            printf("Erro ao posicionar o arquivo.\n");
            break;
        }
    }

    free(p);
    return NULL;
}

TClient *busca_binaria_client(int chave, FILE *in, int inicio, int fim) {
    TClient *c = NULL;
    int cod = -1;

    while (inicio <= fim) {
        int meio = (int)((inicio + fim) / 2);

        if (fseek(in, (meio - 1) * tamanho_registroClient(), SEEK_SET) == 0) {
            c = leClient(in);

            if (c != NULL) {
                cod = c->cod;

                if (cod == chave) {
                    return c;
                } else if (cod > chave) {
                    fim = meio - 1;
                } else {
                    inicio = meio + 1;
                }
            } else {
                printf("Erro ao ler os dados.\n");
                break;
            }
        } else {
            printf("Erro ao posicionar o arquivo.\n");
            break;
        }
    }

    free(c);
    return NULL;
}

TFor *busca_binaria_forn(int chave, FILE *in, int inicio, int fim) {
    TFor *forn = NULL;
    int cod = -1;

    while (inicio <= fim) {
        int meio = (int)((inicio + fim) / 2);

        if (fseek(in, (meio - 1) * tamanho_registroFor(), SEEK_SET) == 0) {
            forn = leFor(in);

            if (forn != NULL) {
                cod = forn->cod;

                if (cod == chave) {
                    return forn;
                } else if (cod > chave) {
                    fim = meio - 1;
                } else {
                    inicio = meio + 1;
                }
            } else {
                printf("Erro ao ler os dados.\n");
                break;
            }
        } else {
            printf("Erro ao posicionar o arquivo.\n");
            break;
        }
    }

    free(forn);
    return NULL;
}
