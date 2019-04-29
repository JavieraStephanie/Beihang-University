#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

// Each member of the expression has coefisient and exponent, also the link to the next data
struct node
{
	int coef;
	int exp;
	struct node *link;
};

// The real multiplication rule of polynomial is coef x coef, exp + exp
void multi(struct node *node1, struct node *node2, struct node *node_res)
{
	node_res->coef = (node1->coef) * (node2->coef);
	node_res->exp = (node1->exp) + (node2->exp);
}

void poly_multi(struct node *poly1, struct node *node2, struct node *poly_res)
{
	struct node *polynode_p = poly1, *resnode_p = poly_res;

	while(1)
	{
		if (polynode_p->link != NULL)
		{
			multi(polynode_p, node2, resnode_p);
			resnode_p->link = (struct node *)malloc(sizeof(struct node));
			resnode_p = resnode_p->link;
			polynode_p = polynode_p->link;
		}
		else
		{
			multi(polynode_p, node2, resnode_p);
			resnode_p->link = NULL;
			break;
		}
	}
}

struct node *merge_poly(struct node *poly1, struct node *poly2)
{
	struct node *poly_res = poly1, *poly1_p_tmp = poly1, *poly2_p_tmp = poly2, *poly_res_tmp = poly1;

	if (poly1_p_tmp->exp > poly2_p_tmp->exp)
	{
		poly_res = poly1;
		poly_res_tmp = poly1;
		poly1_p_tmp = poly1_p_tmp->link;
	}
	else if (poly1_p_tmp->exp < poly2_p_tmp->exp)
	{
		poly_res = poly2;
		poly_res_tmp = poly2;
		poly2_p_tmp = poly2_p_tmp->link;
	}
	else if (poly1_p_tmp->exp == poly2_p_tmp->exp)
	{
		poly_res = poly1;
		poly1_p_tmp->coef += poly2_p_tmp->coef;
		poly_res_tmp = poly1;
		poly1_p_tmp = poly1_p_tmp->link;
		struct node *tmp = poly2_p_tmp;
		poly2_p_tmp = poly2_p_tmp->link;
		free(tmp);
	}

	while (poly1_p_tmp != NULL && poly2_p_tmp != NULL)
	{
		if (poly1_p_tmp->exp > poly2_p_tmp->exp)
		{
			poly_res_tmp->link = poly1_p_tmp;
			poly_res_tmp = poly1_p_tmp;
			poly1_p_tmp = poly1_p_tmp->link;
		}
		else if (poly1_p_tmp->exp < poly2_p_tmp->exp)
		{
			poly_res_tmp->link = poly2_p_tmp;
			poly_res_tmp = poly2_p_tmp;
			poly2_p_tmp = poly2_p_tmp->link;
		}
		else if (poly1_p_tmp->exp == poly2_p_tmp->exp)
		{
			poly1_p_tmp->coef += poly2_p_tmp->coef;
			poly_res_tmp->link = poly1_p_tmp;
			poly_res_tmp = poly1_p_tmp;
			poly1_p_tmp = poly1_p_tmp->link;

			struct node *tmp = poly2_p_tmp;
			poly2_p_tmp = poly2_p_tmp->link;
			free(tmp);
		}
	}

	poly_res_tmp->link = (poly1_p_tmp != 0) ? poly1_p_tmp : poly2_p_tmp;
	return poly_res;
}

struct node *poly_multi_poly(struct node *poly1, struct node *poly2)
{
	struct node *node2_tmp = poly2;
	struct node *poly_p_res = (struct node *)malloc(sizeof(struct node));
	struct node *poly_p_tmp = (struct node *)malloc(sizeof(struct node));

	poly_multi(poly1, node2_tmp, poly_p_res);

	node2_tmp = node2_tmp->link;

	if (node2_tmp != NULL)
	{
		while(1)
		{
			poly_multi(poly1, node2_tmp, poly_p_tmp);
			poly_p_res = merge_poly(poly_p_res, poly_p_tmp);

			if (node2_tmp->link != NULL)
			{
				poly_p_tmp = (struct node *)malloc(sizeof(struct node));
				node2_tmp = node2_tmp->link;
			}
			else 
				break;
		}
	}
	return poly_p_res;
}

int main()
{
	// This is to create space for the first polynomial expression
	struct node *poly1 = (struct node *)malloc(sizeof(struct node));

	// This is to create space for the second polynomial expression
	struct node *poly2 = (struct node*)malloc(sizeof(struct node));

	// This is for the result expression
	struct node *result;

	// This is for the temporary expression structure (to store temporary expression which will be moved later)
	struct node *node_tmp;

	// These are to store temporary coeficient and exponent
	int coef_tmp, exp_tmp;
	char lf;

	node_tmp = poly1;
	while (1)
	{
		// While it's not the end of the expression, keep inputing the element of the expression
		// Consisting of coeficient, exponent, and a character to determine whether the input has reach the end
		scanf("%d %d%c", &coef_tmp, &exp_tmp, &lf);

		// Now store the inputted coeficient to the coeficient data of the temporary expression structure
		node_tmp->coef = coef_tmp;

		//Also the exponent
		node_tmp->exp = exp_tmp;

		// If the character inputted isn't '\n', means that it's not the end of the expression
		if (lf != '\n')
		{
			// We need to allocate a new node to the temporary expression structure
			node_tmp->link = (struct node *)malloc(sizeof(struct node));
			node_tmp = node_tmp->link;
		}

		// Else if it is the end of the expression
		else
		{
			// Then there won't be any new node for the temporary expression structure, we can get out from this input loop
			node_tmp->link = NULL;
			break;
		}
	}

	// Do the same for the second polynomial expression
	node_tmp = poly2;
	while(1)
	{
		scanf("%d %d%c", &coef_tmp, &exp_tmp, &lf);
		node_tmp->coef = coef_tmp;
		node_tmp->exp = exp_tmp;

		if (lf != '\n')
		{
			node_tmp->link = (struct node *)malloc(sizeof(struct node));
			node_tmp = node_tmp->link;
		}
		else
		{
			node_tmp->link = NULL;
			break;
		}
	}

	// The result of the polynomial expression is poly1 x poly2
	result = poly_multi_poly(poly1, poly2);

	// Print out the result polynomial expression
	while (result != NULL)
	{
		printf("%d %d ", result->coef, result->exp);
		result = result->link;
	}

	return 0;
}