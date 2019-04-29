/*简易计算器*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	int data1, data2, res;
	float res2;
	char op;
	res = 0;

	scanf("%d %d %c", &data1, &data2, &op);

	if (op == '*')
	{
		res = data1 * data2;
		printf("%d\n", res);
	}
	else if (op == '+')
	{
		res = data1 + data2;
		printf("%d\n", res);
	}
	else if (op == '-')
	{
		res = data1 - data2;
		printf("%d\n", res);
	}
	else if (op == '/')
	{
		res2 = (float) data1 / data2;
		if (data1 % data2 == 0) {
			printf("%.0f\n", res2);
		}
		else
		{
			printf("%.2f\n", res2);
		}
	}
	return 0;
}