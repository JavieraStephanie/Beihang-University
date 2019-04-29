#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

char formula[MAX], temp[4], notempty=0, tempin;
int numbers[MAX];
int top=0, i=0, j=0, tempnum;

int main()
{
	//input process
	while (tempin != '=')
	{
		scanf("%c", &tempin);
		if (tempin >= '0' && tempin <= '9')
		{
			temp[i] = tempin;
			notempty = 1;
			i++;
		}
		else if (tempin == ' ')
		{
			if (notempty)
			{
				numbers[j] = atoi(temp);
				notempty = 0;
				j++;
				i = 0;
			}
			continue;
		}
		else if (tempin == '(')
		{
			formula[top] = '(';
		}
		else if (tempin == ')')
		{
			formula[top] = ')';
			if (notempty)
			{
				numbers[j] = atoi(temp);
				notempty = 0;
				j++;
				i = 0;
			}
		}
		else if (tempin == '+')
		{
			formula[top] = '+';
			if (notempty)
			{
				numbers[j] = atoi(temp);
				notempty = 0;
				j++;
				i = 0;
			}
		}
		else if (tempin == '-')
		{
			formula[top] = '-';
			if (notempty)
			{
				numbers[j] = atoi(temp);
				notempty = 0;
				j++;
				i = 0;
			}
		}
		else if (tempin == '*')
		{
			formula[top] = '*';
			if (notempty)
			{
				numbers[j] = atoi(temp);
				notempty = 0;
				j++;
				i = 0;
			}
		}
		else if (tempin == '/')
		{
			formula[top] = '/';
			if (notempty)
			{
				numbers[j] = atoi(temp);
				notempty = 0;
				j++;
				i = 0;
			}
		}
		top++;
	}
	numbers[j] = atoi(temp);

	for (i = 1; i != '\0'; i+2, j++)
	{
		for (j = 0; j!='\0'; j++)
		{

		}
	}

	printf("%d", temp[j]);
	system("pause");
	return 0;
}