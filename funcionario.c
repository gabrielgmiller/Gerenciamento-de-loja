#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "buscaBinaria.h"

int tamanho_arquivo(FILE *arq)
{
    fseek(arq,0,SEEK_END);
    int tam = (int)(ftell(arq) / tamanho_registro());
    return tam;
}

// Retorna tamanho do funcionario em bytes
int tamanho_registro() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double) //salario
            + sizeof(int); //numero de vendas
}


// Cria funcionario.
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario, int numVendas) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    //inicializa espaco de memoria com ZEROS
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    func->numVendas = numVendas;
    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->data_nascimento, data_nascimento);
    func->salario = salario;
    return func;
}


// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    fwrite(&func->numVendas, sizeof(int), 1, out);
    //func->nome ao inves de &func->nome, pois string ja eh um ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}


// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    if (0 >= fread(&func->numVendas, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}


// Imprime funcionario
void imprime(TFunc *func) {
    printf("**********************************************");
    printf("\nFuncionario de codigo ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\nSalario: ");
    printf("%4.2f", func->salario);
    printf("\nVendas Realizadas: ");
    printf("%d", func->numVendas);
    printf("\n**********************************************");
}


// Cria a base de dados
void criarBase(FILE *out, int tam, int min){

    int vet[tam];
    TFunc *f;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,min);

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        f = funcionario(vet[i], "Funcionario Base", "000.000.000-00", "01/01/1980", 3000*i, 0);
        salva(f, out);
    }

    free(f);

}

//embaralha base de dados
void shuffle(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void adicionarFunc(FILE *out){
    int cod;
    char nome[50], cpf[15], data_nascimento[11]; // arrays para armazenar os dados
    double salario;
    TFunc *func;

    printf("Qual o codigo do funcionario: ");
    scanf("%d", &cod);

    printf("Qual o nome do funcionario: ");
    getchar(); // Limpar o buffer de entrada
    fgets(nome, sizeof(nome), stdin);

    printf("Qual o cpf do funcionario: ");
    fgets(cpf, sizeof(cpf), stdin);

    printf("Qual a data de nascimento do funcionario: ");
    fgets(data_nascimento, sizeof(data_nascimento), stdin);

    printf("Qual o salario do funcionario: ");
    scanf("%lf", &salario);

    func = funcionario(cod, nome, cpf, data_nascimento, salario, 0);
    salva(func, out);

    printf("Funcionario salvo com sucesso! ");
}

void imprimirBase(FILE *out) {
    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    TFunc *f;

    while (!feof(out)) {
        f = le(out);
        if (f != NULL) {
            if (f->cod != 0) {
                imprime(f);
            }
            free(f);
        }
    }
}

void imprimirBaseFun(FILE *out, int n) {
    printf("\nImprimindo a base de dados...\n");

    int v = 0;
    rewind(out);
    TFunc *f;

    while (!feof(out)) {
        f = le(out);
        if (f != NULL) {
            if (f->cod != 0 && v <= n-11) {
                imprime(f);
                v++;
            }
            free(f);
        }
    }
}

// Função para remover um funcionário pelo código
void removerFuncionario(FILE *arquivo, int cod) {
    int fim = tamanho_arquivo(arquivo);

    // Busca binária para encontrar o funcionário pelo código
    TFunc *resultado_busca = busca_binaria(cod, arquivo, 0, fim);

    if (resultado_busca != NULL) {
        // Posiciona o ponteiro de arquivo no registro a ser excluído
        fseek(arquivo, -tamanho_registro(), SEEK_CUR);

        // Preenche o registro com zeros ou com um valor indicativo de remoção
        TFunc funcionario_removido;
        memset(&funcionario_removido, 0, sizeof(TFunc)); // preenche com zeros

        // Sobrescreve o registro do funcionário no arquivo com zeros
        fwrite(&funcionario_removido, sizeof(TFunc), 1, arquivo);

        printf("Funcionário removido com sucesso!\n");
    } else {
        printf("Funcionário não encontrado.\n");
    }
}
