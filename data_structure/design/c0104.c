/*摄氏华氏温度转换*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	float a, b;
	
	scanf("%f", &b);

	a = (b * 9 / 5) + 32; // farenheit to celcius

	printf("%.1f\n", a);

	return 0;
}
