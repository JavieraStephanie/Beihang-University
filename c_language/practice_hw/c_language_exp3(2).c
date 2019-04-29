#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 50

int main()
{
	int num[10] = { 5, 1, 2, 3, 4, 6, 8, 7, 9 };
	int i, j, l, temp, *p, c=0;

	for (i = 0; i < 10; i++)
	{
		for (j = i; num[j] < num[j - 1]; j--)
		{
			temp = num[j - 1];
			num[j - 1] = num[j];
			num[j] = temp;
		}
	}

	printf("\n");

	for (p=num, i=0; i<10; p++, i++)
	{
		printf("%d", *p);
	}

	system("pause");
	return 0;
}