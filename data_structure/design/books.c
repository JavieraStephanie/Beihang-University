#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXBOOKNAME 51
#define MAXAUTHORNAME 21
#define MAXPUBLISHER 31
#define MAXDATE 11
#define MAXLINELENGTH MAXBOOKNAME + MAXAUTHORNAME + MAXDATE

int main()
{
	int commandnum;
	char bookname[MAXBOOKNAME], authorname[MAXAUTHORNAME], publisher[MAXPUBLISHER], date[MAXDATE], keywords[MAXBOOKNAME];
	char curline[MAXLINELENGTH];
	FILE *fpin;
	FILE *fpout;
	FILE *foverwrite;

	if ((fpout = fopen("ordered.txt", "w")) == NULL)
	{
		printf("File %s can't be opened!\n", "ordered.txt");
		return(-1);
	}

	if ((foverwrite = fopen("ordered.txt", "w+")) == NULL)
	{
		printf("File %s can't be opened!\n", "ordered.txt");
		return(-1);
	}

	if ((fpin = fopen("books.txt", "r")) == NULL)
	{
		printf("File %s can't be opened!\n", "books.txt");
		return(-1);
	}

	scanf("%d", &commandnum);

	while (commandnum != 0)
	{
		if (commandnum == 1)
		{
			scanf("%s %s %s %s", bookname, authorname, publisher, date);

			while (fgets(curline, MAXLINELENGTH, fpin) != NULL)
			{
				if (strstr(curline, bookname))
					break;
				else
					fprintf(fpout, "%-50s%-20s%-30s%-10s\n", bookname, authorname, publisher, date);
					
			}
		}
		else if (commandnum == 2)
		{
			scanf("%s", keywords);

			while (fgets(curline, MAXLINELENGTH, fpin) != NULL)
			{
				if (strstr(curline, keywords))
					fputs(curline, stdout);
			}
		}
		else if (commandnum == 3)
		{
			scanf("%s", keywords);

			while (fgets(curline, MAXLINELENGTH, fpin) != NULL)
			{
				if (strstr(curline, keywords))
					continue;
				else
					fprintf(foverwrite, "%-50s%-20s%-30s%-10s\n", bookname, authorname, publisher, date);

			}

		}
		else if (commandnum == 0)
		{
			return 0;
		}
		scanf("%d", &commandnum);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}