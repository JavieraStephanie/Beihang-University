#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#define MAX 200

struct huffman
{
	int count;
	unsigned int code;  
	struct huffman *left;
	struct huffman *right;
	struct huffman *next;
};

struct huffman charbranch[MAX];
void insert(struct huffman *newbranch);
struct huffman *build(struct huffman *fbranch);
void merge(struct huffman *root);
void code(struct huffman *root, int depth);

int main()
{
	char check, write = 0;
	struct huffman *huff;
	int i, bits = 0, depth = 0;
	FILE *fi, *fo;

	fi = fopen("input.txt", "r");
	if (fi == NULL) 
		exit(1);

	fo = fopen("output.txt", "w");
	if (fo == NULL) 
		exit(1);

	for (i = 0; i < MAX; i++)
	{
		charbranch[i].count = 0;
		charbranch[i].code = 0;
		charbranch[i].next = NULL;
	}

	while ((check = fgetc(fi)) != EOF)
	{
		if (check != '\n')
			charbranch[check].count++;
	}

	charbranch[0].count = 1;

	merge(charbranch);
	huff = build(charbranch);
	code(huff, 0);
	rewind(fi);

	for (i = 0;;)
	{
		check = fgetc(fi);
		if (check != EOF && check != '\n')
		{
			depth = (charbranch[check].code) >> 16;
			for (i = depth - 1; i >= 0; i--)
			{ 
				char code = ((charbranch[check].code) & (1 << i)) >> i;
				write |= code << (7 - bits);
				bits++;
				if (bits == 8)
				{
					fputc(write, fo);
					printf("%hhx", write);
					bits = 0;
					write = 0;
				}
			}
		}
		else if (check == EOF)
		{
			depth = (charbranch[0].code) >> 16;
			for (i = depth - 1; i >= 0; i--)
			{ 
				char code = ((charbranch[0].code) & (1 << i)) >> i;
				write |= code << (7 - bits);
				bits++;
				if (bits == 8)
				{
					fputc(write, fo);
					printf("%hhx", write);
					bits = 0;
					write = 0;
				}
			}
			if (bits != 0)
			{
				printf("%hhx", write);
				fputc(write, fo);
			}
			break;
		}
	}

	fclose(fi);
	fclose(fo);

	system("pause");
	return 0;
}

void insert(struct huffman *newbranch)
{
	struct huffman *p = charbranch;
	while (p->next->count <= newbranch->count)
	{
		if (p->next->next != NULL)
			p = p->next;
		else
		{
			p->next->next = newbranch;
			p = NULL;
			break;
		}
	}
	if (p != NULL)
	{
		newbranch->next = p->next;
		p->next = newbranch;
	}
}

struct huffman *build(struct huffman *fbranch)
{
	struct huffman *nbranch = fbranch->next;
	if (nbranch != NULL)
	{
		struct huffman *newbranch = (struct huffman *)malloc(sizeof(struct huffman));
		newbranch->count = fbranch->count + nbranch->count;
		newbranch->code = 0;
		newbranch->left = fbranch;
		newbranch->right = nbranch;
		newbranch->next = NULL;

		insert(newbranch);
		return create(nbranch->next);
	}
	else
		return fbranch;
}

void merge(struct huffman *root)
{
	int i = 0;
	int min = 0x3f3f3f3f;
	struct huffman *p = NULL;

	for (; i < MAX; i++)
	{
		if (charbranch[i].count != 0 && charbranch[i].next == NULL && (charbranch + i) != root)
		{
			if (charbranch[i].count < min)
			{
				p = &charbranch[i];
				min = charbranch[i].count;
			}
			else if (charbranch[i].count == min)
			{
				if (&charbranch[i] <= p)
					p = &charbranch[i];
			}
		}
	}

	root->next = p;

	if (p != NULL)
		link(p);
}

void code(struct huffman *root, int depth)
{
	if (root != NULL)
	{
		int f_left = 1, f_right = 1;
		if (root->left != NULL)
		{
			root->left->code |= (root->code) << 1;
			f_left = 0;
		}
		if (root->right != NULL)
		{
			root->right->code |= ((root->code) << 1) | 1;
			f_right = 0;
		}
		if (f_left&&f_right)
		{
			root->code &= (1 << 16) - 1;
			root->code |= depth << 16;
		}
		code(root->left, depth + 1);
		code(root->right, depth + 1);
	}
}