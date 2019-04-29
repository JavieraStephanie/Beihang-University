#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num[5] = { 8, 6, 5, 4, 1 }, temp, i=0, j;
	int *pnum=&num;

	while (*pnum > *(pnum + 1))
	{
		for (j = i; *(pnum + j) > *(pnum + j + 1) && j<4; j++)
		{
			temp = *(pnum + j);
			*(pnum + j) = *(pnum + j + 1);
			*(pnum + j + 1) = temp;
		}
		i = 0;
	}

	for (i = 0; i < 5; i++)
	{
		printf("%d ", *(pnum + i));
	}
	
	system("pause");
	return 0;
}