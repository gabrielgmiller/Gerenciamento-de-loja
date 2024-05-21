#include "mergeSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cliente.h"
#include "fornecedor.h"
#include "funcionario.h"
#include "produto.h"

#define TAM_BLOCO 100

/*void merge(FILE *arq, FILE *temp, int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    fseek(arq, inicio * tamanho_registro(), SEEK_SET);
    TFunc *left = le(arq);

    fseek(arq, (meio + 1) * tamanho_registro(), SEEK_SET);
    TFunc *right = le(arq);

    i = 0;
    j = 0;
    k = inicio;

    while (i < n1 && j < n2) {
        if (left->cod <= right->cod) {
            fseek(arq, k * tamanho_registro(), SEEK_SET);
            salva(left, temp);
            i++;
        } else {
            fseek(arq, k * tamanho_registro(), SEEK_SET);
            salva(right, temp);
            j++;
        }
        k++;

        // Atualiza os registros left e right
        if (i < n1) {
            fseek(arq, (inicio + i) * tamanho_registro(), SEEK_SET);
            left = le(arq);
        }
        if (j < n2) {
            fseek(arq, (meio + 1 + j) * tamanho_registro(), SEEK_SET);
            right = le(arq);
        }
    }

    // Copia os registros restantes de left, se houver
    while (i < n1) {
        fseek(arq, k * tamanho_registro(), SEEK_SET);
        salva(left, temp);
        i++;
        k++;

        if (i < n1) {
            fseek(arq, (inicio + i) * tamanho_registro(), SEEK_SET);
            left = le(arq);
        }
    }

    // Copia os registros restantes de right, se houver
    while (j < n2) {
        fseek(arq, k * tamanho_registro(), SEEK_SET);
        salva(right, temp);
        j++;
        k++;

        if (j < n2) {
            fseek(arq, (meio + 1 + j) * tamanho_registro(), SEEK_SET);
            right = le(arq);
        }
    }

    // Copia os registros ordenados de volta para o arquivo original
    fseek(temp, inicio * tamanho_registro(), SEEK_SET);
    for (i = inicio; i <= fim; i++) {
        TFunc *temp_reg = le(temp);
        fseek(arq, i * tamanho_registro(), SEEK_SET);
        salva(temp_reg, arq);
    }
}

void mergeSort(FILE *arq, FILE *temp, int tam) {
    int blockSize = 1;

    while (blockSize <= tam - 1) {
        int leftStart = 0;

        while (leftStart < tam - 1) {
            int mid = leftStart + blockSize - 1;
            int rightEnd = (mid + blockSize < tam) ? (mid + blockSize) : (tam - 1);

            merge(arq, temp, leftStart, mid, rightEnd);

            leftStart = rightEnd + 1;
        }

        blockSize *= 2;
    }
}

void mergeSortInFile(FILE *arq) {
    int tam = tamanho_arquivo(arq);

    FILE *temp = fopen("mergeFuncionarios.dat", "w+b"); // Arquivo temporário para armazenar a ordenação

    if (temp == NULL) {
        perror("Erro ao criar o arquivo temporário");
        exit(EXIT_FAILURE);
    }

    // Copiando o conteúdo do arquivo original ("arq") para o arquivo temporário ("temp")
    rewind(arq); // Volta para o início do arquivo original

    TFunc *func;
    while (!feof(arq)) {
        func = le(arq);
        if (func != NULL) {
            salva(func, temp); // Salva os registros no arquivo temporário
            free(func);
        }
    }
    mergeSort(temp, arq, tam); // Realiza a ordenação externa no arquivo temporário

    fclose(temp);
}
*/

void merge(FILE* arq, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    FILE *L,*R;
    if ((L = fopen("mergeFuncionarios1.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
    if ((R = fopen("mergeFuncionarios2.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
	TFunc *LA,*RA;

    for (i = 0; i < n1; i++)
    {
        fseek(arq, (l + i) * tamanho_registro(), SEEK_SET);
        LA = le(arq);
        fseek(L, (i) * tamanho_registro(), SEEK_SET);
        if(LA != NULL)
            salva(LA,L);
    }

    for (j = 0; j < n2; j++)
    {
        fseek(arq, (m + 1 + j) * tamanho_registro(), SEEK_SET);
        RA = le(arq);
        fseek(R, (j) * tamanho_registro(), SEEK_SET);
        if(RA != NULL)
            salva(RA,R);
    }

    i = 0;

    j = 0;

    k = l;
    while (i < n1 && j < n2)
        {
            fseek(L, (i) * tamanho_registro(), SEEK_SET);
            fseek(R, (j) * tamanho_registro(), SEEK_SET);
            LA = le(L);
            RA = le(R);
            if(LA->cod <= RA->cod) 
            {
                fseek(arq, (k) * tamanho_registro(), SEEK_SET);
                salva(LA,arq);
                i++;
            }
            else
            {
                fseek(arq, (k) * tamanho_registro(), SEEK_SET);
                salva(RA,arq);
                j++;
            }
            k++;

    }


    while (i < n1)
        {
            fseek(arq, (k) * tamanho_registro(), SEEK_SET);
            fseek(L, (i) * tamanho_registro(), SEEK_SET);
            LA = le(L);
            salva(LA,arq);

        i++;
        k++;
    }

    while (j < n2) {
            fseek(arq, (k) * tamanho_registro(), SEEK_SET);
            fseek(R, (j) * tamanho_registro(), SEEK_SET);
            RA = le(R);
            salva(RA,arq);

        j++;
        k++;
    }

    fclose(L);
    fclose(R);
}


void mergeSort(FILE *arq, int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(arq, l, m);
		mergeSort(arq, m + 1, r);

        printf("l = %d; r = %d; m = %d;---------------------", l, r, m);
		merge(arq, l, m, r);
	}
}

void mergeCliente(FILE* arq, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    FILE *L,*R;
    if ((L = fopen("mergeCliente1.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
    if ((R = fopen("mergeCliente2.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
	TClient *LA,*RA;
    for (i = 0; i < n1; i++)
    {
        fseek(arq, (l + i) * tamanho_registroClient(), SEEK_SET);
        LA = leClient(arq);
        fseek(L, (i) * tamanho_registroClient(), SEEK_SET);
        if(LA != NULL)
            salvaClient(LA,L);
    }
    for (j = 0; j < n2; j++)
    {
        fseek(arq, (m + 1 + j) * tamanho_registroClient(), SEEK_SET);
        RA = leClient(arq);
        fseek(R, (j) * tamanho_registroClient(), SEEK_SET);
        if(RA != NULL)
            salvaClient(RA,R);
    }
    i = 0;

    j = 0;
    k = l;
    while (i < n1 && j < n2)
        {
            fseek(L, (i) * tamanho_registroClient(), SEEK_SET);
            fseek(R, (j) * tamanho_registroClient(), SEEK_SET);
            LA = leClient(L);
            RA = leClient(R);
            if(LA->cod <= RA->cod) 
            {
                fseek(arq, (k) * tamanho_registroClient(), SEEK_SET);
                salvaClient(LA,arq);
                i++;
            }
            else
            {
                fseek(arq, (k) * tamanho_registroClient(), SEEK_SET);
                salvaClient(RA,arq);
                j++;
            }
            k++;
        }

    while (i < n1)
        {
            fseek(arq, (k) * tamanho_registroClient(), SEEK_SET);
            fseek(L, (i) * tamanho_registroClient(), SEEK_SET);
            LA = leClient(L);
            salvaClient(LA,arq);
        i++;
        k++;
    }

    while (j < n2) {
            fseek(arq, (k) * tamanho_registroClient(), SEEK_SET);
            fseek(R, (j) * tamanho_registroClient(), SEEK_SET);
            RA = leClient(R);
            salvaClient(RA,arq);
        j++;
        k++;
    }
    fclose(L);
    fclose(R);
}

void mergeSortCliente(FILE *arq, int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSortCliente(arq, l, m);
		mergeSortCliente(arq, m + 1, r);

        printf("l = %d; r = %d; m = %d;---------------------", l, r, m);
		mergeCliente(arq, l, m, r);
	}
}

void mergeProduto(FILE* arq, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    FILE *L,*R;
    if ((L = fopen("mergeProduto1.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
    if ((R = fopen("mergeProduto2.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
	TProd *LA,*RA;

    for (i = 0; i < n1; i++)
    {
        fseek(arq, (l + i) * tamanho_registroProd(), SEEK_SET);
        LA = leProd(arq);
        fseek(L, (i) * tamanho_registroProd(), SEEK_SET);
        if(LA != NULL)
            salvaProd(LA,L);
    }
    for (j = 0; j < n2; j++)
    {
        fseek(arq, (m + 1 + j) * tamanho_registroProd(), SEEK_SET);
        RA = leProd(arq);
        fseek(R, (j) * tamanho_registroProd(), SEEK_SET);
        if(RA != NULL)
            salvaProd(RA,R);
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
        {
            fseek(L, (i) * tamanho_registroProd(), SEEK_SET);
            fseek(R, (j) * tamanho_registroProd(), SEEK_SET);
            LA = leProd(L);
            RA = leProd(R);
            if(LA->cod <= RA->cod)
            {
                fseek(arq, (k) * tamanho_registroProd(), SEEK_SET);
                salvaProd(LA,arq);
                i++;
            }
            else
            {
                fseek(arq, (k) * tamanho_registroProd(), SEEK_SET);
                salvaProd(RA,arq);
                j++;
            }
            k++;
    }

    while (i < n1)
        {
            fseek(arq, (k) * tamanho_registroProd(), SEEK_SET);
            fseek(L, (i) * tamanho_registroProd(), SEEK_SET);
            LA = leProd(L);
            salvaProd(LA,arq);
        i++;
        k++;
    }

    while (j < n2) {
            fseek(arq, (k) * tamanho_registroProd(), SEEK_SET);
            fseek(R, (j) * tamanho_registroProd(), SEEK_SET);
            RA = leProd(R);
            salvaProd(RA,arq);
        j++;
        k++;
    }
    fclose(L);
    fclose(R);
}

void mergeSortProduto(FILE *arq, int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSortProduto(arq, l, m);
		mergeSortProduto(arq, m + 1, r);

        printf("l = %d; r = %d; m = %d;---------------------", l, r, m);
		mergeProduto(arq, l, m, r);
	}
}


void mergeFornecedor(FILE* arq, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    FILE *L,*R;
    if ((L = fopen("mergeFornecedor1.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
    if ((R = fopen("mergeFornecedor2.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
	}
	TFor *LA,*RA;

    for (i = 0; i < n1; i++)
    {
        fseek(arq, (l + i) * tamanho_registroFor(), SEEK_SET);
        LA = leFor(arq);
        fseek(L, (i) * tamanho_registroFor(), SEEK_SET);
        if(LA != NULL)
            salvaFor(LA,L);
    }
    for (j = 0; j < n2; j++)
    {
        fseek(arq, (m + 1 + j) * tamanho_registroFor(), SEEK_SET);
        RA = leFor(arq);
        fseek(R, (j) * tamanho_registroFor(), SEEK_SET);
        if(RA != NULL)
            salvaFor(RA,R);
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
        {
            fseek(L, (i) * tamanho_registroFor(), SEEK_SET);
            fseek(R, (j) * tamanho_registroFor(), SEEK_SET);
            LA = leFor(L);
            RA = leFor(R);
            if(LA->cod <= RA->cod)
            {
                fseek(arq, (k) * tamanho_registroFor(), SEEK_SET);
                salvaFor(LA,arq);
                i++;
            }
            else
            {
                fseek(arq, (k) * tamanho_registroFor(), SEEK_SET);
                salvaFor(RA,arq);
                j++;
            }
            k++;
    }

    while (i < n1)
        {
            fseek(arq, (k) * tamanho_registroFor(), SEEK_SET);
            fseek(L, (i) * tamanho_registroFor(), SEEK_SET);
            LA = leFor(L);
            salvaFor(LA,arq);
        i++;
        k++;
    }

    while (j < n2) {
            fseek(arq, (k) * tamanho_registroFor(), SEEK_SET);
            fseek(R, (j) * tamanho_registroFor(), SEEK_SET);
            RA = leFor(R);
            salvaFor(RA,arq);
        j++;
        k++;
    }
    fclose(L);
    fclose(R);
}

void mergeSortFornecedor(FILE *arq, int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSortFornecedor(arq, l, m);
		mergeSortFornecedor(arq, m + 1, r);

        printf("l = %d; r = %d; m = %d;---------------------", l, r, m);
		mergeFornecedor(arq, l, m, r);
	}
}