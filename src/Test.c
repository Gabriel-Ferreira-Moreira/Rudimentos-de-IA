#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
int a,b;

void Chance_de_Vitoria(int A[3][3], int *i, int *j, bool *chance) {
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
        if (A[0][col] == 1 && A[1][col] == 0 && A[2][col] == 1) {
			*chance = true;
            *i = 2; *j = col + 1; return;
        }
        if (A[0][col] == 1 && A[1][col] == 1 && A[2][col] == 0) {
			*chance = true;
            *i = 3; *j = col + 1; return;
        }
        if (A[0][col] == 0 && A[1][col] == 1 && A[2][col] == 1) {
			*chance = true;
            *i = 1; *j = col + 1; return;
        }
    }

    // Verificar diagonal principal
    if (A[0][0] == 1 && A[1][1] == 0 && A[2][2] == 1) {
		*chance = true;
        *i = 2; *j = 2; return;
    }
    if (A[0][0] == 1 && A[1][1] == 1 && A[2][2] == 0) {
		*chance = true;
        *i = 3; *j = 3; return;
    }
    if (A[0][0] == 0 && A[1][1] == 1 && A[2][2] == 1) {
		*chance = true;
        *i = 1; *j = 1; return;
    }

    // Verificar diagonal secundária
    if (A[0][2] == 1 && A[1][1] == 0 && A[2][0] == 1) {
		*chance = true;
        *i = 2; *j = 2; return;
    }
    if (A[0][2] == 1 && A[1][1] == 1 && A[2][0] == 0) {
		*chance = true;
        *i = 3; *j = 1; return;
    }
    if (A[0][2] == 0 && A[1][1] == 1 && A[2][0] == 1) {
		*chance = true;
        *i = 1; *j = 3; return;
    }
}
void Bloquear_Adversario(int A[3][3], int *i, int *j) {

    // Verificar linhas
    for (int row = 0; row < 3; row++) {
		 if (A[row][0] == 0 && A[row][1] == 2 && A[row][2] == 2) {
            *i = row + 1; *j = 1; return;
        }
        if (A[row][0] == 2 && A[row][1] == 0 && A[row][2] == 2) {
            *i = row + 1; *j = 2; return;
        }
        if (A[row][0] == 2 && A[row][1] == 2 && A[row][2] == 0) {
            *i = row + 1; *j = 3; return;
        }
    }

    // Verificar colunas
    for (int col = 0; col < 3; col++) {
		if (A[0][col] == 0 && A[1][col] == 2 && A[2][col] == 2) {
            *i = 1; *j = col + 1; return;
        }
        if (A[0][col] == 2 && A[1][col] == 0 && A[2][col] == 2) {
            *i = 2; *j = col + 1; return;
        }
        if (A[0][col] == 2 && A[1][col] == 2 && A[2][col] == 0) {
            *i = 3; *j = col + 1; return;
        }
    }

    // Verificar diagonal principal
	if (A[0][0] == 0 && A[1][1] == 2 && A[2][2] == 2) {
	*i = 1; *j = 1; return;
    }
    if (A[0][0] == 2 && A[1][1] == 0 && A[2][2] == 2) {
        *i = 2; *j = 2; return;
    }
    if (A[0][0] == 2 && A[1][1] == 2 && A[2][2] == 0) {
        *i = 3; *j = 3; return;
    }

    // Verificar diagonal secundária
	if (A[0][2] == 0 && A[1][1] == 2 && A[2][0] == 2) {
	*i = 1; *j = 3; return;
    }
    if (A[0][2] == 2 && A[1][1] == 0 && A[2][0] == 2) {
        *i = 2; *j = 2; return;
    }
    if (A[0][2] == 2 && A[1][1] == 2 && A[2][0] == 0) {
        *i = 3; *j = 1; return;
    }
}


void Primeira_Jogada(int *i, int *j) 
{
    int r = rand() % 4; // Sorteia 0, 1, 2 ou 3

    if (r == 0) {
        *i = 1; *j = 1;
    } else if (r == 1) {
        *i = 1; *j = 3;
    } else if (r == 2) {
        *i = 3; *j = 1;
    } else {
        *i = 3; *j = 3;
    }
}

void Quinta_Jogada(int A[3][3], int *i, int *j, int a, int b, bool chance) 
{
	Chance_de_Vitoria(A, &a, &b, &chance);
	*i = a; 
	*j = b;
	if (chance == true) return;

		if (chance == false && A[1][1] == 0) // Se o centro estiver livre, jogue nele
		{
			if (A[0][0] == 0 && A[0][1] == 0 && A[1][0] == 0) {
				*i = 1; *j = 1;  // canto superior esquerdo
			} else if (A[0][2] == 0 && A[0][1] == 0 && A[1][2] == 0) {
				*i = 1; *j = 3;  // canto superior direito
			} else if (A[2][0] == 0 && A[1][0] == 0 && A[2][1] == 0) {
				*i = 3; *j = 1;  // canto inferior esquerdo
			} else if (A[2][2] == 0 && A[1][2] == 0 && A[2][1] == 0) {
				*i = 3; *j = 3;  // canto inferior direito
			}
		}else if(A[0][0] == 2 || A[0][2] == 2 || A[2][0] == 2 || A[2][2] == 2)	
		{
			if(A[0][0] == 2)
			*i = 3, *j = 3;
			else if (A[0][2] == 2)
			*i = 3, *j = 1;
			else if (A[2][0] == 2)
			*i = 1, *j = 3;
			else if (A[2][2] == 2)
			*i = 1, *j = 1;
		}else
		{
			Bloquear_Adversario(A, &a, &b);
			*i = a; 
			*j = b;	
		}

}

