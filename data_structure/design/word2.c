#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

struct node
{
	char word[50];    // word being inputted
	int count;        // word frequency
	struct node *next;        // Pointer to next node
};

struct node *start = NULL;

void add_node(char nWord[50]);

int main()
{
	char word[50];
	char file[30];
	FILE *fp;
	struct node *temp, *current;       //node to traverse with
	int TravFlag = 0;

	fp = fopen("article.txt", "r");

	while (word[strlen(word)] != EOF)
	{
		if (word[strlen(word)] == EOF)
			break;
		TravFlag = 0;
		for (int i = 0; i<50; i++)
		{
			word[i] = '\0';
		}

		fscanf(fp, "%s", word);

		current = start;

		if (word[j] >= 'A' && word[j] <= 'Z')
			word[j] += 32;

		else if (word[j] < 'a' || word[j] > 'z')
		{
			word[strlen(word) - 1] = '\0';
		}

		if (start == NULL)
		{
			start = temp;
			strcpy(start->word, word);
			start->count = 1;
		}
		else if (start != NULL) //if theres already a node
		{
			while (TravFlag == 0)//Loop to Traverse
			{
				if (current->word == word)//If current node is same word
				{
					current->count = current->count + 1;//count increases by 1
					TravFlag = 1;                   //set flag to end loop
				}
				else if (current->word != word&&current->next == NULL)
				{//end of the list
					add_node(word);
					TravFlag = 1;
				}
				else
					current = current->next; //move to next node
			}
		}
	}
	fclose(fp);

	current = start;
	while (current != NULL)
	{
		printf("%s %d\n", current->word, current->count);
		current = current->next;
	}
}

void add_node(char nWord[50])
{
	struct node *temp, *temp2;   // Temporary pointers
	temp = (struct node*)malloc(sizeof(struct node));
	strcpy(temp->word, nWord);
	temp->count = 1;
	temp->next = NULL;

	// Set up link to this node
	if (start == NULL)
		start = temp;
	else
	{
		temp2 = start;
		while (temp2->next != NULL)
		{
			temp2 = temp2->next; // Move to next node
		}
		temp2->next = temp;
	}
}