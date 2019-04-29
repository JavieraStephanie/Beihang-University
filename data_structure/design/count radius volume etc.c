#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main()
{
	float r, h, p, a, ba, vol, cvol;

	//printf("Enter value \n");
	scanf("r = %f h = %f", &r, &h);

	p = 2 * r*PI;
	a = r*r*PI;
	ba = 4 * r*r*PI;
	vol = (4/3)*r*r*r*PI;
	cvol = r*r*h*PI;

	printf("Circumference: %.2f\n", p);
	printf("Circle Area: %.2f\n", a);
	printf("Ball Area: %.2f\n", ba);
	printf("Ball Volume: %.2f\n", vol);
	printf("Cylinder Volume: %.2f\n", cvol);

	system("pause");
	return 0;

}