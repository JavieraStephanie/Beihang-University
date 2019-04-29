#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int n = 1;
	double p, hp, hpt, f, e, x;

	hp = f = x = hpt = 1.0;

	scanf("%lf", &e); //Input e (e>=0.000001) value

	if (e < 0.000001) //Because the range is e>=0.000001, if e<0.000001 should be error
	{
		printf("Input Error");
		return 0;
	}

	while (hp*2 >= e||n<2) //Following the given formula π/2=1+1!/3+2!/(3×5)+3!/(3×5×7)+…+(n-1)!/(3×5×7×…×(2n-1))
	{
		n++;
		f *= (n-1);
		x *= (2 * n - 1);
		hp = f / x;
		hpt += hp;
		
	}

	p = hpt * 2;

	printf("%d %.7lf", n, p);

	return 0;

}