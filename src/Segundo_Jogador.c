#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Segundo_Jogador.h"
#include <time.h>

void Bloqueia_Adversario(int A[3][3], int *i, int *j, bool *chance) {
    // Verificar linhas
    for (int row = 0; row < 3; row++) {
        if (A[row][0] == 0 && A[row][1] == 1 && A[row][2] == 1) {
            *chance = true;
            *i = row + 1; *j = 1; return;
        }
        if (A[row][0] == 1 && A[row][1] == 0 && A[row][2] == 1) {
            *chance = true;
            *i = row + 1; *j = 2; return;
        }
        if (A[row][0] == 1 && A[row][1] == 1 && A[row][2] == 0) {
            *chance = true;
            *i = row + 1; *j = 3; return;
        }
    }

    // Verificar colunas
    for (int col = 0; col < 3; col++) {
        if (A[0][col] == 0 && A[1][col] == 1 && A[2][col] == 1) {
            *chance = true;
            *i = 1; *j = col + 1; return;
        }
        if (A[0][col] == 1 && A[1][col] == 0 && A[2][col] == 1) {
            *chance = true;
            *i = 2; *j = col + 1; return;
        }
        if (A[0][col] == 1 && A[1][col] == 1 && A[2][col] == 0) {
            *chance = true;
            *i = 3; *j = col + 1; return;
        }
    }

    // Verificar diagonal principal
    if (A[0][0] == 0 && A[1][1] == 1 && A[2][2] == 1) {
        *chance = true;
        *i = 1; *j = 1; return;
    }
    if (A[0][0] == 1 && A[1][1] == 0 && A[2][2] == 1) {
        *chance = true;
        *i = 2; *j = 2; return;
    }
    if (A[0][0] == 1 && A[1][1] == 1 && A[2][2] == 0) {
        *chance = true;
        *i = 3; *j = 3; return;
    }

    // Verificar diagonal secundária
    if (A[0][2] == 0 && A[1][1] == 1 && A[2][0] == 1) {
        *chance = true;
        *i = 1; *j = 3; return;
    }
    if (A[0][2] == 1 && A[1][1] == 0 && A[2][0] == 1) {
        *chance = true;
        *i = 2; *j = 2; return;
    }
    if (A[0][2] == 1 && A[1][1] == 1 && A[2][0] == 0) {
        *chance = true;
        *i = 3; *j = 1; return;
    }
}

void Chance_Vitoria(int A[3][3], int *i, int *j, bool *chance) {
    // Verificar linhas
    for (int row = 0; row < 3; row++) {
		 if (A[row][0] == 0 && A[row][1] == 2 && A[row][2] == 2) {
			*chance = true;
            *i = row + 1; *j = 1; return;
        }
        if (A[row][0] == 2 && A[row][1] == 0 && A[row][2] == 2) {
			*chance = true;
            *i = row + 1; *j = 2; return;
        }
        if (A[row][0] == 2 && A[row][1] == 2 && A[row][2] == 0) {
			*chance = true;
            *i = row + 1; *j = 3; return;
        }
    }

    // Verificar colunas
    for (int col = 0; col < 3; col++) {
        if (A[0][col] == 2 && A[1][col] == 0 && A[2][col] == 2) {
			*chance = true;
            *i = 2; *j = col + 1; return;
        }
        if (A[0][col] == 2 && A[1][col] == 2 && A[2][col] == 0) {
			*chance = true;
            *i = 3; *j = col + 1; return;
        }
        if (A[0][col] == 0 && A[1][col] == 2 && A[2][col] == 2) {
			*chance = true;
            *i = 1; *j = col + 1; return;
        }
    }

    // Verificar diagonal principal
    if (A[0][0] == 2 && A[1][1] == 0 && A[2][2] == 2) {
		*chance = true;
        *i = 2; *j = 2; return;
    }
    if (A[0][0] == 2 && A[1][1] == 2 && A[2][2] == 0) {
		*chance = true;
        *i = 3; *j = 3; return;
    }
    if (A[0][0] == 0 && A[1][1] == 2 && A[2][2] == 2) {
		*chance = true;
        *i = 1; *j = 1; return;
    }

    // Verificar diagonal secundária
    if (A[0][2] == 2 && A[1][1] == 0 && A[2][0] == 2) {
		*chance = true;
        *i = 2; *j = 2; return;
    }
    if (A[0][2] == 2 && A[1][1] == 2 && A[2][0] == 0) {
		*chance = true;
        *i = 3; *j = 1; return;
    }
    if (A[0][2] == 0 && A[1][1] == 2 && A[2][0] == 2) {
		*chance = true;
        *i = 1; *j = 3; return;
    }
}


void Segunda_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance)
{            
    // 1. Jogou no meio
    if (A[1][1] == 1 ) { *i = 3; *j = 3; }  
    // 2. Jogou nas laterais
    else if (A[0][1] == 1 || A[1][0] == 1 || A[1][2] == 1 || A[2][1] == 1) 
    {
        if (A[0][1] == 1) { *i = 3; *j = 2; }
        if (A[1][0] == 1) { *i = 2; *j = 3; }
        if (A[1][2] == 1) { *i = 2; *j = 1; }
        if (A[2][1] == 1) { *i = 1; *j = 2; }
    }
    // 3. Jogou nos cantos
    else if (A[0][0] == 1 || A[0][2] == 1 || A[2][0] == 1 || A[2][2] == 1) { *i = 2; *j = 2; }  

}

void Quarta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance)
{
    // 1) Se eu joguei no canto
    if (A[0][0] == 2 || A[0][2] == 2 || A[2][0] == 2 || A[2][2] == 2) 
    {
        Bloqueia_Adversario(A, &a, &b, &chance);
		*i = a; 
		*j = b;	
        if(chance == false) // Se não houver bloqueio necessário, jogar em qualquer posição livre
        {
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
    }
        // 2) Se eu joguei no meio e o adversário (1) jogou do lado ou nos cantos do lado
    else if (A[1][1] == 2 &&
        ((A[0][2] == 1 && A[2][2] == 1) ||
            (A[0][2] == 1 && A[1][2] == 1) ||
            (A[0][2] == 1 && A[0][1] == 1) ||
            (A[0][0] == 1 && A[2][0] == 1) ||
            (A[0][0] == 1 && A[1][0] == 1) ||
            (A[0][0] == 1 && A[0][1] == 1) ||
            (A[2][0] == 1 && A[0][0] == 1) ||
            (A[2][0] == 1 && A[2][1] == 1) ||
            (A[2][0] == 1 && A[1][0] == 1) ||
            (A[2][2] == 1 && A[0][2] == 1) ||
            (A[2][2] == 1 && A[2][1] == 1) ||
            (A[2][2] == 1 && A[1][2] == 1))){
            Bloqueia_Adversario(A, &a, &b, &chance);
            *i = a; *j = b;	
            if(chance == false) // Se não houver bloqueio necessário, jogar em qualquer posição livre
            {
                for(int row = 0; row < 3; row++) 
                {
                    for(int col = 0; col < 3; col++) 
                    {
                        if(A[row][col] == 0) 
                        {
                            *i = row + 1;
                            *j = col + 1;
                            return;
                        }
                    }
                }
            }

    // 3) Se eu joguei no meio e o adversário (1) jogou na diagonal oposta ou lateral oposta
    }else if (A[1][1] == 2 && ( (A[0][0] == 1 && A[2][2] == 1) || (A[0][2] == 1 && A[2][0] == 1) 
                            || (A[0][0] == 1 && (A[0][1] == 1 || A[1][0] == 1)) 
                            || (A[0][2] == 1 && (A[0][1] == 1 || A[1][2] == 1)) 
                            || (A[2][0] == 1 && (A[1][0] == 1 || A[2][1] == 1)) 
                            || (A[2][2] == 1 && (A[1][2] == 1 || A[2][1] == 1)) ))
    {
        if(A[0][1] == 0) { *i = 1; *j = 2; }
        else if (A[1][0] == 0) { *i = 2; *j = 1; }
        else if (A[2][1] == 0) { *i = 3; *j = 2; }
        else if (A[1][2] == 0) { *i = 2; *j = 3; } 
    }
    // 4) Se eu joguei em alguma lateral 
    else if (A[0][1] == 2 || A[1][0] == 2 || A[1][2] == 2 || A[2][1] == 2)  
	{
        Bloqueia_Adversario(A, &a, &b, &chance);
		*i = a; 
		*j = b;	
         if(chance == false) // Se não houver bloqueio necessário, jogar em qualquer posição livre
        {
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
	}
}

void Sexta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance)
{
	// Verificar chance de vencer
	Chance_Vitoria(A, &a, &b, &chance);
	*i = a; 
	*j = b;
	if (chance == false)
	{
		Bloqueia_Adversario(A, &a, &b, &chance);
		*i = a; 
		*j = b;	
        if(chance == false) // Se não houver bloqueio necessário, jogar em qualquer posição livre
        {
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
	}
}
void Oitava_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance)
{
	// Verificar chance de vencer
	Chance_Vitoria(A, &a, &b, &chance);
	*i = a; 
	*j = b;
	if (chance == false)
	{
		Bloqueia_Adversario(A, &a, &b, &chance);
        *i = a; 
		*j = b;	
        if(chance == false) // Se não houver bloqueio necessário, jogar em qualquer posição livre
        {
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
	}
}
void Segundo_Jogador(int *i, int *j, int numJogadas, int A[3][3], int a, int b, bool chance)
{
    if (numJogadas == 2)
    {
        Segunda_Jogada(A, i, j, a, b, chance); 
        a = *i; // Salvar jogada
        b = *j; // Salvar jogada
    }
    else if (numJogadas == 4)
    {
        Quarta_Jogada(A, i, j, a, b, chance);
        a = *i; // Salvar jogada
        b = *j; // Salvar jogada
    }
    else if (numJogadas == 6)
    {
        Sexta_Jogada(A, i, j, a, b, chance);
        a = *i; // Salvar jogada
        b = *j; // Salvar jogada
    }
    else if (numJogadas == 8)
    {
        Oitava_Jogada(A, i, j, a, b, chance);
        a = *i; // Salvar jogada
        b = *j; // Salvar jogada
    }
}
