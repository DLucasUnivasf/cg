#include <stdio.h>

/*
						CONVERSÃO ENTRE SISTEMAS DE REFERÊNCIA
							 	DANIELE SILVA REIS	
*/

float* transforma(char origem, int xmino, int xmaxo, int ymino, int ymaxo, int xmind, int xmaxd, int ymind, int ymaxd, int x, int y)
{
	float s[2];
	
	s[0] = (float)((xmaxd - xmind)*(x - xmino))/(xmaxo - xmino) + xmind;
	s[1] = (float)((ymaxd - ymind)*(y - ymino))/(ymaxo - ymino) + ymind;
	
	return s;
}

int main()
{
	char tipo;
	int xmin1, xmin2, ymin1, ymin2, xmax1, xmax2, ymax1, ymax2;
	int x, y, c=0; 
	float *saida;
	
	while(c==0)
	{
		printf("Insira o sistema de origem ('u' - universo | 'd' - dispositivo): ");
		scanf(" %c", &tipo);
		printf("Insira Xmin, Xmax, Ymin, Ymax do sistema de origem: ");
		scanf("%d %d %d %d", &xmin1, &xmax1, &ymin1, &ymax1);
		printf("Insira Xmin, Xmax, Ymin, Ymax do sistema de destino: ");
		scanf("%d %d %d %d", &xmin2, &xmax2, &ymin2, &ymax2);
		printf("Insira as coordenadas do ponto a ser transformado: ");
		scanf("%d%d", &x, &y);
		saida = transforma(tipo, xmin1, xmax1, ymin1, ymax1, xmin2, xmax2, ymin2, ymax2, x, y);
		printf("As novas coordenadas sao (%.4f, %.4f). \n", saida[0], saida[1]);
		printf("Deseja continuar? (-1 para sair | 0 para continuar): ");
		scanf("%d", &c);
	}
	
	return 0;
}
