
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cliente.h"
#include "fornecedor.h"
#include "funcionario.h"
#include "produto.h"
#include "buscaBinaria.h"
#include "buscaSequencia.h"
#include "selecao_substituicao.h"
#include "intercalacao_otima.h"
#include "mergeSort.h"
#include "interacoes.h"


void limparTela() {
    system("clear");
}

void logTempo(FILE *log, const char *nomeFuncao, double tempo) {
    fprintf(log, "Tempo de execucao da funcao %s: %f segundos.\n", nomeFuncao, tempo);
    fflush(log); // Descarrega o buffer para o arquivo
}

void pausarTela() {
    printf("\nDigite qualquer tecla para prosseguir...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

void mostrarMenuGerenciamento(char categoria[]) {
    printf("=== GERENCIAR %s ===\n\n", categoria);
    printf("1. Criar Base\n");
    printf("2. Adicionar\n");
    printf("3. Remover\n");
    printf("4. Pesquisar\n");
    printf("5. Imprimir Base\n");
    printf("6. Selecao Natural e Intercalacao\n");
    printf("7. Merge Sort Externo\n");
    printf("0. Voltar\n");
    printf("\nEscolha uma opção: ");
}

void mostrarMenuInteracoes() {
    printf("=== INTERACOES ===\n\n");
    printf("1. Realizar Vendas\n");
    printf("2. Realizar Compras\n");
    printf("3. Atualizar estoque\n");
    printf("4. Alterar preco de produto\n");   
    printf("0. Voltar\n");
    printf("\nEscolha uma opção: ");
}

void mostrarMenuPrincipal(FILE *arqfunc, FILE *arqforn, FILE *arqclient, FILE *arqprod,FILE *logFile,FILE *p0) {
    int opcaoPrincipal, opcaoGerenciamento, opcaointeracao;
    int M = 0;
    clock_t inicio, fim;
    double tempo_execucao;

    do {
        limparTela();
        printf("=== MENU PRINCIPAL ===\n\n");
        printf("1. Gerenciar Funcionário\n");
        printf("2. Gerenciar Cliente\n");
        printf("3. Gerenciar Estoque\n");
        printf("4. Gerenciar Fornecedor\n");
        printf("5. Interacoes\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                do{
                    limparTela();
                    mostrarMenuGerenciamento("Funcionário");
                    scanf("%d", &opcaoGerenciamento);

                    switch (opcaoGerenciamento) {
                        case 1:
                            limparTela();
                            int opcao;
                            printf("Qual o numero da base que deseja criar :");
                            scanf("%d", &opcao);
                            inicio = clock();
                            criarBase(arqfunc, opcao, 0);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Criar Base Funcionario", tempo_execucao);
                            imprimirBase(arqfunc);
                            pausarTela();
                            break;
                        case 2:
                            limparTela();
                            inicio = clock();
                            adicionarFunc(arqfunc);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Adicionar Funcionario", tempo_execucao);
                            pausarTela();
                            break;
                        case 3:
                            limparTela();
                            int remover, final = tamanho_arquivo(arqfunc);
                            printf("\nDigite o código do funcionário que deseja remover: ");
                            scanf("%d", &remover);
                            inicio = clock();
                            removerFuncionario(arqfunc, remover);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Remover Funcionario", tempo_execucao);
                            pausarTela();
                            break;
                        case 4:
                            limparTela();
                            int cod, fim = tamanho_arquivo(arqfunc);
                            printf("\nDigite o código do funcionário que deseja pesquisar: ");
                            scanf("%d", &cod);

                            int opcaoBusca;
                            printf("Escolha o método de busca:\n");
                            printf("1. Busca Binária\n");
                            printf("2. Busca Sequencial\n");
                            printf("Escolha uma opção: ");
                            scanf("%d", &opcaoBusca);

                            switch (opcaoBusca) {
                                case 1:
                                    limparTela();
                                    printf("Escolheu Busca Binária.\n");
                                    inicio = clock();
                                    TFunc *resultado_busca_binaria = busca_binaria(cod, arqfunc, 0, fim);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Binaria Funcionario", tempo_execucao);
                                    if (resultado_busca_binaria != NULL) {
                                        imprime(resultado_busca_binaria);
                                        pausarTela();
                                    } else {
                                        printf("Funcionário não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                case 2:
                                    limparTela();
                                    printf("Escolheu Busca Sequencial.\n");
                                    inicio = clock();
                                    TFunc *resultado_busca_sequencial = buscaSequencial(cod, arqfunc);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Binaria Sequencial", tempo_execucao);
                                    if (resultado_busca_sequencial != NULL) {
                                        imprime(resultado_busca_sequencial);
                                        pausarTela();
                                    } else {
                                        printf("Funcionário não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                default:
                                    limparTela();
                                    printf("Opção inválida. Por favor, escolha novamente.\n");
                                    pausarTela();
                            }
                            break;
                        case 5:
                            limparTela();
                            imprimirBase(arqfunc);
                            pausarTela();
                            break;
                        case 6:
                            limparTela();
                            inicio = clock();
                            char nomeDaParticao[20];
                            snprintf(nomeDaParticao, sizeof(nomeDaParticao), "particao");

                            int numParticoes = selecaoSubstituicaoF(arqfunc, nomeDaParticao, 6);

                            if (numParticoes > 1) {
                                printf("Intercalando...\n");
                                intercalacaoF(arqfunc, nomeDaParticao, numParticoes, 4);
                            } else {
                                sprintf(nomeDaParticao, "%s%05d.dat", nomeDaParticao, 0);
                                FILE *out = fopen(nomeDaParticao, "w+b");
                                if (out == NULL) {
                                    perror("Erro ao abrir arquivo de saida.");
                                    exit(EXIT_FAILURE);
                                }
                                sobrescreverArquivoF(arqfunc, out, tamanho_registro());
                                fclose(out);
                            }
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Intercalacao Funcionario", tempo_execucao);
                            //imprimirBaseFun(arqfunc, 50);
                            imprimirBase(arqfunc);
                            pausarTela();
                            break;
                        case 7:
                            limparTela();
                            inicio = clock();
                            mergeSort(arqfunc, 0, tamanho_arquivo(arqfunc)-1);
                            imprimirBase(arqfunc);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Merge Funcionario", tempo_execucao);
                            pausarTela();
                            break;
                        case 0:
                            limparTela();
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            limparTela();
                            printf("\nOpção inválida. Por favor, escolha novamente.\n");
                            pausarTela();
                            break;
                    }
                } while (opcaoGerenciamento != 0);
            break;

            case 2:
                do{
                    limparTela();
                    mostrarMenuGerenciamento("Cliente");
                    scanf("%d", &opcaoGerenciamento);

                    switch (opcaoGerenciamento) {
                        case 1:
                            limparTela();
                            int opcao;
                            printf("Qual o numero da base que deseja criar :");
                            scanf("%d", &opcao);
                            inicio = clock();
                            criarBaseClient(arqclient, opcao, 0);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Criar Base Cliente", tempo_execucao);
                            imprimirBaseClient(arqclient);
                            pausarTela();
                            break;
                        case 2:
                            limparTela();
                            inicio = clock();
                            adicionarClient(arqclient);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Adicionar Cliente", tempo_execucao);
                            pausarTela();
                            break;
                        case 3:
                            limparTela();
                            int remover, final = tamanho_arquivoClient(arqclient);
                            printf("\nDigite o código do cliente que deseja remover: ");
                            scanf("%d", &remover);
                            inicio = clock();
                            removerCliente(arqclient, remover);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Remover Cliente", tempo_execucao);
                            pausarTela();
                            break;
                        case 4:
                            limparTela();
                            int cod, fim = tamanho_arquivoClient(arqclient);
                            printf("\nDigite o código do cliente que deseja pesquisar: ");
                            scanf("%d", &cod);

                            int opcaoBusca;
                            printf("Escolha o método de busca:\n");
                            printf("1. Busca Binária\n");
                            printf("2. Busca Sequencial\n");
                            printf("Escolha uma opção: ");
                            scanf("%d", &opcaoBusca);

                            switch (opcaoBusca) {
                                case 1:
                                    limparTela();
                                    printf("Escolheu Busca Binária.\n");
                                    inicio = clock();
                                    TClient *resultado_busca_binaria_client = busca_binaria_client(cod, arqclient, 0, fim);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Binaria Cliente", tempo_execucao);
                                    if (resultado_busca_binaria_client != NULL) {
                                        imprimeClient(resultado_busca_binaria_client);
                                        pausarTela();
                                    } else {
                                        printf("Cliente não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                case 2:
                                    limparTela();
                                    printf("Escolheu Busca Sequencial.\n");
                                    inicio = clock();
                                    TClient *resultado_busca_sequencial_client = buscaSequencialClient(cod, arqclient);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Sequencial Cliente", tempo_execucao);
                                    if (resultado_busca_sequencial_client != NULL) {
                                        imprimeClient(resultado_busca_sequencial_client);
                                        pausarTela();
                                    } else {
                                        printf("Cliente não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                default:
                                    printf("Opção inválida. Por favor, escolha novamente.\n");
                                    pausarTela();
                            }
                            break;

                        case 5:
                            imprimirBaseClient(arqclient);
                            pausarTela();
                            break;
                        case 6:
                            limparTela();
                            inicio = clock();
                            char nomeDaParticaoClient[20];
                            snprintf(nomeDaParticaoClient, sizeof(nomeDaParticaoClient), "particao");

                            int numParticoesClient = selecaoSubstituicaoClient(arqclient, nomeDaParticaoClient, 6);

                            if (numParticoesClient > 1) {
                                printf("Intercalando...\n");
                                intercalacaoClient(arqclient, nomeDaParticaoClient, numParticoesClient, 4);
                                printf("Concluido!");

                            } else {
                                sprintf(nomeDaParticaoClient, "%s%05d.dat", nomeDaParticaoClient, 0);
                                FILE *outClient = fopen(nomeDaParticaoClient, "w+b");
                                if (outClient == NULL) {
                                    perror("Erro ao abrir arquivo de saida.");
                                    exit(EXIT_FAILURE);
                                }
                                sobrescreverArquivoClient(arqclient, outClient, tamanho_registroClient());
                                fclose(outClient);
                            }
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Intercalacao Cliente", tempo_execucao);
                            imprimirBaseCli(arqclient, 50);
                            pausarTela();
                            break;

                        case 7:
                            limparTela();
                            inicio = clock();
                            mergeSortCliente(arqclient, 0, tamanho_arquivoClient(arqclient)-1);
                            imprimirBaseClient(arqclient);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Merge Cliente", tempo_execucao);
                            pausarTela();
                            break;
                        case 0:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("\nOpção inválida. Por favor, escolha novamente.\n");
                            pausarTela();
                            break;
                    }
                } while (opcaoGerenciamento != 0);
            break;

            case 3:
                do{
                    limparTela();
                    mostrarMenuGerenciamento("Estoque");
                    scanf("%d", &opcaoGerenciamento);

                    switch (opcaoGerenciamento) {
                        case 1:
                            limparTela();
                            int opcao;
                            printf("Qual o numero da base que deseja criar :");
                            scanf("%d", &opcao);
                            inicio = clock();
                            criarBaseProd(arqprod, opcao, 0);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Criar Base Produtos", tempo_execucao);
                            imprimirBaseProd(arqprod);
                            pausarTela();
                            break;
                        case 2:
                            limparTela();
                            inicio = clock();
                            adicionarProd(arqprod);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Adicionar Produto", tempo_execucao);
                            pausarTela();
                            break;
                        case 3:
                            limparTela();
                            int remover, final = tamanho_arquivoProd(arqprod);
                            printf("\nDigite o código do produto que deseja remover: ");
                            scanf("%d", &remover);
                            inicio = clock();
                            removerProduto(arqprod, remover);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Remover Produto", tempo_execucao);
                            pausarTela();
                            break;
                        case 4:
                            limparTela();
                            int cod, fim = tamanho_arquivoProd(arqprod);
                            printf("\nDigite o código do produto que deseja pesquisar: ");
                            scanf("%d", &cod);

                            int opcaoBusca;
                            printf("Escolha o método de busca:\n");
                            printf("1. Busca Binária\n");
                            printf("2. Busca Sequencial\n");
                            printf("Escolha uma opção: ");
                            scanf("%d", &opcaoBusca);

                            switch (opcaoBusca) {
                                case 1:
                                    limparTela();
                                    printf("Escolheu Busca Binária.\n");
                                    inicio = clock();
                                    TProd *resultado_busca_binaria_prod = busca_binaria_prod(cod, arqprod, 0, fim);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Binaria Produto", tempo_execucao);
                                    if (resultado_busca_binaria_prod != NULL) {
                                        imprimeProd(resultado_busca_binaria_prod);
                                        pausarTela();
                                    } else {
                                        printf("Produto não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                case 2:
                                    limparTela();
                                    printf("Escolheu Busca Sequencial.\n");
                                    inicio = clock();
                                    TProd *resultado_busca_sequencial_prod = buscaSequencialProd(cod, arqprod);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Sequencial Produto", tempo_execucao);
                                    if (resultado_busca_sequencial_prod != NULL) {
                                        imprimeProd(resultado_busca_sequencial_prod);
                                        pausarTela();
                                    } else {
                                        printf("Produto não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                default:
                                    printf("Opção inválida. Por favor, escolha novamente.\n");
                                    pausarTela();
                            }
                            break;

                        case 5:
                            imprimirBaseProd(arqprod);
                            pausarTela();
                            break;
                        case 6:
                            limparTela();
                            inicio = clock();
                            char nomeDaParticaoProd[20];
                            snprintf(nomeDaParticaoProd, sizeof(nomeDaParticaoProd), "particao");

                            int numParticoesProd = selecaoSubstituicaoProd(arqprod, nomeDaParticaoProd, 6);

                            if (numParticoesProd > 1) {
                                printf("Intercalando...\n");
                                intercalacaoProd(arqprod, nomeDaParticaoProd, numParticoesProd, 4);
                            } else {
                                sprintf(nomeDaParticaoProd, "%s%05d.dat", nomeDaParticaoProd, 0);
                                FILE *outProd = fopen(nomeDaParticaoProd, "w+b");
                                if (outProd == NULL) {
                                    perror("Erro ao abrir arquivo de saida.");
                                    exit(EXIT_FAILURE);
                                }
                                sobrescreverArquivoProd(arqprod, outProd, tamanho_registroProd());
                                fclose(outProd);
                            }
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Intercalacao Produto", tempo_execucao);
                            imprimirBasePr(arqprod, 50);
                            pausarTela();
                            break;

                        case 7:
                            limparTela();
                            inicio = clock();
                            mergeSortProduto(arqprod, 0, tamanho_arquivoProd(arqprod)-1);
                            imprimirBaseProd(arqprod);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Merge Produto", tempo_execucao);
                            pausarTela();
                            break;
                        case 0:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("\nOpção inválida. Por favor, escolha novamente.\n");
                            pausarTela();
                            break;
                    }
                } while (opcaoGerenciamento != 0);
            break;

            case 4:
                do{
                    limparTela();
                    mostrarMenuGerenciamento("Fornecedor");
                    scanf("%d", &opcaoGerenciamento);

                    switch (opcaoGerenciamento) {
                        case 1:
                            limparTela();
                            int opcao;
                            printf("Qual o numero da base que deseja criar :");
                            scanf("%d", &opcao);
                            inicio = clock();
                            criarBaseFor(arqforn, opcao, 0);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Criar Base Fornecedor", tempo_execucao);
                            imprimirBaseFor(arqforn);
                            pausarTela();
                            break;
                        case 2:
                            limparTela();
                            inicio = clock();
                            adicionarForn(arqforn);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Adicionar Fornecedor", tempo_execucao);
                            pausarTela();
                            break;
                        case 3:
                            limparTela();
                            int remover, final = tamanho_arquivoFor(arqforn);
                            printf("\nDigite o código do fornecedor que deseja remover: ");
                            scanf("%d", &remover);
                            inicio = clock();
                            removerFornecedor(arqforn, remover);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Remover Fornecedor", tempo_execucao);
                            pausarTela();
                            break;
                        case 4:
                            limparTela();
                            int cod, fim = tamanho_arquivoFor(arqforn);
                            printf("\nDigite o código do fornecedor que deseja pesquisar: ");
                            scanf("%d", &cod);

                            int opcaoBusca;
                            printf("Escolha o método de busca:\n");
                            printf("1. Busca Binária\n");
                            printf("2. Busca Sequencial\n");
                            printf("Escolha uma opção: ");
                            scanf("%d", &opcaoBusca);

                            switch (opcaoBusca) {
                                case 1:
                                    limparTela();
                                    printf("Escolheu Busca Binária.\n");
                                    inicio = clock();
                                    TFor *resultado_busca_binaria_forn = busca_binaria_forn(cod, arqforn, 0, fim);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Binaria Fornecedor", tempo_execucao);
                                    if (resultado_busca_binaria_forn != NULL) {
                                        imprimeFor(resultado_busca_binaria_forn);
                                        pausarTela();
                                    } else {
                                        printf("Fornecedor não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                case 2:
                                    limparTela();
                                    printf("Escolheu Busca Sequencial.\n");
                                    inicio = clock();
                                    TFor *resultado_busca_sequencial_forn = buscaSequencialFor(cod, arqforn);
                                    fim = clock();
                                    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                                    logTempo(logFile, "Busca Sequencial Fornecedor", tempo_execucao);
                                    if (resultado_busca_sequencial_forn != NULL) {
                                        imprimeFor(resultado_busca_sequencial_forn);
                                        pausarTela();
                                    } else {
                                        printf("Fornecedor não encontrado.\n");
                                        pausarTela();
                                    }
                                    break;

                                default:
                                    printf("Opção inválida. Por favor, escolha novamente.\n");
                                    pausarTela();
                            }
                            break;

                        case 5:
                            imprimirBaseFor(arqforn);
                            pausarTela();
                            break;
                        case 6:
                            limparTela();
                            inicio = clock();
                            char nomeDaParticaoFor[20];
                            snprintf(nomeDaParticaoFor, sizeof(nomeDaParticaoFor), "particao");

                            int numParticoesFor = selecaoSubstituicaoFor(arqforn, nomeDaParticaoFor, 6);

                            if (numParticoesFor > 1) {
                                printf("Intercalando...\n");
                                intercalacaoFor(arqforn, nomeDaParticaoFor, numParticoesFor, 4);
                            } else {
                                sprintf(nomeDaParticaoFor, "%s%05d.dat", nomeDaParticaoFor, 0);
                                FILE *outFor = fopen(nomeDaParticaoFor, "w+b");
                                if (outFor == NULL) {
                                    perror("Erro ao abrir arquivo de saida.");
                                    exit(EXIT_FAILURE);
                                }
                                sobrescreverArquivoFor(arqforn, outFor, tamanho_registroFor());
                                fclose(outFor);
                            }
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Intercalacao Fornecedor", tempo_execucao);
                            imprimirBaseFo(arqforn, 50);
                            pausarTela();
                            break;

                        case 7:
                            limparTela();
                            inicio = clock();
                            mergeSortFornecedor(arqforn, 0, tamanho_arquivoFor(arqforn)-1);
                            imprimirBaseFor(arqforn);
                            fim = clock();
                            tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                            logTempo(logFile, "Merge Fornecedor", tempo_execucao);
                            pausarTela();
                            break;
                        case 0:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("\nOpção inválida. Por favor, escolha novamente.\n");
                            pausarTela();
                            break;
                    }
                } while (opcaoGerenciamento != 0);
            break;

            case 5:            
                do{
                    limparTela();
                    mostrarMenuInteracoes();
                    scanf("%d", &opcaointeracao);
                    switch (opcaointeracao) {
                        case 1:
                            limparTela();
                            int cfunc, cprod, cclient;
                            printf("\nDigite o código do funcionario que realizou a venda: ");
                            scanf("%d", &cfunc);
                            limparTela();
                            printf("\nDigite o código do cliente que realizou a compra: ");
                            scanf("%d", &cclient);
                            limparTela();
                            printf("\nDigite o código do produto comprado: ");
                            scanf("%d", &cprod);
                            limparTela();
                            realizarVenda(cprod, cfunc, cclient, arqprod, arqfunc, arqclient);
                            pausarTela();
                            break;

                        case 2:
                            limparTela();
                            int cofunc, coprod, coclient;
                            printf("\nDigite o código do cliente que realizou a compra: ");
                            scanf("%d", &coclient);
                            limparTela();
                            printf("\nDigite o código do funcionario que atendeu o cliente: ");
                            scanf("%d", &cofunc);
                            limparTela();
                            printf("\nDigite o código do produto comprado: ");
                            scanf("%d", &coprod);
                            limparTela();
                            realizarCompra(coprod, cofunc, coclient, arqprod, arqfunc, arqclient);
                            pausarTela();
                            break;

                        case 3:
                            limparTela();
                            adicionarProdutoFornecedor(arqprod, arqforn);
                            pausarTela();
                            break;

                        case 4:
                            limparTela();
                            alterarPrecoProdutoFornecedor(arqprod, arqforn);
                            pausarTela();
                            break;

                        case 0:
                            limparTela();
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            limparTela();
                            printf("\nOpção inválida. Por favor, escolha novamente.\n");
                            pausarTela();
                            break;
                    }
                }while (opcaointeracao != 0);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("\nOpção inválida. Por favor, escolha novamente.\n");
                pausarTela();
                break;
        }
    } while (opcaoPrincipal != 0);
}



