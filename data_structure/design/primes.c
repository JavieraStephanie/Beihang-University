#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	int n, i=2;

	scanf("%d", &n);

	while (n >= i)
	{
		while (n%i == 0)
		{
			printf("%d ", i);
			n /= i;
		}

		i++;
	}
	return 0;
}