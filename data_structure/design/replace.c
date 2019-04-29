#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char original[10], replace[10], c[1000];

//This function is to judge all the words that are going to be replaced
//Because we'll ignore all alphabet cases, so be it capital letter or just normal letter as long as it forms the right word, it will be replaced
int judge(int i, int l)
{
	int j;
	for (j = 0; j < l; j++)
	{
		if ((c[i + j] != original[j]) && (c[i + j] != original[j] + 'a' - 'A') && (c[i + j] != original[j] + 'A' - 'a'))
			return 0;
	}
	return 1;
}

int main()
{
	int original_length, i, len = 0;
	char ch;

	//Input the word that want to be replaced
	scanf("%s", original);

	//Input the word that will replace the previous word
	scanf("%s", replace);

	//Get the length of the original word
	original_length = strlen(original);

	//Declare the input and output files
	freopen("filein.txt", "r", stdin);
	freopen("fileout.txt", "w", stdout);

	//Now read the input file content
	memset(c, '\0', sizeof(c));

	while (ch != EOF)
	{
		ch = getchar();
		c[len++] = ch;
	}


	for (i = 0; i < len - 1; i++)
	{
		if (i + original_length >= len - 1)
			printf("%c", c[i]);

		else if (judge(i, original_length))
		{
			printf("%s", replace);
			i += original_length - 1;
		}

		else
			printf("%c", c[i]);
	}

	exit(0);
	return 0;
}