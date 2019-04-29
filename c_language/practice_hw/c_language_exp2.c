#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	double a, b, c, d, x1, x2, imaginary, real;
	
	printf("Input the value of a, b, c\n");
	scanf("%lf %lf %lf", &a, &b, &c);

	d = b*b - 4*a*c;

	if (d > 0)
	{
		x1 = (-b + sqrt(d)) / (2 * a);
		x2 = (-b - sqrt(d)) / (2 * a);
		printf("The roots of equation %.0lfx^2 + %.0lfx + %.0lf is:\n", a, b, c);
		printf("x1 = %.2lf\n", x1);
		printf("x2 = %.2lf\n", x2);
	}

	else if (d == 0)
	{
		x1 = x2 = -b / (2 * a);
		printf("The roots of equation %.0lfx^2 + %.0lfx + %.0lf is:\n", a, b, c);
		printf("x1 = %.2lf\n", x1);
		printf("x2 = %.2lf\n", x2);
	}

	else
	{
		real = -b / (2 * a);
		imaginary = sqrt(-d) / (2 * a);
		printf("The roots of equation %.0lfx^2 + %.0lfx + %.0lf is:\n", a, b, c);
		printf("x1 = %.2lf+%.2lfi\n", real, imaginary);
		printf("x2 = %.2f-%.2fi\n", real, imaginary);
	}

	system("pause");
	return 0;
}