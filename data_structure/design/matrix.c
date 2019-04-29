#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int matrix[10][10];
	int n, r, c, op, num;

	scanf("%d", &n); //n is the size of the matrix

	if (n < 1 || n>10) //If the value of N exceeded the limit 1~10
	{
		printf("Value range limit between 0~10");
		return 0;
	}

	//input the element value for the matrix, it can be positive or negative numbers
	for (r = 0; r < n; r++)
	{
		for (c = 0; c < n; c++)
		{
			scanf("%d", &matrix[r][c]);
		}
	}

	while (1)
	{
		//After inputting the first matrix, input the operation symbol (could only be either +, -, or #)
		op = getchar();
		op = getchar();

		//If the operation symbol is #, it means there will be no new matrix, print out the result matrix
		if (op == '#')
		{
			for (r = 0; r < n; r++)
			{
				for (c = 0; c < n; c++)
				{
					printf("%5d", matrix[r][c]);
				}
				printf("\n");
			}
			return 0;
		}

		//Else, input the next matrix
		for (r = 0; r < n; r++)
		{
			for (c = 0; c < n; c++)
			{
				scanf("%d", &num);
				//Then, if the operation is +, add both matrixes
				if (op == '+')
					matrix[r][c] += num;
				//Else if the operation is -, subtract both matrixes and store the result
				//as the first matrix value for next operation
				else
					matrix[r][c] -= num;
			}
		}
	}
}