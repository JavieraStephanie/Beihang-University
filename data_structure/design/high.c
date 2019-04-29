#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int m, count;
	float s=0, n;

	scanf("%f %d", &n, &m);
	
	s += n; // original height

	for (count = 0; count < (m-1); count++) { //height after divided by 4
		n /= 4;
		s += n * 2;
	}

	n /= 4;

	printf("%.2f\n%.2f", s, n);

	return 0;

}