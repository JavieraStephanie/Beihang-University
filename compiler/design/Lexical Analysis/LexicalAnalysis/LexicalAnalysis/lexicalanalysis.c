#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

FILE *fi, *fo;
int left = 0, right = 0, len = 0;
size_t templen;
char lastsymbol[10], tempstr[100], line[100], str[2];

char* toString(char ch);
char* checkSym(char ch);
bool isSymbol(char ch);
char* checkWord(char* line);
bool isInt(char* line);
bool isIden(char* line);
bool isChar(char ch);
char* subString(char* str, int left, int right);
char* parseWord();
void printOutput(char* code, char* content);

char* toString(char ch)
{
	str[0] = ch;
	str[1] = '\0';

	return str;
}

char* checkSym(char ch) {
	switch (ch) {
	case ';': return ("SEMICN"); break;
	case ',': return ("COMMA"); break;
	case '=': return ("ASSIGN"); break;
	case '(': return ("LPARENT"); break;
	case ')': return ("RPARENT"); break;
	case '[': return ("LBRACK"); break;
	case ']': return ("RBRACK"); break;
	case '{': return ("LBRACE"); break;
	case '}': return ("RBRACE"); break;
	case '/': return ("DIV"); break;
	case '*': return ("MULT"); break;
	case '-': return ("MINU"); break;
	case '+': return ("PLUS"); break;
	case '>': return ("GRE"); break;
	case '<': return ("LSS"); break;
	case '"': return ("QUOTE"); break;
	case '\'': return ("APOSTROPHE"); break;
	case '!': return ("EXCLAM"); break;
	case '\0': return ("EOLN"); break;
	case ' ': return ("SPACE"); break;
	case '\n': return ("ENTER"); break;
	case '\t': return ("TAB"); break;
	}
	return ("\0");
}

bool isSymbol(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == ';' || ch == ':' || ch == '[' || ch == ']' ||
		ch == '"' || ch == '!' || ch == '{' || ch == '}' ||
		ch == '\'' || ch == '\n' || ch == '\0' || ch == '\t')
		return (true);

	return (false);
}

char* checkWord(char* line)
{
	if (!strcmp(line, "if"))				return ("IFTK");
	else if (!strcmp(line, "else"))			return ("ELSETK");
	else if (!strcmp(line, "do"))			return ("DOTK");
	else if (!strcmp(line, "while"))		return ("WHILETK");
	else if (!strcmp(line, "for"))			return ("FORTK");
	else if (!strcmp(line, "scanf"))		return ("SCANFTK");
	else if (!strcmp(line, "printf"))		return ("PRINTFTK");
	else if (!strcmp(line, "return"))		return ("RETURNTK");

	else if (!strcmp(line, "void"))			return ("VOIDTK");
	else if (!strcmp(line, "const"))		return ("CONSTTK");
	else if (!strcmp(line, "main"))			return ("MAINTK");

	else if (!strcmp(line, "int"))			return ("INTTK");
	else if (!strcmp(line, "char"))			return ("CHARTK");
	else									return ("OTHERS");
}

bool isInt(char* line)
{
	int i, len = strlen(line);

	if (len == 0) return false;

	for (i = 0; i < len; i++)
		if ((len > 1 && line[0] == '0') || line[i] < '0' || line[i] > '9') return false;

	return true;
}

bool isIden(char* line)
{
	int i;
	if ((line[0] >= 'A' && line[0] <= 'Z') || (line[0] >= 'a' && line[0] <= 'z') || line[0] == '_') {
		for (i = 1; i < strlen(line); i++) {
			if (!(line[i] >= 'A' && line[i] <= 'Z') && !(line[i] >= 'a' && line[i] <= 'z') &&
				!(line[i] >= '0' && line[i] <= '9') && !(line[i] == '_'))
				return (false);
		}
		return (true);
	}
	return (false);
}

bool isChar(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_' ||
		ch == '+' || ch == '-' || ch == '/' || ch == '*')
		return (true);
	return (false);
}

char* subString(char* str, int left, int right)
{
	int i;
	char* subStr = (char*)malloc(
		sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

char* parseWord() {
	len = strlen(line);

	while (right <= len && left <= right) {
		if (isSymbol(line[right]) == false)
			right++;

		if (isSymbol(line[right]) && left == right) {
			if (!strcmp(lastsymbol, "QUOTE")) {
				if (!strcmp(checkSym(line[right]), "QUOTE")) {
					printOutput("STRCON", tempstr);
					strcpy(lastsymbol, "\0");
					strcpy(tempstr, "\0");
				}
				else {
					templen = strlen(tempstr);
					tempstr[templen++] = line[right];
					tempstr[templen++] = '\0';
				}
			}

			else {
				if (!strcmp(checkSym(line[right]), "ASSIGN")) {
					if (!strcmp(checkSym(line[right + 1]), "ASSIGN")) {
						printOutput("EQL", "==");
						right++;
					}
					else
						printOutput(checkSym(line[right]), toString(line[right]));
				}

				else if (!strcmp(checkSym(line[right]), "GRE")) {
					if (!strcmp(checkSym(line[right + 1]), "ASSIGN")) {
						printOutput("GEQ", ">=");
						right++;
					}
					else
						printOutput(checkSym(line[right]), toString(line[right]));
				}
				else if (!strcmp(checkSym(line[right]), "LSS")) {
					if (!strcmp(checkSym(line[right + 1]), "ASSIGN")) {
						printOutput("LEQ", "<=");
						right++;
					}
					else
						printOutput(checkSym(line[right]), toString(line[right]));
				}
				else if (!strcmp(checkSym(line[right]), "EXCLAM")) {
					if (!strcmp(checkSym(line[right + 1]), "ASSIGN")) {
						printOutput("NEQ", "!=");
						right++;
					}
					else
						printOutput(checkSym(line[right]), toString(line[right]));
				}

				else if (!strcmp(checkSym(line[right]), "APOSTROPHE")) {
					if (isChar(line[right + 1]) && !strcmp(checkSym(line[right + 2]), "APOSTROPHE")) {
						printOutput("CHARCON", toString(line[right + 1]));
						right += 2;
					}
				}

				else if (isspace(line[right]) || line[right] == '\0');

				else if (!strcmp(checkSym(line[right]), "QUOTE"))
					strcpy(lastsymbol, "QUOTE");

				else
					printOutput(checkSym(line[right]), toString(line[right]));
			}

			left = ++right;
		}

		else if ((isSymbol(line[right]) && left != right) || (right == len && left != right)) {
			char* subStr = subString(line, left, right - 1);

			if (!strcmp(lastsymbol, "QUOTE"))
				strcat(tempstr, subStr);

			else {
				if (!strcmp(checkWord(subStr), "OTHERS")) {
					if (isIden(subStr) && !isSymbol(line[right - 1]))
						printOutput("IDENFR", subStr);
					else if (isInt(subStr))
						printOutput("INTCON", subStr);
				}
				else
					printOutput(checkWord(subStr), subStr);
			}

			left = right;
		}
	}

	if (fgets(line, 100, fi) != NULL) {
		left = right = 0;
		return (parseWord());
	}

	return ("\0");
}

void printOutput(char* code, char* content)
{
	fprintf(fo, "%s %s\n", code, content);

	return;
}

int main() {
	if ((fi = fopen("testfile.txt", "r")) == NULL || (fo = fopen("output.txt", "w")) == NULL)
	{
		printf("Error opening file!");
		return(-1);
	}

	fgets(line, 100, fi);
	parseWord();

	fclose(fi);
	fclose(fo);

	return 0;
}