#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAX 10001

int main()
{
	char par[MAX];
	int length[MAX], i, j, max = length[0];

	scanf("%s", par);

	length[0] = 1;
	for (i = 1; par[i] != '\0'; i++)
	{
		length[i] = 1; 
		for (j = 0; j<i; j++)  
		{
			if (par[i] >= par[j])
			{
				if (length[i] < length[j] + 1)
					length[i] = length[j] + 1;
			}
		}
	}
 
	for (i = 1; par[i] != '\0'; i++)
	{
		if (max < length[i])
			max = length[i];
	}

	printf("%d\n", max);

	system("pause");
	return 0;
}