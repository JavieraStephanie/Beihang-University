#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 50

int main()
{
	char place[MAXCHAR];
	int i, j, l, temp;

	printf("Please input a name place (you can use Pinyin or English alphabets)");
	scanf("%s", place);
	printf("You inputted: %s\n", place);

	l = strlen(place);
	for (i = 0; i < l; i++)
	{
		for (j = i+1; j < l; j++)
		{
			if (place[i] > place[j])
			{
				temp = place[i];
				place[i] = place[j];
				place[j] = temp;
			}
		}
	}
	/*for (i = 0; i < l; i++)
	{
		for (j = i; place[j] < place[j - 1]; j--)
		{
			temp = place[j-1];
			place[j-1] = place[j];
			place[j] = temp;
		}		
	}*/

	puts(place);

	system("pause");
	return 0;
}
