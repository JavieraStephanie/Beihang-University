#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10

int main() 
{
	int i, j, a, x, y;
	int array_end = 0;

	int A[MAX] = { 0 };
	int B[MAX] = { 0 };

	//Input array A values
	for (i = 0; i < MAX, array_end==0; i++)
	{
		scanf("%d", &A[i]);   

		//If the user inputs -1, means that the array input has ended
		//Therefore, array_end would be 1, and in the for condition it can be seen that if the array_end is 1, the loop will end (array has ended)
		if (A[i] == -1)
			array_end++;
	} 

	array_end = 0; //Reset array_end to 0 for B array

	//Input array B values
	for (j = 0; j < MAX, array_end==0; j++)
	{ 
		scanf("%d", &B[j]);  

		//If the user inputs -1, means that the array input has ended
		//Therefore, array_end would be 1, and in the for condition it can be seen that if the array_end is 1, the loop will end (array has ended)
		if (B[j] == -1)
			array_end++;
	}  


	//Find the missing values
	//x would be the counter for array A and y would be the counter for array B
	//Because the last element of the array is ignored (the -1 end sign), so the max value for the loop condition would be counter-1 (i-1 or j-1)
	for (x = 0; x < (i - 1); x++)
	{
		for (y = 0, a = 0; y < (j - 1); y++)
		{
			//a would be another pointer in array B that moves differently from y
			//Because it's not guaranteed that the order of the array alements would be the same so there would be lots of difference in elements checking
			//Therefore we need another pointer (here is a), to help with the finding process
			if (A[x] != B[y])
				a++;

			if (a == (j - 1))
				printf("%d ", A[x]);
		}
	}

	return 0;
}