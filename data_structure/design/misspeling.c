#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAXWORDS 3500

typedef struct node
{
	char word[20];
	int position;
}info;

int count = 0;

void Sort(info list[], int n) {
	info temp;
	int i, j;

	for (i = 0; i<n; i++) {
		for (j = i + 1; j<n; j++) {
			if (strcmp(list[i].word, list[j].word) > 0) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}

int main()
{
	char dict[MAXWORDS][20] = { "\0" };
	info art[MAXWORDS] = { "\0",0 };
	char temp[20];
	int total = 0, total2 = 0, i, j, position=0, position2, found = 0;
	FILE *fp = fopen("dictionary.txt", "r"), *fa = fopen("article.txt", "r"), *fo = fopen("misspelling.txt", "w");

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

	while (!feof(fa))
	{
		fscanf(fa, "%s", temp);
		total2++;
		for (i = 0; temp[i] != '\0'; i++)
		{
			position2 = position;
			position2++;
			if (temp[i] >= 'A' && temp[i] <= 'Z')
			{
				temp[i] += 32;
			}

			else if (temp[i] < 'a' || temp[i] > 'z')
			{
				position2++;
				temp[i] = '\0';
				break;
			}
		}
		for (i = 0; i<total; ++i)
			if (strcmp(dict[i], temp) == 0)
			{
				total2--;
				break;
			}

		if (i >= total)
		{
			for (i = 0; i<total2; ++i)
				if (strcmp(art[i].word, temp) == 0)
				{
					total2--;
					break;
				}
			if (i >= total2)
			{
				strcpy(art[total2 - 1].word, temp);
				art[total2 - 1].position = position;
			}
		}
		position = position2;
	}

	Sort(art, total2);

	for (i = 0; i < total2; ++i)
	{
		for (j = 0; j < total; ++j)
		{
			if (strcmp(dict[j], art[i].word) == 0)
			{
				found = 1;
				break;
			}
			else
				found = 0;
		}
		if (found == 0)
		{
			fprintf(fo, "%s %d\n", art[i].word, art[i].position);
		}
		else if (found == 1)
			continue;
	}

	fclose(fp);
	fclose(fa);
	fclose(fo);
	return 0;
}