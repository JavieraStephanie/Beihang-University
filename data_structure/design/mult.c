#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAX 101

void reverse(char str[]);
void add(char A[], char B[], char rst[]);
void multiply(char A[], char B[], char rst[]);

int main()
{
	char str1[MAX], str2[MAX], total[201];

	scanf("%s", str1);
	scanf("%s", str2);

	multiply(str1, str2, total);
	
	printf("%s", total);

	system("pause");
	return 0;
}

void reverse(char str[])
{
	int l = 0, r = strlen(str) - 1;
	char tmp;

	while (l < r)
	{
		tmp = str[l];
		str[l] = str[r];
		str[r] = tmp;
		l++, r--;
	}
}

void add(char str1[], char str2[], char total[])
{
	reverse(str1);
	reverse(str2);
	int i = 0, tmp, carry = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		tmp = str1[i] - '0' + str2[i] - '0';
		if (tmp > 9)
		{
			tmp = tmp - 10;
			total[i] = tmp + '0';
			if (carry) 
				total[i]++;
			carry = 1;
		}
		else
		{
			total[i] = tmp + '0';
			if (carry) 
				total[i]++;
			carry = 0;
		}
		i++;
	}

	if (str2[i] == '\0' && str1[i] != '\0')
	{
		total[i] = str1[i];
		if (carry) 
			total[i]++;
		i++;
		while (str1[i] != '\0')
		{
			total[i] = str1[i];
			i++;
		}
	}
	else if (str1[i] == '\0' && str2[i] != '\0')
	{
		total[i] = str2[i];
		if (carry) 
			total[i]++;
		i++;
		while (str2[i] != '\0')
		{
			total[i] = str2[i];
			i++;
		}
	}
	else if (str1[i] == '\0' && str2[i] == '\0' && carry)
	{
		total[i] = 1;
		i++;
	}

	while (total[i - 1] == '0' && i>1) 
		i--;
	total[i] = '\0';
	reverse(str1);
	reverse(str2);
	if (str1 != total) 
		reverse(total);
}

void multiply(char str1[], char str2[], char total[])
{
	int i, j, k, carry, tmp;
	char temp[201];
	total[0] = '0'; 
	total[1] = '\0';

	reverse(str1);
	reverse(str2);

	i = 0;

	carry = 0;
	while (str2[i] != '\0')
	{
		for (j = 0; j < strlen(str1); j++)
		{
			tmp = (str1[j] - '0')*(str2[i] - '0');
			temp[j] = '0' + tmp % 10;
			temp[j] += carry;
			carry = 0;
			if (temp[j] > '9')
			{
				temp[j] -= 10;
				carry++;
			}
			while (tmp > 9)
			{
				tmp -= 10;
				carry++;
			}
		}
		if (carry) 
			temp[j++] = '0' + carry;
		carry = 0;
		temp[j] = '\0';
		reverse(temp);
		for (k = 0; k < i; k++)	
			temp[j + k] = '0';
		temp[j + k] = '\0';

		add(total, temp, total);
		i++;
	}
	reverse(str1);
	reverse(str2);
}
