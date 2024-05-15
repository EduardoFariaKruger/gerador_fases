#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct coordenada
{
	int x;
	int y;
};

void preenche_matriz(int **matriz, int linhas, int colunas)
{	
	if (matriz != NULL)
	{
		for (int i = 0; i < linhas; i++)
		{
			for (int j = 0; j < colunas; j++)
			{
				matriz[i][j] = 0;
			}
		}
	}
}

int ** gera_matriz(int linhas, int colunas)
{
	//alocacao
	int **matriz = (int**)malloc(linhas * sizeof(int *));

	if(matriz == NULL)
	{
		return NULL;
	}

	for(int i = 0; i < linhas; i++)
	{
		//para cada linha ele tenha alocar a coluna
		matriz[i] = (int *)malloc(colunas * sizeof (int));

		//checa se a alocacao foi bem socedida
		if (matriz[i] == NULL)
		{
			//libera a memoria ate entao alocada caso de erro
			for(int j = 0; j < colunas; j++)
			{
				free(matriz[i]);
			}

			//libera a matriz inteira
			free(matriz);

			return NULL;
		}
	}
	return matriz;	
}

void libera_matriz(int **matriz, int linhas, int colunas)
{
	if(matriz != NULL)
	{
		for (int i = 0; i < linhas; i++)
		{
			free(matriz[i]);  // Libera a memória alocada para a linha i
		}
		free(matriz);  // Libera o ponteiro principal da matriz
	}
}

void imprime_matriz(int **matriz, int linhas, int colunas)
{
	printf("\e[1;1H\e[2J");
	if(matriz )
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
	sleep(1);
}

int gera(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

int esta_dentro(struct coordenada c, int linhas, int colunas)
{
	if (c.x >= 0 && c.x < linhas)
	{
		if(c.y >= 0 && c.y < colunas)
		{
			return 1;
		}
	}
	return 0;
}

struct coordenada random_coord(int a, int b)
{
	struct coordenada coord;
	coord.x = rand() % (b - a + 1) + a;
	coord.x = rand() % (b - a + 1) + a;
	return coord;
}

struct coordenada move(struct coordenada pos_ini, int move)
{
	struct coordenada b;
	b = pos_ini;
	switch (move)
	{	
		case 1:
			b.y++;
			break;
		case 2:
			b.y--;
			break;
		case 3:
			b.x++;
			break;
		case 4:
			b.x--;
			break;
	}
	return b;
}

int isIn_Vector(struct coordenada vetor[], int tam, struct coordenada ponto)
{
	int c = 0;
	for (int i = 0; i < tam; i++)
	{
		if(vetor[i].x == ponto.x && vetor[i].y == ponto.y)
		{
			c = 1;
		}
	}
	return c;
}

void gera_fase(int **matriz, int linhas, int colunas, struct coordenada pos_inicial, int qtdSalasCombate, int qtdSalasMercado, int qtdSalasQuimico, struct coordenada lajotas[], int *tam)
{
	int random;
	struct coordenada ponto;
	if(qtdSalasCombate > 0 || qtdSalasMercado > 0 || qtdSalasQuimico > 0)
	{
		random = gera(1, 4);
		ponto = move(pos_inicial, random);
		if(esta_dentro(ponto, linhas, colunas) && !isIn_Vector(lajotas, *tam, ponto))
		{
			if(qtdSalasCombate > 0)
			{
				//1 para sala de combate
				matriz[ponto.x][ponto.y] = 1;
				lajotas[*tam] = ponto;
				(*tam)++;
				printf("um\n");
				imprime_matriz(matriz, linhas, colunas);
				gera_fase(matriz, linhas, colunas, ponto, qtdSalasCombate - 1, qtdSalasMercado, qtdSalasQuimico, lajotas, tam);
			}
			else
			{
				if(qtdSalasMercado > 0)
				{
					//2 para sala de mercado
					matriz[ponto.x][ponto.y] = 2;
					lajotas[*tam] = ponto;
					(*tam)++;
					printf("dois\n");
					imprime_matriz(matriz, linhas, colunas);
					gera_fase(matriz, linhas, colunas, ponto, qtdSalasCombate, qtdSalasMercado - 1, qtdSalasQuimico, lajotas, tam);
				}
				else
				{
					//3 para sala do quimico
					matriz[ponto.x][ponto.y] = 3;
					lajotas[*tam] = ponto;
					(*tam)++;
					printf("tres\n");
					imprime_matriz(matriz, linhas, colunas);
					gera_fase(matriz, linhas, colunas, ponto, qtdSalasCombate, qtdSalasMercado, qtdSalasQuimico - 1, lajotas, tam); 
				}
			}
		}
		else
		{
			gera_fase(matriz, linhas, colunas, pos_inicial, qtdSalasCombate, qtdSalasMercado, qtdSalasQuimico, lajotas, tam);
		}
	}
}	

void imprime_vetor(struct coordenada vet[], int tam)
{
	for (int i = 0; i < tam; i++)
	{
		printf("(%d %d)  ", vet[i].x, vet[i].y);
	}
	printf("\n");
}



int main () 
{
	srand((unsigned)time(NULL));

	int linhas;
	int colunas;
	int tam = 0;
	int salas;
	int mercados;
	int quimicos;
	int **matriz;
	struct coordenada vazio;
	vazio.x = 0;
	vazio.y = 0;
	struct coordenada aleat;
	struct coordenada vetorCoord[100];
	for(int i=0; i < 100; i++)
	{
		vetorCoord[i] = vazio;
	}
	printf("quantidade de salas de combate na matriz: ");
	scanf("%d", &salas);
	printf("quantidade de mercados na matriz: ");
	scanf("%d", &mercados);
	printf("quantidade de quimicos na matriz: ");
	scanf("%d", &quimicos);
	linhas = (salas + mercados + quimicos)*2;
	colunas = (salas + mercados + quimicos)*2;
	aleat.x = linhas / 2;
	aleat.y = colunas / 2;
	printf("%d\n", vetorCoord[0].x);
	matriz = gera_matriz(linhas, colunas);
	if (matriz != NULL)
	{
		preenche_matriz(matriz, linhas, colunas);
		if(esta_dentro(aleat, linhas, colunas))
		{
			matriz[aleat.x][aleat.y] = 4; //4 para representar onde o player ira surgir
			vetorCoord[tam] = aleat;
			tam++;
		}
		gera_fase(matriz, linhas, colunas, aleat, salas, mercados, quimicos, vetorCoord, &tam);
		imprime_matriz(matriz, linhas, colunas);
	}
	printf("\n");
	imprime_vetor(vetorCoord, tam);
	libera_matriz(matriz, linhas, colunas);
	return 0;
}
