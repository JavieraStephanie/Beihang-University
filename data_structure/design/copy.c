#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	freopen("fcopy.in", "r", stdin); //First set fcopy.in as the input file (standard input)
	freopen("fcopy.out", "w", stdout); //And fcopy.out as the output file

	char s, s1 = ' ';

	s = getchar(); //Now get char from the input (for this case it would be from fcopy.in) and store it to s

	while (s != EOF) //While s is not the end of the input/file
	{
		if ((s == ' ') || (s == '\t')) //If the next character is spacebar or tab
		{
			if ((s1 != ' ') && (s1 != '\t')) //But the current character is not, means that it's not continious spacebar/tab
				printf(" "); //Then we can print out as spacebar
		}

		else
			printf("%c", s); //print out that character

		s1 = s; //s1 would be the current s
		s = getchar(); //while s would be the next character from the input/file
	}

	return 0;
}
