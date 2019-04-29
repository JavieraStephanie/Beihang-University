#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	char t;
	int a[26] = { 0 }, i, j, max = 0;

	while (scanf("%c", &t) != EOF) //Keep inputing new characters as long as it's not the end of the text do the following
	{
		//Check which alphabet was entered, and that alphabet number will add up by 1, this will be recorded in
		//alphabet array a. So a[0] = a, a[1] = b, etc
		switch (t)
		{
		case'a':
			a[0]++;
			break;
		case'b':
			a[1]++;
			break;
		case'c':
			a[2]++;
			break;
		case'd':
			a[3]++;
			break;
		case'e':
			a[4]++;
			break;
		case'f':
			a[5]++;
			break;
		case'g':
			a[6]++;
			break;
		case'h':
			a[7]++;
			break;
		case'i':
			a[8]++;
			break;
		case'j':
			a[9]++;
			break;
		case'k':
			a[10]++;
			break;
		case'l':
			a[11]++;
			break;
		case'm':
			a[12]++;
			break;
		case'n':
			a[13]++;
			break;
		case'o':
			a[14]++;
			break;
		case'p':
			a[15]++;
			break;
		case'q':
			a[16]++;
			break;
		case'r':
			a[17]++;
			break;
		case's':
			a[18]++;
			break;
		case't':
			a[19]++;
			break;
		case'u':
			a[20]++;
			break;
		case'v':
			a[21]++;
			break;
		case'w':
			a[22]++;
			break;
		case'x':
			a[23]++;
			break;
		case'y':
			a[24]++;
			break;
		case'z':
			a[25]++;
			break;
		}

	}

	//Find the alphabet with most value and then set that as the new max
	for (i = 0; i < 26; i++)
	{
		if (max < a[i])
			max = a[i];
	}

	//Because the display would be vertical bars so the alphabet with the max value would be the tallest bar
	//then the counting should start from the max one and then go down
	for (i = max; i >= 1; i--)
	{
		for (j = 0; j < 26; j++)
		{
			if (a[j] < i)
				printf(" ");
			else
				printf("*");
		}

		printf("\n");
	}

	printf("abcdefghijklmnopqrstuvwxyz"); //Because in the display rule, we should print the alphabets at the bottom of the screen

	return 0;
}