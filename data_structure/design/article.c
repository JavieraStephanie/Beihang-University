#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <ctype.h>

typedef struct node
{
	char word[20];
	int count;
}info;

void main()
{
	char temp[20];
	char *lower[1000];
	info text[1000] = { "\0",0 };
	int total = 0, i, j, c = 0;
	FILE *fp = fopen("article.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s", temp);
		total++;
		for (i = 0; i<total; ++i)
			if (strcmp(text[i].word, temp) == 0)
			{
				text[i].count++;
				total--;
				break;
			}
		if (i >= total)
		{
			strcpy(text[total - 1].word, temp);
			text[total - 1].count++;
		}
	}

	for (i = 0, j = 0; i < total; i++)
	{
		lower[i] = text[i].word;
	}

	for (i = 0; i<total; i++)
	{
		printf("%s ", lower[i]);
		for (j = 0; j < text[i].count; ++j)
			c++;
		printf("%d", c);
		c = 0;
		printf("\n");
	}
	system("pause");
}