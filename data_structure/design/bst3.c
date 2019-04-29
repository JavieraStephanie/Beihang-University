#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

void printSorted(int arr[], int start, int end)
{
	if (start > end)
		return;

	// print left subtree
	printSorted(arr, start * 2 + 1, end);

	// print root
	printf("%d  ", arr[start]);

	// print right subtree
	printSorted(arr, start * 2 + 2, end);
}

int main()
{
	int n, i;
	int arr[MAX];

	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		scanf("%d", arr[i]);
	}
	int arr_size = sizeof(arr) / sizeof(int);
	printSorted(arr, 0, arr_size - 1);
	getchar();
	return 0;
}