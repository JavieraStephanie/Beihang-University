/*日期天数转换*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int year, month, day, count=0, pass=0, i;

	int daysperMonthl[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysperMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	scanf("%d %d %d", &year, &month, &day);

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		for (i = 0; i < (month - 1); ++i)
		{
			pass += daysperMonthl[i];
		}
	}

	else {
		for (i = 0; i < (month - 1); ++i)
		{
			pass += daysperMonth[i];
		}
	}

	count += pass + day;

	printf("%d\n", count);

	return 0;
}
