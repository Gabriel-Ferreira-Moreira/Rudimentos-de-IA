#ifndef SEGUNDO_JOGADOR_H
#define SEGUNDO_JOGADOR_H

#include <stdbool.h>

void Bloqueia_Adversario(int A[3][3], int *i, int *j, bool *chance);
void Chance_Vitoria(int A[3][3], int *i, int *j, bool *chance);

void Segunda_Jogada(int *a, int *b, int A[3][3]);
void Quarta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Sexta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Oitava_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Segundo_Jogador(int *i, int *j, int numJogadas, int A[3][3], int a, int b, bool chance);

#endif
