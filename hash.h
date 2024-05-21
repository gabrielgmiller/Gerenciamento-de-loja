#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"

typedef struct HashCompartment {
    int next;
} HashCompartment;

typedef struct Node {
    TFunc* funcionario;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

typedef struct {
    LinkedList* table;
    int size;
} HashTable;
int hash(int cod, int size);

void creates_hash(const char *hash_name, int size);

int search(int cod, FILE *hash_file, const char *data_file_name, int size);

int insert(TFunc *funcionario, FILE *hash_file, const char *data_file_name, int size);

void print_hash(FILE *hash_file, const char *data_file_name, int size);

int delete_in_hash(int cod, FILE *hash_file, const char *data_file_name, int size);

void saves_compartment(HashCompartment *compartment, FILE *hash_file);

void criarBaseHash(FILE *data_file, const char *hash_file_name, const char *data_file_name, int hash_size, int tam, int min) ;

HashCompartment *reads_compartment(FILE *hash_file);

#endif // HASH_H_INCLUDED
