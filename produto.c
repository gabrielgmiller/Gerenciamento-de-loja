#include "produto.h"
#include "buscaBinaria.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>




// Retorna tamanho do funcionario em bytes
int tamanho_registroProd() {
    return sizeof(int)  //cod
            + sizeof(char) * 50 //nome
            + sizeof(double)//preco
            + sizeof(int); // numVendas
}

int tamanho_arquivoProd(FILE *arq)
{
    fseek(arq,0,SEEK_END);
    int tam = (int)(ftell(arq) / tamanho_registroProd());
    return tam;
}

// Cria funcionario.
TProd *produto(int cod, char *nome,double preco, int numVendas) {
    TProd *prod = (TProd *) malloc(sizeof(TProd));
    //inicializa espaco de memoria com ZEROS
    if (prod) memset(prod, 0, sizeof(TProd));
    //copia valores para os campos de prod
    prod->cod = cod;
    strcpy(prod->nome, nome);
    prod->preco = preco;
    prod->numVendas = numVendas;
    return prod;
}


// Salva funcionario no arquivo out, na posicao atual do cursor
void salvaProd(TProd *prod, FILE *out) {
    fwrite(&prod->cod, sizeof(int), 1, out);
    //prod->nome ao inves de &prod->nome, pois string ja eh um ponteiro
    fwrite(prod->nome, sizeof(char), sizeof(prod->nome), out);
    fwrite(&prod->preco, sizeof(double), 1, out);
    fwrite(&prod->numVendas, sizeof(int), 1, out);
}


// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TProd *leProd(FILE *in) {
    TProd *prod = (TProd *) malloc(sizeof(TProd));
    if (0 >= fread(&prod->cod, sizeof(int), 1, in)) {
        free(prod);
        return NULL;
    }
    fread(prod->nome, sizeof(char), sizeof(prod->nome), in);
    fread(&prod->preco, sizeof(double), 1, in);
    fread(&prod->numVendas, sizeof(int), 1, in);
    return prod;
}


// Imprime funcionario
void imprimeProd(TProd *prod) {
    printf("**********************************************");
    printf("\nProduto de codigo ");
    printf("%d", prod->cod);
    printf("\nNome: ");
    printf("%s", prod->nome);
    printf("\nPreco: ");
    printf("%4.2f", prod->preco);
    printf("\nNumero de Vendas: ");
    printf("%d", prod->numVendas);
    printf("\n**********************************************");
}


// Cria a base de dados
void criarBaseProd(FILE *out, int tam, int min){

    int vet[tam];
    TProd *f;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffleProd(vet,tam,min);

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        f = produto(vet[i], "Produto Base", 30*i, vet[i] * 5);
        salvaProd(f, out);
    }

    free(f);

}

//embaralha base de dados
void shuffleProd(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void adicionarProd(FILE *out){
    int cod, numVendas;
    char nome[50], data_nascimento[11];
    double preco;
    TProd *prod;

    printf("Qual o codigo do produto: ");
    scanf("%d", &cod);

    printf("Qual o nome do produto: ");
    getchar(); // Limpar o buffer de entrada
    fgets(nome, sizeof(nome), stdin);

    printf("Qual o preco do produto: ");
    scanf("%lf", &preco);

    printf("Qual o num de vendas do produto: ");
    scanf("%d", &numVendas);

    prod = produto(cod,nome,preco,numVendas);
    salvaProd(prod,out);

    printf("\nProduto salvo com sucesso! ");
}



void imprimirBaseProd(FILE *out){

    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    TProd *f;

    while ((f = leProd(out)) != NULL)
        imprimeProd(f);

    free(f);

}
void imprimirBasePr(FILE *out, int n) {
    printf("\nImprimindo a base de dados...\n");

    int v = 0;
    rewind(out);
    TProd *p;

    while (!feof(out)) {
        p = leProd(out);
        if (p != NULL) {
            if (p->cod != 0 && v <= n-11) {
                imprimeProd(p);
                v++;
            }
            free(p);
        }
    }
}

void removerProduto(FILE *arquivo, int cod) {
    int fim = tamanho_arquivoProd(arquivo);

    TProd *resultado_busca = busca_binaria_prod(cod, arquivo, 0, fim);

    if (resultado_busca != NULL) {
        fseek(arquivo, -tamanho_registroProd(), SEEK_CUR);

        TProd produto_removido;
        memset(&produto_removido, 0, sizeof(TProd));

        fwrite(&produto_removido, sizeof(TProd), 1, arquivo);

        printf("Produto removido com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}
