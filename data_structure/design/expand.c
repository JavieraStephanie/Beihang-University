#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#define MAX 100

int main()
{
	int i = 0, j = 0, m;
	char t1[MAX], t2[MAX], c;

	gets(t1); //Input string value and store it to t1, the string may include '-' symbol

	//Now we'll check the string, so as long as we haven't reached the end of the string, do the following loop
	//We don't use for statement because two situations will be handled differently so for this case while statement
	//would be more flexible
	while (t1[i] != '\0') 
	{
		t2[j++] = t1[i]; //While we start from the 0 index for t1, we start from the 1 index for t2
						 //t2 is the real string that we'll print out

		m = t1[i + 2] - t1[i];
		//Now check if the next char of t1 is the expand symbol '-'and see if the character after that is larger than
		//the current one (this is due to the expanding rules and conditions)
		if (t1[i + 1] == '-' && ((m < 26 && m > 0) || (isdigit(t1[i]) && isdigit(t1[i+2]))))
		{
			//If it is the expand symbol and the character after the symbol is larger than the current one then store
			//all those in-between characters to t2
			for (c = t1[i] + 1; c <= t1[i + 2]; c++)
			{
				t2[j++] = c;
			}

			i += 3; //After that, the index would add up by 3 because we'll have to skip the expand symbol and the 
					//character after that, going to the next character

		}

		//Otherwise, it's just a single normal character, then we'll just move on to the next character
		else
		{
			i++;
		}
	}

	//After all the checking is done, put an end to the t2 string then print out the string
	t2[j] = '\0';
	puts(t2);

	return 0;
}