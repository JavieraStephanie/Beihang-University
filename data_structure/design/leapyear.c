#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int year
    //int month, day, i;
	//char* season;

	int daysperMonthl[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysperMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	scanf("%d %d", &year, &month);

	/*if (month >= 2 && month <= 4)
		season = "Spring";
	else if (month >= 5 && month <= 7)
		season = "Summer";
	else if (month <= 8 && month >= 10)
		season = "Fall";
	else if (month == 11 || month == 12 || month || 1)
		season = "Winter";*/ 

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		printf("%d %d is leap year\n", year, month);

		/*for (i = 0; i <= (month-1); i++)
			day = daysperMonthl[i];*/ 
	}

	else
		printf("%d %d isn't a leap year\n", year, month);
		for (i = 0; i <= (month-1); i++)
			day = daysperMonth[i];

	/*printf("The season is %s\n", season);
	printf("There are %d days\n", day);*/ 

	system("pause");
	return 0;
}
