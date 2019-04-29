#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

int queue[MAX];
int top, i, j;

void pop();

int main()
{
	for (top = 0; top < MAX; top++)
	{
		scanf("%d", &queue[top]);
		if (queue[top] == -1)
			break;
	}

	for (i = 0; i<top; )
	{
		if (queue[i] == 1)
		{
			i += 2;
			continue;
		}
		else if (queue[i] == 0)
		{
			for (j = i - 1; (queue[j] == 0 || queue[j] == 1) && j != 0; j--);
			if (j == 0)
				printf("error ");
			else
				pop();
			i++;
			continue;
		}
	}

	system("pause");
	return 0;
}

void pop()
{
	printf("%d ", queue[j]);
	queue[j] = 0;
	return;
}