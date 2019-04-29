#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLENGTH 101

void check(char *number);
void counte0(char *number0);
void counte1(char *number1);

int main()
{
	char notation[MAXLENGTH];

	scanf("%100s", notation);

	check(notation);
	//printf("%s", notation);

	system("pause");
	return 0;
}

void check(char *number)
{
	int i, j, len;

	len = strlen(number);

	for (i = 0; i < len; i++)
	{
		if (i == 0 && number[i] == '0' && number[i+1] == '.')
		{
			counte0(number);
			break;
		}
		else if (i == 0 && number[i] != '0' && number[i + 1] == '.')
		{
			printf("%se0", number);
			break;
		}
		else if (i != 0 && i != 1 && number[i] == '.')
		{
			printf("%c.", number[0]);
			for (j = 1; j < len; j++)
			{
				if (number[j] == '.')
					continue;
				else
					printf("%c", number[j]);
			}
			printf("e%d", i - 1);
			break;
		}
	}
}

void counte0(char*number0)
{
	int i, j, len, e;

	len = strlen(number0);

	for (i = 2, e = 1; i < len; e++, i++)
	{
		if (number0[i] != '0' && i==len-1)
		{
			printf("%ce-%d", number0[i], e);
			break;
		}
		else if (number0[i] != '0' && i < len - 1)
		{
			printf("%c.", number0[i]);
			for (j = i+ 1; j < len; j++)
			{
				printf("%c", number0[j]);
			}
			printf("e-%d", e);
			break;
		}
	}
}