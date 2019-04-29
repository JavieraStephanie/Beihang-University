#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define WORD 9

struct wordtree
{
	struct wordtree *below, *above;
	char *word;
	int used;
};

char *GetWord(FILE *fi)
{
	char *temp = NULL;
	int byte, count, wordsize;
	for (byte = fgetc(fi); !isalpha(byte); byte = fgetc(fi))
	{
		if (byte == EOF)
			return NULL;
	}
	if ((temp = malloc(wordsize = WORD)) == NULL)
	{
		return NULL;
	}
	for (count = 0; isalpha(byte); byte = fgetc(fi))
	{
		if (count == WORD - 1)
		{
			char *temp2;
			if ((temp2 = realloc(temp, wordsize += WORD)) == NULL)
				return NULL;
			else
				temp = temp2;
		}
		*(temp + count++) = byte;
	}
	*(temp + count) = 0;
	ungetc(byte, fi);
	return temp;
}

int Addword(char*text, struct wordtree **base)
{
	struct wordtree *temp;
	if ((temp = malloc(sizeof(*temp))) == NULL)
		return 0;
	temp->below = temp->above = NULL;
	temp->word = text;
	temp->used = 1;
	if (*base == NULL)
		*base = temp;
	else
	{
		struct wordtree *prev = NULL, *current = base;
		int direction;
		while (current != NULL)
		{
			prev = current;
			if ((direction = strcmp(current->word, temp->word)) == 0)
			{
				current->used += 1;
				free(temp);
				return 0;
			}
			else
			{
				if (direction < 0)
					current = current->above;
				else
					current = current->below;
			}
		}
		if (direction < 0)
			prev->above = temp;
		else
			prev->below = temp;
	}
		return 1;
}

void Delword(struct wordtree *root, int trace)
{
	if (root == NULL)
		return;
	Delword(root->below, trace);
	if (trace)
		printf("%s %d", root->word, root->used);
	Delword(root->above, trace);
	free(root->word);
	free(root);
}

int Allwords(FILE *fi, int trace)
{
	struct wordtree *root = NULL;
	char *allword;
	int count = 0;
	while ((allword = GetWord(fi)) != NULL)
		count += Addword(allword, &root);
	Delword(root, trace);
	return count;
}

int usage(char *name, char *text)
{
	fprintf(stderr, "Usage: %s[[-v]filename]\n", name);
	if (text != NULL)
		fprintf(stderr, "%s\n", text);
	return EXIT_FAILURE;
}

int main(int argc, char*argv[])
{
	FILE *fi;
	int trace = 0;
	switch (argc)
	{
	case 1:
		trace = 0;
		fi = stdin;
		break;
	case 2:
		if (strcmp("-v", argv[1]) == 0)
		{
			trace = 1;
			fi = stdin;
		}
		else
		{
			trace = 0;
			if ((fi = fopen(argv[1], "r")) == NULL)
				return usage(argv[0], "File not found");
		}
		break;
	case 3:
		if (strcmp("-v", argv[1]) == 0)
		{
			trace = 1;
			if ((fi = fopen(argv[2], "r")) == NULL)
				return usage(argv[0], "File not found");
			else
				return usage(argv[0], NULL);
		}
		break;
	default:
		return usage(argv[0], NULL);
		break;
	}
	printf("%d", Allwords(fi, trace));
	if (fi != stdin)
		fclose(fi);


	return 0;
}