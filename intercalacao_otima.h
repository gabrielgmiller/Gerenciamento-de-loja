#ifndef INTERCALACAO_H_INCLUDED
#define INTERCALACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"

void intercalacaoF(FILE *out, char *nome, int totalParticoes, int F);
void sobrescreverArquivoF(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);

void intercalacaoClient(FILE *out, char *nome, int totalParticoes, int F);

void sobrescreverArquivoClient(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);

void intercalacaoFor(FILE *out, char *nome, int totalParticoes, int F);

void sobrescreverArquivoFor(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);

void intercalacaoProd(FILE *out, char *nome, int totalParticoes, int F);

void sobrescreverArquivoProd(FILE *arquivoOriginal, FILE *novoArquivo, int tamanhoRegistro);


#endif // INTERCALACAO_H_INCLUDED
