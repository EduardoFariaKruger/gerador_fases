#include <stdio.h>
#include <stdlib.h>

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
	if(matriz )
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
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
		case 2:
			b.y--;
		case 3:
			b.x++;
		case 4:
			b.x--;	
	}
	return b;
}

int is_inside(struct coordenada vetor[], int tam, struct coordenada ponto)
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

void gera_fase(struct coordenada *vetorCoord, int *vetTam, int **matriz, int vezes, int linhas, int colunas, struct coordenada pos_inicial)
{
	if(vezes >= 0)
	{
		int aleat;
		struct coordenada ponto;
		aleat = gera(1, 4);
		ponto = move(pos_inicial, aleat);
		if(esta_dentro(ponto, linhas, colunas) && !is_inside(vetorCoord, *vetTam, ponto))
		{
			matriz[ponto.x][ponto.y] = 1;
			vetorCoord[*vetTam] = ponto;
			(*vetTam)++;
			gera_fase(vetorCoord, vetTam, matriz, vezes-1, linhas, colunas, ponto);
		}
		gera_fase(vetorCoord, vetTam, matriz, vezes, linhas, colunas, pos_inicial);
	}
}



int main () 
{
	srand(100);

	//vetor de posicoes ocupadas
	//alocar ele dinamicamente conforme mais tijolos forem percorridos
	//declarar a matriz a ser usada
	//alocar dinamicamente conforme as necessidades do usuario
	int linhas;
	int colunas;
	int tam = 0;
	int salas;
	//int numeroDeSalas;
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

	printf("quantidade de linhas da matriz: ");
	scanf("%d", &linhas);
	printf("quantidade de colunas da matriz: ");
	scanf("%d", &colunas);
	printf("quantidade de salas na matriz: ");
	scanf("%d", &salas);
	aleat.x = linhas / 2;
	aleat.y = colunas / 2;
	printf("%d\n", vetorCoord[0].x);
	matriz = gera_matriz(linhas, colunas);
	if (matriz != NULL)
	{
		preenche_matriz(matriz, linhas, colunas);
		if(esta_dentro(aleat, linhas, colunas))
		{
			matriz[aleat.x][aleat.y] = 1;
			vetorCoord[tam] = aleat;
			tam++;
		}
		gera_fase(vetorCoord, &tam, matriz, salas, linhas, colunas, aleat);
		imprime_matriz(matriz, linhas, colunas);
	}
	for (int p = 0; p < tam; p++)
	{
		printf("%d %d\n", vetorCoord[p].x, vetorCoord[p].y);
	}
	return 0;
}
