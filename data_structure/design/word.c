#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

typedef struct node
{
	char word[20];
	int count;
}info;

void Sort(info[]);

FILE *fp;
int total = 0;

int main()
{
	char word[20];
	info text[1000] = { "\0", 0 };
	int i, j, c = 0, t;
	fp = fopen("article.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s", word);
		total++;
		for (i = 0; word[i] != '\0'; i++)
		{
			if (word[i] >= 'A' && word[i] <= 'Z')
			{
				word[i] += 32;
			}

			else if (word[i] < 'a' || word[i] > 'z')
			{
				/*while (word[i]<'a' || word[i]>'z' || word[i]<'A' || word[i]>'Z')
				{
					t = i;
					t++;
				}*/
				//if (word[t] == '\0')
					word[i] = '\0';
			}
		}
		for (i = 0; i<total; ++i)
			if (strcmp(text[i].word, word) == 0)
			{
				text[i].count++;
				total--;
				break;
			}
		if (i >= total)
		{
			strcpy(text[total - 1].word, word);
			text[total - 1].count++;
		}
	}
	Sort(text);
	for (i = 0; i<total; i++)
	{
		printf("%s ", text[i].word);
		for (j = 0; j < text[i].count; ++j)
			c++;
		printf("%d", c);
		c = 0;
		printf("\n");
	}

	fclose(fp);

	return 0;
}

void Sort(info list[]) {
	info temp;
	int i, j;

	for (i = 0; i<total; i++) {
		for (j = i + 1; j<total; j++) {
			if (strcmp(list[i].word, list[j].word) > 0) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}