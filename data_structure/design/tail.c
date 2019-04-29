#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
# include <ctype.h>
#define DEFLINES 10
#define MAXLENGTH 100

//First struct the variable, each variable has these two members, content line pointer and a link to another struct
struct Tail
{
	char *line;
	struct Tail *link;
};

int main(int argc, char  *argv[])
{
	char curline[MAXLENGTH]; // To record the content of current line (each line has a maximum length of MAXLENGTH, here I set it to 100)
	char *filename; // This is to store the file name itself
	int n = DEFLINES;
	int i;
	struct Tail *list, *ptr; // Now here is to struct the Tail structure, one is for the list, and the other is the pointer
	FILE *fp; // Just a normal file pointer

	// Below is the input handler, the corrent format has three arguments: tail, [-n], filename
	// If there are 3 arguments (argc == 3), then it is the right input format, the third argument (argv[2] must be the filename)
	// In the second argument there will be '-' and a number, therefore 2 elements. The first element must be '-' for the input to be right
	// And then let the number after '-' be the line number
	if (argc == 3 && argv[1][0] == '-')
	{
		n = atoi(argv[1] + 1);
		filename = argv[2];
	}

	// If there are only 2 arguments, then the second argument is the filename, there's no line number
	else if (argc == 2)
	{
		filename = argv[1];
	}

	// Other cases than the two that was mentioned above is a wrong format, so here we notify the user the correct format he/she must input
	else
	{
		printf("Corrent usage: tail [-n] filename \n");
		return(1);
	}
	//END OF INPUT HANDLER

	// If the file pointer returns NULL after trying to open the filename the user inputs, tell the user that the file can't be opened
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("File %s can't be opened!\n", filename);
		return(-1);
	}

	// Allocate some memories as big as the size of the Tail structure for both list and pointer (They're both of the same type)
	list = ptr = (struct Tail *)malloc(sizeof(struct Tail));
	ptr->line = NULL; // For the pointer, it's first pointing to a NULL content
	for (i = 1; i < n; i++)
	{
		ptr->link = (struct Tail *)malloc(sizeof(struct Tail));
		ptr = ptr->link;
		ptr->line = NULL;
	}
	ptr->link = list;

	// Pointer and List is actually of the same structure, while list is the real file content list, pointer is just a pointer that points to that list
	// So that any modification won't affect the real list
	ptr = list; // Assign ptr to point to list
	while (fgets(curline, MAXLENGTH, fp) != NULL)
	{
		if (ptr->line != NULL) // While the line pointer isn't pointing to an empty line
			free(ptr->line); // Free that pointer content
		ptr->line = (char *)malloc(strlen(curline) + 1);
		strcpy(ptr->line, curline);
		ptr = ptr->link; // Now move pointer to the next one
	}

	// While hasn't reach the line(s) amount that the user wants, print that line content
	for (i = 0; i < n; i++)
	{
		if (ptr->line != NULL) // As long as the pointer hasn't reach the end, print the content
		{
			printf("%s", ptr->line);
			ptr = ptr->link; // After printing the line content, the pointer can point to the next line to be printed
		}
	}

	fclose(fp); // Close the file pointer to save memory
	return 0;
}