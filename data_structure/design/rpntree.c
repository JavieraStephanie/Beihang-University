#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#define MAX 500

struct symbol
{
	int num;
	char op;
	struct symbol *left;
	struct symbol *right;
};

int priority(char op);
void numrev(char infix[], char reversenum[], int *iter_infix, int *iter_revnum);
int getnum(char reversenum[], int *iter_revnum);
void revinfix(char infix[], char reversenum[]);
void revtree(char reversenum[], struct symbol **tree);
int revnum(char reversenum[]);

int main()
{
	char infix[MAX], reversenum[MAX];
	char temp;
	struct symbol *tree = NULL;
	int i = 0;

	while ((temp = getchar()) != '=') 
		infix[i++] = temp;

	infix[i] = '\0';

	revinfix(infix, reversenum);
	revtree(reversenum, &tree);

	temp = tree->op;
	printf("%c", temp);

	if (tree->left != NULL)
	{
		temp = tree->left->op;
		if (temp == '\0') printf(" %d", tree->left->num);
		else printf(" %c", temp);
	}

	if (tree->right != NULL)
	{
		temp = tree->right->op;
		if (temp == '\0') printf(" %d\n", tree->right->num);
		else printf(" %c\n", temp);
	}
	else 
		printf("\n");

	printf("%d", revnum(reversenum));

	system("pause");
	return 0;
}

int priority(char op)
{
	enum ops { ADD = 1, SUB = 1, MUL = 2, DIV = 2 };
	switch (op)
	{
	case '+':
		return ADD;

	case '-':
		return SUB;

	case '*':
		return MUL;

	case '/':
		return DIV;

	default:
		return 0;
	}
}

void numrev(char infix[], char reversenum[], int *iter_infix, int *iter_revnum)
{
	while (infix[*iter_infix] != '\0' && !priority(infix[*iter_infix]) && infix[*iter_infix] != ')' && infix[*iter_infix] != ' ')
		reversenum[(*iter_revnum)++] = infix[(*iter_infix)++];

	reversenum[(*iter_revnum)++] = ' ';
	(*iter_infix)--;
}

int getnum(char reversenum[], int *iter_revnum)
{
	int rst = 0;
	while (reversenum[*iter_revnum] != ' ')
	{
		rst = rst * 10 + reversenum[*iter_revnum] - '0';
		(*iter_revnum)++;
	}
	return rst;
}

void revinfix(char infix[], char reversenum[])
{
	int length = strlen(infix), iter_infix = 0, iter_revnum = 0, iter_ops = 0;
	char ops[MAX];

	for (; iter_infix < length; iter_infix++)
	{
		if (infix[iter_infix] == ' ')
			continue;

		else if (infix[iter_infix] >= '0' && infix[iter_infix] <= '9')
			numrev(infix, reversenum, &iter_infix, &iter_revnum);

		else if (infix[iter_infix] == '(')
			ops[iter_ops++] = infix[iter_infix];

		else if (priority(infix[iter_infix]))
		{
			iter_ops--;
			while (iter_ops >= 0 && priority(ops[iter_ops]) >= priority(infix[iter_infix]))
			{
				reversenum[iter_revnum++] = ops[iter_ops--];
				reversenum[iter_revnum++] = ' ';
			}
			iter_ops++;
			ops[iter_ops++] = infix[iter_infix];
		}

		else if (infix[iter_infix] == ')')
		{
			iter_ops--;
			while (ops[iter_ops] != '(')
			{
				reversenum[iter_revnum++] = ops[iter_ops--];
				reversenum[iter_revnum++] = ' ';
			}
		}
	}

	iter_ops--;

	while (ops[iter_ops] != '(' && ops[iter_ops] >= 0)
	{
		reversenum[iter_revnum++] = ops[iter_ops--];
		reversenum[iter_revnum++] = ' ';
	}

	reversenum[iter_revnum] = '\0';
}

void revtree(char reversenum[], struct symbol **tree)
{
	struct symbol *branches[MAX];
	struct symbol *newbranch;
	int iter_revnum = 0, iter_array = 0;

	while (reversenum[iter_revnum] != '\0')
	{
		if (reversenum[iter_revnum] >= '0'&& reversenum[iter_revnum] <= '9')
		{
			newbranch = (struct symbol *)malloc(sizeof(struct symbol));
			newbranch->num = getnum(reversenum, &iter_revnum);
			newbranch->op = '\0';
			newbranch->left = NULL;
			newbranch->right = NULL;
			branches[iter_array++] = newbranch;
		}

		else if (priority(reversenum[iter_revnum]))
		{
			newbranch = (struct symbol *)malloc(sizeof(struct symbol));
			newbranch->op = reversenum[iter_revnum];

			if ((--iter_array) >= 0) 
				newbranch->right = branches[iter_array];

			else 
				newbranch->right = NULL;

			if ((--iter_array) >= 0) 
				newbranch->left = branches[iter_array];

			else 
				newbranch->left = NULL;

			branches[iter_array++] = newbranch;
		}

		iter_revnum++;
	}

	*tree = branches[0];
}

int revnum(char reversenum[])
{
	int num[MAX], iter_revnum = 0, iter_array = 0, length = strlen(reversenum);

	for (; iter_revnum < length; iter_revnum++)
	{
		if (reversenum[iter_revnum] == ' ') 
			continue;

		else if (reversenum[iter_revnum] >= '0' &&reversenum[iter_revnum] <= '9')
			num[iter_array++] = getnum(reversenum, &iter_revnum);

		else
		{
			iter_array--;
			if (reversenum[iter_revnum] == '+')
				num[iter_array - 1] += num[iter_array];

			else if (reversenum[iter_revnum] == '-')
				num[iter_array - 1] -= num[iter_array];

			else if (reversenum[iter_revnum] == '*')
				num[iter_array - 1] *= num[iter_array];

			else if (reversenum[iter_revnum] == '/')
			{
				if (num[iter_array] == 0)
				{
					num[iter_array - 1] = 0;
					continue;
				}
				num[iter_array - 1] /= num[iter_array];
			}
			iter_revnum++;
		}
	}

	if (iter_array == 1)
		return num[0];

	else
		return num[iter_array - 1];
}