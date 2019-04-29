#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define right 'r'  
#define lower 'l'  
#define lower_right 'i'  
#define lower_left 'e'  
#define none 'o' 

int table[19][19]; // It is known from the question that the chess table has the size of 19x19, therefore create an array for it
int checkmate();
int hit_space(int x, int y, char vec);
int tetra_colinear_on_vec(int x, int y, char vec);
char tetra_colinear(int x, int y);

int main()
{
	int i, j; // It's a 2D array, so we use two counters; i and j

	// Input all the numbers to the table
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 19; j++)
			scanf("%d", &table[i][j]);
	}

	// Check if there's a checkmate, if no, then print 'No'
	if (!checkmate())
		printf("No\n");

	system("pause");
	return 0;
}

// This is the function to check if there's a checkmate in the chess table
int checkmate()
{
	int i, j; // Again, since it's a 2D array, we use two counters

	// Now check in the table (array)
	// This is for the checkmate of player 1
	for (i = 0; i < 19; i++)
		for (j = 0; j < 19; j++)
		{
			if (table[i][j] == 1) // If there's a piece in the current chess box
			{
				// Check for other pieces nearby and see if it forms a checkmate
				char vec = tetra_colinear(i, j);

				// There are only 'right', 'lower', 'lower_right', and 'lower_left' because we check the table from up to down, left to right
				// So obviously we won't need to check for pieces above the current piece nor left of the current piece
				if (vec == right || vec == lower || vec == lower_right || vec == lower_left)
				{
					if (hit_space(i, j, vec))
					{
						printf("1:%d,%d\n", i + 1, j + 1); // If the pieces forms the checkmate, then print out the row and column number
						return 1;
					}
				}
			}
		}

	// This works the same as the one for player 1, only that this is for player 2
	for (i = 0; i < 19; i++)
		for (j = 0; j < 19; j++)
		{
			if (table[i][j] == 2)
			{
				char vec = tetra_colinear(i, j);
				if (vec == right || vec == lower || vec == lower_right || vec == lower_left)
				{
					if (hit_space(i, j, vec))
					{
						printf("2:%d,%d\n", i + 1, j + 1);
						return 1;
					}
				}
			}
		}

	return 0;
}

char tetra_colinear(int x, int y)
{
	char vec;

	vec = right;
	if (tetra_colinear_on_vec(x, y, vec))
		return vec;

	vec = lower;
	if (tetra_colinear_on_vec(x, y, vec))
		return vec;

	vec = lower_right;
	if (tetra_colinear_on_vec(x, y, vec))
		return vec;

	vec = lower_left;
	if (tetra_colinear_on_vec(x, y, vec))
		return vec;

	return none;
}

int tetra_colinear_on_vec(int x, int y, char vec)
{
	if (vec == right)
		if (x + 3 < 19 && table[x][y] == table[x + 1][y] && table[x + 1][y] == table[x + 2][y] && table[x + 2][y] == table[x + 3][y])
			return 1;

	if (vec == lower)
		if (y + 3 < 19 && table[x][y] == table[x][y + 1] && table[x][y + 1] == table[x][y + 2] && table[x][y + 2] == table[x][y + 3])
			return 1;

	if (vec == lower_right)
		if (x + 3 < 19 && y + 3 < 19 && table[x][y] == table[x + 1][y + 1] && table[x + 1][y + 1] == table[x + 2][y + 2] && table[x + 2][y + 2] == table[x + 3][y + 3])
			return 1;

	if (vec == lower_left)
		if (x + 3 < 19 && y - 3 >= 0 && table[x][y] == table[x + 1][y - 1] && table[x + 1][y - 1] == table[x + 2][y - 2] && table[x + 2][y - 2] == table[x + 3][y - 3])
			return 1;

	return 0;
}

int hit_space(int x, int y, char vec)
{
	if (vec == right)
	{
		if (x - 1 >= 0 && table[x - 1][y] == 0)
			return 1;
		if (x + 4 < 19 && table[x + 4][y] == 0)
			return 1;
	}

	if (vec == lower)
	{
		if (y - 1 >= 0 && table[x][y - 1] == 0)
			return 1;
		if (y + 4 < 19 && table[x][y + 4] == 0)
			return 1;
	}

	if (vec == lower_right)
	{
		if (x - 1 >= 0 && y - 1 >= 0 && table[x - 1][y - 1] == 0)
			return 1;
		if (x + 4 < 19 && y + 4 < 19 && table[x + 4][y + 4] == 0)
			return 1;
	}

	if (vec == lower_left)
	{
		if (x - 1 >= 0 && y + 1 < 19 && table[x - 1][y + 1] == 0)
			return 1;
		if (x + 4 < 19 && y - 4 >= 0 && table[x + 4][y - 4] == 0)
			return 1;
	}

	return 0;
}





