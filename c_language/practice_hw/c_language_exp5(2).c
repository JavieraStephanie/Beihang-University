#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

void join(char *str1, char *str2);
int main()
{
	char str1[MAX] = "I love ", str2[MAX] = "eating meatballs";
	printf("%s\n\n", str1);
	printf("%s\n\n", str2);

	join(str1, str2);
	printf("%s\n\n", str1);

	system("pause");
	return 0;
}

void join(char *str1, char *str2)
{
	strcat(str1, str2);
}