//Jogo da Velha para 2 jogadores humanos
//Criado em 30/08/2022 por Ernesto F. F. Ramirez

#include <iostream>

using namespace std;

int M [3] [3], vencedor = 0, numJogadas = 0;
char menu;


void inicializa_Jogo()
{
	M[0][0] = 0; 	M[0][1] = 0; 	M[0][2] = 0;
	M[1][0] = 0; 	M[1][1] = 0; 	M[1][2] = 0;
	M[2][0] = 0; 	M[2][1] = 0; 	M[2][2] = 0;
	
	cout << "- - - - - - - - -  \n";
	cout << " Bem-vindo ao Jogo da velha!!!\n";
	cout << "- - - - - - - - - -\n\n";
}


void mostra(int A [3] [3])
{
	cout << "- - - - - - - - -  \n";
	cout << "    "<< A[0][0] << "   " << A[0][1] << "   " << A[0][2] << "\n";
	cout << "    "<< A[1][0] << "   " << A[1][1] << "   " << A[1][2] << "\n";
	cout << "    "<< A[2][0] << "   " << A[2][1] << "   " << A[2][2] << "\n";
	cout << "- - - - - - - - -  \n\n";
}

int verifica(int A [3] [3])
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

void joga1(int A [3] [3])
{
	int i, j;
	bool sai = false;
	
	do
	{
		cout << "- - JOGADOR 1 - -\n";
		cout << "LINHA = ";
		cin >> i;
		cout << "COLUNA = ";
		cin >> j;
		cout << "- - - - - - - - -  \n";
	
		if ((A[i-1][j-1] != 0)||(i > 3)||(j>3)||(i<1)||(j<1))
		{
			cout << "  JOGADA ILEGAL! Tente novamente! \n\n";
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


void joga2(int A [3] [3])
{
	int i, j;
	bool sai = false;
	
	do
	{
		cout << "- - JOGADOR 2 - -\n";
		cout << "LINHA = ";
		cin >> i;
		cout << "COLUNA = ";
		cin >> j;
		cout << "- - - - - - - - -  \n";
	
		if ((A[i-1][j-1] != 0)||(i > 3)||(j>3)||(i<1)||(j<1))
		{
			cout << "  JOGADA ILEGAL! Tente novamente! \n\n";
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
    inicializa_Jogo();
	mostra(M);
	vencedor = verifica(M);
	cout << vencedor << "\n";
	
	do
	{
		joga1(M);
		numJogadas++;
		mostra(M);
		vencedor = verifica(M);
		cout << vencedor << "\n";
		if (vencedor == 1)
		{
			cout << "\n - - - JOGADOR 1 VENCE!!! - - -\n\n";
			cout << "Digite qualquer caractere para finalizar: ";
			cin >> menu;
			return 0;
		}
		
		if (numJogadas == 9)
		{
			cout << "\n- - - JOGO EMPATADO!!! - - -\n\n";
			cout << "Digite qualquer caractere para finalizar: ";
			cin >> menu;
			return 0;
		}
		
		joga2(M);
		numJogadas++;
		mostra(M);
		vencedor = verifica(M);
		cout << vencedor << "\n";
		if (vencedor == 2)
		{
			cout << "\n - - - JOGADOR 2 VENCE!!! - - -\n\n";
			cout << "Digite qualquer caractere para finalizar: ";
			cin >> menu;
			return 0;
		}
	}
	while (vencedor == 0);


}

