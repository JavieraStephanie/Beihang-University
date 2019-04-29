#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define DATAMAX 11
#define USERMAX 51
#define FLUSH fflush(stdin);

int n; //The number of phonebook data, it is defined here and not only in certain function because multiple functions would need to get this value

//Because every data has contents (not just individual datas) so we use struct here to define all contents of data
//Every data has name and phone number both are in array form which size doesn't exceed 10 characters
typedef struct
{
	char name[DATAMAX];
	char number[DATAMAX];
}userinfo, *userptr; //The struct type would be called userinfo and userptr would be the pointer that points to this struct

//This function is to sort the datas, it would need the userinfo type of list (we could say it would need the telephone book data)
void Sort(userinfo list[])
{
	userinfo temp;
	int i, j;

	//Pointer i would be the main pointer and pointer j would always start after pointer i, so if pointer i is pointing to the 0 data, pointer j would point to the 1 data
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			//Here we use strcmp function to compare both datas and decide which one should come first
			//strcmp is a built-in function library of C language
			//If the next data should come first, then switch the datas
			//Otherwise just continue checking until pointer j reach the end then move on to the next data and check all datas too (loop)
			if (strcmp(list[i].name, list[j].name) > 0)
			{
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}

int main()
{
	int i, count, c=0;
	userinfo list[USERMAX] = { '\0', '\0' };

	//Input the value of n (phonebook user amount)
	scanf("%d", &n);

	//Input all the phonebook user datas
	for (count = 0; count < n; count++)
	{
		//Input the name and only read the first 10 characters in case the user inputs more than 10 max characters limit
		//Store that input to the phonebook list user name
		scanf("%10s", list[count].name);
		
		//As we said before only read and save the first 10 characters, the remaining characters should be 'flushed' in order for it to disappear or it will
		//appear in the next string, we wouldn't want that
		while (1)
		{
			c = getchar();
			if (c == ' ' || c == '\n' || c == EOF)
				break;
		}

		//Same for the user phone number; input then flush the exceeding characters
		scanf("%10s", list[count].number);
		while (1)
		{
			c = getchar();
			if (c == ' ' || c == '\n' || c == EOF) 
				break;
		}
	}

	//Sort the phonebook now with the Sort function
	Sort(list);

	//Input all the phonebook user datas
	//The 12s is because it's known from the problem that we could output a string of 12 characters size
	for (i = 0; i < count; i++)
	{
		printf("%12s%12s", list[i].name, list[i].number);
		printf("\n");
	}	

	return 0;
}
