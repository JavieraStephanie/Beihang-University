/*正整数的打印*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int main()
{
	char ent[6];
	int num, savenum = 0, rem, rev=0, dig = 0;

	fgets(ent, 6, stdin);

	num = atoi(ent);

	savenum = num + 0;

	while (num != 0) {
		rem = num % 10;
		rev = rev * 10 + rem;
		num /= 10;
		++dig;
	}

	printf("%d\n%d\n%d\n", dig, savenum, rev);

	return 0;
}