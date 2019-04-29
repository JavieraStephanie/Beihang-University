#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int main()
{
	char ent[4];
	int num, N, a, b, t;

	fgets(ent, 4, stdin);

	num = atoi(ent);
	
	for (a = 1; a <= 9; a++) {
		for (b = 1; b <= 9; b++) {
			N = (a*10 + b)*((b * 10) + a);
			if (N == num)
				break;
		}

		if (N == num)
			break;
	}

	if (a>b) // A < B
	{
		t = a;
		a = b;
		b = t;
	}

	if (N == num)
		printf("%d%d", a, b);

	if (N != num)
		printf("No Answer");

	return 0;
}