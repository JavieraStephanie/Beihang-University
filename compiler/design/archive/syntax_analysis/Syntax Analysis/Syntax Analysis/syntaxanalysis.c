#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char* checkSym(char ch);
bool isSymbol(char ch);
char* checkWord(char* line);
bool isRelatType(char* line);
bool isConstVal(char* line);
bool isType(char* line);
bool isInt(char* line);
bool isReal(char* line);
bool isIden(char* line);
bool isString(char* line);
bool checkParHead(char* line);
bool checkParam(char* line);
bool checkIO(char* line);
bool checkCondition(char* line);
bool checkAssign(char* line);
char* subString(char* str, int left, int right);
char* parse();

size_t templen;
int lc = 0, l = 0, r = 0;
char lastsymbol[10], type[10], word[10], tempstr[50], line[100], begin = 0, cond = 0, repeat = 0, forloop = 0,
	assign = 0, str = 0, con = 0, var = 0;

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
	case '\0': return ("EOLN"); break;
	}
}

bool isSymbol(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == ';' || ch == ':' || ch == '[' || ch == ']' ||
		ch == '\'' || ch == '\n' || ch == '\0')
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
	else if (!strcmp(line, "repeat"))		return ("REPEATSYM");
	else if (!strcmp(line, "until"))		return ("UNTILSYM");
	else if (!strcmp(line, "read"))			return ("READSYM");
	else if (!strcmp(line, "readln"))		return ("READSYM");
	else if (!strcmp(line, "write"))		return ("WRITESYM");
	else if (!strcmp(line, "writeln"))		return ("WRITESYM");
	else if (!strcmp(line, "to"))			return ("TOSYM");
	else if (!strcmp(line, "downto"))		return ("TOSYM");

	else if (!strcmp(line, "program"))		return ("PROGSYM");
	else if (!strcmp(line, "type"))			return ("TYPESYM");
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

bool isOp(char* line)
{
	if (!strcmp(line, "DIV") || !strcmp(line, "TIMES") || !strcmp(line, "MINUS") || !strcmp(line, "PLUS"))
		return (true);
	return (false);
}

bool isRelatType(char* line)
{
	if (!strcmp(line, "BEQ") || !strcmp(line, "EQL") || !strcmp(line, "NEQ") ||
		!strcmp(line, "GTR") || !strcmp(line, "LEQ") || !strcmp(line, "LSS"))
		return (true);
	return (false);
}

bool isConstVal(char* line)
{
	if (!strcmp(line, "INT") || !strcmp(line, "REAL") || !strcmp(line, "STRING") || !strcmp(line, "IDEN"))
		return (true);
	return (false);
}

bool isType(char* line)
{
	if (!strcmp(line, "INTTYPE") || !strcmp(line, "REALTYPE") || !strcmp(line, "CHARTYPE") ||
		!strcmp(line, "STRTYPE") || !strcmp(line, "BOOLTYPE") || !strcmp(line, "IDEN"))
		return (true);
	return (false);
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
		if (line[i] < '0' || line[i] > '9' || (line[i] == '-' && i > 0))
			return false;
		if (line[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

bool isIden(char* line)
{
	if ((line[0] >= 'A' && line[0] <= 'Z') || (line[0] >= 'a' && line[0] <= 'z'))
		return (true);
	return (false);
}

bool checkParHead(char* line)
{
	if (!strcmp(line, "LPAREN")) {
		if (checkParam(parse()))
			return checkParHead(parse());
	}

	else if (!strcmp(line, "SEMICOLON"))
		return (true);
	
	else if (!strcmp(line, "COLON") && !strcmp(lastsymbol, "FUNCTSYM")) {
		if (isType(parse()))
			return (true);
		else {
			printf("(L: %d, C: %d)Type of function expected\n", lc, r);
			return (false);
		}
	}

	printf("(L: %d, C: %d)Parameter or ';' expected\n", lc, r);
	return (false);
}

bool checkParam(char* line)
{
	if (!strcmp(line, "IDEN")) {
		line = parse();
		if (!strcmp(line, "COLON")) {
			if (isType(parse()))
				return checkParam(parse());
		}
		else if (!strcmp(line, "COMMA"))
			return checkParam(parse());
		else
			return (false);
	}

	else if (!strcmp(line, "SEMICOLON"))
		return checkParam(parse());

	else if (!strcmp(line, "RPAREN"))
		return (true);

	return (false);
}

bool isString(char* line)
{
	if (!strcmp(line, "QUOTE") && str == 0) {
		str++;
		return isString(parse());
	}

	else if (!strcmp(line, "QUOTE") && str !=0) {
		str = 0;
		return (true);
	}

	else if (strcmp(line, "QUOTE")) {
		return isString(parse());
	}

	return (false);
}

bool checkIO(char* line)
{
	if (!strcmp(line, "LPAREN")) {
		return checkIO(parse());
	}

	if (!strcmp(line, "STRING"))
		return checkIO(parse());

	else if (!strcmp(line, "IDEN") && str == 0) {
		line = parse();
		if (!strcmp(line, "LPAREN") && assign == 0) {
			if (isConstVal(parse())) {
				if (!strcmp(parse(), "RPAREN")) {
					if (!strcmp(parse(), "SEMICOLON")) {
						return (true);
					}
				}
			}
		}
		else
			return checkIO(line);
	}

	else if (!strcmp(line, "COMMA"))
		return checkIO(parse());

	else if (!strcmp(line, "RPAREN"))
		return (true);

	else
		return (false);
}

bool checkCondition(char* line)
{
	if (isConstVal(line)) {
		if (isRelatType(parse())) {
			if (isConstVal(parse())) {
				return (true);
			}
			else printf("(L: %d, C : %d)Constant value expected\n", lc, r);
		}
		else printf("(L: %d, C : %d)Relation operator expected\n", lc, r);
	}
	else printf("(L: %d, C : %d)Constant value expected\n", lc, r);

	return (false);
}

bool checkAssign(char* line)
{
	if (!strcmp(line, "SEMICOLON") && assign == 0) {
		printf("(L: %d)This is a function call\n", lc);
		return (true);
	}

	else if (!strcmp(line, "LPAREN") && assign == 0) {
		if (isConstVal(parse())) {
			if (!strcmp(parse(), "RPAREN")) {
				if (!strcmp(parse(), "SEMICOLON")) {
					printf("(L: %d)This is a function call\n", lc);
					return (true);
				}
			}
		}
	}

	else if (!strcmp(line, "EQL") || !strcmp(line, "BECOMES")) {
		assign++;
		return checkAssign(parse());
	}

	else if (isConstVal(line)) {
		return checkAssign(parse());
	}

	else if (isOp(line)) {
		return checkAssign(parse());
	}

	else if (!strcmp(line, "SEMICOLON")) {
		printf("(L: %d)This is an assignment statement\n", lc);
		assign = 0;
		return (true);
	}

	return (false);
}

void checkConstant(char* line)
{
	if (!strcmp(line, "IDEN")) {
		if (!strcmp(parse(), "EQL")) {
			line = parse();
			if (isConstVal(line)) {
				con = 0;
				printf("(L: %d)This is a constant declaration\n", lc);
			}
			else if (!strcmp(line, "MINUS")) {
				if (isConstVal(parse())) {
					con = 0;
					printf("(L: %d)This is a constant declaration\n", lc);
				}
			}
			else printf("(L: %d, C : %d)Constant value expected\n", lc, r);
		}
		else printf("(L: %d, C : %d)'=' expected\n", lc, r);
	}
	else printf("(L: %d, C : %d)Identifier expected\n", lc, r);

	return;
}

void checkVar(char* line)
{
	if (!strcmp(line, "IDEN")) {
		line = parse();
		if (!strcmp(line, "COLON")) {
			var++;
			line = parse();
			if (isType(line)) {
				var = 0;
				printf("(L: %d)This is a var declaration\n", lc);
			}
			else if (!strcmp(line, "ARRTYPE")) {
				if (!strcmp(parse(), "LBRACKETS"))
					if (!strcmp(parse(), "UNKNOWN"))
						if (!strcmp(parse(), "RBRACKETS"))
							if (!strcmp(parse(), "OFSYM"))
								if (isType(parse())) {
									var = 0;
									printf("(L: %d)This is a var declaration\n", lc);
								}
			}
			else printf("(L: %d, C : %d)Type expected\n", lc, r);
		}
		else if (!strcmp(line, "COMMA"))
			checkVar(parse());
		else printf("(L: %d, C : %d)':' or ',' expected\n", lc, r);
	}

	return;
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

char* parse() {
	int len = strlen(line);

	while (r <= len && l <= r) {
		if (isSymbol(line[r]) == false)
			r++;

		if (isSymbol(line[r]) == true && l == r) {
			l = ++r;

			if (!strcmp(checkSym(line[r - 1]), "LSS")) {
				if (!strcmp(checkSym(line[r]), "GTR")) {
					l = ++r;
					return ("NEQ");
				}
				else if (!strcmp(checkSym(line[r]), "EQL")) {
					l = ++r;
					return ("LEQ");
				}
				return (checkSym(line[r - 1]));
			}

			else if (!strcmp(checkSym(line[r - 1]), "GTR")) {
				if (!strcmp(checkSym(line[r]), "EQL")) {
					l = ++r;
					return ("BEQ");
				}
				return (checkSym(line[r - 1]));
			}

			else if (!strcmp(checkSym(line[r - 1]), "COLON") && !strcmp(checkSym(line[r]), "EQL")) {
				l = ++r;
				return ("BECOMES");
			}

			else if (!strcmp(checkSym(line[r - 1]), "SPACE") || !strcmp(checkSym(line[r - 1]), "ENTER"));

			else {
				if (!strcmp(checkSym(line[r - 1]), "QUOTE") && str == 0) {
					if (isString("QUOTE")) {
						return ("STRING");
					}
				}
				else {
					return (checkSym(line[r - 1]));
				}
			}
		}
		else if (isSymbol(line[r]) == true && l != r || (r == len && l != r)) {
			char* subStr = subString(line, l, r - 1);

			l = r;

			if (!strcmp(checkWord(subStr), "OTHERS")) {
				if (isIden(subStr) == true && isSymbol(line[r - 1]) == false) {
					if (!strcmp(lastsymbol, "\0")) {
						if (assign == 0) {
							checkAssign(parse());
						}
						else {
							checkAssign("IDEN");
						}
					}

					else if (!strcmp(lastsymbol, "CONSTSYM") && con == 0) {
						con++;
						checkConstant("IDEN");
					}

					else if (!strcmp(lastsymbol, "VARSYM") && var == 0) {
						checkVar("IDEN");
					}

					else
						return ("IDEN");
				}
				else if (isInt(subStr) == true)
					return ("INT");
				else if (isReal(subStr) == true)
					return ("REAL");
				else if (isIden(subStr) == false && isSymbol(line[r - 1]) == false)
					return ("UNKNOWN");
			}

			else if (isType(checkWord(subStr)))
				return (checkWord(subStr));

			else if (!strcmp(checkWord(subStr), "ARRTYPE") || !strcmp(checkWord(subStr), "OFSYM"))
				return checkWord(subStr);

			else
				strcpy(lastsymbol, checkWord(subStr));

			if (!strcmp(lastsymbol, "CONSTSYM") || !strcmp(lastsymbol, "VARSYM") || 
				!strcmp(lastsymbol, "TYPESYM"))
				parse();

			else if (!strcmp(lastsymbol, "PROCSYM")) {
				if (!strcmp(parse(), "IDEN")) {
					if (checkParHead(parse()))
						printf("(L: %d)This is a procedure declaration\n", lc);
				}
				else
					printf("(L: %d, C: %d)Identifier expected\n", lc, r);
				strcpy(lastsymbol, "\0");
			 }

			else if (!strcmp(lastsymbol, "FUNCTSYM")) {
				if (!strcmp(parse(), "IDEN")) {
					if (checkParHead(parse()))
						printf("(L: %d)This is a function declaration\n", lc);
				}
				else
					printf("(L: %d, C: %d)Identifier expected\n", lc, r);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "READSYM")) {
				if (checkIO(parse()))
					printf("(L: %d)This is a read statement\n", lc);
				else
					printf("(L: %d)This is a wrong read statement\n", lc);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "WRITESYM")) {
				if (checkIO(parse()))
					printf("(L: %d)This is a write statement\n", lc);
				else
					printf("(L: %d)This is a wrong write statement\n", lc);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "BEGINSYM")) {
				begin++;
				printf("(L: %d)This is the beginning of a sub-procedure\n", lc);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "ENDSYM")) {
				if (begin) {
					printf("(L: %d)This is the end of a sub-procedure\n", lc);
					begin--;
				}
				else
					printf("'begin' expected before 'end'\n");
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "IFSYM")) {
				cond++;
				if (checkCondition(parse()))
					printf("(L: %d)This is an if condition\n", lc);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "THENSYM")) {
				if (cond)
					printf("(L: %d)This will be executed if the condition is met\n", lc);
				else if (!cond)
					printf("(L: %d)Condition expected\n", lc);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "ELSESYM")) {
				if (cond) {
					printf("(L: %d)If none of the condition is met, this will be executed\n", lc);
					cond--;
				}
				else if (!cond)
					printf("Condition expected\n");
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "FORSYM")) {
				if (!strcmp(parse(), "IDEN")) {
					if (!strcmp(parse(), "BECOMES")) {
						if (isConstVal(parse())) {
							parse();
							if (!strcmp(lastsymbol, "TOSYM")) {
								if (isConstVal(parse()))
									printf("(L: %d)This is a for loop condition\n", lc);
								else printf("(L: %d, C: %d)Constant expression expected\n", lc, r);
							}
							else printf("(L: %d, C: %d)'to' expression expected\n", lc, r);
						}
						else printf("(L: %d, C: %d)Constant expression expected\n", lc, r);
					}
					else printf("(L: %d, C: %d)Identifier expected\n", lc, r);
				}
				else printf("(L: %d, C: %d)Identifier expected\n", lc, r);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "REPEATSYM")) {
				repeat++;
				printf("(L: %d)This is a repeat loop\n", lc);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "UNTILSYM")) {
				if (repeat) {
					if (checkCondition(parse())) {
						printf("(L: %d)This is the repeat loop condition\n", lc);
						repeat--;
					}
					else
						printf("(L: %d)This is a wrong repeat loop condition format\n", lc);
				}
				else
					printf("(L: %d, C: %d)'repeat' expected\n", lc, r);
				strcpy(lastsymbol, "\0");
			}
		}
	}
	return ("\0");
}

int main() {
	FILE *fo;
	int i;
	char filename[50], ch;

	printf("Please type in your file name: \n");
	scanf("%s", filename);

	if ((fo = fopen(filename, "r")) == NULL)
	{
		printf("Error");
		return(-1);
	}

	while (fgets(line, 100, fo) != NULL) {
		l = r = 0;
		lc++;
		parse();
	}

	fclose(fo);

	system("pause");
	return 0;
}