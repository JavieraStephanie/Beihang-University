#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

int main() 
{
	char S[240];
	int N, i, s, x, y;
	
	scanf("%s", S);
	scanf("%d", &N);
	
	s = strlen(S);

	for (i = 0; i < N; i++)  //loop
	{
		for (x = 0; x < s; x++) //string checking
		{
			if (S[x] > S[x + 1]) //number changing
			{
				for (y = x; y <= s; y++) 
				{
					S[y] = S[y + 1];
				}
				break;
			}
		}
	}

	printf("%s\n", S); //doesn't write the 0

	return 0;
}