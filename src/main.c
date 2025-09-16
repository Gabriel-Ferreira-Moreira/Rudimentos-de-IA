#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    // ----------- Windows -----------
    #include <windows.h>
    #include "C:\\Jogo-da-Velha\\inc\\BOT.h"
    void wait(int s) {
        Sleep(s * 1000); // Sleep usa milissegundos
    }
	void clear() {
		system("cls"); // comando do Windows para limpar o terminal
	}
#else
    // ----------- Linux -----------
    #include <unistd.h>
	#include "../inc/BOT.h"
    void wait(int s) {
        sleep(s); // sleep já usa segundos
    }
	void clear() {
		system("clear"); // comando do Linux para limpar o terminal
	}
#endif

int M[3][3], vencedor = 0, numJogadas = 0;
int a,b;
char menu, Primeiro, Dificuldade='2';



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
	bool sai = false;
	do
	{
	if (Primeiro == '2'){
		printf("- - JOGADOR - -\n");
		printf("LINHA = ");
		scanf("%d", &i);
		printf("COLUNA = ");
		scanf("%d", &j);
		printf("- - - - - - - - -  \n");

	}else	
	{
		bool chance = false;
		Primeiro_Jogador(&i, &j, numJogadas, A, a, b, chance,Dificuldade);
		printf("- - BOT - -\n");
		wait(1); 
	}
	
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
	a = i; 
	b = j;
}

void joga2(int A[3][3], int numJogadas)
{
	int i, j;
	bool sai = false;
	
	do
	{
		if (Primeiro == '1'){
		printf("- - JOGADOR - -\n");
		printf("LINHA = ");
		scanf("%d", &i);
		printf("COLUNA = ");
		scanf("%d", &j);
		printf("- - - - - - - - -  \n");

		}else 
		{
			bool chance = false;
			Segundo_Jogador(&i, &j, numJogadas, A, a, b, chance,Dificuldade);
				printf("- - BOT - -\n");
				wait(1);

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
	}
	while (sai == false);
	a = i; 
	b = j;
}


//PROGRAMA PRINCIPAL
int main()
{
	clear();
	srand(time(NULL)); // semente
	printf("Quem comeca jogando? \n1 - BOT \n2 - JOGADOR \n");
	scanf(" %c", &Primeiro);
	clear();
	inicializa_Jogo();
	mostra(M);
	wait(1); 
	vencedor = verifica(M);

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
		joga2(M, numJogadas);
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