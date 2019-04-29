struct WordTree {
  struct WordTree *below, /* words that come before this word */
                  *above; /* words that come after this word  */
  char *word;
  unsigned long used;
};


#define WORDCHUNK 9


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
** GetWord(input): return a char pointer to the next word (as a string)
** Accepts:	a FILE * for the input stream
** Returns:	a char *
**		On Success: the return value will point to a nul-terminated string
**		On Failure: the return value will be set to NULL
*/ 
char *GetWord(FILE *input)
{
  char *temp = NULL;
  int byte,
      count,           /* counts chars used in current allocation */
      wordsize;        /* size of current allocation in chars     */

  /* skip leading non-alphabetics */
  for (byte = fgetc(input); !isalpha(byte); byte = fgetc(input))
  {
    if (byte == EOF)
      return NULL;
  }

  /* allocate initial word storage space */
  if ((temp = malloc(wordsize = WORDCHUNK)) == NULL)
    return NULL;

  /* start stashing bytes. stop when we run out of alphabetics */
  for (count = 0; isalpha(byte); byte = fgetc(input))
  {
    if (count == wordsize-1)
    {
      char *temp2;

      if ((temp2 = realloc(temp,wordsize+=WORDCHUNK)) == NULL)
        return NULL;
      else
        temp = temp2;
    }
    *(temp+count++) = byte;
  }

  /* nul-terminate the word, to make it a string */
  *(temp+count) = 0;

  /* put the non-alphabetic back */
  ungetc(byte,input);

  return temp;
}


/*
** AddWord(text, base): add a word to the word tree
** Accepts:	a char * pointing to the string to be added
**		a struct WordTree ** pointing to the struct WordTree * where
**		  the address of the root node is stored.
** Returns:	an int indicating the number of new words added with this invocation
**		  (will be 0 or 1)
*/ 
int AddWord(char *text, struct WordTree **base)
{
  struct WordTree *temp;
  int direction;

  /* allocate space for our new word node - return 0 if no more space */
  if ((temp = malloc(sizeof *temp)) == NULL)
    return 0;

  /* fill in the word node values */
  temp->below = temp->above = NULL;
  temp->word = text;
  temp->used = 1;

  /* put the word node into the proper place in the word tree */
  if (*base == NULL)	/* no words recorded yet */
    *base = temp;	/* so make this node the root node */
  else
  {
    struct WordTree *prev = NULL,
                    *this = *base;
    int direction;

    /* find the node that should point to this node */
    while (this != NULL)
    {
      prev = this;

      if ((direction = strcmp(this->word, temp->word)) == 0)
      {
	/* word already exists in the tree - just count it, return 0 added */
        this->used += 1;
        free(temp);
        return 0;
      }
      else
        if (direction < 0)	/* new word is above this word */
          this = this->above;
        else			/* new word is below this word */
          this = this->below;
    }

    /* this == NULL, and we update the prev node */
    if (direction < 0)
      prev->above = temp;
    else
      prev->below = temp;
  }
  return 1;
}


void DelWord(struct WordTree *root, int trace)
{
  if (root == NULL) return;

  DelWord(root->below,trace);
  if (trace) printf("Word \"%s\" was used %lu times\n",root->word,root->used);
  DelWord(root->above,trace);
  free(root->word); free(root);
}


unsigned long AllWords(FILE *input, int trace)
{
  struct WordTree *root = NULL;
  char *a_word;
  unsigned long wordcount = 0;

  while ((a_word = GetWord(input)) != NULL)
    wordcount += AddWord(a_word, &root);

  DelWord(root,trace);

  return wordcount;
}


int usage(char *name, char *text)
{
  fprintf(stderr,"Usage: %s [[-v] filename]\n",name);
  if (text != NULL) fprintf(stderr,"       %s\n",text);

  return EXIT_FAILURE;
}


int main(int argc, char *argv[])
{
  FILE *input;
  unsigned trace = 0;		/* terse */

  /* argc  action
  **    1  read from stdin, terse report
  **    2  argv[1] == "-v"
  **         read from stdin, verbose report
  **       argv[1] != "-v"
  **         read from file named by argv[1], terse report
  **    3  argv[1] == "-v"
  **         read from file named by argv[2], verbose report
  **       argv[1] != "-v"
  **         usage error
  **   >3  usage error
  */


  switch (argc)
  {
    case 1:
      trace = 0;
      input = stdin;
      break;

    case 2:
      if (strcmp("-v",argv[1]) == 0)
      {
        trace = 1;
        input = stdin;
      }
      else
      {
        trace = 0;
        if ((input = fopen(argv[1],"r")) == NULL) 
          return usage(argv[0],"Input file not found");
      }
      break;

    case 3:
      if (strcmp("-v",argv[1]) == 0)
      {
        trace = 1;
        if ((input = fopen(argv[2],"r")) == NULL)
          return usage(argv[0],"Input file not found");
      }
      else
        return usage(argv[0],NULL);
      break;

    default:
      return usage(argv[0],NULL);
      break;
  }

  printf("There were %lu words\n",AllWords(input,trace));
  if (input != stdin) fclose(input);

  return EXIT_SUCCESS;
}

/*
This program copyright (c) Lew Pitcher, 2008
*/
