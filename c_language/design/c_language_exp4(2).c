#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 1000

int main()
{
	int p[MAXCHAR][20];
	int i, j, k;

	printf("Below is 10 lines of pascal triangle:\n");
	
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < i+1; j++)
		{
			if (j == 0 || j == i)
			{
				p[i][j] = 1;
				printf("%d ", p[i][j]);
			}

			else
			{
				p[i][j] = p[i - 1][j] + p[i - 1][j - 1];
				printf("%d ", p[i][j]);
			}
		}
		printf("\n");
	}

	system("pause");
	return 0;
}