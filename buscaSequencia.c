#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"
#include "produto.h"
#include "fornecedor.h"
#include "cliente.h"
#include "buscaSequencia.h"

TFunc *buscaSequencial(int chave, FILE *in) {
    TFunc *f;
    int achou = 0;

    rewind(in);
    while ((f = le(in)) != NULL) {
        if (f->cod == chave) {
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        return f;
    } else {
        free(f); // Liberar f apenas se não for encontrado
        return NULL;
    }
}


TProd *buscaSequencialProd(int chave, FILE *in) {
    TProd *p;
    int achou = 0;

    rewind(in);

    while ((p = leProd(in)) != NULL) {
        if (p->cod == chave) {
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        return p;
    } else {
        free(p); // Liberar f apenas se não for encontrado
        return NULL;
    }
}


TFor *buscaSequencialFor(int chave, FILE *in) {
    TFor *forn;
    int achou = 0;

    rewind(in);

    while ((forn = leFor(in)) != NULL) {
        if (forn->cod == chave) {
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        return forn;
    } else {
        free(forn); // Liberar f apenas se não for encontrado
        return NULL;
    }
}


TClient *buscaSequencialClient(int chave, FILE *in) {
    TClient *client;
    int achou = 0;

    rewind(in);

    while ((client = leClient(in)) != NULL) {
        if (client->cod == chave) {
            achou = 1;
            break;
        }
        free(client);
    }

    if (achou == 1) {
        return client;
    } else {
        free(client); // Liberar f apenas se não for encontrado
        return NULL;
    }
}
