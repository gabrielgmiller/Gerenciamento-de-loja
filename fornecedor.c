#include "fornecedor.h"
#include "buscaBinaria.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int tamanho_arquivoFor(FILE *arq)
{
    fseek(arq,0,SEEK_END);
    int tam = (int)(ftell(arq) / tamanho_registroFor());
    return tam;
}

// Retorna tamanho do fornecedor em bytes
int tamanho_registroFor() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cnpj
            + sizeof(int);
}


// Cria fornecedor.
TFor *fornecedor(int cod, char *nome, char *cnpj, int comissao) {
    TFor *forn = (TFor *) malloc(sizeof(TFor));
    //inicializa espaco de memoria com ZEROS
    if (forn) memset(forn, 0, sizeof(TFor));
    //copia valores para os campos de forn
    forn->cod = cod;
    forn->comissao = comissao;
    strcpy(forn->nome, nome);
    strcpy(forn->cnpj, cnpj);
    return forn;
}


// Salva fornecedor no arquivo out, na posicao atual do cursor
void salvaFor(TFor *forn, FILE *out) {
    fwrite(&forn->cod, sizeof(int), 1, out);
    fwrite(&forn->comissao, sizeof(int), 1, out);
    //forn->nome ao inves de &forn->nome, pois string ja eh um ponteiro
    fwrite(forn->nome, sizeof(char), sizeof(forn->nome), out);
    fwrite(forn->cnpj, sizeof(char), sizeof(forn->cnpj), out);
}


// Le um fornecedor do arquivo in na posicao atual do cursor
// Retorna um ponteiro para fornecedor lido do arquivo
TFor *leFor(FILE *in) {
    TFor *forn = (TFor *) malloc(sizeof(TFor));
    if (0 >= fread(&forn->cod, sizeof(int), 1, in)) {
        free(forn);
        return NULL;
    }
    if (0 >= fread(&forn->comissao, sizeof(int), 1, in)) {
        free(forn);
        return NULL;
    }
    fread(forn->nome, sizeof(char), sizeof(forn->nome), in);
    fread(forn->cnpj, sizeof(char), sizeof(forn->cnpj), in);
    return forn;
}


// Imprime fornecedor
void imprimeFor(TFor *forn) {
    printf("**********************************************");
    printf("\nFornecedor de codigo ");
    printf("%d", forn->cod);
    printf("\nNome: ");
    printf("%s", forn->nome);
    printf("\nCNPJ: ");
    printf("%s", forn->cnpj);
    printf("\nComissao: ");
    printf("%d", forn->comissao);
    printf("\n**********************************************");
}


// Cria a base de dados
void criarBaseFor(FILE *out, int tam, int min){

    int vet[tam];
    TFor *forn;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffleFor(vet,tam,min);

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        forn = fornecedor(vet[i], "Fornecedor", "000.000.000-00", 0);
        salvaFor(forn, out);
    }

    free(forn);

}

//embaralha base de dados
void shuffleFor(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void adicionarForn(FILE *out){
    int cod;
    char nome[50], cnpj[15];
    double salario;
    TFor *forn;

    printf("Qual o codigo do fornecedor: ");
    scanf("%d", &cod);

    printf("Qual o nome do fornecedor: ");
    getchar();
    fgets(nome, sizeof(nome), stdin);

    printf("Qual o cnpj do fornecedor: ");
    fgets(cnpj, sizeof(cnpj), stdin);

    forn = fornecedor(cod, nome, cnpj, 0);
    salvaFor(forn,out);

    printf("\nFornecedor salvo com sucesso! ");
}




void imprimirBaseFor(FILE *out){

    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    TFor *forn;

    while ((forn = leFor(out)) != NULL)
        imprimeFor(forn);

    free(forn);

}
void imprimirBaseFo(FILE *out, int n) {
    printf("\nImprimindo a base de dados...\n");

    int v = 0;
    rewind(out);
    TFor *f;

    while (!feof(out)) {
        f = leFor(out);
        if (f != NULL) {
            if (f->cod != 0 && v <= n-11) {
                imprimeFor(f);
                v++;
            }
            free(f);
        }
    }
}
void removerFornecedor(FILE *arquivo, int cod) {
    int fim = tamanho_arquivoFor(arquivo);

    TFor *resultado_busca = busca_binaria_forn(cod, arquivo, 0, fim);

    if (resultado_busca != NULL) {
        fseek(arquivo, -tamanho_registroFor(), SEEK_CUR);

        TFor fornecedor_removido;
        memset(&fornecedor_removido, 0, sizeof(TFor));

        fwrite(&fornecedor_removido, sizeof(TFor), 1, arquivo);

        printf("Fornecedor removido com sucesso!\n");
    } else {
        printf("Fornecedor não encontrado.\n");
    }
}
