#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#define MAX 100

int n, tree[MAX], i, curline=1;
  
struct branch
{
    // each point has a number
    int num;
    
    int line;
    
    // each one has left and right branches
    struct branch *left;
    struct branch *right;
};

struct branch *NewBranch(int data);
struct branch* insert(struct branch* branch, int num);

void input();
void output(int ints[], int len);
void printPaths(struct branch* branch);
void printPathsRecur(struct branch* branch, int path[], int pathLen);

int main ()
{
    // Input the values using the input function
	input();

    // Initialize the tree as NULL
    struct branch *root = NULL;
    
    // Insert the root branch for the tree as the first branch
    root = insert(root, tree[0]);
    
    // Insert the branches to the tree
    for (i=1;i<n;i++)
    	insert(root, tree[i]);
    
    // Print the result
	printPaths(root);

	system("pause");
    return 0;
}

// Just a normal input function
void input()
{
	scanf("%d", &n);
	for (i = 0; i < n ; i++)
		scanf("%d", &tree[i]);
}

struct branch *NewBranch(int data)
{
	struct branch *temp = (struct branch *)malloc(sizeof(struct branch));
	temp->num = data;
	temp->line = curline;
	temp->left = temp->right = NULL;
	return temp;
}

// The real function for inserting the new branches
struct branch* insert(struct branch* branch, int num)
{
       // If there's no branch to be inserted, there's nothing to be inserted then
       // Create a new branch using the *NewBranch function
	if (branch == NULL)
		return NewBranch(num);
    
    // If the number of the new point/branch is smaller, then insert it on the left branch
    // Or else insert it to the right branch
	if (num < branch->num)
	{
		branch->left = insert(branch->left, num);
	}
	else if (num >= branch->num)
	{
		branch->right = insert(branch->right, num);
	}

	return branch;
}

void printPaths(struct branch* branch)
{
	int path[1000];
	printPathsRecur(branch, path, 0);
}

void printPathsRecur(struct branch* branch, int path[], int pathLen)
{
	if (branch == NULL) 
		return;

	path[pathLen] = branch->num;
	pathLen++;

	if (branch->left == NULL && branch->right == NULL)
	{
		output(path, pathLen);
	}
	else
	{
		printPathsRecur(branch->left, path, pathLen);
		printPathsRecur(branch->right, path, pathLen);
	}
}

void output(int ints[], int len)
{
	int i, line=0;
	for (i = 0; i<len; i++) 
	{
		line++;
	}
	printf("%d %d", ints[i-1], line);
	printf("\n");
}
