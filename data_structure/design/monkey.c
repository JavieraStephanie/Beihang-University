#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void monkeyking(int n, int m, int q);

// Each structure has data (int type) and link to the next data 
typedef struct node {
	int data;
	struct node *link;
}LNode, *LinkList;

int main()
{
	int n, m, q;

	// Input n, m and q values as the question requires
	scanf("%d %d %d", &n, &m, &q);

	// Do the operation to find the monkey king
	monkeyking(n, m, q);

	system("pause");
	return 0;
}

void monkeyking(int n, int m, int q)
{
	// Initialize linklists
	LinkList p = NULL, r = NULL, list = NULL;
	int i;

	for (i = 1; i <= n; i++)
	{
		// Initialize space for linklist p
		p = (LinkList)malloc(sizeof(LNode));

		// Insert i as p's data
		p->data = i;

		// If linklist is empty (NULL), list should point to list p
		if (list == NULL)
			list = p;
		
		// Else if the linklist isn't empty anymore, linklist r should link to list p
		else
			r->link = p;

		// And then now set the p value to list r
		r = p;
	}

	// List p will link to linklist
	p->link = list;

	// And then now set the linklist value to list p
	p = list;
	for (i = 1; i < q; i++)
	{
		r = p;
		p = p->link;
	}
	while (p->link != p)
	{
		for (i = 1; i < m; i++)
		{
			r = p;
			p = p->link;
		}
		r->link = p->link;

		free(p);
		p = r->link;
	}
	
	// Print the winning monkey
	printf("%d", p -> data);
}