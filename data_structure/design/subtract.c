#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include<string.h>
#define MAX 81

int main()
{
	char A[MAX], B[MAX], C[MAX]={ '/0' };
	int i, j, s = 0, t, ct, m;

	gets(A);
	gets(B);

	i = strlen(A) - 1;
	j = strlen(B) - 1;

	if (i > j)
	{
		while (i >= 0)
		{
			while (j >= 0)
			{
				if (A[i] < B[j])
				{
					A[i - 1] -= 1;
					C[i] = (A[i]-'0') + 10 - (B[j]-'0') + '0';
				}

				else
				{
					C[i] = (A[i]-'0') - (B[j]-'0') + '0';
				}

				i--;
				j--;
			}
			C[i] = A[i] - 0;
			i--;
		}
	}

	else if (i < j)
	{
		while (j >= 0)
		{
			while (i >= 0)
			{
				if (B[j] < A[i])
				{
					C[j] = (B[j]-'0') + 10 - (A[i]-'0') + '0';

					if (B[j - 1] > '0')
						B[j - 1] -= 1;

					else
					{
						for (m = j - 1; B[m] == '0' && m >= 0; m--);
						B[m] -= 1;
						for (; m < j-1; m++)
						{
							B[m + 1] += 9;
						}
					}
				}
				else
				{
					C[j] = (B[j]-'0') - (A[i]-'0') + '0';
				}
				i--;
				j--;
			}

			C[j] = B[j] - 0;
			j--;
		}

		printf("-");
	}

	else if (i == j)
	{
		for (i = j = 0; i < strlen(A); i++, j++)
		{
			if (A[i] < B[j])
			{
				s = 1;
				break;
			}
		}

		if (s==1) 
		{
			while (j >= 0 && i >= 0)
			{
				if (B[j] < A[i])
				{
					B[j - 1] -= 1;
					C[i] = (B[j]-'0') + 10 - (A[i]-'0') + '0';
				}
				else
				{
					C[i] = (B[j]-'0') - (A[i]-'0') + '0';
				}
				i--;
				j--;
			}
			printf("-");
		}

		else if (s==0)
		{
			while (i >= 0 && j >=0)
			{
				if (A[i] < B[j])
				{
					A[i - 1] -= 1;
					C[i] = (A[i]-'0') + 10 - (B[j]-'0') + '0';
				}
				else
				{
					C[i] = (A[i]-'0') - (B[j]-'0') + '0';
				}
				i--;
				j--;
			}
		}
	}

	for (t = 0; C[t] == '0' && t < strlen(C); t++);

	if (t == strlen(C))
		printf("0");

	else
	{
		for (ct = t; ct < strlen(C); ct++)
		{
			if (C[ct] < '1' || C[ct] > '9')
				C[ct] = '0';
		}

		/*if ((C[0] == '0' && C[1] == '0') || (C[0] == '-' && C[1] == '0'))
			printf("0");*/

		//else
		//{
			for (ct = t; ct < strlen(C); ct++)
			{
				printf("%c", C[ct]);
			}
		//}
	}

	return 0;
}