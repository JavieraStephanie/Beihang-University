#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int count = 0;
size_t templen;
char lastsymbol[10], tempstr[50];

char* checkSym(char ch) {
	switch (ch) {
	case ' ': return ("SPACE"); break;
	case '\n': return ("ENTER"); break;
	case ';': return ("SEMICOLON"); break;
	case ',': return ("COMMA"); break;
	case '=': return ("EQL"); break;
	case '(': return ("LPAREN"); break;
	case ')': return ("RPAREN"); break;
	case '[': return ("LBRACKETS"); break;
	case ']': return ("RBRACKETS"); break;
	case '/': return ("DIV"); break;
	case '*': return ("TIMES"); break;
	case '-': return ("MINUS"); break;
	case '+': return ("PLUS"); break;
	case '>': return ("GTR"); break;
	case '<': return ("LSS"); break;
	case ':': return ("COLON"); break;
	case '\'': return ("QUOTE"); break;
	case '\"': return ("QUOTE"); break;
	}
}

bool isSymbol(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == ';' || ch == ':' || ch == '[' || ch == ']' ||
		ch == '\'' || ch == '\n' || ch == '"')
		return (true);

	return (false);
}

char* checkWord(char* line)
{
	if (!strcmp(line, "begin"))				return ("BEGINSYM");
	else if (!strcmp(line, "end"))			return ("ENDSYM");
	else if (!strcmp(line, "if"))			return ("IFSYM");
	else if (!strcmp(line, "else"))			return ("ELSESYM");
	else if (!strcmp(line, "then"))			return ("THENSYM");
	else if (!strcmp(line, "for"))			return ("FORSYM");
	else if (!strcmp(line, "do"))			return ("DOSYM");
	else if (!strcmp(line, "repeat"))		return ("REPEATSYM");
	else if (!strcmp(line, "until"))		return ("UNTILSYM");
	else if (!strcmp(line, "read"))			return ("READSYM");
	else if (!strcmp(line, "readln"))		return ("READSYM");
	else if (!strcmp(line, "write"))		return ("WRITESYM");
	else if (!strcmp(line, "writeln"))		return ("WRITESYM");
	else if (!strcmp(line, "to"))			return ("TOSYM");
	else if (!strcmp(line, "downto"))		return ("DOWNTOSYM");

	else if (!strcmp(line, "const"))		return ("CONSTSYM");
	else if (!strcmp(line, "var"))			return ("VARSYM");
	else if (!strcmp(line, "procedure"))	return ("PROCSYM");
	else if (!strcmp(line, "function"))		return ("FUNCTSYM");

	else if (!strcmp(line, "integer"))		return ("INTTYPE");
	else if (!strcmp(line, "real"))			return ("REALTYPE");
	else if (!strcmp(line, "char"))			return ("CHARTYPE");
	else if (!strcmp(line, "string"))		return ("STRTYPE");
	else if (!strcmp(line, "array"))		return ("ARRTYPE");
	else if (!strcmp(line, "of"))			return ("OFSYM");
	else if (!strcmp(line, "boolean"))		return ("BOOLTYPE");
	else									return ("OTHERS");
}

bool isInt(char* line)
{
	int i, len = strlen(line);

	if (len == 0)
		return false;

	for (i = 0; i < len; i++) {
		if (line[i] < '0' || line[i] > '9' || (line[i] == '-' && i > 0))
			return false;
	}

	return true;
}

bool isReal(char* line)
{
	int i, len = strlen(line);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (((line[i] < '0' || line[i] > '9') && line[i] != '.') || (line[i] == '-' && i > 0))
			return false;
		if (line[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

bool isIden(char* line)
{
	int i;
	if ((line[0] >= 'A' && line[0] <= 'Z') || (line[0] >= 'a' && line[0] <= 'z')) {
		for (i = 1; i < strlen(line); i++) {
			if (!(line[i] >= 'A' && line[i] <= 'Z') && !(line[i] >= 'a' && line[i] <= 'z') &&
				!(line[i] >= '0' && line[i] <= '9'))
				return (false);
		}
		return (true);
	}
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

void parse(char* str) {
	int left = 0, right = 0;
	int len = strlen(str);

	while (right <= len && left <= right) {
		if (isSymbol(str[right]) == false)
			right++;

		if (isSymbol(str[right]) == true && left == right) {
			if (!strcmp(lastsymbol, "QUOTE")) {
				if(!strcmp(checkSym(str[right]), "QUOTE")) {
					printf("%d\tSTRING\t\t%s\n", count, tempstr);
					strcpy(lastsymbol, "\0");
					strcpy(tempstr, "\0");
					count++;
					printf("%d\t%s\t%c\n", count, checkSym(str[right]), str[right]);
				}
				else {
					templen = strlen(tempstr);
					tempstr[templen++] = str[right];
					tempstr[templen++] = '\0';
				}
			}

			else {
				if (!strcmp(checkSym(str[right]), "GTR")) {
					count++;
					if (!strcmp(checkSym(str[right + 1]), "EQL"))
						printf("%d\tBEQ\t\t%c%c\n", count, str[right++], str[right]);
					else
						printf("%d\t%s\t%c\n", count, checkSym(str[right]), str[right]);
				}

				else if (!strcmp(checkSym(str[right]), "LSS")) {
					count++;
					if (!strcmp(checkSym(str[right + 1]), "GTR"))
						printf("%d\tNEQ\t\t%c%c\n", count, str[right++], str[right]);
					else if (!strcmp(checkSym(str[right + 1]), "EQL"))
						printf("%d\tLEQ\t\t%c%c\n", count, str[right++], str[right]);
					else
						printf("%d\t%s\t%c\n", count, checkSym(str[right]), str[right]);
				}

				else if (!strcmp(checkSym(str[right]), "COLON")) {
					count++;
					if (!strcmp(checkSym(str[right + 1]), "EQL"))
						printf("%d\tBECOMES\t\t%c%c\n", count, str[right++], str[right]);
					else
						printf("%d\t%s\t%c\n", count, checkSym(str[right]), str[right]);
				}

				else if (isspace(str[right])) count = count;

				else {
					count++;
					printf("%d\t%s\t%c\n", count, checkSym(str[right]), str[right]);

					if (!strcmp(checkSym(str[right]), "QUOTE"))
						strcpy(lastsymbol, "QUOTE");
				}
			}

			left = ++right;
		}
		else if (isSymbol(str[right]) == true && left != right
			|| (right == len && left != right)) {
			char* subStr = subString(str, left, right - 1);

			if (!strcmp(lastsymbol, "QUOTE"))
				strcat(tempstr, subStr);

			else {
				if (!strcmp(checkWord(subStr), "OTHERS")) {
					count++;

					if (isIden(subStr) == true && isSymbol(str[right - 1]) == false)
						printf("%d\tIDEN\t\t%s\n", count, subStr);
					else if (isInt(subStr) == true)
						printf("%d\tINT\t\t%s\n", count, subStr);
					else if (isReal(subStr) == true)
						printf("%d\tREAL\t%s\n", count, subStr);
					else if (!strcmp(subStr, "")) {
						count--;
						break;
					}
					else if (isIden(subStr) == false && isSymbol(str[right - 1]) == false)
						printf("%d\tUNKNOWN\t\t%s\n", count, subStr);
				}

				else {
					count++;
					printf("%d\t%s\t%s\n", count, checkWord(subStr), subStr);
				}
			}

			left = right;
		}
	}
	return;
}

int main() {
	FILE *fo;
	int i;
	char line[100], filename[50], ch;

	printf("Please type in your file name: \n");
	scanf("%s", filename);

	if ((fo = fopen(filename, "r")) == NULL)
	{
		printf("Error");
		return(-1);
	}

	while (fgets(line, 100, fo) != NULL)
		parse(line);

	fclose(fo);

	system("pause");
	return 0;
}