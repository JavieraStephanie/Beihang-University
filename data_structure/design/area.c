#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int max(int m, int n) {
	if (m > n)
		return m;
	else
		return n;
}

int min(int m, int n) {
	if (m > n)
		return n;
	else
		return m;
}

int main() 
{

	int ax1, ax2, ay1, ay2; //All the coordinates for rectangle A
	int bx1, bx2, by1, by2; //All the coordinates for rectangle B
	int axmax, axmin, aymax, aymin;
	int bxmax, bxmin, bymax, bymin;
	int ymin, ymax, xmin, xmax;

	scanf("%d %d %d %d", &ax1, &ay1, &ax2, &ay2); //Input all the coordinates for rectangle A
	scanf("%d %d %d %d", &bx1, &by1, &bx2, &by2); //Input all the coordinates for rectangle B

	//If the input exceeded 0~1000 range, return 0 (Input error)
	if (ax1 < 0 || ax1>1000 || ax2 < 0 || ax2>1000 || ay1 < 0 || ay1>1000 || ay2 < 0 || ay2>1000)
	{
		printf("Value range limit is 0-1000");
		return 0;
	}
	if (bx1 < 0 || bx1>1000 || bx2 < 0 || bx2>1000 || by1 < 0 || by1>1000 || by2 < 0 || by2>1000)
	{
		printf("Value range limit is 0-1000");
		return 0;
	}

	//Since we don't know which one has larger value between y1 and y2 (for both rect A and B)
	//We have to check which one is larger
	aymax = max(ay1, ay2); //Compare both values and return the larger one as the max value for aymax
	aymin = min(ay1, ay2); //Compare both values and return the smaller one as the max value for aymin

	axmax = max(ax1, ax2); //Compare both values and return the larger one as the max value for axmax
	axmin = min(ax1, ax2); //Compare both values and return the smaller one as the max value for axmin

	bymax = max(by1, by2); //Compare both values and return the larger one as the max value for bymax
	bymin = min(by1, by2); //Compare both values and return the smaller one as the max value for bymin

	bxmax = max(bx1, bx2); //Compare both values and return the larger one as the max value for bxmax
	bxmin = min(bx1, bx2); //Compare both values and return the smaller one as the max value for bxmin

	//After those comparisons, now we compare between rect A and B to see which one is larger (to check the position)
	ymax = min(aymax, bymax); //Compare aymax and bymax and the smaller value would be the top coordinate for the instersecting rect
	ymin = max(aymin, bymin); //Compare aymin and bymin and the larger value would be the top coordinate for the instersecting rect
	xmax = min(axmax, bxmax); //Compare axmax and bxmax and the smaller value would be the top coordinate for the instersecting rect
	xmin = max(axmin, bxmin); //Compare axmin and bxmin and the larger value would be the top coordinate for the instersecting rect

	if ((ymax - ymin) > 0 && (xmax - xmin) > 0) //if both max coordinates - min coordinates have positive result, then it's valid
		printf("%d", (ymax - ymin)*(xmax - xmin));
	else
		printf("0");

	return 0;
}