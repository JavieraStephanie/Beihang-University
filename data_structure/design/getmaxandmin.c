/*找最大最小整数*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>

int main()
{
	int count, num;
	int min = INT_MAX;
	int max = INT_MIN;

	scanf("%d", &count);

	while (count--) {
		scanf("%d", &num);
		if (num > max)
			max = num;
		if (num < min)
			min = num;
	}

	printf("%d %d", max, min);

	return 0;
}