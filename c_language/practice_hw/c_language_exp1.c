#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
	char name[11];
	char ID[11];
	int score1[3];
	int score2[3];
	int score3[3];
}studentinfo, *studentptr;


int main()
{
	int i, average, s1, s2, s3;
	studentinfo list[6] = { '\0', 0 };

	printf("Input student info in following format:\n");
	printf("<name> <ID> <score1> <score2> <score3>\n\n");

	for (i = 0; i < 5; i++)
		scanf("%s %s %d %d %d", list[i].name, list[i].ID, list[i].score1, list[i].score2, list[i].score3);

	printf("\nName		ID		Average Score\n\n");
	for (i = 0; i < 5; i++)
	{
		s1 = *list[i].score1;
		s2 = *list[i].score2;
		s3 = *list[i].score3;
		average = (s1 + s2 + s3) / 3;
		printf("%s		%s		%d\n\n", list[i].name, list[i].ID, average);
	}

	system("pause");
	return 0;
}