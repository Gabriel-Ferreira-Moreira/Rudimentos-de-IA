#ifndef BOT_H
#define BOT_H

#include <stdbool.h>

// 🔹 Funções do Primeiro Jogador
void Primeiro_Jogador(int *i, int *j, int numJogadas, int A[3][3], int a, int b, bool chance, char Dificuldade);
void Chance_de_Vitoria(int A[3][3], int *i, int *j, bool *chance);
void Bloquear_Adversario(int A[3][3], int *i, int *j);

void Jogada_Aleatoria(int A[3][3], int *i, int *j);
void Primeira_Jogada(int *i, int *j);
void Terceira_Jogada(int A[3][3], int *i, int *j, int a, int b);
void Quinta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Setima_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Nona_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);

// 🔹 Funções do Segundo Jogador
void Bloqueia_Adversario(int A[3][3], int *i, int *j, bool *chance);
void Chance_Vitoria(int A[3][3], int *i, int *j, bool *chance);

void Segunda_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Quarta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Sexta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Oitava_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance);
void Segundo_Jogador(int *i, int *j, int numJogadas, int A[3][3], int a, int b, bool chance, char Dificuldade);

#endif // BOT_H
