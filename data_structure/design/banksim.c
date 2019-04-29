#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

int period, i, j, k = 1, m, done = 0, wait, total, top = 0, time = 0, many=0;
int queue[MAX], waittime[MAX], teller, window=3;

int main()
{
	scanf("%d", &period);

	//input the people queue number
	for (i = 0; i < period; i++)
	{
		teller = 0;
		scanf("%d", &total);
		for (j = 0; j < total; j++) //store the people in the queue array
		{
			queue[top] = k;
			waittime[top] = time;
			k++;
			top++;
			/*if (top - done >= 7)
			{
				if (teller < 5)
				{
					teller++;
					done++;
				}
			}
			else
			{
				if (teller < 3)
				{
					teller++;
					done++;
				}
			}*/
		}
		if ((top-done) / window >= 7)
		{
			if ((top - done) / (window+1) < 7)
			{
				if (window <= 4) 
					(window)++;
			}
			else
			{
				window = 5;
			}
		}
		while (teller < window && done < top)
		{
			done++;
			teller++;
		}
		if (top - done-1 != 0)
		{
			for (wait = done, m = 0; m < top - done; wait++, m++)
			{
				waittime[wait] += 1;
			}
		}
	}
	//if the period ends but there are still people inside
	if (top - done != 0)
	{
		while (top - done != 0)
		{
			teller = 0;
			while (teller < window && done < top)
			{
				done++;
				teller++;
			}
			if (top - done != 0)
			{
				for (wait = done, m = 0; m < top - done; wait++, m++)
					waittime[wait] += 1;
			}
			if ((top - done) / window < 7 && window>3)
				window--;
		}
	}
	for (i = 0; i < top; i++)
		printf("%d : %d\n", queue[i], waittime[i]);

	system("pause");
	return 0;
}