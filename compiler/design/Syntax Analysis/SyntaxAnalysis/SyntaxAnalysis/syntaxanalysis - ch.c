#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

FILE* fi, * fo;
size_t templen;
bool normal = false, hasvar = false, mainFunc = false, neg = false, assign = false, valfunc = true;
int lc = 1, l = 0, r = 0, len = 0, str = 0, num = 0, num2 = 0, intcon = 0, funccounter = 0;
char* subStr, lastsymbol[10], tempstr[100], line[100], chstr[2], op[5] = "PLUS", op2[5] = "\0", funcname[20] = "\0";
//delays
char dcontent[100] = "\0", dcontent2[100] = "\0", dcontent3[100] = "\0", dcode[10] = "\0", dcode2[10] = "\0", dcode3[10] = "\0";

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
char* checkParam(char* line);
void checkContent(char* line);
char* checkStatement(char* line);
char* checkForCondition(char* line);
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

struct table {
	char name[30];
	bool valfunc;
}valtab[100];

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

void storeFunc(char* name)
{
	strcpy(valtab[funccounter].name, name);
	valtab[funccounter].valfunc = valfunc;

	funccounter++;

	return;
}

int findId()
{
	int i = 0;
	while (strcmp(valtab[i].name, funcname) && i < 100 && strcmp(valtab[i].name, "\0")) {
		i++;
	}
	return i;
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
	if (ch == ';'	|| ch == ','	|| ch == '='	|| ch == '(' ||
		ch == ')'	|| ch == '['	|| ch == ']'	|| ch == '{' ||
		ch == '}'	|| ch == '/'	|| ch == '*'	|| ch == '-' ||
		ch == '+'	|| ch == '>'	|| ch == '<'	|| ch == '"' ||
		ch == '\''	|| ch == '!'	|| ch == '\0'	|| ch == ' ' ||
		ch == '\n'	|| ch == '\t')
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
		str++;
		return isString(parseWord());
	}

	else if (!strcmp(line, "QUOTE") && str != 0) {
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
		printOutput(dcode, dcontent);
		if (!strcmp(parseWord(), "ASSIGN")) {
			printOutput(dcode, dcontent);
			if (!strcmp(type, "INTTK")) {
				printOutput(dcode, dcontent);
				line = parseWord();
				if (!strcmp(line, "MINU") || !strcmp(line, "PLUS")) {
					printOutput(dcode, dcontent);
					line = parseWord();
					if (!strcmp(line, "INTCON")) {
						printOutput(dcode, dcontent);
						printSyntax("<无符号整数>");
						printSyntax("<整数>");
					}
				}
				else if (!strcmp(line, "INTCON")) {
					printOutput(dcode, dcontent);
					printSyntax("<无符号整数>");
					printSyntax("<整数>");
				}
			}
			else if (!strcmp(type, "CHARTK")) {
				printOutput(dcode, dcontent);
				line = parseWord();
				if (!strcmp(line, "CHARCON")) printOutput(dcode, dcontent);
			}

			line = parseWord();

			if (!strcmp(line, "COMMA")) {
				printOutput(dcode, dcontent);
				checkConst(parseWord(), type);
			}
			else if (!strcmp(line, "SEMICN")) {
				printSyntax("<常量定义>");
				printOutput(dcode, dcontent);
			}
		}
	}

	return;
}

void checkVar(char* line, char* type)
{
	if (!strcmp(line, "IDENFR")) {
		if (!normal) {
			strcpy(dcode2, dcode);
			strcpy(dcontent2, dcontent);
		}
		else printOutput(dcode, dcontent);

		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			if (hasvar) printSyntax("<变量说明>");
			printOutput(dcode3, dcontent3);
			printOutput(dcode2, dcontent2);
			storeFunc(subStr);
			printSyntax("<声明头部>");
			printOutput(dcode, dcontent);
			hasvar = false;
			checkFunc(line);
			return;
		}
		else if (!strcmp(line, "LBRACK")) {
			printOutput(dcode3, dcontent3);
			printOutput(dcode2, dcontent2);
			printOutput(dcode, dcontent);
			line = parseWord();
			if (!strcmp(line, "INTCON") && intcon > 0) {
				printOutput(dcode, dcontent);
				printSyntax("<无符号整数>");
			}
			line = parseWord();
			if (!strcmp(line, "RBRACK")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
		}

		if (!strcmp(line, "COMMA")) {
			printOutput(dcode3, dcontent3);
			printOutput(dcode2, dcontent2);
			printOutput(dcode, dcontent);
			normal = true;
			checkVar(parseWord(), type);
		}
		else if (!strcmp(line, "SEMICN")) {
			printOutput(dcode3, dcontent3);
			printOutput(dcode2, dcontent2);
			printSyntax("<变量定义>");
			printOutput(dcode, dcontent);
			normal = false;
			hasvar = true;
		}
	}

	return;
}

void checkFunc(char* line)
{
	if (!strcmp(line, "IDENFR") || !strcmp(line, "MAINTK")) {
		printOutput(dcode, dcontent);
		if (!strcmp(line, "MAINTK")) mainFunc = true;
		else if (!strcmp(line, "IDENFR")) {
			storeFunc(subStr);
			if (valfunc) printSyntax("<声明头部>");
		}
		line = parseWord();
	}

	if (!strcmp(line, "LPARENT")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (isType(line) && !mainFunc) line = checkParam(line);
		if (!strcmp(line, "RPARENT")) {
			if (!mainFunc) printSyntax("<参数表>");
			printOutput(dcode, dcontent);
			line = parseWord();
			if (!strcmp(line, "LBRACE")) checkContent(line);
		}
	}

	return;
}

char* checkParam(char* line)
{
	if (isType(line)) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "IDENFR")) printOutput(dcode, dcontent);

		line = parseWord();
		if (!strcmp(line, "COMMA")) {
			printOutput(dcode, dcontent);
			line = checkParam(parseWord());
		}
	}

	return (line);
}

void checkContent(char* line)
{
	if (!strcmp(line, "LBRACE")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "CONSTTK")) {
			while (!strcmp(line, "CONSTTK")) {
				printOutput(dcode, dcontent);
				line = parseWord();
				if (isType(line)) {
					printOutput(dcode, dcontent);
					checkConst(parseWord(), line);
				}
				line = parseWord();
			}
			printSyntax("<常量说明>");
		}

		if (isType(line)) {
			printOutput(dcode, dcontent);
			while (isType(line)) {
				strcpy(dcode3, dcode);
				strcpy(dcontent3, dcontent);
				checkVar(parseWord(), line);
				line = parseWord();
			}
			if (hasvar) {
				printSyntax("<变量说明>");
				hasvar = false;
			}
		}
		
		if (strcmp(line, "RBRACE")) {
			while (strcmp(line, "RBRACE")) line = checkStatement(line);
		}

		if (!strcmp(line, "RBRACE")) {
			printSyntax("<语句列>");
			printSyntax("<复合语句>");
			printOutput(dcode, dcontent);
			if (mainFunc) printSyntax("<主函数>");
			else if (valfunc) printSyntax("<有返回值函数定义>");
			else printSyntax("<无返回值函数定义>");
			valfunc = true;
		}
	}

	return;
}

char* checkStatement(char* line)
{
	//Recursive sub-statement
	if (!strcmp(line, "LBRACE")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (strcmp(line, "RBRACE")) {
			while (strcmp(line, "RBRACE")) line = checkStatement(line);
		}

		if (!strcmp(line, "RBRACE")) {
			printSyntax("<语句列>");
			printOutput(dcode, dcontent);
			printSyntax("<语句>");
			line = parseWord();
		}
	}
	//If-else
	else if (!strcmp(line, "IFTK")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			printOutput(dcode, dcontent);
			assign = true;
			line = checkCondition(parseWord());
			assign = false;

			if (!strcmp(line, "RPARENT")) {
				line = checkStatement(parseWord());
				if (!strcmp(line, "ELSETK")) {
					printOutput(dcode, dcontent);
					line = checkStatement(parseWord());
				}
				printSyntax("<条件语句>");
				printSyntax("<语句>");
			}
		}
	}
	//Do-While 
	else if (!strcmp(line, "DOTK")) {
		printOutput(dcode, dcontent);
		line = checkStatement(parseWord());

		if (!strcmp(line, "WHILETK")) {
			printOutput(dcode, dcontent);
			if (!strcmp(parseWord(), "LPARENT")) {
				printOutput(dcode, dcontent);
				assign = true;
				line = checkCondition(parseWord());
				assign = false;
				if (!strcmp(line, "RPARENT")) {
					printSyntax("<循环语句>");
					printSyntax("<语句>");
					line = parseWord();
				}
			}
		}
	}
	//While
	else if (!strcmp(line, "WHILETK")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			printOutput(dcode, dcontent);
			assign = true;
			line = checkCondition(parseWord());
			assign = false;

			if (!strcmp(line, "RPARENT")) {
				//line = checkStatement(parseWord());
				line = parseWord();
				if (!strcmp(line, "LBRACE")) {
					printOutput(dcode, dcontent);
					line = parseWord();
					if (strcmp(line, "RBRACE")) {
						while (strcmp(line, "RBRACE")) line = checkStatement(line);
					}
					if (!strcmp(line, "RBRACE")) {
						printSyntax("<语句列>");
						printOutput(dcode, dcontent);
						printSyntax("<语句>");
						line = parseWord();
					}
				}
				else line = checkStatement(line);

				printSyntax("<循环语句>");
				printSyntax("<语句>");
			}
		}
	}
	//For
	else if (!strcmp(line, "FORTK")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			printOutput(dcode, dcontent);
			line = checkForCondition(parseWord());
			if (!strcmp(line, "RPARENT")) {
				printOutput(dcode, dcontent);
				line = checkStatement(parseWord());
				printSyntax("<循环语句>");
				printSyntax("<语句>");
			}
		}
	}
	//Function call && Assignment statement
	else if (!strcmp(line, "IDENFR")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			strcpy(funcname, subStr);
			printOutput(dcode, dcontent);
			assign = true;
			line = checkFuncCall(parseWord());
			assign = false;
			if (!strcmp(line, "RPARENT")) {
				printOutput(dcode, dcontent);
				if (valtab[findId()].valfunc) printSyntax("<有返回值函数调用语句>");
				else printSyntax("<无返回值函数调用语句>");
				line = parseWord();
			}
		}
		else if (!strcmp(line, "ASSIGN")) {
			printOutput(dcode, dcontent);
			line = checkAssign(line);
			printSyntax("<赋值语句>");
		}
		else if (!strcmp(line, "LBRACK")) {
			printOutput(dcode, dcontent);
			assign = true;
			line = parseWord();
			if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				num = intcon;
				while (strcmp(line, "RBRACK")) line = checkExpression(line);
				printSyntax("<表达式>");
				num = num2 = intcon = 0;
			}
			assign = false;
			if (!strcmp(line, "RBRACK"))
			{
				printOutput(dcode, dcontent);
				line = parseWord();
				if (!strcmp(line, "ASSIGN")) {
					printOutput(dcode, dcontent);
					line = checkAssign(line);
					printSyntax("<赋值语句>");
				}
			}
		}
	}
	//Read Statement
	else if (!strcmp(line, "SCANFTK")) {
		printOutput(dcode, dcontent);
		line = checkRead(parseWord());
	}
	//Write Statement
	else if (!strcmp(line, "PRINTFTK")) {
		printOutput(dcode, dcontent);
		assign = true;
		line = checkWrite(parseWord());
		assign = false;
	}
	//Return Statement
	else if (!strcmp(line, "RETURNTK")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			printOutput(dcode, dcontent);
			assign = true;
			line = parseWord();
			if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				num = intcon;
				while (strcmp(line, "RPARENT")) line = checkExpression(line);
				printSyntax("<表达式>");
				num = num2 = intcon = 0;
			}
			assign = false;
			if (!strcmp(line, "RPARENT")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
		}
		printSyntax("<返回语句>");
	}
	
	//Empty Statement
	if (!strcmp(line, "SEMICN")) {
		printOutput(dcode, dcontent);
		printSyntax("<语句>");
		line = parseWord();
	}
	
	/*if (!strcmp(line, "EOF")) {
		printf("The program is incomplete!\n");
		exit(1);
	}
	else if (!strcmp(line, "VOIDTK") || isType(line)) {
		printf("'}' Expected!\n");
		return(line);
	}
	else*/ return (line);
}

char* checkForCondition(char* line)
{
	if (!strcmp(line, "IDENFR")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "ASSIGN")) {
			line = checkAssign(line);
			if (!strcmp(line, "SEMICN")) {
				printOutput(dcode, dcontent);
				assign = true;
				line = checkCondition(parseWord());
				assign = false;
				printSyntax("<条件>");
				if (!strcmp(line, "SEMICN")) {
					printOutput(dcode, dcontent);
					line = checkIncrement(parseWord());
				}
			}
		}
	}
	
	return (line);
}

char* checkCondition(char* line)
{
	if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		printOutput(dcode, dcontent);
		line = parseWord();
	}
	if (isConstVal(line) || !strcmp(line, "LPARENT")) {
		num = intcon;
		line = checkExpression(line);
		printSyntax("<表达式>");
		num = num2 = intcon = 0;
	}

	if (isRelat(line)) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			printOutput(dcode, dcontent);
			line = parseWord();
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			line = checkExpression(line);
			printSyntax("<表达式>");
			num = num2 = intcon = 0;
		}
	}

	if (!strcmp(line, "RPARENT")) {
		printSyntax("<条件>");
		printOutput(dcode, dcontent);
	}

	return (line);
}

char* checkIncrement(char* line)
{
	if (!strcmp(line, "IDENFR")) {
		printOutput(dcode, dcontent);
		if (!strcmp(parseWord(), "ASSIGN")) {
			printOutput(dcode, dcontent);
			if (!strcmp(parseWord(), "IDENFR")) {
				printOutput(dcode, dcontent);
				line = parseWord();
				if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
					printOutput(dcode, dcontent);
					if (!strcmp(parseWord(), "INTCON")) {
						printOutput(dcode, dcontent);
						printSyntax("<无符号整数>");
						printSyntax("<步长>");
						line = parseWord();
					}
				}
			}
		}
	}

	return (line);
}

char* checkFuncCall(char* line)
{
	while (strcmp(line, "RPARENT")) {
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			printOutput(dcode, dcontent);
			line = parseWord();
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			line = checkExpression(line);
			printSyntax("<表达式>");
			num = num2 = intcon = 0;
			if (!strcmp(line, "COMMA")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
		}
	}

	printSyntax("<值参数表>");
	
	return (line);
}

char* checkRead(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		while (!strcmp(line, "IDENFR")) {
			printOutput(dcode, dcontent);
			line = parseWord();
			if (!strcmp(line, "COMMA")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
			else if (!strcmp(line, "RPARENT")) break;
		}
		if (!strcmp(line, "RPARENT")) {
			printOutput(dcode, dcontent);
			printSyntax("<读语句>");
			line = parseWord();
		}
	}
	
	return (line);
}

char* checkWrite(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "STRCON")) {
			printOutput(dcode, dcontent);
			printSyntax("<字符串>");
			line = parseWord();
			if (!strcmp(line, "COMMA")) {
				printOutput(dcode, dcontent);
				num = intcon;
				line = checkExpression(parseWord());
				printSyntax("<表达式>");
				num = num2 = intcon = 0;
			}
		}
		else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			line = checkExpression(line);
			printSyntax("<表达式>");
			num = num2 = intcon = 0;
		}
		else if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			printOutput(dcode, dcontent);
			line = parseWord();
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				num = intcon;
				line = checkExpression(line);
				printSyntax("<表达式>");
				num = num2 = intcon = 0;
			}
		}

		if (!strcmp(line, "RPARENT")) {
			printOutput(dcode, dcontent);
			printSyntax("<写语句>");
			line = parseWord();
		}
	}

	return (line);
}

char* checkAssign(char* line)
{
	if (!strcmp(line, "ASSIGN")) {
		printOutput(dcode, dcontent);
		assign = true;
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			printOutput(dcode, dcontent);
			line = parseWord();
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			line = checkExpression(line);
			printSyntax("<表达式>");
			num = num2 = intcon = 0;
		}
		
		assign = false;
	}

	return (line);
}

char* checkExpression(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			printOutput(dcode, dcontent);
			line = parseWord();
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			while (strcmp(line, "RPARENT")) line = checkExpression(line);
			printSyntax("<表达式>");
		}

		if (!strcmp(line, "RPARENT")) {
			printOutput(dcode, dcontent);
			printSyntax("<因子>");
		}
	}
	else if (isConstVal(line)) {
		printOutput(dcode, dcontent);
		if (!strcmp(line, "INTCON")) {
			printSyntax("<无符号整数>");
			printSyntax("<整数>");
		}
		printSyntax("<因子>");
	}
	else if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "INTCON")) {
			printOutput(dcode, dcontent);
			printSyntax("<无符号整数>");
			printSyntax("<整数>");
			printSyntax("<因子>");
		}
	}
	
	line = parseWord();
	strcpy(op2, line);

	while (!strcmp(op2, "MULT") || !strcmp(op2, "DIV")) {
		printOutput(dcode, dcontent);
		line = parseWord();

		if (!strcmp(line, "LPARENT")) {
			printOutput(dcode, dcontent);
			line = parseWord();
			if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				printOutput(dcode, dcontent);
				line = parseWord();
			}
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				num = intcon;
				while (strcmp(line, "RPARENT")) line = checkExpression(line);
				printSyntax("<表达式>");
			}

			if (!strcmp(line, "RPARENT")) {
				printOutput(dcode, dcontent);
				printSyntax("<因子>");
			}
		}
		else if (isConstVal(line)) {
			printOutput(dcode, dcontent);
			if (!strcmp(line, "INTCON")) {
				printSyntax("<无符号整数>");
				printSyntax("<整数>");
			}
			printSyntax("<因子>");
		}
		else if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			printOutput(dcode, dcontent);
			line = parseWord();
			if (!strcmp(line, "INTCON")) {
				printOutput(dcode, dcontent);
				printSyntax("<无符号整数>");
				printSyntax("<整数>");
				printSyntax("<因子>");
			}
		}

		if (!strcmp(op2, "MULT")) {
			num2 *= intcon;
		}
		else if (!strcmp(op2, "DIV")) {
			num2 /= intcon;
		}

		line = parseWord();
		strcpy(op2, line);
	}

	printSyntax("<项>");

	if (!strcmp(op, "PLUS")) {
		num += num2;
	}
	else if (!strcmp(op, "MINU")) {
		num -= num2;
	}

	strcpy(op, op2);

	if (isOp(line)) {
		printOutput(dcode, dcontent);
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			line = checkExpression(line);
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num2 = intcon;
			line = checkExpression(line);
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
		if (!isSymbol(line[r]))
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
						delayedOutput("STRCON", tempstr);
						strcpy(tempstr, "\0");
						return ("STRCON");
					}
				}

				else if (!strcmp(checkSym(line[r - 1]), "QUOTE") && str != 0) return ("QUOTE");

				else if (!strcmp(checkSym(line[r - 1]), "ASSIGN") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					delayedOutput("EQL", "==");
					return ("EQL");
				}

				else if (!strcmp(checkSym(line[r - 1]), "GRE") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					delayedOutput("GEQ", ">=");
					return ("GEQ");
				}
				else if (!strcmp(checkSym(line[r - 1]), "LSS") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					delayedOutput("LEQ", "<=");
					return ("LEQ");
				}
				else if (!strcmp(checkSym(line[r - 1]), "EXCLAM") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					delayedOutput("NEQ", "!=");
					return ("NEQ");
				}

				else if (!strcmp(checkSym(line[r - 1]), "APOSTROPHE") && isChar(line[r]) && !strcmp(checkSym(line[r + 1]), "APOSTROPHE")) {
					delayedOutput("CHARCON", toString(line[r]));
					r += 2;
					l = r;
					return ("CHARCON");
				}

				else if (isspace(line[r - 1]) || line[r - 1] == '\0');

				else {
					delayedOutput(checkSym(line[r - 1]), toString(line[r - 1]));
					return (checkSym(line[r - 1]));
				}
			}
		}

		else if ((isSymbol(line[r]) && l != r) || (r == len && l != r)) {
			subStr = subString(line, l, r - 1);

			l = r;

			if (str > 0) strcat(tempstr, subStr);

			else {
				if (!strcmp(checkWord(subStr), "OTHERS")) {
					if (isIden(subStr) && !isSymbol(line[r - 1])) {
						delayedOutput("IDENFR", subStr);

						if (line[r] == '[' && assign) {
							printOutput(dcode, dcontent);
							parseWord();
							printOutput(dcode, dcontent);
							if (!strcmp(checkExpression(parseWord()), "RBRACK")) {
								printSyntax("<表达式>");
								printOutput(dcode, dcontent);
							}
						}

						else if (line[r] == '(' && assign) {
							strcpy(funcname, subStr);
							if (valtab[findId()].valfunc) {
								printOutput(dcode, dcontent);
								parseWord();
								printOutput(dcode, dcontent);
								if (!strcmp(checkFuncCall(parseWord()), "RPARENT")) {
									printOutput(dcode, dcontent);
									printSyntax("<有返回值函数调用语句>");
								}
							}
							else {
								parseWord();
								checkFuncCall(parseWord());
								printOutput(dcode, dcontent);
							}
						}

						return ("IDENFR");
					}
					else if (isInt(subStr)) {
						delayedOutput("INTCON", subStr);
						intcon = atoi(subStr);

						return ("INTCON");
					}
				}
				else {
					delayedOutput(checkWord(subStr), subStr);
					return (checkWord(subStr));
				}
			}
		}
	}

	if (r > len && fgets(line, 100, fi) != NULL) {
		l = r = 0;
		return (parseWord());
	}
	else return("EOF");

	return ("\0");
}

void parse(char* line)
{
	if (!strcmp(line, "CONSTTK")) {
		while (!strcmp(line, "CONSTTK")) {
			printOutput(dcode, dcontent);
			line = parseWord();
			if (isType(line)) {
				printOutput(dcode, dcontent);
				checkConst(parseWord(), line);
			}
			line = parseWord();
		}
		printSyntax("<常量说明>");
	}

	if (isType(line)) {
		while (isType(line)) {
			strcpy(dcode3, dcode);
			strcpy(dcontent3, dcontent);
			normal = false;
			checkVar(parseWord(), line);
			line = parseWord();
		}
	}

	if (!strcmp(line, "VOIDTK")) {
		if (hasvar) {
			printSyntax("<变量说明>");
			hasvar = false;
		}
		while ((!strcmp(line, "VOIDTK") || isType(line)) && !mainFunc) {
			printOutput(dcode, dcontent);
			if (!strcmp(line, "VOIDTK")) valfunc = false;
			else valfunc = true;
			checkFunc(parseWord());
			line = parseWord();
		}
	}

	return;
}

void printOutput(char* code, char* content)
{
	if (strcmp(code, "\0"))
		fprintf(fo, "%s %s\n", code, content);

	if (!strcmp(code, dcode3) && !strcmp(content, dcontent3)) {
		strcpy(dcode3, "\0");
		strcpy(dcontent3, "\0");
	}
	if (!strcmp(code, dcode2) && !strcmp(content, dcontent2)) {
		strcpy(dcode2, "\0");
		strcpy(dcontent2, "\0");
	}
	if (!strcmp(code, dcode) && !strcmp(content, dcontent)) {
		strcpy(dcode, "\0");
		strcpy(dcontent, "\0");
	}

	return;
}

void printSyntax(char* content)
{
	fprintf(fo, "%s\n", content);

	return;
}

int main() {
	if ((fi = fopen("testfile.txt", "r")) == NULL || (fo = fopen("output.txt", "w")) == NULL)
	{
		printf("Error opening file!");
		return(-1);
	}

	fgets(line, 100, fi);
	parse(parseWord());

	printSyntax("<程序>");

	fclose(fi);
	fclose(fo);

	return 0;
}