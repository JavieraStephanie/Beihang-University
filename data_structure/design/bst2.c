#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

int tree[MAX], pos[MAX];
int i, j, k, n, mid, mid2 = 0;

void input();
void sort();

int main()
{	
	input();
	sort();
	position();


	system("pause");
	return 0;
}

void input()
{
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &tree[i]);
}
void sort()
{
	int s, k, temp;
	for (s = 0; s < n; s++)
	{
		temp = tree[s];
		for (k = s+1; k<n; k++)
		{
			if (tree[k] < temp)
			{
				temp = tree[k];
				tree[k] = tree[s];
			}
		}
		tree[s] = temp;
	}
}