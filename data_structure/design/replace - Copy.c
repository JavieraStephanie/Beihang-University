#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, int a, int b)
{
	int i = b;

	//We'll want to move the last element of the current expression arrangement later so we should first save that element to a temporary variable
	int temp = arr[b];

	//We'll start looking from behind, while the pointer i hasn't reach the end (in this case, the first element of the arrangement) then do the loop
	for (; i > a; i--)
		arr[i] = arr[i - 1]; //Replace the current element with the element before, keep doing this kind of loop in a recursion method

	//Now we change the first element of the expression with the previous last element that we saved to a temporary variable
	arr[a] = temp;
}

//This function actually works the same as rearrange only that this moves backward, returning the arrangement to its original form
void derearrange(int *arr, int a, int b)
{
	int i = a;
	int temp = arr[a];
	for (; i < b; i++)
		arr[i] = arr[i + 1];
	arr[b] = temp;
}

//In the following function, d is the pointer that points to the start of the array and N is the one that points to the last element in the array
void perm(int *arr, int d, int N)
{
	int i;
	
	//So if d is larger than N, this isn't right, it means that the operation is done, so now we can print out the operation result
	if (d > N)
	{
		//Print one line of permutation arrangement and we'll loop to the operation again and see if there are still other possible arrangements
		for (i = 0; i <= N; i++)
			printf("%d ", arr[i]);
		printf("\n");
	}

	//If the operation isn't done yet
	else
	{
		//We now use i as the pointer, and we let i start from where d starts
		for (i = d; i <= N; i++)
		{
			//Using the rearrange function, arrange the expression to a new arrangement
			rearrange(arr, d, i);
			
			//For every new arrangement, print that arrangement (using recursion method)
			perm(arr, d + 1, N);

			//Return the new arrangements to its original form
			derearrange(arr, d, i);
		}
	}
}

int main()
{
	int N, i;

	//Input the value of N, N would be the amount of the number the user will input later
	scanf("%d", &N);

	//It is known from the problem that N range should be 1<=N<=10
	//So here we say if N exceeds 1 or 10, then return 0 (error)
	if (N < 1 || N>10)
		return 0;

	//arr below is a pointer that acts as an array that has the size of N integers, so it should be N*(size of integer)
	int *arr = (int *)malloc(N * sizeof(int));

	//Input the array elements
	for (i = 0; i < N; i++)
		arr[i] = i + 1;

	//Now let's do the operation
	perm(arr, 0, N - 1);

	//For efficiency, free pointer arr when it's not used anymore or it will eat up RAM
	free(arr);
	return 0;
}