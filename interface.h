#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>

void mostrarMenuPrincipal(FILE *arqfunc, FILE *arqforn, FILE *arqclient, FILE *arqprod,FILE *logFile,FILE *p0);
void mostrarMenuGerenciamento(char categoria[]);
void logTempo(FILE *log, const char *nomeFuncao, double tempo);
void mostrarMenuInteracoes();
void pausarTela();
void limparTela();
#endif
