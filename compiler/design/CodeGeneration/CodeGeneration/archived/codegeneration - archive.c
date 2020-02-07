#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

FILE* fi, * fo;
size_t templen;
bool arr = false, delay = false, tempExp = false, ret = false, arraysize = false, hasvar = false, mainFunc = false, neg = false, assign = false, valfunc = true, idenvar = false;
int id = -1, varnum = 0, paramnum = 0, newline = 0, lc = 1, l = 0, r = 0, len = 0, str = 0, num = 0, num2 = 0, intcon = 0, layer = 0, funccounter = 0, valcounter = 0;
int funcid[10], fid = 0, idenid[10], iid = 0, intExp[10], iei = 0, regnum = 0;
char* subStr, *assigniden, tempstr[100], charval[2], arrlimit[10], line[200], chstr[2], op[5] = "PLUS", op2[5] = "\0", funcname[20] = "\0", functype[10] = "\0", idenname[20] = "\0", identype[10] = "\0";
char* countval, * countval2, * countop, * relatop;

int findId();
int findParam(int i, int layer);
int findFunc();
void errorOut(int errnum);

char* toString(char ch);
char* checkSym(char ch);
bool isSymbol(char ch);
char* checkWord(char* line);
bool isRelat(char* line);
bool isConstVal(char* line);
bool isType(char* line);
bool isInt(char* line);
bool isIden(char* line);
bool isChar(char ch);
char* isString(char* line);

char* checkConst(char* line, char* type);
char* checkVar(char* line, char* type);
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

void printError(char* code);

struct functable {
	char name[30];
	char functype[10];
	bool valfunc;
	int paramnum;
	int varnum;
	struct paramtable {
		char name[30];
		char paramtype[10];
	}params[10];
}functab[100];

struct valtable {
	char name[30];
	char identype[10];
	char val[30];
	int funclayer;
	bool neg;
	bool idenvar;
	bool arr;
	int arrlimit;
}valtab[100];

struct opcode {
	int f; //Function codenum
	int d; //Destination addr
	int s; //Source 1
	int t; //Source 2
}mips[1000];

char* toString(char ch)
{
	chstr[0] = ch;
	chstr[1] = '\0';

	return chstr;
}

void storeFunc(char* name)
{
	int i;

	for (i = 0; i < funccounter; i++) {
		if (!strcmp(functab[i].name, name)) {
			errorOut(2);
			return;
		}
	}

	strcpy(functab[funccounter].name, name);
	strcpy(functab[funccounter].functype, identype);
	functab[funccounter].valfunc = valfunc;

	//funccounter++;

	return;
}

void storeVal(char* name, char* val)
{
	int i;

	for (i = 0; i < valcounter; i++) {
		if (!strcmp(valtab[i].name, name) && valtab[i].funclayer == layer) {
			errorOut(2);
			return;
		}
	}

	strcpy(valtab[valcounter].name, name);
	strcpy(valtab[valcounter].identype, identype);
	valtab[valcounter].idenvar = idenvar;
	valtab[valcounter].funclayer = layer;
	if (!valtab[valcounter].idenvar) strcpy(valtab[valcounter].val, val);
	else valtab[valcounter].arr = arr;

	if (valtab[valcounter].arr) valtab[valcounter].arrlimit = atoi(arrlimit);

	if (!valtab[valcounter].idenvar) {
		if (!strcmp(valtab[i].identype, "CHARTK"))
			printf("const char %s = '%s'\n", valtab[i].name, valtab[i].val);
		else printf("const int %s = %s\n", valtab[i].name, valtab[i].val);
	}
	else {
		if (!strcmp(valtab[i].identype, "CHARTK"))
			printf("var char %s", valtab[i].name);
		else printf("var int %s", valtab[i].name);

		if (valtab[valcounter].arr) printf("[%d]", valtab[valcounter].arrlimit);
		printf("\n");
	}

	valcounter++;
	varnum++;
	arr = false;

	return;
}

void storeParam(char* name, char* type)
{
	if (paramnum > 0) {
		if (findParam(paramnum, funccounter) >= 0) {
			errorOut(2);
			return;
		}
	}

	strcpy(functab[funccounter].params[paramnum].name, name);
	strcpy(functab[funccounter].params[paramnum].paramtype, type);

	paramnum++;
	
	return;
}

int findId()
{
	int i = valcounter;

	while (i >= 0) {
		if ((valtab[i].funclayer == layer || valtab[i].funclayer == 0) && !strcmp(valtab[i].name, idenname))
			break;
		i--;
	}

	return i;
}

int findParam(int i, int layer)
{
	while (i >= 0) {
		if (!strcmp(functab[layer].params[i].name, idenname))
			break;
		i--;
	}

	return i;
}

int findFunc()
{
	int i = funccounter;
	while (i >= 0) {
		if (!strcmp(functab[i].name, funcname))
			break;
		i--;
	}
	return i;
}

void errorOut(int errnum)
{
	switch (errnum) {
	case 1: printError("a"); break; //非法符号或不符合词法
	case 2: printError("b"); break; //名字重定义
	case 3: printError("c"); break; //未定义的名字
	case 4: printError("d"); break; //函数参数个数不匹配
	case 5: printError("e"); break; //函数参数类型不匹配
	case 6: printError("f"); break; //条件判断中出现不合法的类型
	case 7: printError("g"); break; //无返回值的函数存在不匹配的return语句
	case 8: printError("h"); break; //有返回值的函数缺少return语句或存在不匹配的return语句
	case 9: printError("i"); break; //数组元素的下标只能是整型表达式
	case 10: printError("j"); break; //不能改变常量的值
	case 11: printError("k"); break; //应为分号
	case 12: printError("l"); break; //应为右小括号’)’
	case 13: printError("m"); break; //应为右中括号’]’
	case 14: printError("n"); break; //do-while语句中缺少while
	case 15: printError("o"); break; //常量定义中=后面只能是整型或字符型常量
	}
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
	if (ch == ';' || ch == ',' || ch == '=' || ch == '(' ||
		ch == ')' || ch == '[' || ch == ']' || ch == '{' ||
		ch == '}' || ch == '/' || ch == '*' || ch == '-' ||
		ch == '+' || ch == '>' || ch == '<' || ch == '"' ||
		ch == '\'' || ch == '!' || ch == '\0' || ch == ' ' ||
		ch == '\n' || ch == '\t')
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
	if (!strcmp(line, "DIV")) countop = "/";
	else if (!strcmp(line, "MULT")) countop = "*";
	else if (!strcmp(line, "MINU")) countop = "-";
	else if (!strcmp(line, "PLUS")) countop = "+";
	if (!strcmp(line, "DIV") || !strcmp(line, "MULT") || !strcmp(line, "MINU") || !strcmp(line, "PLUS"))
		return (true);
	return (false);
}

bool isRelat(char* line)
{
	if (!strcmp(line, "GEQ")) relatop = ">=";
	else if (!strcmp(line, "EQL")) relatop = "==";
	else if (!strcmp(line, "NEQ")) relatop = "!=";
	else if (!strcmp(line, "GRE")) relatop = ">";
	else if (!strcmp(line, "LEQ")) relatop = "<=";
	else if (!strcmp(line, "LSS")) relatop = "<";
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
		if ((len > 1 && line[0] == '0') || line[i] < '0' || line[i] > '9') {
			return false;
		}

	return true;
}

bool isIden(char* line)
{
	int i;
	if ((line[0] >= 'A' && line[0] <= 'Z') || (line[0] >= 'a' && line[0] <= 'z') || line[0] == '_') {
		for (i = 1; i < strlen(line); i++) {
			if (!(line[i] >= 'A' && line[i] <= 'Z') && !(line[i] >= 'a' && line[i] <= 'z') &&
				!(line[i] >= '0' && line[i] <= '9') && !(line[i] == '_')) {
				return (false);
			}
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

	else errorOut(1);
	
	return (false);
}

char* isString(char* line)
{
	if (!strcmp(line, "QUOTE") && str == 0) {
		str++;
		return isString(parseWord());
	}

	else if (!strcmp(line, "QUOTE") && str != 0) {
		str = 0;
		return (line);
	}

	return (line);
}

//////////////////////////////////SYNTAX CHECK////////////////////////////////////
char* checkConst(char* line, char* type)
{
	idenvar = false;
	strcpy(identype, type);
	if (!strcmp(line, "IDENFR")) {
		strcpy(idenname, subStr);
		newline = 0;
		if (!strcmp(parseWord(), "ASSIGN")) {
			if (!strcmp(type, "INTTK")) {
				newline = 0;
				line = parseWord();
				if (!strcmp(line, "MINU") || !strcmp(line, "PLUS")) {
					newline = 0;
					line = parseWord();
				}
				if (strcmp(line, "INTCON")) errorOut(15);
				else if (!strcmp(line, "INTCON")) storeVal(idenname, subStr);
			}
			else if (!strcmp(type, "CHARTK")) {
				newline = 0;
				line = parseWord();
				if (strcmp(line, "CHARCON")) errorOut(15);
				else if (!strcmp(line, "CHARCON")) storeVal(idenname, charval);
			}
			else errorOut(15);

			newline = 0;
			line = parseWord();

			if (!strcmp(line, "COMMA")) {
				newline = 0;
				line = checkConst(parseWord(), type);
			}
		}
		else errorOut(1);
	}
	else errorOut(1);

	return (line);
}

char* checkVar(char* line, char* type)
{
	idenvar = true;
	strcpy(identype, type);
	if (!strcmp(line, "IDENFR")) {
		strcpy(idenname, subStr);
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			storeFunc(subStr);
			hasvar = false;
			checkFunc(line);
			newline = 0;
			line = parseWord();
			return (line);
		}
		else if (!strcmp(line, "LBRACK")) {
			newline = 0;
			arr = true;
			line = parseWord();
			if (strcmp(line, "INTCON") || intcon <= 0) errorOut(1);
			else strcpy(arrlimit, subStr);
			newline = 0;
			line = parseWord();

			if (strcmp(line, "RBRACK")) errorOut(13);
			else {
				newline = 0;
				line = parseWord();
			}
		}

		if (!strcmp(line, "COMMA")) {
			storeVal(idenname, "\0");
			newline = 0;
			line = checkVar(parseWord(), type);
		}
		else if (!strcmp(line, "SEMICN")) {
			storeVal(idenname, "\0");
			hasvar = true;
		}
		else errorOut(11);

		arr = false;
	}
	else errorOut(1);

	return (line);
}

void checkFunc(char* line)
{
	if (!strcmp(line, "IDENFR") || !strcmp(line, "MAINTK")) {
		if (!strcmp(line, "MAINTK")) mainFunc = true;
		else if (!strcmp(line, "IDENFR")) storeFunc(subStr);
		strcpy(functype, identype);
		newline = 0;
		line = parseWord();
	}

	if (!strcmp(line, "LPARENT")) {
		newline = 0;
		line = parseWord();
		if (isType(line) && !mainFunc) line = checkParam(line);

		if (!strcmp(line, "RPARENT")) {
			functab[funccounter].paramnum = paramnum;

			if (!strcmp(functab[funccounter].functype, "INTTK"))
				printf("int %s()\n", functab[funccounter].name);
			else if (!strcmp(functab[funccounter].functype, "CHARTK"))
				printf("char %s()\n", functab[funccounter].name);
			else if (!strcmp(functab[funccounter].functype, "VOIDTK"))
				printf("void %s()\n", functab[funccounter].name);

			for (int i = 0; i < paramnum; i++) {
				printf("para ");
				if (!strcmp(functab[funccounter].params[i].paramtype, "INTTK"))
					printf("int %s\n", functab[funccounter].params[i].name);
				else printf("char %s\n", functab[funccounter].params[i].name);
			}
			funccounter++;
			paramnum = 0;
			newline = 0;
			line = parseWord();
			if (!strcmp(line, "LBRACE"))
			{
				layer++;
				checkContent(line);
				valfunc = true;
				ret = false;
			}
			else errorOut(1);
		}
		else errorOut(12);
	}
	else errorOut(1);

	return;
}

char* checkParam(char* line)
{
	if (isType(line)) {
		strcpy(identype, line);
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "IDENFR")) {
			strcpy(idenname, subStr);
			storeParam(subStr, identype);
		}
		else errorOut(1);

		newline = 0;
		line = parseWord();
		if (!strcmp(line, "COMMA")) {
			newline = 0;
			line = checkParam(parseWord());
		}
	}

	return (line);
}

void checkContent(char* line)
{
	if (!strcmp(line, "LBRACE")) {
		varnum = 0;
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "CONSTTK")) {
			while (!strcmp(line, "CONSTTK")) {
				newline = 0;
				line = parseWord();
				if (isType(line)) {
					newline = 0;
					line = checkConst(parseWord(), line);
				}
				else errorOut(1);
				newline = 0;
				if (!strcmp(line, "SEMICN")) line = parseWord();
				else errorOut(11);
			}
		}

		if (isType(line)) {
			while (isType(line)) {
				newline = 0;
				line = checkVar(parseWord(), line);
				newline = 0;
				if (!strcmp(line, "SEMICN")) line = parseWord();
			}
		}

		functab[funccounter-1].varnum = varnum;

		if (strcmp(line, "RBRACE")) {
			while (strcmp(line, "RBRACE")) line = checkStatement(line);
		}

		if (!strcmp(line, "RBRACE")) {
			if (valfunc && !ret) {
				newline = 0;
				errorOut(8);
			}
		}
	}

	return;
}

char* checkStatement(char* line)
{
	//Recursive sub-statement
	if (!strcmp(line, "LBRACE")) {
		newline = 0;
		line = parseWord();
		if (strcmp(line, "RBRACE")) {
			while (strcmp(line, "RBRACE")) line = checkStatement(line);
		}

		if (!strcmp(line, "RBRACE")) {
			newline = 0;
			line = parseWord();
		}
	}
	//If-else
	else if (!strcmp(line, "IFTK")) {
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			newline = 0;
			assign = true;
			line = checkCondition(parseWord());
			intExp[iei] = 0;
			assign = false;

			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = checkStatement(parseWord());
				if (!strcmp(line, "ELSETK")) {
					newline = 0;
					line = checkStatement(parseWord());
				}
			}
			else errorOut(12);
		}
		else errorOut(1);
	}
	//Do-While 
	else if (!strcmp(line, "DOTK")) {
		newline = 0;
		line = checkStatement(parseWord());

		if (!strcmp(line, "WHILETK")) {
			newline = 0;
			if (!strcmp(parseWord(), "LPARENT")) {
				newline = 0;
				assign = true;
				line = checkCondition(parseWord());
				intExp[iei] = 0;
				assign = false;
				if (!strcmp(line, "RPARENT")) {
					newline = 0;
					line = parseWord();
				}
				else errorOut(12);
			}
			else errorOut(1);
		}
		else errorOut(14);
	}
	//While
	else if (!strcmp(line, "WHILETK")) {
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			newline = 0;
			assign = true;
			line = checkCondition(parseWord());
			intExp[iei] = 0;
			assign = false;

			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				//this one causes error somehow
				//line = checkStatement(parseWord());
				line = parseWord();
				if (!strcmp(line, "LBRACE")) {
					newline = 0;
					line = parseWord();
					if (strcmp(line, "RBRACE")) {
						while (strcmp(line, "RBRACE")) line = checkStatement(line);
					}
					if (!strcmp(line, "RBRACE")) {
						newline = 0;
						line = parseWord();
					}
				}
				else line = checkStatement(line);
			}
			else errorOut(12);
		}
		else errorOut(1);
	}
	//For
	else if (!strcmp(line, "FORTK")) {
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			newline = 0;
			line = checkForCondition(parseWord());
			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = checkStatement(parseWord());
			}
			else errorOut(12);
		}
		else errorOut(1);
	}
	//Function call && Assignment statement
	else if (!strcmp(line, "IDENFR")) {
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			newline = 0;
			strcpy(funcname, subStr);
			if (findFunc() < 0) {
				errorOut(3);
				while (strcmp(line, "RPARENT") && strcmp(line, "SEMICN")) line = parseWord();
			}
			else {
				funcid[fid++] = findFunc();
				assign = true;
				newline = 0;
				line = checkFuncCall(parseWord());
				intExp[iei] = 0;
				assign = false;
				if (paramnum != functab[funcid[fid - 1]].paramnum) errorOut(4);
				paramnum = 0;
				fid--;
			}
			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = parseWord();
			}
			else errorOut(12);
		}
		else {
			strcpy(idenname, subStr);
			assigniden = subStr;
			if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
			else if (findId() >= 0 && !valtab[findId()].idenvar) errorOut(10);

			if (!strcmp(line, "LBRACK")) {
				idenid[iid++] = findId();
				newline = 0;
				assign = true;
				line = parseWord();
				if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
					newline = 0;
					line = parseWord();
				}
				if (isConstVal(line) || !strcmp(line, "LPARENT")) {
					num = intcon;
					line = checkExpression(line);
					num = num2 = intcon = regnum = 0;
					if (intExp[iei] == 0) errorOut(9);
				}
				else errorOut(1);
				intExp[iei] = 0;
				assign = false;
				iid--;
				if (!strcmp(line, "RBRACK"))
				{
					newline = 0;
					line = parseWord();
				}
				else errorOut(13);
			}
			if (!strcmp(line, "ASSIGN")) {
				line = checkAssign(line);
				printf("%s = t%d\n", assigniden, regnum);
			}
			else errorOut(1);
		}
		if (strcmp(line, "SEMICN")) errorOut(11);
	}
	//Read Statement
	else if (!strcmp(line, "SCANFTK")) {
		newline = 0;
		line = checkRead(parseWord());
		if (strcmp(line, "SEMICN")) errorOut(11);
	}
	//Write Statement
	else if (!strcmp(line, "PRINTFTK")) {
		newline = 0;
		assign = true;
		line = checkWrite(parseWord());
		intExp[iei] = 0;
		assign = false;
		if (strcmp(line, "SEMICN")) errorOut(11);
	}
	//Return Statement
	else if (!strcmp(line, "RETURNTK")) {
		ret = true;
		newline = 0;
		printf("ret");
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			if (!valfunc) errorOut(7);
			newline = 0;
			assign = true;
			line = parseWord();
			if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				newline = 0;
				line = parseWord();
			}
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				num = intcon;
				while (strcmp(line, "RPARENT")) line = checkExpression(line);
				if (intExp[iei] == 0 && !strcmp(functab[layer - 1].functype, "INTTK")) errorOut(8);
				else if (intExp[iei] == 1 && !strcmp(functab[layer - 1].functype, "CHARTK")) errorOut(8);
			}
			else errorOut(1);
			printf(" t%d", regnum);
			num = num2 = intcon = regnum = 0;
			intExp[iei] = 0;
			assign = false;
			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = parseWord();
			}
			else errorOut(12);
		}
		else if (valfunc) errorOut(8);
		if (strcmp(line, "SEMICN")) errorOut(11);
		printf("\n");
	}
	
	//Unexpected symbols
	else if (strcmp(line, "SEMICN") && strcmp(line, "RBRACE")) {
		errorOut(1);
		newline = 0;
		line = parseWord();
	}

	//Statement
	if (!strcmp(line, "SEMICN")) {
		newline = 0;
		line = parseWord();
	}

	if (!strcmp(line, "EOF")) {
		errorOut(1);
		printf("The program is incomplete!\n");
		exit(1);
	}
	else if (!strcmp(line, "VOIDTK") || isType(line)) {
		errorOut(1);
		return(line);
	}
	else return (line);
}

char* checkForCondition(char* line)
{
	if (!strcmp(line, "IDENFR")) {
		strcpy(idenname, subStr);
		if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
		else if (findId() >= 0 && !valtab[findId()].idenvar) errorOut(10);
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "ASSIGN")) {
			line = checkAssign(line);
			if (!strcmp(line, "SEMICN")) {
				newline = 0;
				assign = true;
				line = checkCondition(parseWord());
				intExp[iei] = 0;
				assign = false;
				if (!strcmp(line, "SEMICN")) {
					newline = 0;
					line = checkIncrement(parseWord());
				}
				else errorOut(11);
			}
			else errorOut(11);
		}
		else errorOut(1);
	}
	else errorOut(1);

	return (line);
}

char* checkCondition(char* line)
{
	if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		newline = 0;
		line = parseWord();
	}
	if (isConstVal(line) || !strcmp(line, "LPARENT")) {
		num = intcon;
		line = checkExpression(line);
		if (intExp[iei] == 0) errorOut(6);
		intExp[iei] = 0;
		printf("t%d", regnum);
		num = num2 = intcon = regnum = 0;
	}
	else errorOut(1);

	if (isRelat(line)) {
		printf(" %s ", relatop);
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			newline = 0;
			line = parseWord();
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			line = checkExpression(line);
			if (intExp[iei] == 0) errorOut(6);
			intExp[iei] = 0;
			printf("t%d\n", regnum);
			num = num2 = intcon = regnum = 0;
		}
		else errorOut(1);
	}
	else printf(" == 1\n");

	return (line);
}

char* checkIncrement(char* line)
{
	if (!strcmp(line, "IDENFR")) {
		strcpy(idenname, subStr);
		if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
		else if (findId() >= 0 && !valtab[findId()].idenvar) errorOut(10);
		newline = 0;
		if (!strcmp(parseWord(), "ASSIGN")) {
			newline = 0;
			if (!strcmp(parseWord(), "IDENFR")) {
				strcpy(idenname, subStr);
				if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
				newline = 0;
				line = parseWord();
				if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
					newline = 0;
					if (!strcmp(parseWord(), "INTCON")) {
						newline = 0;
						line = parseWord();
					}
					else errorOut(1);
				}
				else errorOut(1);
			}
			else errorOut(1);
		}
		else errorOut(1);
	}
	else errorOut(1);

	return (line);
}

char* checkFuncCall(char* line)
{
	if (isConstVal(line) || !strcmp(line, "LPARENT") || !strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		while (strcmp(line, "RPARENT")) {
			if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				newline = 0;
				line = parseWord();
			}
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				num = intcon;
				line = checkExpression(line);

				if (!strcmp(functab[funcid[fid - 1]].params[paramnum].paramtype, "INTTK") && intExp[iei] == 0) errorOut(5);
				else if (!strcmp(functab[funcid[fid - 1]].params[paramnum].paramtype, "CHARTK") && intExp[iei] == 1) errorOut(5);
				printf("push t%d\n", regnum - 1);
				paramnum++;
				num = num2 = intcon = regnum = 0;
				intExp[iei] = 0;
				if (!strcmp(line, "COMMA")) {
					newline = 0;
					line = parseWord();
				}
			}
			else errorOut(1);
		}
	}
	else if (strcmp(line, "RPARENT")) errorOut(1);

	printf("call %s\n", funcname);
	return (line);
}

char* checkRead(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		newline = 0;
		line = parseWord();
		while (!strcmp(line, "IDENFR")) {
			strcpy(idenname, subStr);
			if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
			newline = 0;
			line = parseWord();
			if (!strcmp(line, "COMMA")) {
				newline = 0;
				line = parseWord();
			}
			//else if (!strcmp(line, "RPARENT")) break;
			else break;
		}
		if (!strcmp(line, "RPARENT")) {
			newline = 0;
			line = parseWord();
		}
		else errorOut(12);
	}
	else errorOut(1);

	return (line);
}

char* checkWrite(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "STRCON")) {
			newline = 0;
			line = parseWord();
			if (!strcmp(line, "COMMA")) {
				newline = 0;
				num = intcon;
				line = checkExpression(parseWord());
				num = num2 = intcon = regnum = 0;
			}
		}
		else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			num = intcon;
			line = checkExpression(line);
			num = num2 = intcon = regnum = 0;
		}
		else if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			newline = 0;
			line = parseWord();
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				num = intcon;
				line = checkExpression(line);
				num = num2 = intcon = regnum = 0;
			}
			else errorOut(1);
		}
		else errorOut(1);

		if (!strcmp(line, "RPARENT")) {
			newline = 0;
			line = parseWord();
		}
		else errorOut(12);
	}
	else errorOut(1);

	return (line);
}

char* checkAssign(char* line)
{
	newline = 0;
	assign = true;
	line = parseWord();
	if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		newline = 0;
		line = parseWord();
	}
	if (isConstVal(line) || !strcmp(line, "LPARENT")) {
		//num = intcon;
		delay = true;
		line = checkExpression(line);
		num = num2 = intcon = regnum = 0;
	}

	intExp[iei] = 0;
	assign = false;

	return (line);
}

char* checkExpression(char* line)
{
	if (!strcmp(line, "LPARENT")) {
		intExp[iei] = 1;
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			line = parseWord();
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			//num2 = intcon;
			if (isConstVal(line)) countval = subStr;
			while (strcmp(line, "RPARENT")) line = checkExpression(line);
		}

		if (strcmp(line, "RPARENT")) errorOut(12);
	}
	else if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		intExp[iei] = 1;
		line = parseWord();
	}
	if (isConstVal(line)) {
		num2 = intcon;
		countval = subStr;
		printf("%d\n", num2);
	}

	line = parseWord();
	strcpy(op2, line);

	while (!strcmp(op2, "MULT") || !strcmp(op2, "DIV")) {
		if (!strcmp(op2, "MULT")) countop = "*";
		else countop = "/";

		intExp[iei] = 1;
		line = parseWord();

		if (!strcmp(line, "LPARENT")) {
			line = parseWord();
			if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				line = parseWord();
			}
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				//num = intcon;
				while (strcmp(line, "RPARENT")) line = checkExpression(line);
			}

			if (strcmp(line, "RPARENT")) errorOut(12);
		}
		else if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			line = parseWord();
		}
		//if (isConstVal(line)) countval2 = subStr;

		if (!strcmp(op2, "MULT")) {
			printf("MULT %d %d\n", num2, intcon);
			num2 *= intcon;
			printf("MULT %d\n", num2);
		}
		else if (!strcmp(op2, "DIV")) {
			printf("DIV %d %d\n", num2, intcon);
			num2 /= intcon;
		}

		/*printf("t%d = %s %s %s\n", regnum, countval, countop, countval2);
		countval = (toString('t'));
		snprintf(tempstr, sizeof(tempstr), "%d", regnum);
		strcat(countval, tempstr);
		strcpy(tempstr, "\0");
		regnum++;*/
		line = parseWord();
		strcpy(op2, line);
	}

	if (!strcmp(op, "PLUS")) {
		printf("ADD %d %d\n", num, num2);
		num += num2;
	}
	else if (!strcmp(op, "MINU")) {
		printf("SUB %d %d\n", num, num2);
		intExp[iei] = 1;
		num -= num2;
	}
	
	strcpy(op, op2);

	if (isOp(line)) {
		intExp[iei] = 1;
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			line = checkExpression(line);
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			/*printf("t%d = %s %s %s\n", regnum, countval, countop, countval2);
			countval = (toString('t'));
			snprintf(tempstr, sizeof(tempstr), "%d", regnum);
			strcat(countval, tempstr);
			strcpy(tempstr, "\0");
			regnum++;*/
			line = checkExpression(line);
		}
	}

	printf("RESULT: %d\n", num);
	delay = false;
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
	char* temp;
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
					temp = isString("QUOTE");
					if (!strcmp(temp, "QUOTE")) {
						strcpy(tempstr, "\0");
						return ("STRCON");
					}
					else return (temp);
				}

				else if (!strcmp(checkSym(line[r - 1]), "QUOTE") && str != 0) return ("QUOTE");

				else if (!strcmp(checkSym(line[r - 1]), "ASSIGN") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					return ("EQL");
				}
				else if (!strcmp(checkSym(line[r - 1]), "GRE") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					return ("GEQ");
				}
				else if (!strcmp(checkSym(line[r - 1]), "LSS") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					return ("LEQ");
				}
				else if (!strcmp(checkSym(line[r - 1]), "EXCLAM") && !strcmp(checkSym(line[r]), "ASSIGN")) {
					l = ++r;
					return ("NEQ");
				}

				else if (!strcmp(checkSym(line[r - 1]), "APOSTROPHE") && isChar(line[r])) {
					if (!strcmp(checkSym(line[r + 1]), "APOSTROPHE")) {
						countval2 = toString(line[r]);
						strcpy(charval, countval2);
						r += 2;
					}
					else {
						errorOut(1);
						r++;
					}
					l = r;
					return ("CHARCON");
				}

				else if (isspace(line[r - 1]) || line[r - 1] == '\0');

				else return (checkSym(line[r - 1]));
			}
		}

		else if ((isSymbol(line[r]) && l != r) || (r == len && l != r)) {
			subStr = subString(line, l, r - 1);

			l = r;

			if (str > 0) strcat(tempstr, subStr);

			else {
				if (!strcmp(checkWord(subStr), "OTHERS")) {
					if (isIden(subStr) && !isSymbol(line[r - 1])) {
						if (line[r] == '[' && assign) {
							strcpy(idenname, subStr);
							if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) {
								errorOut(3);
								temp = parseWord();
								assign = false;
								while (strcmp(temp, "RBRACK") && strcmp(temp, "SEMICN")) temp = parseWord();
								assign = true;
							}
							else {
								if ((id = findId()) >= 0) {
									if (!strcmp(valtab[id].identype, "INTTK")) intExp[iei] = 1;
									else intExp[iei] = 0;
								}
								else {
									id = findParam(functab[layer - 1].paramnum, layer - 1);
									if (!strcmp(functab[layer - 1].params[id].paramtype, "INTTK")) intExp[iei] = 1;
									else intExp[iei] = 0;
								}
								idenid[iid++] = id;
								parseWord();
								iei++;
								temp = checkExpression(parseWord());
								if (intExp[iei] == 0) errorOut(9);
								intExp[iei] = 0; iei--; iid--;
							}
							if (strcmp(temp, "RBRACK")) {
								errorOut(13);
								return (temp);
							}
						}

						else if (line[r] == '(' && assign) {
							strcpy(funcname, subStr);
							if (findFunc() < 0) {
								errorOut(3);
								temp = parseWord();
								assign = false;
								while (strcmp(temp, "RPARENT")) temp = parseWord();
								assign = true;
							}
							else if (functab[findFunc()].valfunc) {
								funcid[fid++] = findFunc();
								iei++;
								if (!strcmp(functab[funcid[fid - 1]].functype, "INTTK")) intExp[iei] = 1;
								else intExp[iei] = 0;
								parseWord();
								iei++;
								temp = checkFuncCall(parseWord());
								iei--;
								if (paramnum != functab[funcid[fid - 1]].paramnum) errorOut(4);
								paramnum = 0;
								fid--; intExp[iei] = 0; iei--;
								if (strcmp(temp, "RPARENT")) {
									errorOut(12);
									return (temp);
								}
							}
							else {
								parseWord();
								checkFuncCall(parseWord());
							}
						}

						else if (assign) {
							strcpy(idenname, subStr);
							countval2 = subStr;
							if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0);// errorOut(3);
							else {
								if ((id = findId()) >= 0) {
									if (!strcmp(valtab[id].identype, "INTTK")) intExp[iei] = 1;
								}
								else {
									id = findParam(functab[layer - 1].paramnum, layer - 1);
									if (!strcmp(functab[layer - 1].params[id].paramtype, "INTTK")) intExp[iei] = 1;
								}
							}
						}

						return ("IDENFR");
					}
					else if (isInt(subStr)) {
						if (assign) intExp[iei] = 1;
						countval2 = subStr;
						intcon = atoi(subStr);
						return ("INTCON");
					}
				}
				else return (checkWord(subStr));
			}
		}
	}

	if (r > len && fgets(line, 200, fi) != NULL) {
		l = r = 0;
		lc++;
		newline += 1;
		if (str > 0) {
			errorOut(1);
			str = 0;
		}
		return (parseWord());
	}
	else return("EOF");

	return ("\0");
}

void parse(char* line)
{
	int i = 0;

	if (!strcmp(line, "CONSTTK")) {
		while (!strcmp(line, "CONSTTK")) {
			newline = 0;
			line = parseWord();
			if (isType(line)) {
				newline = 0;
				line = checkConst(parseWord(), line);
			}
			else errorOut(1);
			newline = 0;
			if (!strcmp(line, "SEMICN")) line = parseWord();
			else errorOut(11);
		}
	}

	if (isType(line)) {
		while (isType(line)) {
			newline = 0;
			line = checkVar(parseWord(), line);
			newline = 0;
			if (!strcmp(line, "SEMICN")) line = parseWord();
		}
	}

	if (!strcmp(line, "VOIDTK")) {
		while ((!strcmp(line, "VOIDTK") || isType(line)) && !mainFunc) {
			if (!strcmp(line, "VOIDTK")) valfunc = false;
			else valfunc = true;
			strcpy(identype, line);
			newline = 0;
			checkFunc(parseWord());
			newline = 0;
			line = parseWord();
		}
	}

	return;
}

void printError(char* code)
{
	fprintf(fo, "%d %s\n", lc - newline, code);

	if(str == 0) newline = 0;

	return;
}

int main() {
	if ((fi = fopen("testfile.txt", "r")) == NULL || (fo = fopen("error.txt", "w")) == NULL)
	{
		printf("Error opening file!");
		return(-1);
	}

	fgets(line, 200, fi);
	parse(parseWord());

	fclose(fi);
	fclose(fo);

	return 0;
}