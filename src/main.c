#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "C:\Jogo-da-Velha\inc\Primeiro_Jogador.h"

int M[3][3], vencedor = 0, numJogadas = 0;
int a,b;
char menu;

void inicializa_Jogo()
{
	M[0][0] = 0; 	M[0][1] = 0; 	M[0][2] = 0;
	M[1][0] = 0; 	M[1][1] = 0; 	M[1][2] = 0;
	M[2][0] = 0; 	M[2][1] = 0; 	M[2][2] = 0;
	
	printf("- - - - - - - - -  \n");
	printf(" Bem-vindo ao Jogo da velha!!!\n");
	printf("- - - - - - - - - -\n\n");
}

void mostra(int A[3][3])
{
	printf("\n");
	for(int i = 0; i < 3; i++) {
		// Linha com os símbolos
		printf(" ");
		for(int j = 0; j < 3; j++) {
			if(A[i][j] == 1)
				printf(" O ");
			else if(A[i][j] == 2)
				printf(" X ");
			else
				printf("   ");
			
			if(j < 2) printf("|");
		}
		printf("\n");
		
		// Linha separadora (exceto na última linha)
		if(i < 2) {
			printf("-----------\n");
		}
	}
	printf("\n");
}

int verifica(int A[3][3])
{
	int resultado = 0;
	
	//Verifica linhas
	if ( (A[0][0]*A[0][1]*A[0][2] == 1) || (A[1][0]*A[1][1]*A[1][2] == 1) || (A[2][0]*A[2][1]*A[2][2] == 1) )
		resultado = 1;
	if ( (A[0][0]*A[0][1]*A[0][2] == 8) || (A[1][0]*A[1][1]*A[1][2] == 8) || (A[2][0]*A[2][1]*A[2][2] == 8) )
		resultado = 2;
	
	//Verifica colunas
	if ( (A[0][0]*A[1][0]*A[2][0] == 1) || (A[0][1]*A[1][1]*A[2][1] == 1) || (A[0][2]*A[1][2]*A[2][2] == 1) )
		resultado = 1;
	if ( (A[0][0]*A[1][0]*A[2][0] == 8) || (A[0][1]*A[1][1]*A[2][1] == 8) || (A[0][2]*A[1][2]*A[2][2] == 8) )
		resultado = 2;

	//Verifica diagonais
	if ( (A[0][0]*A[1][1]*A[2][2] == 1) || (A[0][2]*A[1][1]*A[2][0] == 1) )
		resultado = 1;
	if ( (A[0][0]*A[1][1]*A[2][2] == 8) || (A[0][2]*A[1][1]*A[2][0] == 8) )
		resultado = 2;

	return resultado;
}

void joga1(int A[3][3], int numJogadas)
{
	int i, j;
	bool sai = false, chance = false;

	do
	{
	#if 0
		printf("- - JOGADOR 1 - -\n");
		printf("LINHA = ");
		scanf("%d", &i);
		printf("COLUNA = ");
		scanf("%d", &j);
		printf("- - - - - - - - -  \n");
	#else
	printf("- - BOT - -\n");
	Sleep(1200); // pausa de 2000 ms = 2 s
	if (numJogadas == 1)
	{
		Primeira_Jogada(&i, &j);
		a = i; // Salvar jogada
		b = j; // Salvar jogada
	}else if (numJogadas == 3)
	{
		Terceira_Jogada(A, &i, &j);
		a = i; // Salvar jogada
		b = j; // Salvar jogada
	} else if (numJogadas == 5)
	{
		Quinta_Jogada(A, &i, &j, a, b, chance);
		a = i; // Salvar jogada
		b = j; // Salvar jogada
	} else if (numJogadas == 7)
	{
		Setima_Jogada(A, &i, &j, a, b, chance);
		a = i; // Salvar jogada
		b = j; // Salvar jogada
	} else if (numJogadas == 9)
	{
		Nona_Jogada(A, &i, &j, a, b, chance);
		a = i; // Salvar jogada
		b = j; // Salvar jogada
	}
	
	#endif
		if ((A[i-1][j-1] != 0)||(i > 3)||(j>3)||(i<1)||(j<1))
		{
			printf("  JOGADA ILEGAL! Tente novamente! \n\n");
			mostra(M);
		}
		else
		{
			A[i-1][j-1] = 1;
			sai = true;
		}
	}
	while (sai == false);
}

void joga2(int A[3][3])
{
	int i, j;
	bool sai = false;
	
	do
	{
		printf("- - JOGADOR 2 - -\n");
		printf("LINHA = ");
		scanf("%d", &i);
		printf("COLUNA = ");
		scanf("%d", &j);
		printf("- - - - - - - - -  \n");

		if ((A[i-1][j-1] != 0)||(i > 3)||(j>3)||(i<1)||(j<1))
		{
			printf("  JOGADA ILEGAL! Tente novamente! \n\n");
			mostra(M);
		}
		else
		{
			A[i-1][j-1] = 2;
			sai = true;
		}
	}
	while (sai == false);
}

//PROGRAMA PRINCIPAL
int main()
{
	srand(time(NULL)); // semente
    inicializa_Jogo();
	mostra(M);
	vencedor = verifica(M);
	printf("%d\n", vencedor);
	system("cls"); // comando do Windows para limpar o terminal

	do
	{
		numJogadas++;
		joga1(M, numJogadas);
		mostra(M);
		vencedor = verifica(M);
		if (vencedor == 1)
		{
			printf("\n - - - BOT VENCE!!! - - -\n\n");
			printf("Digite qualquer caractere para finalizar: ");
			scanf(" %c", &menu);
			return 0;
		}
		
		if (numJogadas == 9)
		{
			printf("\n- - - JOGO EMPATADO!!! - - -\n\n");
			printf("Digite qualquer caractere para finalizar: ");
			scanf(" %c", &menu);
			return 0;
		}
		
		numJogadas++;
		joga2(M);
		mostra(M);
		vencedor = verifica(M);
		if (vencedor == 2)
		{
			printf("\n - - - JOGADOR 2 VENCE!!! - - -\n\n");
			printf("Digite qualquer caractere para finalizar: ");
			scanf(" %c", &menu);
			return 0;
		}
	}
	while (vencedor == 0);

	return 0;
}