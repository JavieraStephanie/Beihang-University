#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int i, j;
int matrix[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, matrixt[3][3];
void transpose();

int main()
{
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("	%d", matrix[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	transpose();


	system("pause");
	return 0;
}

void transpose()
{
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			matrixt[i][j] = matrix[j][i];
			printf("	%d", matrixt[i][j]);
		}
		printf("\n");
	}

	return;
}