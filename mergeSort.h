#ifndef MERGE_SORT_EXTERNO_H
#define MERGE_SORT_EXTERNO_H

#include <stdio.h>


/*void merge(FILE *arq, FILE *temp, int inicio, int meio, int fim);


void mergeSort(FILE *arq, FILE *temp, int tam);


void mergeSortInFile(FILE *arq) ;
*/

void merge(FILE* arq, int l, int m, int r);
void mergeSort(FILE *arq, int l, int r);

void mergeProduto(FILE* arq, int l, int m, int r);
void mergeSortProduto(FILE *arq, int l, int r);

void mergeCliente(FILE* arq, int l, int m, int r);
void mergeSortCliente(FILE *arq, int l, int r);

void mergeFornecedor(FILE* arq, int l, int m, int r);
void mergeSortFornecedor(FILE *arq, int l, int r);

#endif /* MERGE_SORT_EXTERNO_H */
