#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100


void convert(int n);

int main()
{
	int n;

	scanf("%d", &n);

	convert(n);

	system("pause");
	return 0;
}

void convert(int n)
{
	if (n / 10 == 0)
	{
		putchar('0' + n % 10);
	}
	else
	{
		convert(n / 10);
		putchar('0' + n % 10);
	}
}