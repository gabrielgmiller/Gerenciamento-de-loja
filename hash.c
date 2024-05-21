#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"

int hash(int cod, int size)
{
    return cod % size;
}

void creates_hash(const char *hash_name, int size)
{
    FILE *hash_file = fopen(hash_name, "wb");
    if (hash_file == NULL)
    {
        printf("Erro ao criar arquivo hash\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        HashCompartment *compartment = (HashCompartment *)malloc(sizeof(HashCompartment));
        compartment->next = -1;
        saves_compartment(compartment, hash_file);

        free(compartment);
    }
    fclose(hash_file);
}

int search(int cod, FILE *hash_file, const char *data_file_name, int size)
{
    int comparisons = 0;

    int h = hash(cod, size);
    int hash_position = h * sizeof(int);

    comparisons++;
    if (hash_position == 0)
    {
        rewind(hash_file);
    }
    else
    {
        fseek(hash_file, hash_position, SEEK_SET);
    }

    HashCompartment *compartment = reads_compartment(hash_file);

    comparisons++;
    if (compartment->next == -1)
    {
        printf("- N�mero de compara��es: %d\n", comparisons);
        printf("!!Funcion�rio n�o encontrado!!\n");
        return -1;
    }
    else
    {
        FILE *data_file = fopen(data_file_name, "rb");

        if (data_file == NULL)
        {
            printf("Erro ao abrir arquivo de dados\n");
            return -1;
        }

        comparisons++;
        if (compartment->next == 0)
        {
            fseek(data_file, 0, SEEK_SET);
        }
        else
        {
            fseek(data_file, tamanho_registro() * compartment->next, SEEK_SET);
        }

        int position = compartment->next;
        while (position != -1)
        {
            comparisons++;
            if (position == 0)
            {
                rewind(data_file);
            }
            else
            {
                fseek(data_file, tamanho_registro() * position, SEEK_SET);
            }

            TFunc *funcionario = le(data_file);

            comparisons++;
            if (funcionario->cod == cod)
            {
                fclose(data_file);
                printf("- N�mero de compara��es: %d\n", comparisons);
                printf("Funcion�rio encontrado na posi��o %d.\n", position);
                return position;
            }
            else
            {
                position = funcionario->numVendas;
            }
        }

        printf("- N�mero de compara��es: %d\n", comparisons);
        printf("!!Funcion�rio n�o encontrado!!\n");
        fclose(data_file);
        return -1;
    }
}

int insert(TFunc *funcionario, FILE *hash_file, const char *data_file_name, int size)
{
    int h = hash(funcionario->cod, size);
    int hash_position = (h) * sizeof(int);

    if (hash_position == 0)
    {
        rewind(hash_file);
    }
    else
    {
        fseek(hash_file, hash_position, SEEK_SET);
    }

    HashCompartment *compartment = reads_compartment(hash_file);

    if (compartment->next != -1)
    {
        FILE *data_file = fopen(data_file_name, "r+b");

        if (data_file == NULL)
        {
            printf("Erro ao abrir arquivo de dados\n");
            return -1;
        }

        if (compartment->next == 0)
        {
            rewind(data_file);
        }
        else
        {
            fseek(data_file, tamanho_registro() * compartment->next, SEEK_SET);
        }

        hash_position = compartment->next;

        while (1)
        {
            TFunc *f = le(data_file);
            if (f->numVendas == -1)
            {
                fseek(data_file, 0, SEEK_END);
                salva(funcionario, data_file);
                f->numVendas = tamanho_arquivo(data_file) - 1;

                if (hash_position == 0)
                {
                    rewind(data_file);
                }
                else
                {
                    fseek(data_file, tamanho_registro() * hash_position, SEEK_SET);
                }
                salva(f, data_file);
                free(f);
                fclose(data_file);
                return 1;
            }
            else
            {
                fseek(data_file, tamanho_registro() * f->numVendas, SEEK_SET);
                hash_position = f->numVendas;
            }
        }
    }
    else
    {
        FILE *data_file;
        if ((data_file = fopen(data_file_name, "a+b")) == NULL)
        {
            printf("Erro ao abrir arquivo de dados\n");
            return -1;
        }

        salva(funcionario, data_file);

        compartment->next = tamanho_arquivo(data_file) - 1;
        fseek(hash_file, sizeof(HashCompartment) * (h), SEEK_SET);
        saves_compartment(compartment, hash_file);
        fclose(data_file);
        free(compartment);
        return 1;
    }
}

void print_hash(FILE *hash_file, const char *data_file_name, int size)
{
    for (int i = 0; i < size; i++)
    {
        int hash_position = i * sizeof(int);

        if (hash_position == 0)
        {
            rewind(hash_file);
        }
        else
        {
            fseek(hash_file, hash_position, SEEK_SET);
        }

        HashCompartment *compartment = reads_compartment(hash_file);
        printf("\n\n-> Compartimento %d", i + 1);

        if (compartment->next == -1)
        {
            printf(" - Vazio\n");
        }
        else
        {
            FILE *data_file = fopen(data_file_name, "rb");

            if (data_file == NULL)
            {
                printf("Erro ao abrir arquivo de dados\n");
                free(compartment);
                return;
            }

            int position = compartment->next;

            while (position != -1)
            {
                fseek(data_file, tamanho_registro() * position, SEEK_SET);
                TFunc *funcionario = le(data_file);

                if (funcionario != NULL && funcionario->cod != 0)
                {
                    imprime(funcionario);
                    free(funcionario);
                }
                else
                {
                    printf("Erro ao ler registro do arquivo de dados\n");
                    break;
                }

                position = funcionario->numVendas;
            }

            fclose(data_file);
        }

        free(compartment);
    }
}




int delete_in_hash(int cod, FILE *hash_file, const char *data_file_name, int size)
{
    int h = hash(cod, size);
    int hash_position = (h) * sizeof(int);

    if (hash_position == 0)
    {
        rewind(hash_file);
    }
    else
    {
        fseek(hash_file, hash_position, SEEK_SET);
    }

    HashCompartment *compartment = reads_compartment(hash_file);

    if (compartment->next == -1)
    {
        free(compartment);
        return -1;
    }
    else
    {
        FILE *data_file = fopen(data_file_name, "r+b");

        if (data_file == NULL)
        {
            printf("Erro ao abrir arquivo de dados\n");
            return -1;
        }

        if (compartment->next == 0)
        {
            rewind(data_file);
        }
        else
        {
            fseek(data_file, tamanho_registro() * compartment->next, SEEK_SET);
        }

        int position = compartment->next;
        int previous_position = -1;

        while (1)
        {
            TFunc *f = le(data_file);
            if (f->cod == cod)
            {
                fseek(data_file, tamanho_registro() * position, SEEK_SET);
                TFunc *funcionario_removido = funcionario(f->cod, "", "", "", 0.0, -1);
                salva(funcionario_removido, data_file);

                free(funcionario_removido);
                fclose(data_file);
                free(compartment);

                return position;
            }
            else
            {
                previous_position = position;
                position = f->numVendas;

                fseek(data_file, tamanho_registro() * position, SEEK_SET);
            }
        }

        free(compartment);
        fclose(data_file);
        return -1;
    }
}

void saves_compartment(HashCompartment *compartment, FILE *hash_file)
{
    fwrite(&compartment->next, sizeof(int), 1, hash_file);
}

HashCompartment *reads_compartment(FILE *hash_file)
{
    HashCompartment *compartment = (HashCompartment *)malloc(sizeof(HashCompartment));
    fread(&compartment->next, sizeof(int), 1, hash_file);
    return compartment;
}

void criarBaseHash(FILE *data_file, const char *hash_file_name, const char *data_file_name, int hash_size, int tam, int min) {
    int vet[tam];
    TFunc *f;

    for(int i = 0; i < tam; i++)
        vet[i] = i + 1;

    shuffle(vet, tam, min);

    printf("\nGerando a base de dados...\n");

    FILE *hash_file = fopen(hash_file_name, "r+b");

    if (hash_file == NULL) {
        printf("Erro ao abrir o arquivo hash\n");
        return;
    }

    for (int i = 0; i < tam; i++) {
        f = funcionario(vet[i], "Funcionario Base", "000.000.000-00", "01/01/1980", 3000 * i, 0);
        insert(f, hash_file, data_file_name, hash_size); // Corrigido aqui
        free(f);
    }

    fclose(hash_file);
}