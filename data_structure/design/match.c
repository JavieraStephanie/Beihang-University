#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *fp;
char par[1000], symbol[1000], notmatch='n';
int line[1000], symbol1=0, symbol2=0;
int i, j, k, l, isComment = 0, open1 = 0, close1 = 0, open2 = 0, close2= 0, curline;

int main()
{
	FILE *fp;
	fp = fopen("example.c", "r");

	//Store all the symbols in the array
	for (i = 0, l = 0, curline = 1; !feof(fp); curline++, l++)
	{
		fgets(par, 1000, fp);
		for (j = 0; par[j] != '\0'; j++)
		{
			//if the symbols are found, store it in the symbols array
			if (par[j] == '(')
			{
				symbol[i] = par[j];
				line[i] = curline;
				i++;
				open1 += 1;
			}
			else if (par[j] == ')')
			{
				symbol[i] = par[j];
				line[i] = curline;
				i++;
				close1 += 1;
			}
			else if (par[j] == '{')
			{
				symbol[i] = par[j];
				line[i] = curline;
				i++;
				open2 += 1;
			}
			else if (par[j] == '}')
			{
				symbol[i] = par[j];
				line[i] = curline;
				i++;
				close2 += 1;
			}
			else if (par[j] == '"')
			{
				j++;
				while (par[j] != '"')
				{
					j++;
				}
			} //if the symbols are found in the say section, ignore them
			else if (par[j] == '/' && par[++j] == '/')
			{
				break;
			} //if it's the one line comment, ignore the symbols
			else if (par[j] == '/' && par[j + 1] == '*') //if it's the many-lines comment, get the next line of the code
			{
				isComment = 1;
				break;
			}
			else if (isComment) //if it's the many-lines comment, find for the end symbol of the comment system
			{
				for (k = 0; par[k] != '\0'; k++)
				{
					if (par[k] == '*' && par[k + 1] == '/')
					{
						isComment = 0;
						break;
					}
					else
						continue;
				}
			}
		}
	}
	
	//Look if there are any unmatching symbols
	if (close1 > open1 || close2 > open2)
	{
		for (i = 0; i < strlen(symbol); i++)
		{
			if (symbol[i] == '{')
				symbol2++;
			else if (symbol[i] == '}')
			{
				symbol2--;
				if (symbol2 == -1)
				{
					notmatch = '}';
					break;
				}
			}
			if (symbol[i] == '(')
				symbol1++;
			else if (symbol[i] == ')')
			{
				symbol1--;
				if (symbol1 == -1)
				{
					notmatch = ')';
					break;
				}
			}
		}
	}
	else if (open1 > close1 || open2 > close2)
	{
		for (i = strlen(symbol)-1; i >= 0; i--)
		{
			if (symbol[i] == '}')
				symbol2++;
			else if (symbol[i] == '{')
			{
				symbol2--;
				if (symbol2 == -1)
				{
					notmatch = '{';
					break;
				}
			}
			if (symbol[i] == ')')
				symbol1++;
			else if (symbol[i] == '(')
			{
				symbol1--;
				if (symbol1 == -1)
				{
					notmatch = '(';
					break;
				}
			}
		}
	}
	//the printout command
	if (symbol1 == 0 && symbol2 == 0)
	{
		for (i = 0; i < strlen(symbol); i++)
			printf("%c", symbol[i]);
	}

	else
	{
		if (symbol2 > 0 && notmatch == 'n')
			notmatch = '{';
		else if (symbol1 > 0 && notmatch == 'n')
			notmatch = '(';
		printf("without maching '%c' at line %d", notmatch, line[i]);
	}

	fclose(fp);

	system("pause");
	return 0;
}