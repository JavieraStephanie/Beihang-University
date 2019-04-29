#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAXWORDS 3500

int count = 0;

int LinearSearch(char arr[][20], int n, char x[]);
int BinarySearch(char arr[][20], int l, int r, char x[]);
int InterpolationSearch(char arr[][20], int n, char x[]);

int main()
{
	char dict[MAXWORDS][20] = { "\0" };
	char temp[20], search[20];
	int total = 0, i, formula, found;
	FILE *fp = fopen("dictionary3000.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s", temp);
		total++;
		for (i = 0; i<total; ++i)
			if (strcmp(dict[i], temp) == 0)
			{
				total--;
				break;
			}
		if (i >= total)
		{
			strcpy(dict[total - 1], temp);
		}
	}

	scanf("%s %d", search, &formula);
	
	if (formula == 1)
	{
		found = LinearSearch(dict, total, search);
	}

	else if (formula == 2)
	{
		found = BinarySearch(dict, 0, total, search);
	}
	else if (formula == 3)
	{
		found = InterpolationSearch(dict, total, search);
	}
	else if (formula == 4)
	{
		found = 4;
	}

	printf("%d %d", found, count);
	return 0;
}

int LinearSearch(char arr[][20], int n, char x[])
{
	int i;
	for (i = 0; i < n; i++)
	{
		count++;
		if (strcmp(arr[i], x) == 0)
			return 1;
		else if (strcmp(arr[i], x) > 0)
			return 0;
	}
	return 0;
}

int BinarySearch(char arr[][20], int l, int r, char x[])
{
	if (r >= l)
	{
		count++;
		int mid = l + (r - l) / 2;
		if (strcmp(arr[mid], x) == 0)
			return 1;
		if (strcmp(arr[mid], x) > 0)
			return BinarySearch(arr, l, mid - 1, x);
		return BinarySearch(arr, mid + 1, r, x);
	}
	return 0;
}

int InterpolationSearch(char arr[][20], int n, char x[])
{
	int lo = 0;
	int hi = n - 1;
	
	while (lo <= hi&& (strcmp(arr[lo], x) < 0) && (strcmp(arr[hi], x) >= 0))
	{
		int pos = lo + (((double)(hi - lo) / (strcmp(arr[hi], arr[lo])))*(strcmp(x, arr[lo])));
		//int pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo]))*(x - arr[lo]));
		if (strcmp(arr[pos], x) == 0)
			return 1;
		if (strcmp(arr[pos], x) < 0)
			lo = pos + 1;
		else
			hi = pos - 1;
	}
	return 0;
}