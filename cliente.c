#include "cliente.h"
#include "buscaBinaria.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int tamanho_arquivoClient(FILE *arq)
{
    fseek(arq,0,SEEK_END);
    int tam = (int)(ftell(arq) / tamanho_registroClient());
    return tam;
}

// Retorna tamanho do Client em bytes
int tamanho_registroClient() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(int);  //compras
}


// Cria Client.
TClient *client(int cod, char *nome, char *cpf, char *data_nascimento, int numCompras) {
    TClient *client = (TClient *) malloc(sizeof(TClient));
    //inicializa espaco de memoria com ZEROS
    if (client) memset(client, 0, sizeof(TClient));
    //copia valores para os campos de client
    client->cod = cod;
    client->numCompras = numCompras;
    strcpy(client->nome, nome);
    strcpy(client->cpf, cpf);
    strcpy(client->data_nascimento, data_nascimento);
    return client;
}


// Salva Client no arquivo out, na posicao atual do cursor
void salvaClient(TClient *client, FILE *out) {
    fwrite(&client->cod, sizeof(int), 1, out);
    fwrite(&client->numCompras, sizeof(int), 1, out);
    //client->nome ao inves de &client->nome, pois string ja eh um ponteiro
    fwrite(client->nome, sizeof(char), sizeof(client->nome), out);
    fwrite(client->cpf, sizeof(char), sizeof(client->cpf), out);
    fwrite(client->data_nascimento, sizeof(char), sizeof(client->data_nascimento), out);
}


// Le um Client do arquivo in na posicao atual do cursor
// Retorna um ponteiro para Client lido do arquivo
TClient *leClient(FILE *in) {
    TClient *client = (TClient *) malloc(sizeof(TClient));
    if (0 >= fread(&client->cod, sizeof(int), 1, in)) {
        free(client);
        return NULL;
    }
    if (0 >= fread(&client->numCompras, sizeof(int), 1, in)) {
        free(client);
        return NULL;
    }
    fread(client->nome, sizeof(char), sizeof(client->nome), in);
    fread(client->cpf, sizeof(char), sizeof(client->cpf), in);
    fread(client->data_nascimento, sizeof(char), sizeof(client->data_nascimento), in);
    return client;
}


// Imprime Client
void imprimeClient(TClient *client) {
    printf("**********************************************");
    printf("\nCliente de codigo ");
    printf("%d", client->cod);
    printf("\nNome: ");
    printf("%s", client->nome);
    printf("\nCPF: ");
    printf("%s", client->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", client->data_nascimento);
    printf("\nNumero de compras: ");
    printf("%d", client->numCompras);
    printf("\n**********************************************");
}


// Cria a base de dados
void criarBaseClient(FILE *out, int tam, int min){

    int vet[tam];
    TClient *clie;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffleClient(vet,tam,min);

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        clie = client(vet[i], "Cliente Base", "000.000.000-00", "01/01/1980", 0);
        salvaClient(clie, out);
    }

    free(clie);

}

//embaralha base de dados
void shuffleClient(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void adicionarClient(FILE *out){
    int cod;
    char nome[50], cpf[15], data_nascimento[11];
    TClient *cliente;

    printf("Qual o codigo do cliente: ");
    scanf("%d", &cod);

    printf("Qual o nome do cliente: ");
    getchar(); // Limpar o buffer de entrada
    fgets(nome, sizeof(nome), stdin);

    printf("Qual o cpf do cliente: ");
    fgets(cpf, sizeof(cpf), stdin);

    printf("Qual a data de nascimento do cliente: ");
    fgets(data_nascimento, sizeof(data_nascimento), stdin);

    cliente = client(cod, nome, cpf, data_nascimento, 0);
    salvaClient(cliente, out);

    printf("\nCliente salvo com sucesso! ");
}

void imprimirBaseClient(FILE *out){

    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    TClient *clie;

    while ((clie = leClient(out)) != NULL)
        imprimeClient(clie);

    free(clie);

}
void imprimirBaseCli(FILE *out, int n) {
    printf("\nImprimindo a base de dados...\n");

    int v = 0;
    rewind(out);
    TClient *c;

    while (!feof(out)) {
        c = leClient(out);
        if (c != NULL) {
            if (c->cod != 0 && v <= n-11) {
                imprimeClient(c);
                v++;
            }
            free(c);
        }
    }
}
void removerCliente(FILE *arquivo, int cod) {
    int fim = tamanho_arquivo(arquivo);

    TClient *resultado_busca = busca_binaria_client(cod, arquivo, 0, fim);

    if (resultado_busca != NULL) {
        fseek(arquivo, -tamanho_registroClient(), SEEK_CUR);

        TClient cliente_removido;
        memset(&cliente_removido, 0, sizeof(TClient));

        fwrite(&cliente_removido, sizeof(TClient), 1, arquivo);

        printf("Cliente removido com sucesso!\n");
    } else {
        printf("Cliente não encontrado.\n");
    }
}
