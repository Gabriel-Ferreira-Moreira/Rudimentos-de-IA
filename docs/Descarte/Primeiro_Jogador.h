#ifndef PRIMEIRO_JOGADOR_H
#define PRIMEIRO_JOGADOR_H

#include <stdbool.h>

void Primeiro_Jogador(int *i, int *j, int numJogadas, int A[3][3], int a, int b, bool chance);
void Chance_de_Vitoria(int A[3][3], int *i, int *j, bool *chance);
void Bloquear_Adversario(int A[3][3], int *i, int *j);

void Primeira_Jogada(int *i, int *j);
void Terceira_Jogada(int A[3][3], int *i, int *j, int a, int b);
void Quinta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Setima_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Nona_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);

#endif
