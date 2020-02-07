#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

char* toString(char ch);
void delayedOutput(char* code, char* content);
char* checkSym(char ch);
bool isSymbol(char ch);
char* checkWord(char* line);
bool isRelat(char* line);
bool isConstVal(char* line);
bool isType(char* line);
bool isInt(char* line);
bool isIden(char* line);
bool isChar(char ch);
bool isString(char* line);

void checkConst(char* line, char* type);
void checkVar(char* line, char* type);
void checkFunc(char* line);
void checkParam(char* line);
void checkContent(char* line);
char* checkStatement(char* line);
char* checkCondition(char* line);
char* checkIncrement(char* line);
char* checkFuncCall(char* line);
char* checkRead(char* line);
char* checkWrite(char* line);
char* checkAssign(char* line);
char* checkExpression(char* line);

char* subString(char* str, int left, int right);
char* parseWord();
void parse(char* line);

void printOutput(char* code, char* content);
void printSyntax(char* content);

FILE *fi, *fo;
size_t templen;
bool mainFunc = false, neg = false, assign = false, increment = false;
int lc = 1, l = 0, r = 0, len = 0, str = 0, num = 0, num2 = 0, intcon = 0;
char lastsymbol[10], tempstr[100], line[100], chstr[2], op[5] = "PLUS", op2[5] = "\0", dcontent[10] = "\0", dcode[10] = "\0";

char* toString(char ch)
{
	chstr[0] = ch;
	chstr[1] = '\0';

	return chstr;
}

void delayedOutput(char* code, char* content)
{
	strcpy(dcontent, content);
	strcpy(dcode, code);

	return;
}

/////////////////////////////BASIC CHECKS///////////////////////////////////
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

	else if (!strcmp(line, "const"))		return ("CONSTTK");
	else if (!strcmp(line, "main"))			return ("MAINTK");

	else if (!strcmp(line, "int"))			return ("INTTK");
	else if (!strcmp(line, "char"))			return ("CHARTK");
	else if (!strcmp(line, "void"))			return ("VOIDTK");
	else									return ("OTHERS");
}

bool isOp(char* line)
{
	if (!strcmp(line, "DIV") || !strcmp(line, "MULT") || !strcmp(line, "MINU") || !strcmp(line, "PLUS"))
		return (true);
	return (false);
}

bool isRelat(char* line)
{
	if (!strcmp(line, "GEQ") || !strcmp(line, "EQL") || !strcmp(line, "NEQ") ||
		!strcmp(line, "GRE") || !strcmp(line, "LEQ") || !strcmp(line, "LSS"))
		return (true);
	return (false);
}

bool isConstVal(char* line)
{
	if (!strcmp(line, "INTCON") || !strcmp(line, "CHARCON") || !strcmp(line, "IDENFR")) {
		return (true);
	}
	return (false);
}

bool isType(char* line)
{
	if (!strcmp(line, "INTTK") || !strcmp(line, "CHARTK"))
		return (true);
	return (false);
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

bool isString(char* line)
{
	if (!strcmp(line, "QUOTE") && str == 0) {
		//strcat(tempstr, "\"");
		str++;
		return isString(parseWord());
	}

	else if (!strcmp(line, "QUOTE") && str != 0) {
		//strcat(tempstr, "\"");
		str = 0;
		return (true);
	}

	else if (strcmp(line, "QUOTE")) {
		return isString(parseWord());
	}

	return (false);
}

//////////////////////////////////SYNTAX CHECK////////////////////////////////////
void checkConst(char* line, char* type)
{
	if (!strcmp(line, "IDENFR")) {
		if (!strcmp(parseWord(), "ASSIGN")) {
			if (!strcmp(type, "INTTK")) {
				line = parseWord();
				if (!strcmp(line, "MINU")) {
					if (!strcmp(parseWord(), "INTCON"));
				}
				else if (!strcmp(line, "PLUS")) {
					if (!strcmp(parseWord(), "INTCON"));
				}
				else if (!strcmp(line, "INTCON"));
			}
			else if (!strcmp(type, "CHARTK")) {
				if (!strcmp(parseWord(), "CHARCON"));
			}

			line = parseWord();
			if (!strcmp(line, "COMMA")) checkConst(parseWord(), type);
			else if (!strcmp(line, "SEMICN")) {
				printSyntax("<Constant Declaration>");//printSyntax("＜常量定义＞");
				printOutput(dcode, dcontent);
			}
		}
	}

	return;
}

void checkVar(char* line, char* type)
{
	if (!strcmp(line, "IDENFR")) {
		line = parseWord();
		if (!strcmp(line, "LBRACK")) {
			if (!strcmp(parseWord(), "INTCON")) {
				if (!strcmp(parseWord(), "RBRACK")) {
					//printf("\tArray var declaration\n");
					line = parseWord();
				}
			}
		}
		if (!strcmp(line, "COMMA")) checkVar(parseWord(), type);
		else if (!strcmp(line, "SEMICN")) {
			printSyntax("<Variable Declaration>");//printSyntax("＜变量定义＞");

			printOutput(dcode, dcontent);
		}
		else if (!strcmp(line, "LPARENT")) {
			printSyntax("<Statement Header>");//printSyntax("＜声明头部＞");
			checkFunc(line);
		}
	}

	return;
}

void checkFunc(char* line)
{
	if (isType(line)) {
		if (!strcmp(parseWord(), "IDENFR")) printSyntax("<Statement Header>");//printSyntax("＜声明头部＞");
		else return;
	}

	else if (!strcmp(line, "VOIDTK")) {
		line = parseWord();
		if (!strcmp(line, "IDENFR")) printSyntax("<Statement Header>");//printSyntax("＜声明头部＞");
		else if (!strcmp(line, "MAINTK")) {
			mainFunc = true;
			printSyntax("<Statement Header>");//printSyntax("＜声明头部＞");
		}
		else return;
	}

	else if (!strcmp(line, "IDENFR") || !strcmp(line, "MAINTK")) {
		if (!strcmp(line, "MAINTK")) mainFunc = true;
		printSyntax("<Statement Header>");//printSyntax("＜声明头部＞");
		line = parseWord();
	}

	if (!strcmp(line, "LPARENT")) {
		line = parseWord();
		if (isType(line) && !mainFunc) {
			checkParam(line);
			checkContent(parseWord());
		}
		else if (!strcmp(line, "RPARENT")) {
			if (!mainFunc) printSyntax("<Parameters Table>");//printSyntax("＜参数表＞");
			printOutput(dcode, dcontent);
			checkContent(parseWord());
		}
	}

	return;
}

void checkParam(char* line)
{
	if (isType(line)) {
		if (!strcmp(parseWord(), "IDENFR"));

		line = parseWord();
		if (!strcmp(line, "COMMA")) checkParam(parseWord());
		else if (!strcmp(line, "RPARENT")) {
			printSyntax("<Parameters Table>");//printSyntax("＜参数表＞");
			printOutput(dcode, dcontent);
		}
	}

	return;
}

void checkContent(char* line)
{
	if (!strcmp(line, "LBRACE")) {
		line = parseWord();
		while (!strcmp(line, "CONSTTK")) {
			line = parseWord();
			if (isType(line)) checkConst(parseWord(), line);
			line = parseWord();
		}

		while (isType(line)) {
			checkVar(parseWord(), line);
			line = parseWord();
		}

		line = checkStatement(line);

		while (strcmp(line, "RBRACE")) line = checkStatement(line);
		if (!strcmp(line, "RBRACE")) {
			//printSyntax("＜语句列＞");
			printSyntax("<Statement List>");
			//printSyntax("＜复合语句＞");
			printSyntax("<Compound Statement>");
			printOutput(dcode, dcontent);
			if (mainFunc) printSyntax("<Main Function>");//printSyntax("＜主函数＞");
			else printSyntax("End of function declaration");
		}
		else if (!strcmp(line, "VOIDTK") || isType(line)) {
			printf("Incomplete function!\n");
			return(line);
		}
	}

	return;
}

char* checkStatement(char* line)
{
	//If-else
	if (!strcmp(line, "IFTK")) {
		if (!strcmp(parseWord(), "LPARENT")) {
			assign = true;
			line = checkCondition(parseWord());
			assign = false;

			if (!strcmp(line, "\0")) {
				line = parseWord();
				if (!strcmp(line, "LBRACE")) {
					line = checkStatement(parseWord());
					while (strcmp(line, "RBRACE")) line = checkStatement(line);
					if (!strcmp(line, "RBRACE")) {
						printSyntax("<Statement List>");//printSyntax("＜语句列＞");
						printOutput(dcode, dcontent);
						line = parseWord();
					}
				}
				else line = checkStatement(line);

				//printf("This is an if statement\n");

				if (!strcmp(line, "ELSETK")) {
					line = parseWord();
					if (!strcmp(line, "LBRACE")) {
						line = checkStatement(parseWord());
						while (strcmp(line, "RBRACE")) line = checkStatement(line);
						if (!strcmp(line, "RBRACE")) {
							printSyntax("<Statement List>");//printSyntax("＜语句列＞");
							printOutput(dcode, dcontent);
							line = parseWord();
						}
					}
					else line = checkStatement(line);

					//printf("This is an else statement\n");
				}

				//printSyntax("＜条件语句＞");
				printSyntax("<Condition Statement>");
				//printSyntax("＜语句＞");
				printSyntax("<Statement>");
			}
			else line = parseWord();
		}
		else line = parseWord();
	}
	//While
	else if (!strcmp(line, "WHILETK")) {
		if (!strcmp(parseWord(), "LPARENT")) {
			assign = true;
			line = checkCondition(parseWord());
			assign = false;

			if (!strcmp(line, "\0")) {
				line = parseWord();
				if (!strcmp(line, "LBRACE")) {
					line = checkStatement(parseWord());
					while (strcmp(line, "RBRACE")) line = checkStatement(line);
					if (!strcmp(line, "RBRACE")) {
						printSyntax("<Statement List>");//printSyntax("＜语句列＞");
						printOutput(dcode, dcontent);
						line = parseWord();
					}
				}
				else line = checkStatement(line);

				//printSyntax("＜循环语句＞");
				printSyntax("<Loop Statement>");
				//printSyntax("＜语句＞");
				printSyntax("<Statement>");
			}
			else line = parseWord();
		}
		else line = parseWord();
	}
	//Do-While
	else if (!strcmp(line, "DOTK")) {
		line = parseWord();
		if (!strcmp(line, "LBRACE")) {
			line = checkStatement(parseWord());
			while (strcmp(line, "RBRACE")) line = checkStatement(line);
			if (!strcmp(line, "RBRACE")) {
				printSyntax("<Statement List>");//printSyntax("＜语句列＞");
				printOutput(dcode, dcontent);
				line = parseWord();
			}
		}
		else line = checkStatement(line);

		if (!strcmp(line, "WHILETK")) {
			if (!strcmp(parseWord(), "LPARENT")) {
				assign = true;
				line = checkCondition(parseWord());
				assign = false;
				if (!strcmp(line, "\0")) {
					printSyntax("<Loop Statement>");//printSyntax("＜循环语句＞");
					//printSyntax("＜语句＞");
					printSyntax("<Statement>");
				}
			}
		}
		line = parseWord();
	}
	//For
	else if (!strcmp(line, "FORTK")) {
		if (!strcmp(parseWord(), "LPARENT")) {
			if (!strcmp(parseWord(), "IDENFR")) {
				line = checkAssign(parseWord());
				if (!strcmp(line, "\0")) {
					assign = true;
					line = checkCondition(parseWord());
					assign = false;
					if (!strcmp(line, "SEMICN")) {
						printOutput(dcode, dcontent);
						line = checkIncrement(parseWord());
						if (!strcmp(line, "RPARENT")) {
							line = parseWord();
							if (!strcmp(line, "LBRACE")) {
								line = checkStatement(parseWord());
								while (strcmp(line, "RBRACE")) line = checkStatement(line);
								if (!strcmp(line, "RBRACE")) {
									printSyntax("<Statement List>");//printSyntax("＜语句列＞");
									printOutput(dcode, dcontent);
									line = parseWord();
								}
							}
							else line = checkStatement(line);

							//printSyntax("＜循环语句＞");
							printSyntax("<Loop Statement>");
							//printSyntax("＜语句＞");
							printSyntax("<Statement>");
						}
					}
				}
			}
			else line = parseWord();
		}
		else line = parseWord();
	}
	//Recursive sub-statement
	else if (!strcmp(line, "LBRACE")) {
		line = checkStatement(parseWord());
		while (strcmp(line, "RBRACE")) line = checkStatement(line);
		if (!strcmp(line, "RBRACE")) {
			printSyntax("<Statement List>");//printSyntax("＜语句列＞");
			printOutput(dcode, dcontent);
		}
		line = parseWord();
	}
	//Function call
	//Assignment statement
	else if (!strcmp(line, "IDENFR")) {
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			assign = true;
			line = checkFuncCall(parseWord());
			if (!strcmp(line, "RPARENT")) {
				printOutput(dcode, dcontent);
				line = parseWord();
				if (!strcmp(line, "SEMICN")) {
					printSyntax("<Function Call>");
					printOutput(dcode, dcontent);
					//printSyntax("＜语句＞");
					printSyntax("<Statement>");
				}
				else {
					printf("; Expected!\n");
				}
			}
			assign = false;
			line = parseWord();
		}
		else if (!strcmp(line, "ASSIGN")) {
			line = checkAssign(line);
			if (!strcmp(line, "\0")) line = parseWord();
		}
		else if (!strcmp(line, "LBRACK")) {
			assign = true;
			line = checkExpression(parseWord());
			assign = false;
			if (!strcmp(line, "RBRACK"))
			{
				printSyntax("<Expression>"); //printSyntax("＜表达式＞");
				line = parseWord();
				if (!strcmp(line, "ASSIGN")) {
					line = checkAssign(line);
					if (!strcmp(line, "\0")) line = parseWord();
				}
			}
		}
	}
	//Read Statement
	else if (!strcmp(line, "SCANFTK")) {
		checkRead(parseWord());
		line = parseWord();
	}
	//Write Statement
	else if (!strcmp(line, "PRINTFTK")) {
		assign = true;
		checkWrite(parseWord());
		assign = false;
		line = parseWord();
	}
	//Return Statement
	else if (!strcmp(line, "RETURNTK")) {
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			assign = true;
			line = parseWord();
			num = intcon;
			line = checkExpression(line);
			printSyntax("<Expression>"); //printSyntax("＜表达式＞");
			num = num2 = intcon;
			assign = false;
			if (!strcmp(line, "RPARENT")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
			//printSyntax("＜返回语句＞");
			printSyntax("<Return Statement>");
			if (!strcmp(line, "SEMICN")) {
				printOutput(dcode, dcontent);
				//printSyntax("＜语句＞");
				printSyntax("<Statement>");
			}
		}

		else if (!strcmp(line, "SEMICN")) {
			printSyntax("<Return Statement>");
			printOutput(dcode, dcontent);
			//printSyntax("＜语句＞");
			printSyntax("<Statement>");
		}
		line = parseWord();
	}
	//Empty Statement
	else if (!strcmp(line, "SEMICN")) {
		printSyntax("<Empty statement>");
		printOutput(dcode, dcontent);
		//printSyntax("＜语句＞");
		printSyntax("<Statement>");
		line = parseWord();
	}

	if (!strcmp(line, "EOF")) {
		printf("The program is incomplete!\n");
		exit(1);
	}
	else if (!strcmp(line, "VOIDTK") || isType(line)) {
		printf("'}' Expected!\n");
		return(line);
	}
	else return (line);
}

char* checkCondition(char* line)
{
	line = checkExpression(line);
	printSyntax("<Expression>"); //printSyntax("＜表达式＞");
	if (isRelat(line)) {
		line = checkExpression(parseWord());
		printSyntax("<Expression>"); //printSyntax("＜表达式＞");
		//printSyntax("＜条件＞");
		printSyntax("<Condition>");
		//if (!strcmp(line, "RPARENT")) printf("This is a condition\n");
		if (!strcmp(line, "RPARENT")) {
			return ("\0");
		}
		else return (line);
	}

	return ("\0");
}

char* checkIncrement(char* line)
{
	if (!strcmp(line, "IDENFR")) {
		if (!strcmp(parseWord(), "ASSIGN")) {
			if (!strcmp(parseWord(), "IDENFR")) {
				line = parseWord();
				if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
					increment = true;
					if (!strcmp(parseWord(), "INTCON")) {
						line = parseWord();
						if (!strcmp(line, "RPARENT")) {
							printSyntax("<This is the for statement in(de)crement>");
							printOutput(dcode, dcontent);
							increment = false;
							return (line);
						}
					}
					increment = false;
				}
			}
		}
	}
	return ("\0");
}

char* checkFuncCall(char* line)
{
	while (isConstVal(line) || !strcmp(line, "LPARENT")) {
		num = intcon;
		line = checkExpression(line);
		printSyntax("<Expression>"); //printSyntax("＜表达式＞");
		num = num2 = intcon = 0;
		if (!strcmp(line, "COMMA")) line = parseWord();
	}

	//printSyntax("＜值参数表＞");
	printSyntax("<Value Parameters Table>");

	return (line);
}

char* checkRead(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		line = parseWord();
		while (!strcmp(line, "IDENFR")) {
			line = parseWord();
			if (!strcmp(line, "COMMA")) line = parseWord();
			else if (!strcmp(line, "RPARENT")) break;
		}
		if (!strcmp(line, "RPARENT")) {
			printOutput(dcode, dcontent);
			//printSyntax("＜读语句＞");
			printSyntax("<Read Statement>");
			if (!strcmp(parseWord(), "SEMICN")) {
				printOutput(dcode, dcontent);
				//printSyntax("＜语句＞");
				printSyntax("<Statement>");
			}
		}
	}
	return ("\0");
}

char* checkWrite(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		line = parseWord();
		if (!strcmp(line, "STRCON")) {
			line = parseWord();
			if (!strcmp(line, "COMMA")) {
				num = intcon;
				line = checkExpression(parseWord());
				printSyntax("<Expression>"); //printSyntax("＜表达式＞");
				num = num2 = intcon;
			}
		}
		else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			line = checkExpression(line);
			printSyntax("<Expression>"); //printSyntax("＜表达式＞");
			num = num2 = intcon;
		}

		if (!strcmp(line, "RPARENT")) {
			printOutput(dcode, dcontent);
			//printSyntax("＜写语句＞");
			printSyntax("<Write Statement>");
			if (!strcmp(parseWord(), "SEMICN")) {
				printOutput(dcode, dcontent);
				//printSyntax("＜语句＞");
				printSyntax("<Statement>");
			}
		}
	}

	return ("\0");
}

char* checkAssign(char* line)
{
	if (!strcmp(line, "ASSIGN")) {
		assign = true;
		line = checkExpression(parseWord());
		printSyntax("<Expression>"); //printSyntax("＜表达式＞");
		if (!strcmp(line, "SEMICN")) {
			printSyntax("<Assign Statement>");//printSyntax("＜赋值语句＞");
			printOutput(dcode, dcontent);
			//printSyntax("＜语句＞");
			printSyntax("<Statement>");
		}
		assign = false;
	}
	
	return ("\0");
}

char* checkExpression(char* line)
{
	if (!strcmp(line, "LPARENT")) line = checkExpression(parseWord());
	if (!strcmp(line, "RPARENT")) {
		printSyntax("<Expression>");
		printOutput(dcode, dcontent);
		printSyntax("<Factor>");
	}

	printSyntax("<Term>");

	line = parseWord();
	strcpy(op2, line);

	while (!strcmp(op2, "MULT") || !strcmp(op2, "DIV")) {
		line = parseWord();

		if (!strcmp(line, "LPARENT")) line = checkExpression(parseWord());
		if (!strcmp(line, "RPARENT")) {
			printSyntax("<Expression>");
			printOutput(dcode, dcontent);
			printSyntax("<Factor>");
		}

		printSyntax("<Term>");

		if (!strcmp(op2, "MULT")) {
			num2 *= intcon;
		}
		else if (!strcmp(op2, "DIV")) {
			num2 /= intcon;
		}

		line = parseWord();
		strcpy(op2, line);
	}

	if (!strcmp(op, "PLUS")) {
		num += num2;
	}
	else if (!strcmp(op, "MINU")) {
		num -= num2;
	}

	strcpy(op, op2);

	if (isOp(line)) {
		line = parseWord();
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num2 = intcon;
			return (checkExpression(line));
		}
	}

	return (line);
}

/////////////////////////////////PARSING JOBS & OTHERS////////////////////////////
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

	while (r <= len && l <= r) {
		if (isSymbol(line[r]) == false)
			r++;

		if (isSymbol(line[r]) && l == r) {
			l = ++r;

			if (strcmp(checkSym(line[r - 1]), "QUOTE") && str != 0) {
				templen = strlen(tempstr);
				tempstr[templen++] = line[r - 1];
				tempstr[templen++] = '\0';
			}

			else {
				if (!strcmp(checkSym(line[r - 1]), "QUOTE") && str == 0) {
					if (isString("QUOTE")) {
						printOutput("STRCON", tempstr);
						//printSyntax("<字符串>");
						printSyntax("<String>");
						strcpy(tempstr, "\0");
						return ("STRCON");
					}
				}

				else if (!strcmp(checkSym(line[r - 1]), "QUOTE") && str != 0) return ("QUOTE");

				else if (!strcmp(checkSym(line[r - 1]), "ASSIGN") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					printOutput("EQL", "==");
					return ("EQL");
				}

				else if (!strcmp(checkSym(line[r - 1]), "GRE") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					printOutput("GEQ", ">=");
					return ("GEQ");
				}

				else if (!strcmp(checkSym(line[r - 1]), "LSS") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					printOutput("LEQ", "<=");
					return ("LEQ");
				}

				else if (!strcmp(checkSym(line[r - 1]), "EXCLAM") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					printOutput("NEQ", "!=");
					return ("NEQ");
				}

				else if (isspace(line[r - 1]));

				else if (!strcmp(checkSym(line[r - 1]), "EOLN")) break;

				else if (!strcmp(checkSym(line[r - 1]), "APOSTROPHE") && isChar(line[r]) && !strcmp(checkSym(line[r + 1]), "APOSTROPHE")) {
					printOutput("CHARCON", toString(line[r]));
					if (assign) printSyntax("<Factor>");
					++r;
					l = ++r;
					return ("CHARCON");
				}

				else if (!strcmp(checkSym(line[r - 1]), "SEMICN") || !strcmp(checkSym(line[r - 1]), "RPARENT") || !strcmp(checkSym(line[r - 1]), "RBRACE")) {
					delayedOutput(checkSym(line[r - 1]), toString(line[r - 1]));
					return (checkSym(line[r - 1]));
				}

				else {
					printOutput(checkSym(line[r - 1]), toString(line[r - 1]));
					return (checkSym(line[r - 1]));
				}
			}
		}
		else if ((isSymbol(line[r]) && l != r) || (r == len && l != r)) {
			char* subStr = subString(line, l, r - 1);

			if (str > 0) {
				strcat(tempstr, subStr);
				l = r;
			}

			else {
				l = r;

				if (!strcmp(checkWord(subStr), "OTHERS")) {
					if (isIden(subStr) && !isSymbol(line[r - 1])) {
						if (line[r] == '[' && assign) {
							printOutput("IDENFR", subStr);
							parseWord();
							if (!strcmp(checkExpression(parseWord()), "RBRACK")) printSyntax("<Expression>");
						}
						else if (line[r] == '(' && assign) {
							printOutput("IDENFR", subStr);
							parseWord();
							if (!strcmp(checkFuncCall(parseWord()), "RPARENT")) {
								printOutput(dcode, dcontent);
								printSyntax("<Function Call>");
							}
						}
						else printOutput("IDENFR", subStr);
						if (assign) printSyntax("<Factor>");
						return ("IDENFR");
					}
					else if (isInt(subStr)) {
						printOutput("INTCON", subStr);
						printSyntax("<Unsigned Integer>");
						if (!increment) printSyntax("<Integer>");
						intcon = atoi(subStr);
						if (assign) printSyntax("<Factor>");
						return ("INTCON");
					}
					else if (!isIden(subStr) && !isSymbol(line[r - 1]))
						return ("UNKNOWN");
				}

				else {
					printOutput(checkWord(subStr), subStr);
					return (checkWord(subStr));
				}
			}
		}
	}

	if (r > len && fgets(line, 100, fi) != NULL) {
		l = r = 0;
		lc++;
		return (parseWord());
	}
	else return("EOF");

	return ("\0");
}

void parse(char* line)
{
	while (!strcmp(line, "CONSTTK")) {
		line = parseWord();
		if (isType(line)) checkConst(parseWord(), line);
		//printSyntax("＜常量说明＞");
		printSyntax("<Constant Statement>");
		line = parseWord();
	}

	while (isType(line)) {
		checkVar(parseWord(), line);
		line = parseWord();
	}

	if (!strcmp(line, "VOIDTK")) {
		while ((!strcmp(line, "VOIDTK") || isType(line)) && !mainFunc) {
			checkFunc(parseWord());
			line = parseWord();
		}
	}

	//printSyntax("＜程序＞\n");
	printSyntax("<Program>");
	return;
}

void printOutput(char* code, char* content)
{
	if (strcmp(code, "\0"))
		fprintf(fo, "%s %s\n", code, content);

	strcpy(dcode, "\0");
	strcpy(dcontent, "\0");

	return;
}

void printSyntax(char* content)
{
	fprintf(fo, "%s\n", content);

	return;
}

int main() {
	int i;
	char* locale;

	locale = setlocale(LC_ALL, "en_US.UTF-8");

	if ((fi = fopen("testfile.txt", "r")) == NULL || (fo = fopen("output.txt", "w")) == NULL)
	{
		printf("Error opening file!");
		return(-1);
	}

	fgets(line, 100, fi);
	parse(parseWord());

	fclose(fi);
	fclose(fo);

	return 0;
}