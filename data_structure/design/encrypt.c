#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXCHAR 51

void findKey(char* key, char* mark) 
{
	int len = strlen(key); // Get the length of the key string
	int i, j;

	i = j = 0;

	memset(mark, 0, 26);

	for (i = 0; i < len; i++)
	{
		if (mark[key[i] - 97] == 0)
		{
			mark[key[i] - 97] = 1;
			key[j] = key[i];
			j++;
		}
	}
	key[j] = '\0';

	for (i = 0, j = 0; i < 26; i++)
	{
		if (mark[i] == 0) 
		{
			mark[j] = 97 + i;
			j++;
		}
	}
	mark[j] = '\0';
}

int main() 
{
	char* encrypt;
	char map[27], key[MAXCHAR], mark[26];

	int i, len, markLen, nFileLen;

	FILE* inputFile;
	FILE* outputFile;

	scanf("%50s", key); // Input the key string

	findKey(key, mark);

	printf("%s\n", key);

	len = strlen(key);
	strcpy(map, key);

	markLen = strlen(mark);
	for (i = len; i < 26; i++) map[i] = mark[markLen + len - 1 - i];
	map[26] = '\0';
	printf("%s\n", map);

	inputFile = fopen("encrypt.txt", "r");

	if (inputFile == NULL) 
	{
		printf("encrypt.txt doesn't exist\n");
		return 1;
	}

	fseek(inputFile, 0, SEEK_END);
	nFileLen = ftell(inputFile);
	encrypt = (char*)malloc(nFileLen + 1);
	fseek(inputFile, 0, SEEK_SET);
	fread(encrypt, nFileLen, 1, inputFile);
	encrypt[nFileLen] = '\0';

	printf("%s\n", encrypt);

	for (i = 0; i < nFileLen; i++) 
	{
		if (encrypt[i]<123 && encrypt[i]>96)
			encrypt[i] = map[encrypt[i] - 97];
	}

	outputFile = fopen("output.txt", "w+");

	fwrite(encrypt, nFileLen, 1, outputFile);

	printf("%s\n", encrypt);

	fclose(outputFile);
	fclose(inputFile);
	free(encrypt);
	return 0;
}