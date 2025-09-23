#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include "C:\\Jogo-da-Velha\\inc\\BOT.h"
#else
    #include "../inc/BOT.h"
#endif

void Chance_de_Vitoria(int A[3][3], int *i, int *j, bool *chance) {
    for (int row = 0; row < 3; row++) {
        if (A[row][0] == 0 && A[row][1] == 1 && A[row][2] == 1) { *chance = true; *i = row + 1; *j = 1; return; }
        if (A[row][0] == 1 && A[row][1] == 0 && A[row][2] == 1) { *chance = true; *i = row + 1; *j = 2; return; }
        if (A[row][0] == 1 && A[row][1] == 1 && A[row][2] == 0) { *chance = true; *i = row + 1; *j = 3; return; }
    }
    for (int col = 0; col < 3; col++) {
        if (A[0][col] == 1 && A[1][col] == 0 && A[2][col] == 1) { *chance = true; *i = 2; *j = col + 1; return; }
        if (A[0][col] == 1 && A[1][col] == 1 && A[2][col] == 0) { *chance = true; *i = 3; *j = col + 1; return; }
        if (A[0][col] == 0 && A[1][col] == 1 && A[2][col] == 1) { *chance = true; *i = 1; *j = col + 1; return; }
    }
    if (A[0][0] == 1 && A[1][1] == 0 && A[2][2] == 1) { *chance = true; *i = 2; *j = 2; return; }
    if (A[0][0] == 1 && A[1][1] == 1 && A[2][2] == 0) { *chance = true; *i = 3; *j = 3; return; }
    if (A[0][0] == 0 && A[1][1] == 1 && A[2][2] == 1) { *chance = true; *i = 1; *j = 1; return; }
    if (A[0][2] == 1 && A[1][1] == 0 && A[2][0] == 1) { *chance = true; *i = 2; *j = 2; return; }
    if (A[0][2] == 1 && A[1][1] == 1 && A[2][0] == 0) { *chance = true; *i = 3; *j = 1; return; }
    if (A[0][2] == 0 && A[1][1] == 1 && A[2][0] == 1) { *chance = true; *i = 1; *j = 3; return; }
}

void Bloquear_Adversario(int A[3][3], int *i, int *j) {
    for (int row = 0; row < 3; row++) {
        if (A[row][0] == 0 && A[row][1] == 2 && A[row][2] == 2) { *i = row + 1; *j = 1; return; }
        if (A[row][0] == 2 && A[row][1] == 0 && A[row][2] == 2) { *i = row + 1; *j = 2; return; }
        if (A[row][0] == 2 && A[row][1] == 2 && A[row][2] == 0) { *i = row + 1; *j = 3; return; }
    }
    for (int col = 0; col < 3; col++) {
        if (A[0][col] == 0 && A[1][col] == 2 && A[2][col] == 2) { *i = 1; *j = col + 1; return; }
        if (A[0][col] == 2 && A[1][col] == 0 && A[2][col] == 2) { *i = 2; *j = col + 1; return; }
        if (A[0][col] == 2 && A[1][col] == 2 && A[2][col] == 0) { *i = 3; *j = col + 1; return; }
    }
    if (A[0][0] == 0 && A[1][1] == 2 && A[2][2] == 2) { *i = 1; *j = 1; return; }
    if (A[0][0] == 2 && A[1][1] == 0 && A[2][2] == 2) { *i = 2; *j = 2; return; }
    if (A[0][0] == 2 && A[1][1] == 2 && A[2][2] == 0) { *i = 3; *j = 3; return; }
    if (A[0][2] == 0 && A[1][1] == 2 && A[2][0] == 2) { *i = 1; *j = 3; return; }
    if (A[0][2] == 2 && A[1][1] == 0 && A[2][0] == 2) { *i = 2; *j = 2; return; }
    if (A[0][2] == 2 && A[1][1] == 2 && A[2][0] == 0) { *i = 3; *j = 1; return; }
}
void Primeira_Jogada(int *i, int *j) {
    #if 1
    int r = rand() % 4;
    if (r == 0) { *i = 1; *j = 1; }
    else if (r == 1) { *i = 1; *j = 3; }
    else if (r == 2) { *i = 3; *j = 1; }
    else { *i = 3; *j = 3; }
    #else
    *i=1; *j=1; return;
    #endif
}
void Jogada_Aleatoria(int A[3][3], int *i, int *j){
    int emptyCells[9][2];
    int count = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (A[row][col] == 0) {
                emptyCells[count][0] = row + 1;
                emptyCells[count][1] = col + 1;
                count++;
            }
        }
    }
    if (count > 0) {
        int r = rand() % count;
        *i = emptyCells[r][0];
        *j = emptyCells[r][1];
    }
}
void Jogada_Aleatorias(int A[3][3], int *i, int *j){
 for(int row = 0; row < 3; row++) {
                for(int col = 0; col < 3; col++) {
                    if(A[row][col] == 0) {
                        *i = row + 1;
                        *j = col + 1;
                        return;
                    }
                }
            }
}

void Terceira_Jogada(int A[3][3], int *i, int *j, int a, int b) {
    if (A[1][1] == 2) {
        if (a == 1 && b == 3) { *i = 3; *j = 1; }
        else if (a == 1 && b == 1) { *i = 3; *j = 3; }
        else if (a == 3 && b == 1) { *i = 1; *j = 3; }
        else if (a == 3 && b == 3) { *i = 1; *j = 1; }
    } else {
        if (A[0][0] == 2 || A[0][2] == 2 || A[2][0] == 2 || A[2][2] == 2) {
            if (((A[0][0] == 1 && A[2][2] == 2) || (A[0][0] == 2 && A[2][2] == 1)) ||
                ((A[0][2] == 1 && A[2][0] == 2) || (A[0][2] == 2 && A[2][0] == 1))) {
                if (A[0][0] == 0) { *i = 1; *j = 1; }
                else if (A[0][2] == 0) { *i = 1; *j = 3; }
                else if (A[2][0] == 0) { *i = 3; *j = 1; }
                else if (A[2][2] == 0) { *i = 3; *j = 3; }
            } else if (A[0][0] == 2) { *i = 3; *j = 3; }
            else if (A[0][2] == 2) { *i = 3; *j = 1; }
            else if (A[2][0] == 2) { *i = 1; *j = 3; }
            else if (A[2][2] == 2) { *i = 1; *j = 1; }
        } else {
            if ((A[0][0] == 1 && (A[0][1] == 2 || A[1][0] == 2)) ||
                (A[0][2] == 1 && (A[0][1] == 2 || A[1][2] == 2)) ||
                (A[2][0] == 1 && (A[1][0] == 2 || A[2][1] == 2)) ||
                (A[2][2] == 1 && (A[1][2] == 2 || A[2][1] == 2))) {
                if (A[0][0] == 1) { if (A[0][1] == 2) { *i = 3; *j = 1; } if (A[1][1] == 2) { *i = 1; *j = 3; } }
                else if (A[0][2] == 1) { if (A[0][1] == 2) { *i = 3; *j = 3; } if (A[1][2] == 2) { *i = 1; *j = 1; } }
                else if (A[2][0] == 1) { if (A[1][0] == 2) { *i = 3; *j = 3; } if (A[2][1] == 2) { *i = 1; *j = 1; } }
                else if (A[2][2] == 1) { if (A[2][1] == 2) { *i = 1; *j = 3; } if (A[1][2] == 2) { *i = 3; *j = 1; } }
            } else {
                if (A[0][0] == 1) { if (A[1][2] == 2) { *i = 1; *j = 3; } if (A[2][1] == 2) { *i = 3; *j = 1; } }
                else if (A[0][2] == 1) { if (A[1][0] == 2) { *i = 1; *j = 1; } if (A[2][1] == 2) { *i = 3; *j = 3; } }
                else if (A[2][0] == 1) { if (A[0][1] == 2) { *i = 1; *j = 1; } if (A[1][2] == 2) { *i = 3; *j = 3; } }
                else if (A[2][2] == 1) { if (A[0][1] == 2) { *i = 1; *j = 3; } if (A[1][0] == 2) { *i = 3; *j = 1; } }
            }
        }
    }
}

void Quinta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance) {
    Chance_de_Vitoria(A, &a, &b, &chance);
    *i = a; *j = b;
    if (chance == true) return;
    if (chance == false && A[1][1] == 0) {
        if (A[0][0] == 0 && A[0][1] == 0 && A[1][0] == 0) { *i = 1; *j = 1; }
        else if (A[0][2] == 0 && A[0][1] == 0 && A[1][2] == 0) { *i = 1; *j = 3; }
        else if (A[2][0] == 0 && A[1][0] == 0 && A[2][1] == 0) { *i = 3; *j = 1; }
        else if (A[2][2] == 0 && A[1][2] == 0 && A[2][1] == 0) { *i = 3; *j = 3; }
    } else if (A[0][0] == 2 || A[0][2] == 2 || A[2][0] == 2 || A[2][2] == 2) {
        if (A[0][0] == 2) { *i = 3; *j = 3; }
        else if (A[0][2] == 2) { *i = 3; *j = 1; }
        else if (A[2][0] == 2) { *i = 1; *j = 3; }
        else if (A[2][2] == 2) { *i = 1; *j = 1; }
    } else {
        Bloquear_Adversario(A, &a, &b);
        *i = a; *j = b;
    }
}

void Setima_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance) {
    Chance_de_Vitoria(A, &a, &b, &chance);
    *i = a; *j = b;
    if (chance == false) {
        Bloquear_Adversario(A, &a, &b);
        *i = a; *j = b;
    }
}

void Nona_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance) 
{
	Chance_de_Vitoria(A, &a, &b, &chance);
	*i = a; 
	*j = b;
	if (chance == false)
	{
		Bloquear_Adversario(A, &a, &b);
		*i = a; 
		*j = b;	
	}
}


void Primeiro_Jogador(int *i, int *j, int numJogadas, int A[3][3], int a, int b, bool chance, char Dificuldade) 
{
    if (Dificuldade == '0')
    {
        if (numJogadas < 2) {
                    Jogada_Aleatoria(A, i, j);
                } else if (numJogadas < 4) {
                    Jogada_Aleatoria(A, i, j);
                } else if (numJogadas < 6) {
                    Jogada_Aleatoria(A, i, j);
                } else if (numJogadas < 8) {
                    Jogada_Aleatoria(A, i, j);
                } else if (numJogadas < 10) {
                    Jogada_Aleatoria(A, i, j);
                }
    }
    else if (Dificuldade == '1')
    {
            int diff=1;
         if (numJogadas < 2) {
                    Jogada_Aleatorias(A, i, j);
                } else if (numJogadas < 4) {
                    Jogada_Aleatorias(A, i, j);
                } else if (numJogadas < 6) {
                    Jogada_Aleatorias(A, i, j);
                } else if (numJogadas < 8) {
                    Jogada_Aleatorias(A, i, j);
                } else if (numJogadas < 10) {
                    Jogada_Aleatorias(A, i, j);
                }
    }
    else if (Dificuldade == '2')
    {
        if (numJogadas < 2) {
                    Primeira_Jogada(i, j);
                } else if (numJogadas < 4) {
                    Terceira_Jogada(A, i, j, a, b);
                } else if (numJogadas < 6) {
                    Quinta_Jogada(A, i, j, a, b, chance);
                } else if (numJogadas < 8) {
                    Setima_Jogada(A, i, j, a, b, chance);
                } else if (numJogadas < 10) {
                    Nona_Jogada(A, i, j, a, b, chance);
                }
    }
}

