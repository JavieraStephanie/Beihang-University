#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

FILE* fi, * fo, * fm;
size_t templen;
bool nostore = false, arr = false, func = false, expimm = true, resimm = false, arrimm = false, imm = false, ret = false, arraysize = false, hasvar = false, mainFunc = false, neg = false, negExp = false, assign = false, valfunc = true, idenvar = false;
int id = -1, varnum = 0, paramnum = 0, newline = 0, lc = 1, l = 0, r = 0, len = 0, str = 0, num = 0, intcon = 0, layer = 0, funccounter = 0, valcounter = 0;
int funcid[10], fid = 0, idenid[10], iid = 0, intExp[10], iei = 0, regholder = 0, regnum = 0, vreg = 0, stacknum = 0, labelnum = 0, arrreg = 0;
int increid = 0, increnum = 0, increop = 0;
char* subStr, assigniden[30], tempstr[100], stringval[100], charval[2], arrlimit[10], lineo[200], chstr[2], op[5] = "PLUS", op2[5] = "\0", funcname[20] = "\0", functype[10] = "\0", idenname[50] = "\0", identype[10] = "\0";
char* expline, countop[5], relatop[3], countval[30], cond[30], init[30], incre[30], increreg[5];

//MIPS DATA COUNTER
bool syscall = false, iscond = false, func1 = false, funcdelay = false, increparam = false, increlocal = false, localid = false;
int strnum = 0, datac = 0, datac2 = 0, datac3 = 0, datac4 = 0, codecounter = 0, maincounter = 0, vars = 0, arrId = 0, condcounter = 0, condstart = 0;
char mipsCode[1000][100], mainCode[1000][100], dataAddr[10], curType[10], curIndex[20];
char d[30], s[30], t[30], cond1[30], cond2[30], condstring[1000][200], assignreg[30];

int findId();
int findLocalId();
int findParam(int i, int layer);
int findFunc();
void getReg(char* val, char* type);
void errorOut(int errnum);
void storeData(char* name, int type, int datatype, char* content);
void storeCode(char* code, char* d, char* s, char* t);
void storeCode2(char* code, char* d, char* s);
void storeCode3(char* code, char* d);
void storeCode4(char* code);
char* reverseRelat(char* relatop);
void makeBranch(char* cond1, char* relatop, char* cond2, char* label, int condcounter, int condstart);

char* dataType(int id);
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
char* checkAssign(char* line, int tempid, bool isparam, bool localid, char* arrindex);
int checkExpression(char* line);
int checkTerm(char* line);
int checkFactor(char* line);

char* subString(char* str, int left, int right);
char* parseWord();
void parse(char* line);

void printError(char* code);
void printCode(char* code, char* d, char* s, char* t);
void printCode2(char* code, char* d, char* s);

struct valtable {
	char name[30];
	char identype[10];
	char val[30];
	int funclayer;
	int addr;
	bool neg;
	bool idenvar;
	bool arr;
	int arrlimit;
}valtab[100];

struct functable {
	char name[30];
	char functype[10];
	bool valfunc;
	int paramnum;
	int constnum;
	int varnum;
	int arrtotal;
	int labelnum;
	struct valtable vars[20];
	struct paramtable {
		char name[30];
		char paramtype[10];
	}params[10];
}functab[25];

struct mipsData {
	char name[30];
	int type;
	int datatype;
	char content[100];
}mipsData[25], mipsData2[25], mipsData3[25], mipsData4[25];

char* toString(char ch)
{
	chstr[0] = ch;
	chstr[1] = '\0';

	return chstr;
}

int getRegnumMin1()
{
	if ((regnum - 1) == -1) return 9;
	else return (regnum - 1);
}

int getRegnumS(int x)
{
	if (x >= 6) return 0;

	return x;
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
	functab[funccounter].labelnum = ++labelnum;

	return;
}

void storeVal(char* name, char* val)
{
	int i;
	char tempname[50];

	for (i = 0; i < valcounter; i++) {
		if (!strcmp(valtab[i].name, name) && valtab[i].funclayer == layer) {
			errorOut(2);
			return;
		}
	}

	if (!nostore) {
		strcpy(valtab[valcounter].name, name);
		strcpy(valtab[valcounter].identype, identype);
		valtab[valcounter].idenvar = idenvar;
		valtab[valcounter].funclayer = layer;
		if (!valtab[valcounter].idenvar) strcpy(valtab[valcounter].val, val);
		else valtab[valcounter].arr = arr;

		if (valtab[valcounter].arr) valtab[valcounter].arrlimit = atoi(arrlimit);

		if (!valtab[valcounter].idenvar) {
			snprintf(tempname, sizeof(tempname), "%sloc%d", name, layer);
			strcpy(valtab[valcounter].name, tempname);
			if (!strcmp(valtab[valcounter].identype, "CHARTK")) {
				fprintf(fm, "const char %s = '%s'\n", valtab[valcounter].name, valtab[valcounter].val);
				strcpy(tempstr, "\0");
				snprintf(tempstr, sizeof(tempstr), "'%s'", valtab[valcounter].val);
				storeData(tempname, 5, 1, tempstr);
			}
			else {
				fprintf(fm, "const int %s = %s\n", valtab[valcounter].name, valtab[valcounter].val);
				if (neg) {
					snprintf(tempstr, sizeof(tempstr), "-%s", valtab[valcounter].val);
					storeData(tempname, 2, 0, tempstr);
				}
				else storeData(tempname, 2, 0, valtab[valcounter].val);
			}
		}
		else {
			if (valtab[valcounter].arr) {
				snprintf(tempname, sizeof(tempname), "%slocarr%d", name, layer);
				strcpy(valtab[valcounter].name, tempname);
				fprintf(fm, "[%d]", valtab[valcounter].arrlimit);
				strcpy(tempstr, "\0");
				if (!strcmp(valtab[valcounter].identype, "CHARTK")) {
					snprintf(tempstr, sizeof(tempstr), "%d", valtab[valcounter].arrlimit);
					storeData(valtab[valcounter].name, 8, 1, tempstr);
				}
				else {
					snprintf(tempstr, sizeof(tempstr), "%d", valtab[valcounter].arrlimit * 4);
					storeData(valtab[valcounter].name, 8, 0, tempstr);
				}
			}
			else {
				if (!strcmp(valtab[valcounter].identype, "CHARTK")) {
					fprintf(fm, "var char %s", valtab[valcounter].name);
					if (!arr) {
						valtab[valcounter].addr = vars;
						vars += 4;
					}
				}
				else {
					fprintf(fm, "var int %s", valtab[valcounter].name);
					if (!arr) {
						valtab[valcounter].addr = vars;
						vars += 4;
					}
				}
			}
			fprintf(fm, "\n");
		}

		valcounter++;
	}

	else {
		//if (idenvar) functab[layer - 1].vars[varnum].arr = arr;

		//TEMPORARY, MUST CHANGE
		if (arr) {
			snprintf(tempname, sizeof(tempname), "%slocarr%d", name, layer);
			strcpy(valtab[valcounter].name, tempname);
			strcpy(valtab[valcounter].identype, identype);
			valtab[valcounter].idenvar = idenvar;
			valtab[valcounter].funclayer = layer;

			valtab[valcounter].arr = arr;
			valtab[valcounter].arrlimit = atoi(arrlimit);

			strcpy(tempstr, "\0");
			if (!strcmp(valtab[valcounter].identype, "CHARTK")) {
				snprintf(tempstr, sizeof(tempstr), "%d", valtab[valcounter].arrlimit);
				storeData(valtab[valcounter].name, 8, 1, tempstr);
			}
			else {
				snprintf(tempstr, sizeof(tempstr), "%d", valtab[valcounter].arrlimit * 4);
				storeData(valtab[valcounter].name, 8, 0, tempstr);
			}
			valcounter++;

		}
		else {
			strcpy(functab[layer - 1].vars[varnum].name, name);
			strcpy(functab[layer - 1].vars[varnum].identype, identype);
			functab[layer - 1].vars[varnum].idenvar = idenvar;
			functab[layer - 1].vars[varnum].funclayer = layer;
		}
	}

	varnum++;
	arr = neg = false;

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
	int i;
	char tempname[50], tempname2[50], arrname[50], arrname2[50];
	
	i = findLocalId();
	
	if (i == -1) {
		i = valcounter;

		snprintf(tempname, sizeof(tempname), "%sloc%d", idenname, layer); snprintf(tempname2, sizeof(tempname2), "%sloc0", idenname);
		snprintf(arrname, sizeof(arrname), "%slocarr%d", idenname, layer); snprintf(arrname2, sizeof(arrname2), "%slocarr0", idenname);
		while (i >= 0) {
			if ((valtab[i].funclayer == layer || valtab[i].funclayer == 0) &&
				(!strcmp(valtab[i].name, idenname) || !strcmp(valtab[i].name, tempname) || !strcmp(valtab[i].name, tempname2) ||
				 !strcmp(valtab[i].name, arrname) || !strcmp(valtab[i].name, arrname2)))
				break;
			i--;
		}
		localid = false;
	}

	return i;
}

int findLocalId()
{
	int i = functab[layer - 1].varnum;

	while (i >= 0) {
		if (!strcmp(functab[layer - 1].vars[i].name, idenname))
			break;
		i--;
	}

	localid = true;

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

void getReg(char* val, char* type)
{
	int tempid, tempparam;
	char d[30], s[30], t[30];

	fprintf(fm, "$t%d = %s\n", regnum, val);

	if (syscall) snprintf(d, sizeof(d), "$a0");
	else snprintf(d, sizeof(d), "$t%d", regnum);

	if (!strcmp(type, "IDENFR")) {
		strcpy(idenname, val);
		if ((tempparam = findParam(functab[layer - 1].paramnum, layer - 1)) >= 0) {
			snprintf(t, sizeof(t), "%d($sp)", (tempparam + 2) * 4);
			storeCode2("lw", d, t);

		}
		else if ((tempid = findId()) >= 0) {
			if (localid) {
				localid = false;
				if (!functab[layer - 1].vars[tempid].arr) {
					snprintf(t, sizeof(t), "%d($sp)", (functab[layer - 1].paramnum + tempid + 2) * 4);
					storeCode2("lw", d, t);
				}
			}
			else {
				if (valtab[tempid].idenvar) {
					if (!valtab[tempid].arr) {
						snprintf(tempstr, sizeof(tempstr), "%d", valtab[tempid].addr);
						storeCode("addi", "$s7", "$0", tempstr);
						if (!strcmp(valtab[tempid].identype, "CHARTK")) storeCode2("lb", d, "vars($s7)");
						else storeCode2("lw", d, "vars($s7)");
					}
					else {
					}
				}
				else {
					if (!strcmp(valtab[tempid].identype, "CHARTK")) storeCode2("lb", d, valtab[tempid].name);
					else storeCode2("lw", d, valtab[tempid].name);
				}
			}
		}
	}
	else {
		if (!strcmp(type, "CHARTK")) snprintf(t, sizeof(t), "%d", charval[0]);
		else snprintf(t, sizeof(t), "%d", atoi(val));
		storeCode("addi", d, "$0", t);
	}

	if (regnum == 9) regnum = 0;
	else regnum++;
	syscall = false;
	return;
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

void storeData(char* name, int type, int datatype, char* content)
{
	if (type == 2) {
		strcpy(mipsData[datac].name, name);
		mipsData[datac].type = type;
		mipsData[datac].datatype = datatype;
		strcpy(mipsData[datac].content, content);
		datac++;
	}
	else if (type == 4) {
		strcpy(mipsData2[datac2].name, name);
		mipsData2[datac2].type = type;
		mipsData2[datac2].datatype = datatype;
		strcpy(mipsData2[datac2].content, content);
		datac2++;
	}
	else if (type == 5) {
		strcpy(mipsData3[datac3].name, name);
		mipsData3[datac3].type = type;
		mipsData3[datac3].datatype = datatype;
		strcpy(mipsData3[datac3].content, content);
		datac3++;
	}
	else if (type == 8) {
		strcpy(mipsData4[datac4].name, name);
		mipsData4[datac4].type = type;
		mipsData4[datac4].datatype = datatype;
		strcpy(mipsData4[datac4].content, content);
		datac4++;
	}
	return;
}

void storeCode(char* code, char* d, char* s, char* t)
{
	char temp[200];
	snprintf(temp, sizeof(temp), "%s %s, %s, %s", code, d, s, t);

	if (iscond) strcpy(condstring[condcounter++], temp);
	else {
		if (mainFunc) strcpy(mainCode[maincounter++], temp);
		else strcpy(mipsCode[codecounter++], temp);
	}

	return;
}

void storeCode2(char* code, char* d, char* s)
{
	char temp[200];
	snprintf(temp, sizeof(temp), "%s %s, %s", code, d, s);

	if (iscond) strcpy(condstring[condcounter++], temp);
	else {
		if (mainFunc) strcpy(mainCode[maincounter++], temp);
		else strcpy(mipsCode[codecounter++], temp);
	}

	return;
}

void storeCode3(char* code, char* d)
{
	char temp[200];
	snprintf(temp, sizeof(temp), "%s %s", code, d);

	if (iscond) strcpy(condstring[condcounter++], temp);
	else {
		if (mainFunc) strcpy(mainCode[maincounter++], temp);
		else strcpy(mipsCode[codecounter++], temp);
	}

	return;
}

void storeCode4(char* code)
{
	char temp[200];
	snprintf(temp, sizeof(temp), "%s", code);

	if (iscond) strcpy(condstring[condcounter++], temp);
	else {
		if (mainFunc) strcpy(mainCode[maincounter++], temp);
		else strcpy(mipsCode[codecounter++], temp);
	}

	return;
}

char* reverseRelat(char* relatop) {
	if (!strcmp(relatop, "==")) strcpy(relatop, "!=");
	else if (!strcmp(relatop, "!=")) strcpy(relatop, "==");
	else if (!strcmp(relatop, "<")) strcpy(relatop, ">=");
	else if (!strcmp(relatop, ">")) strcpy(relatop, "<=");
	else if (!strcmp(relatop, "<=")) strcpy(relatop, ">");
	else if (!strcmp(relatop, ">=")) strcpy(relatop, "<");

	return (relatop);
}

void makeBranch(char* cond1, char* relatop, char* cond2, char* label, int condcounter, int condstart)
{
	for (int i = condstart; i < condcounter; i++) {
		storeCode4(condstring[i]);
	}
	if (!strcmp(relatop, "==")) storeCode("beq", cond1, cond2, label);
	else if (!strcmp(relatop, "!=")) storeCode("bne", cond1, cond2, label);
	else if (!strcmp(relatop, "<")) storeCode("blt", cond1, cond2, label);
	else if (!strcmp(relatop, ">")) storeCode("bgt", cond1, cond2, label);
	else if (!strcmp(relatop, "<=")) storeCode("ble", cond1, cond2, label);
	else if (!strcmp(relatop, ">=")) storeCode("bge", cond1, cond2, label);
	return;
}

char* dataType(int id)
{
	switch (id) {
	case 0: return (".data");
	case 1: return (".text");
	case 2: return (".word");
	case 3: return (".ascii");
	case 4: return (".asciiz");
	case 5: return (".byte");
	case 6: return (".align");
	case 7: return (".half");
	case 8: return (".space");
	case 9: return (".double");
	case 10: return (".float");
	}
	return ("\0");
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
	if (ch == '!' || ch == '(' || ch == ')' || ch == '*' ||
		ch == '+' || ch == ',' || ch == '-' || ch == '/' ||
		ch == ';' || ch == '<' || ch == '=' || ch == '>' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
		ch == '"' || ch == '\''|| ch == '\0'|| ch == ' ' ||
		ch == '\n'|| ch == '\t')
		return (true);
	else if (ch == '#' || ch == '$' || ch == '%' || ch == '&' ||
			 ch == '.' || ch == ':' || ch == '?' || ch == '@' ||
			 ch == '\\'|| ch == '^' || ch == '`' || ch == '|' ||
			 ch == '~')
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
	if (!strcmp(line, "DIV") || !strcmp(line, "MULT") || !strcmp(line, "MINU") || !strcmp(line, "PLUS")) {
		strcpy(countop, line);
		return (true);
	}

	strcpy(countop, "\0");
	return (false);
}

bool isRelat(char* line)
{
	if (!strcmp(line, "GEQ")) strcpy(relatop, ">=");
	else if (!strcmp(line, "EQL")) strcpy(relatop, "==");
	else if (!strcmp(line, "NEQ")) strcpy(relatop, "!=");
	else if (!strcmp(line, "GRE")) strcpy(relatop, ">");
	else if (!strcmp(line, "LEQ")) strcpy(relatop, "<=");
	else if (!strcmp(line, "LSS")) strcpy(relatop, "<");
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
					if (!strcmp(line, "MINU")) neg = true;
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
				fprintf(fm, "int %s()\n", functab[funccounter].name);
			else if (!strcmp(functab[funccounter].functype, "CHARTK"))
				fprintf(fm, "char %s()\n", functab[funccounter].name);
			else if (!strcmp(functab[funccounter].functype, "VOIDTK"))
				fprintf(fm, "void %s()\n", functab[funccounter].name);

			for (int i = 0; i < paramnum; i++) {
				fprintf(fm, "para ");
				if (!strcmp(functab[funccounter].params[i].paramtype, "INTTK"))
					fprintf(fm, "int %s\n", functab[funccounter].params[i].name);
				else fprintf(fm, "char %s\n", functab[funccounter].params[i].name);
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
		else if (strcmp(line, "RPARENT")) errorOut(1);
	}
	else errorOut(1);

	return (line);
}

void checkContent(char* line)
{
	if (mainFunc) {
		fprintf(fm, "main :\n");
		storeCode4("main :");
	}
	else {
		fprintf(fm, "Label %d :\n", functab[funccounter - 1].labelnum);
		snprintf(d, sizeof(d), "LABEL%d:", functab[funccounter - 1].labelnum);
		storeCode4(d);
	}
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

		functab[funccounter - 1].constnum = varnum; varnum = 0;

		if (isType(line)) {
			nostore = true;
			while (isType(line)) {
				newline = 0;
				line = checkVar(parseWord(), line);
				newline = 0;
				if (!strcmp(line, "SEMICN")) line = parseWord();
			}
		}

		functab[funccounter - 1].varnum = varnum; nostore = false;

		storeCode("addi", "$sp", "$sp", "-8");
		snprintf(t, sizeof(t), "-%d", (functab[funccounter - 1].varnum) * 4);
		storeCode("addi", "$sp", "$sp", t);

		if (!mainFunc) {
			snprintf(t, sizeof(t), "-%d", functab[funccounter - 1].paramnum * 4);
			storeCode("addi", "$sp", "$sp", t);

			for (int i = functab[funccounter - 1].paramnum; i > 0; i--) {
				snprintf(s, sizeof(s), "$s%d", i - 1);
				snprintf(d, sizeof(d), "%d($sp)", (i + 1) * 4);
				storeCode2("sw", s, d);
			}
			storeCode2("sw", "$ra", "4($sp)");
		}

		if (strcmp(line, "RBRACE")) {
			while (strcmp(line, "RBRACE")) line = checkStatement(line);
		}

		if (!strcmp(line, "RBRACE")) {
			if (valfunc && !ret) {
				newline = 0;
				errorOut(8);
			}
			else if (!mainFunc && !valfunc && !ret) {

				for (int i = functab[layer - 1].paramnum; i > 0; i--) {
					snprintf(s, sizeof(s), "$s%d", i - 1);
					snprintf(d, sizeof(d), "%d($sp)", (i + 1) * 4);
					storeCode2("lw", s, d);
				}
				storeCode2("lw", "$ra", "4($sp)");

				snprintf(t, sizeof(t), "%d", (functab[layer - 1].varnum) * 4);
				storeCode("addi", "$sp", "$sp", t);

				snprintf(t, sizeof(t), "%d", (functab[layer - 1].paramnum + 2) * 4);
				storeCode("addi", "$sp", "$sp", t);

				storeCode3("jr", "$ra");
			}
			else if (mainFunc) storeCode("addi", "$sp", "$sp", "8");
		}
	}

	return;
}

char* checkStatement(char* line)
{
	char temprelatop[5], increment[30], arrindex[5], tempcond1[30], tempcond2[30], increiden[30];
	int label, nextlabel, newlinelabel, elselabel, tempid, tempcondcounter, tempcondstart, tempincreid, tempincrenum, tempincreop;
	bool isparam = false, tempincreparam = false, templocalid = false, tempincrelocal = false;
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
		label = ++labelnum;
		nextlabel = label + 1;
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			newline = 0;
			assign = true;
			line = checkCondition(parseWord());
			strcpy(temprelatop, relatop); strcpy(tempcond1, cond1); strcpy(tempcond2, cond2);
			tempcondcounter = condcounter; tempcondstart = condstart;
			intExp[iei] = 0;
			assign = false;

			fprintf(fm, "%s\n", temprelatop);
			fprintf(fm, "BZ LABEL %d\n", nextlabel);
			snprintf(tempstr, sizeof(tempstr), "LABEL%d", nextlabel);
			makeBranch(tempcond1, reverseRelat(temprelatop), tempcond2, tempstr, tempcondcounter, tempcondstart);
			newlinelabel = ++labelnum;

			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = checkStatement(parseWord());
				if (!strcmp(line, "ELSETK")) {
					nextlabel = newlinelabel + 1;
					fprintf(fm, "GOTO LABEL %d\n", nextlabel);
					snprintf(d, sizeof(d), "LABEL%d", nextlabel);
					storeCode3("b", d);
					newline = 0;
					fprintf(fm, "Label %d :\n", newlinelabel);
					snprintf(d, sizeof(d), "LABEL%d:", newlinelabel);
					storeCode4(d);
					elselabel = ++labelnum;
					line = checkStatement(parseWord());
				}
				fprintf(fm, "GOTO LABEL %d\n", nextlabel);
				snprintf(d, sizeof(d), "LABEL%d", nextlabel);
				storeCode3("b", d);
				fprintf(fm, "Label %d :\n", nextlabel);
				snprintf(d, sizeof(d), "LABEL%d:", nextlabel);
				storeCode4(d);
			}
			else errorOut(12);
		}
		else errorOut(1);
		ret = false;
	}
	//Do-While 
	else if (!strcmp(line, "DOTK")) {
		newline = 0;
		label = ++labelnum;
		fprintf(fm, "Label %d :\n", label);
		snprintf(d, sizeof(d), "LABEL%d:", label);
		storeCode4(d);
		line = checkStatement(parseWord());

		if (!strcmp(line, "WHILETK")) {
			newline = 0;
			if (!strcmp(parseWord(), "LPARENT")) {
				newline = 0;
				assign = true;
				line = checkCondition(parseWord());
				strcpy(temprelatop, relatop); strcpy(tempcond1, cond1); strcpy(tempcond2, cond2);
				tempcondcounter = condcounter; tempcondstart = condstart;
				intExp[iei] = 0;
				assign = false;
				if (!strcmp(line, "RPARENT")) {
					newline = 0;
					line = parseWord();
				}
				else errorOut(12);
				fprintf(fm, "%s\n", temprelatop);
				fprintf(fm, "BNZ LABEL %d\n", label);
				snprintf(tempstr, sizeof(tempstr), "LABEL%d", label);
				makeBranch(tempcond1, temprelatop, tempcond2, tempstr, tempcondcounter, tempcondstart);
			}
			else errorOut(1);
		}
		else errorOut(14);
		ret = false;
	}
	//While
	else if (!strcmp(line, "WHILETK")) {
		label = ++labelnum;
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			newline = 0;
			assign = true;
			line = checkCondition(parseWord());
			strcpy(temprelatop, relatop); strcpy(tempcond1, cond1); strcpy(tempcond2, cond2);
			tempcondcounter = condcounter; tempcondstart = condstart;
			fprintf(fm, "Label %d :\n", label);
			snprintf(d, sizeof(d), "LABEL%d", label);
			storeCode3("b", d);
			intExp[iei] = 0;
			assign = false;

			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = parseWord();
				nextlabel = ++labelnum;
				fprintf(fm, "Label %d :\n", nextlabel);
				snprintf(d, sizeof(d), "LABEL%d:", nextlabel);
				storeCode4(d);
				//Print Label
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
				fprintf(fm, "Label %d :\n", label);
				snprintf(d, sizeof(d), "LABEL%d:", label);
				storeCode4(d);
				//Print Label
				fprintf(fm, "%s\n", temprelatop);
				fprintf(fm, "BNZ LABEL %d\n", label + 1);
				snprintf(tempstr, sizeof(tempstr), "LABEL%d", label + 1);
				makeBranch(tempcond1, temprelatop, tempcond2, tempstr, tempcondcounter, tempcondstart);
				labelnum++;
			}
			else errorOut(12);
		}
		else errorOut(1);
		ret = false;
	}
	//For
	else if (!strcmp(line, "FORTK")) {

		label = ++labelnum;
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			newline = 0;
			line = checkForCondition(parseWord());
			fprintf(fm, "%s\n", init);
			strcpy(temprelatop, relatop); strcpy(tempcond1, cond1); strcpy(tempcond2, cond2);
			strcpy(increment, incre); tempincreop = increop;  tempincreid = increid; tempincreparam = increparam; tempincrenum = increnum; tempincrelocal = increlocal;
			tempcondcounter = condcounter; tempcondstart = condstart;
			fprintf(fm, "GOTO LABEL %d\n", label);
			snprintf(d, sizeof(d), "LABEL%d", label);
			storeCode3("b", d);

			labelnum++;

			fprintf(fm, "Label %d :\n", labelnum);
			snprintf(d, sizeof(d), "LABEL%d:", labelnum);
			storeCode4(d);
			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = checkStatement(parseWord());
			}
			else errorOut(12);

			fprintf(fm, "%s\n", increment);

			if (tempincreparam) strcpy(increiden, functab[layer - 1].params[tempincreid].name);
			else if (tempincrelocal) strcpy(increiden, functab[layer - 1].vars[tempincreid].name);
			else strcpy(increiden, valtab[tempincreid].name);

			getReg(increiden, "IDENFR");
			snprintf(d, sizeof(d), "$t%d", getRegnumMin1());

			if (tempincreop == 0) snprintf(s, sizeof(s), "%d", tempincrenum);
			else snprintf(s, sizeof(s), "-%d", tempincrenum);

			storeCode("addi", d, d, s);

			if (tempincreparam || tempincrelocal) {
				if (tempincrelocal) snprintf(s, sizeof(s), "%d($sp)", (functab[layer - 1].paramnum + tempincreid + 2) * 4);
				else snprintf(s, sizeof(s), "%d($sp)", (tempincreid + 2) * 4);
				storeCode2("sw", d, s);
			}
			else {
				snprintf(tempstr, sizeof(tempstr), "%d", valtab[tempincreid].addr);
				storeCode("addi", "$s7", "$0", tempstr);
				if (!strcmp(valtab[tempincreid].identype, "CHARTK")) storeCode2("sb", d, "vars($s7)");
				else storeCode2("sw", d, "vars($s7)");
			}

			fprintf(fm, "Label %d :\n", label);
			snprintf(d, sizeof(d), "LABEL%d:", label);
			storeCode4(d);

			fprintf(fm, "%s\n", temprelatop);
			fprintf(fm, "BNZ LABEL %d\n", label + 1);
			snprintf(tempstr, sizeof(tempstr), "LABEL%d", label + 1);
			makeBranch(tempcond1, temprelatop, tempcond2, tempstr, tempcondcounter, tempcondstart);
			labelnum++;
		}
		else errorOut(1);
		ret = false;
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
				fprintf(fm, "GOTO LABEL%d\n", functab[funcid[fid - 1]].labelnum);

				snprintf(t, sizeof(t), "LABEL%d", functab[funcid[fid - 1]].labelnum);
				storeCode3("jal", t);

				intExp[iei] = 0;
				assign = false;
				if (paramnum != functab[funcid[fid - 1]].paramnum) errorOut(4);
				paramnum = 0; stacknum = 0;
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
			strcpy(assigniden, subStr);
			if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
			else if (findId() >= 0 && !valtab[findId()].idenvar) errorOut(10);

			if ((tempid = findParam(functab[layer - 1].paramnum, layer - 1)) >= 0) isparam = true;
			else if ((tempid = findId()) >= 0) isparam = false;

			templocalid = localid;
			if (!strcmp(line, "LBRACK")) {
				newline = 0;
				assign = true;
				line = parseWord();
				//ARR INDEX CANNOT BE A MINUS INTEGER
				if (!strcmp(line, "PLUS")) {
					checkExpression(line);
					line = expline;
				}
				else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
					checkExpression(line);
					line = expline;
					if (intExp[iei] == 0) errorOut(9);
				}
				else errorOut(1);

				if (imm) {
					if (arr) {
						snprintf(arrindex, sizeof(arrindex), "%s", countval);
						regnum++;
					}
					else {
						getReg(countval, curType);
						snprintf(arrindex, sizeof(arrindex), "$t%d", getRegnumMin1());
					}
				}
				else strcpy(arrindex, assignreg);

				storeCode("sll", arrindex, arrindex, "2");
				storeCode("add", "$s6", "$0", arrindex);
				snprintf(d, sizeof(d), "%slocarr%d($s6)", assigniden, valtab[tempid].funclayer);

				regnum = 0; imm = expimm = resimm = arr = func = negExp = neg = false;
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

			if (!strcmp(line, "ASSIGN")) line = checkAssign(line, tempid, isparam, templocalid, d);
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
		fprintf(fm, "ret");
		line = parseWord();
		if (!strcmp(line, "LPARENT")) {
			if (!valfunc) errorOut(7);
			newline = 0;
			assign = true;
			line = parseWord();
			if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				while (isspace(lineo[r])) r++;
				if (lineo[r] == '(') {
					if (!strcmp(line, "MINU")) negExp = true;
					newline = 0;
					line = parseWord();
					if (isConstVal(line) || !strcmp(line, "LPARENT")) {
						checkExpression(line);
						line = expline;
					}
				}
				else {
					checkExpression(line);
					line = expline;
				}
			}
			else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				while (strcmp(line, "RPARENT")) {
					checkExpression(line);
					line = expline;
				}
				if (intExp[iei] == 0 && !strcmp(functab[layer - 1].functype, "INTTK")) errorOut(8);
				else if (intExp[iei] == 1 && !strcmp(functab[layer - 1].functype, "CHARTK")) errorOut(8);
			}
			else errorOut(1);

			if (imm) {
				if (!func) {
					getReg(countval, curType);
					snprintf(s, sizeof(s), "$t%d", getRegnumMin1());
				}
				else snprintf(s, sizeof(s), "$v1");

				if (neg) storeCode2("neg", s, s);
			}
			else strcpy(s, assignreg);

			if (negExp) storeCode2("neg", s, s);
			strcpy(d, "$v1");
			storeCode2("move", d, s);

			regnum = 0; imm = expimm = resimm = arr = func = negExp = neg = false;
			intExp[iei] = 0;
			assign = false;
			if (!strcmp(line, "RPARENT")) {
				newline = 0;
				line = parseWord();
			}
			else errorOut(12);
		}
		else if (valfunc) errorOut(1);
		if (strcmp(line, "SEMICN")) errorOut(11);
		fprintf(fm, "\n");

		for (int i = functab[layer - 1].paramnum; i > 0; i--) {
			snprintf(s, sizeof(s), "$s%d", i - 1);
			snprintf(d, sizeof(d), "%d($sp)", (i + 1) * 4);
			storeCode2("lw", s, d);
		}
		storeCode2("lw", "$ra", "4($sp)");

		snprintf(t, sizeof(t), "%d", (functab[layer - 1].varnum) * 4);
		storeCode("addi", "$sp", "$sp", t);

		snprintf(t, sizeof(t), "%d", (functab[layer - 1].paramnum + 2) * 4);
		storeCode("addi", "$sp", "$sp", t);

		storeCode3("jr", "$ra");
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
	int tempid;
	bool isparam = false, templocalid = false;

	if (!strcmp(line, "IDENFR")) {
		strcpy(idenname, subStr);
		if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
		else if (findId() >= 0 && !valtab[findId()].idenvar) errorOut(10);

		if ((tempid = findParam(functab[layer - 1].paramnum, layer - 1)) >= 0) isparam = true;
		else if ((tempid = findId()) >= 0) isparam = false;

		newline = 0; templocalid = localid;
		line = parseWord();
		if (!strcmp(line, "ASSIGN")) {
			line = checkAssign(line, tempid, isparam, templocalid, 0);
			snprintf(init, sizeof(init), "%s = ", idenname);
			if (imm) strcat(init, countval);
			else {
				strcpy(tempstr, assignreg);
				strcat(init, tempstr);
			}
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
	condstart = condcounter; iscond = true;

	if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		while (isspace(lineo[r])) r++;
		if (lineo[r] == '(') {
			if (!strcmp(line, "MINU")) negExp = true;
			newline = 0;
			line = parseWord();
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				checkExpression(line);
				line = expline;
			}
			else errorOut(1);
		}
		else {
			checkExpression(line);
			line = expline;
		}
	}
	else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
		checkExpression(line);
		line = expline;
		if (intExp[iei] == 0) errorOut(6);
		intExp[iei] = 0;
		if (imm) {
			if (!func) {
				if (!arr) getReg(countval, curType);
				snprintf(cond1, sizeof(cond1), "$t%d", getRegnumMin1());
			}
			else {
				storeCode2("move", "$v0", "$v1");
				strcpy(cond1, "$v0");
			}
			if (neg) storeCode2("neg", cond1, cond1);
		}
		else strcpy(cond1, assignreg);
		if (negExp) storeCode2("neg", cond1, cond1);
		imm = expimm = resimm = arr = func = negExp = neg = false;
	}
	else errorOut(1);

	if (isRelat(line)) {
		newline = 0;
		line = parseWord();
		if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			while (isspace(lineo[r])) r++;
			if (lineo[r] == '(') {
				if (!strcmp(line, "MINU")) negExp = true;
				newline = 0;
				line = parseWord();
				if (isConstVal(line) || !strcmp(line, "LPARENT")) {
					checkExpression(line);
					line = expline;
				}
				else errorOut(1);
			}
			else {
				checkExpression(line);
				line = expline;
			}
		}
		else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
			checkExpression(line);
			line = expline;
			if (intExp[iei] == 0) errorOut(6);
			intExp[iei] = 0;
			if (imm) {
				if (!func) {
					if (!arr) getReg(countval, curType);
					snprintf(cond2, sizeof(cond2), "$t%d", getRegnumMin1());
				}
				else strcpy(cond2, "$v1");
				if (neg) storeCode2("neg", cond2, cond2);
			}
			else strcpy(cond2, assignreg);
			if (negExp) storeCode2("neg", cond2, cond2);
			imm = expimm = resimm = arr = func = negExp = neg = false;
		}
		else errorOut(1);
	}
	else {
		strcpy(relatop, "!=");
		strcpy(cond2, "$0");
	}

	iscond = false;
	return (line);
}

char* checkIncrement(char* line)
{
	if (!strcmp(line, "IDENFR")) {
		strcpy(idenname, subStr);
		if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
		else if (findId() >= 0 && !valtab[findId()].idenvar) errorOut(10);

		if ((increid = findParam(functab[layer - 1].paramnum, layer - 1)) >= 0) increparam = true;
		else if ((increid = findId()) >= 0) increparam = false;

		newline = 0; increlocal = localid;
		if (!strcmp(parseWord(), "ASSIGN")) {
			newline = 0;
			if (!strcmp(parseWord(), "IDENFR")) {
				strcpy(idenname, subStr);
				snprintf(incre, sizeof(incre), "%s = %s", idenname, idenname);
				snprintf(increreg, sizeof(increreg), "$t%d", regnum++);

				if (regnum == 10) regnum = 0;
				if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
				newline = 0;
				line = parseWord();
				if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
					newline = 0;
					if (!strcmp(line, "PLUS")) increop = 0;
					else increop = 1;
					if (!strcmp(parseWord(), "INTCON")) {
						newline = 0;
						snprintf(tempstr, sizeof(tempstr), "%d", intcon);
						strcat(incre, tempstr);
						increnum = intcon;
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
				while (isspace(lineo[r])) r++;
				if (lineo[r] == '(') {
					if (!strcmp(line, "MINU")) negExp = true;
					newline = 0;
					line = parseWord();
					if (isConstVal(line) || !strcmp(line, "LPARENT")) {
						checkExpression(line);
						line = expline;
					}
					else errorOut(1);
				}
				else {
					checkExpression(line);
					line = expline;
				}
			}
			else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				checkExpression(line);
				line = expline;
				if (!strcmp(functab[funcid[fid - 1]].params[paramnum].paramtype, "INTTK") && intExp[iei] == 0) errorOut(5);
				else if (!strcmp(functab[funcid[fid - 1]].params[paramnum].paramtype, "CHARTK") && intExp[iei] == 1) errorOut(5);
				fprintf(fm, "push ");
				if (imm) {
					fprintf(fm, "%s\n", countval);
					getReg(countval, curType);
					snprintf(s, sizeof(s), "$t%d", getRegnumMin1());
					if (neg) storeCode2("neg", s, s);
				}
				else {
					fprintf(fm, "%s\n", assignreg);
					strcpy(s, assignreg);
				}
				if (negExp) storeCode2("neg", s, s);
				snprintf(d, sizeof(d), "$s%d", stacknum++);
				storeCode2("move", d, s);
				paramnum++; arr = func = negExp = neg = false;
				intExp[iei] = 0;
				if (!strcmp(line, "COMMA")) {
					newline = 0;
					line = parseWord();
				}
				else if (strcmp(line, "RPARENT")) errorOut(1);
			}
			else errorOut(1);
		}
	}
	//else if (strcmp(line, "RPARENT")) errorOut(1);

	fprintf(fm, "call %s\n", funcname);
	return (line);
}

char* checkRead(char* line)
{
	int tempid;
	if (!strcmp(line, "LPARENT")) {
		newline = 0;
		line = parseWord();
		while (!strcmp(line, "IDENFR")) {
			strcpy(idenname, subStr);
			//IT CAN'T BE A CONST OR ARRAY
			if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
			else {
				if ((valtab[findId()].idenvar && !valtab[findId()].arr) || 
					(functab[layer - 1].vars[findId()].idenvar && !functab[layer - 1].vars[findId()].arr)) {
					if (!strcmp(valtab[findId()].identype, "CHARTK")) storeCode2("li", "$v0", "12");
					else storeCode2("li", "$v0", "5");
					storeCode4("syscall");

					if (localid) {
						localid = false;
						snprintf(s, sizeof(s), "%d($sp)", (functab[layer - 1].paramnum + findId() + 2) * 4);
						storeCode2("sw", "$v0", s);
					}
					else {
						snprintf(tempstr, sizeof(tempstr), "%d", valtab[findId()].addr);
						storeCode("addi", "$s7", "$0", tempstr);
						if (!strcmp(valtab[findId()].identype, "CHARTK")) storeCode2("sb", "$v0", "vars($s7)");
						else storeCode2("sw", "$v0", "vars($s7)");
					}
				}
				else if (findParam(functab[layer - 1].paramnum, layer - 1) < 0) {
					tempid = findParam(functab[layer - 1].paramnum, layer - 1);
					if (!strcmp(functab[layer - 1].params[tempid].paramtype, "CHARTK")) storeCode2("li", "$v0", "12");
					else storeCode2("li", "$v0", "5");
					storeCode4("syscall");
					snprintf(s, sizeof(s), "%d($sp)", (tempid + 2) * 4);
					storeCode2("sw", "$v0", s);
				}
			}
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
			snprintf(dataAddr, sizeof(dataAddr), "str%d", strnum++);
			storeData(dataAddr, 4, 0, stringval);
			storeCode2("la", "$a0", dataAddr);
			storeCode2("li", "$v0", "4");
			storeCode4("syscall");
			line = parseWord();
			if (!strcmp(line, "COMMA")) {
				newline = 0;
				line = parseWord();
			}
		}
		if (isConstVal(line) || !strcmp(line, "LPARENT") || !strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
			if (isConstVal(line) || !strcmp(line, "LPARENT")) checkExpression(line);
			else if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
				while (isspace(lineo[r])) r++;
				if (lineo[r] == '(') {
					if (!strcmp(line, "MINU")) negExp = true;
					newline = 0;
					line = parseWord();
					if (isConstVal(line) || !strcmp(line, "LPARENT")) {
						checkExpression(line);
						line = expline;
					}
					else errorOut(1);
				}
				else {
					checkExpression(line);
					line = expline;
				}
			}
			if (imm) {
				syscall = true;
				if (arr) {
					snprintf(tempstr, sizeof(tempstr), "$t%d", getRegnumMin1());
					storeCode2("move", "$a0", tempstr);
					strcpy(curType, valtab[arrId].identype);
				}
				else if (func) storeCode2("move", "$a0", "$v1");
				else {
					getReg(countval, curType);
					strcpy(curType, valtab[findId()].identype);
				}

				if (neg) storeCode2("neg", "$a0", "$a0");

				if (negExp) storeCode2("neg", "$a0", "$a0");
				if (!strcmp(curType, "CHARTK")) storeCode2("li", "$v0", "11");
				else storeCode2("li", "$v0", "1");
			}
			else {
				if (negExp) storeCode2("neg", assignreg, assignreg);
				storeCode("add", "$a0", "$0", assignreg);
				if (!intExp[iei]) storeCode2("li", "$v0", "11");
				else storeCode2("li", "$v0", "1");
			}
			storeCode4("syscall");
			line = expline; regnum = 0; imm = expimm = resimm = arr = func = negExp = neg = syscall = false;
		}
		else errorOut(1);

		if (!strcmp(line, "RPARENT")) {
			newline = 0;
			storeCode2("li", "$a0", "'\\n'");
			storeCode2("li", "$v0", "11");
			storeCode4("syscall");
			line = parseWord();
		}
		else errorOut(12);
	}
	else errorOut(1);

	return (line);
}

char* checkAssign(char* line, int tempid, bool isparam, bool localid, char* arrreg)
{
	char tempd[30];
	if (isparam || localid) snprintf(tempd, sizeof(tempd), "$s%d", getRegnumS(tempid));
	else {
		if (valtab[tempid].arr) strcpy(tempd, arrreg);
		else {
			snprintf(tempstr, sizeof(tempstr), "%d", valtab[tempid].addr);
			storeCode("addi", "$s6", "$0", tempstr);
			strcpy(tempd, "vars($s6)");
		}
	}
	newline = 0;
	assign = true;
	line = parseWord();
	if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		while (isspace(lineo[r])) r++;
		if (lineo[r] == '(') {
			if (!strcmp(line, "MINU")) negExp = true;
			newline = 0;
			line = parseWord();
			if (isConstVal(line) || !strcmp(line, "LPARENT")) {
				checkExpression(line);
				line = expline;
			}
		}
		else {
			checkExpression(line);
			line = expline;
		}
	}
	else if (isConstVal(line) || !strcmp(line, "LPARENT")) {
		checkExpression(line);
		line = expline;
	}
	assign = false;

	if (imm) {
		if (!func) {
			if (!arr) getReg(countval, curType);
			snprintf(s, sizeof(s), "$t%d", getRegnumMin1());
		}
		else snprintf(s, sizeof(s), "$v1");
		if (neg) storeCode2("neg", s, s);
	}
	else strcpy(s, assignreg);

	if (negExp) storeCode2("neg", s, s);
	if (isparam || localid) {
		storeCode2("move", tempd, s);
		if (localid) snprintf(s, sizeof(s), "%d($sp)", (functab[layer - 1].paramnum + tempid + 2) * 4);
		else snprintf(s, sizeof(s), "%d($sp)", (tempid + 2) * 4);
		storeCode2("sw", tempd, s);
	}
	else {
		if (!strcmp(valtab[tempid].identype, "CHARTK")) storeCode2("sb", s, tempd);
		else storeCode2("sw", s, tempd);
	}

	intExp[iei] = 0;
	regnum = 0; imm = expimm = resimm = arr = func = negExp = neg = false;

	return (line);
}

int checkExpression(char* line)
{
	int term, tempres, tempreg = regnum, oldreg = regnum, retaddr = 1, tempstat = 0, res = checkTerm(line);
	char tempval[30], temptype[10], d[30], tempassignreg[30];
	bool tempneg = false, tempexpimm = false;
	if (imm) {
		expimm = true;
		tempexpimm = true;
	}
	if (neg) tempneg = true;
	tempres = num; tempreg = getRegnumMin1();
	strcpy(tempval, countval); strcpy(temptype, curType); strcpy(tempassignreg, assignreg);
	if (func) {
		tempstat = 1;
		retaddr = functab[fid].paramnum + 2;
	}
	else if (arr) tempstat = 2;
	else tempstat = 0;

	if (isOp(expline)) {
		while (!strcmp(countop, "PLUS") || !strcmp(countop, "MINU")) {
			intExp[iei] = 1;
			if (!strcmp(countop, "PLUS")) {
				snprintf(d, sizeof(d), "$t%d", regnum++);
				if (regnum == 10) regnum = 0; arr = func = neg = false;
				if (tempstat == 1) storeCode2("sw", "$v1", "0($sp)");
				if (tempstat == 2 || !expimm) funcdelay = true;
				term = checkTerm(parseWord());
				oldreg = regnum;
				if (funcdelay && func) {
					snprintf(s, sizeof(s), "$t%d", tempreg);
					storeCode2("lw", s, "0($sp)");
				}
				else if (tempexpimm) {
					if (tempstat == 1) {
						storeCode2("lw", "$v0", "0($sp)");
						strcpy(s, "$v0");
					}
					else {
						if (tempstat != 2) {
							getReg(tempval, temptype);
							snprintf(s, sizeof(s), "$t%d", getRegnumMin1());
						}
						else snprintf(s, sizeof(s), "$t%d", tempreg);
						if (tempneg) storeCode2("neg", s, s);
					}
				}
				else strcpy(s, tempassignreg);

				if (imm) {
					if (func) strcpy(t, "$v1");
					else {
						if (!arr) getReg(countval, curType);
						snprintf(t, sizeof(t), "$t%d", getRegnumMin1());
						if (neg) storeCode2("neg", t, t);
						arr = false;
					}
				}
				else strcpy(t, assignreg);

				regnum = oldreg;
				fprintf(fm, "%s = %s + %s\n", d, s, t);
				storeCode("add", d, s, t);
				res += term;
			}
			else {
				snprintf(d, sizeof(d), "$t%d", regnum++);
				if (regnum == 10) regnum = 0; arr = func = neg = false;
				if (tempstat == 1) storeCode2("sw", "$v1", "0($sp)");
				if (tempstat == 2 || !expimm) funcdelay = true;
				term = checkTerm(parseWord());
				oldreg = regnum;
				if (funcdelay && func) {
					snprintf(s, sizeof(s), "$t%d", tempreg);
					storeCode2("lw", s, "0($sp)");
				}
				else if (tempexpimm) {
					if (tempstat == 1) {
						storeCode2("lw", "$v0", "0($sp)");
						strcpy(s, "$v0");
					}
					else {
						if (tempstat != 2) {
							getReg(tempval, temptype);
							snprintf(s, sizeof(s), "$t%d", getRegnumMin1());
						}
						else snprintf(s, sizeof(s), "$t%d", tempreg);
						if (tempneg) storeCode2("neg", s, s);
					}
				}
				else strcpy(s, tempassignreg);

				if (imm) {
					if (func) {
						strcpy(t, "$v1");
						func = false;
					}
					else {
						if (!arr) getReg(countval, curType);
						snprintf(t, sizeof(t), "$t%d", getRegnumMin1());
						if (neg) storeCode2("neg", t, t);
						arr = false;
					}
				}
				else strcpy(t, assignreg);

				regnum = oldreg;
				fprintf(fm, "%s = %s - %s\n", d, s, t);
				storeCode("sub", d, s, t);
				res -= term;
			}
			imm = expimm = tempexpimm = func = arr = tempneg = neg = funcdelay = false;
			tempreg = regnum - 1; strcpy(assignreg, d); strcpy(tempassignreg, d);
		}
	}
	
	return res;
}

int checkTerm(char* line)
{
	int fact, tempres, tempreg = regnum, oldreg = regnum, tempstat = 0, res = checkFactor(line);
	char tempval[30], temptype[10], d[30], tempassignreg[30];
	bool tempneg = false, tempresimm = false;
	if (imm) {
		resimm = true;
		tempresimm = true;
	}
	if (neg) tempneg = true;
	tempres = num; tempreg = getRegnumMin1();
	strcpy(tempval, countval); strcpy(temptype, curType); strcpy(tempassignreg, assignreg);
	if (func) tempstat = 1;
	else if (arr) tempstat = 2;
	else tempstat = 0;
	line = parseWord();

	if (isOp(line)) {
		while (!strcmp(countop, "MULT") || !strcmp(countop, "DIV")) {
			intExp[iei] = 1;
			if (!strcmp(countop, "MULT")) {
				snprintf(d, sizeof(d), "$t%d", regnum++);
				if (regnum == 10) regnum = 0;  arr = func = neg = false;
				if (tempstat == 1) storeCode2("move", "$v0", "$v1");
				if (tempstat == 2 || !resimm) funcdelay = true;
				fact = checkFactor(parseWord());
				oldreg = regnum;
				if (funcdelay && func) {
					snprintf(s, sizeof(s), "$t%d", tempreg);
					storeCode2("lw", s, "0($sp)");
				}
				else if (tempresimm) {
					if (tempstat == 1) strcpy(s, "$v0");
					else {
						if (tempstat != 2) {
							getReg(tempval, temptype);
							snprintf(s, sizeof(s), "$t%d", getRegnumMin1());
						}
						else snprintf(s, sizeof(s), "$t%d", tempreg);
						if (tempneg) storeCode2("neg", s, s);
					}
				}
				else strcpy(s, tempassignreg);

				if (imm) {
					if (func) {
						strcpy(t, "$v1");
						func = false;
					}
					else {
						if (!arr) getReg(countval, curType);
						snprintf(t, sizeof(t), "$t%d", getRegnumMin1());
						if (neg) storeCode2("neg", t, t);
						arr = false;
					}
				}
				else strcpy(t, assignreg);

				regnum = oldreg;
				fprintf(fm, "%s = %s * %s\n", d, s, t);
				storeCode2("mult", s, t);
				storeCode3("mflo", d);
				res *= fact;
			}
			else {
				snprintf(d, sizeof(d), "$t%d", regnum++);
				if (regnum == 10) regnum = 0;  arr = func = neg = false;
				if (tempstat == 1) storeCode2("move", "$v0", "$v1");
				if (tempstat == 2 || !resimm) funcdelay = true;
				fact = checkFactor(parseWord());
				oldreg = regnum;
				if (funcdelay && func) {
					snprintf(s, sizeof(s), "$t%d", tempreg);
					storeCode2("lw", s, "0($sp)");
				}
				else if (tempresimm) {
					if (tempstat == 1) strcpy(s, "$v0");
					else {
						if (tempstat != 2) {
							getReg(tempval, temptype);
							snprintf(s, sizeof(s), "$t%d", getRegnumMin1());
						}
						else snprintf(s, sizeof(s), "$t%d", tempreg);
						if (tempneg) storeCode2("neg", s, s);
					}
				}
				else strcpy(s, tempassignreg);

				if (imm) {
					if (func) {
						strcpy(t, "$v1");
						func = false;
					}
					else {
						if (!arr) getReg(countval, curType);
						snprintf(t, sizeof(t), "$t%d", getRegnumMin1());
						if (neg) storeCode2("neg", t, t);
						arr = false;
					}
				}
				else strcpy(t, assignreg);

				regnum = oldreg;
				fprintf(fm, "%s = %s / %s\n", d, s, t);
				storeCode2("div", s, t);
				storeCode3("mflo", d);
				res /= fact;
			}
			imm = resimm = tempresimm = func = arr = tempneg = neg = funcdelay = false;
			tempreg = regnum - 1; strcpy(assignreg, d); strcpy(tempassignreg, d);
			line = parseWord();
			isOp(line);
		}
	}

	expline = line;

	return res;
}

int checkFactor(char* line)
{
	bool tempimm = false, tempimm2 = false;

	if (!strcmp(line, "PLUS") || !strcmp(line, "MINU")) {
		if (!strcmp(line, "MINU")) neg = true;
		intExp[iei] = 1;
		line = parseWord();
	}

	if (isConstVal(line)) {
		imm = true;
		num = intcon;
	}
	else if (!strcmp(line, "LPARENT")) {
		intExp[iei] = 1;
		line = parseWord();
		if (expimm) tempimm = true;
		if (resimm) tempimm2 = true;
		int res = checkExpression(line);
		if (strcmp(expline, "RPARENT")) errorOut(12);
		expimm = tempimm;
		resimm = tempimm2;
		return res;
	}

	return num;
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
	len = strlen(lineo);

	while (r <= len && l <= r) {
		if (!isSymbol(lineo[r]))
			r++;

		if (isSymbol(lineo[r]) && l == r) {
			l = ++r;
			if (strcmp(checkSym(lineo[r - 1]), "QUOTE") && str != 0) {
				templen = strlen(tempstr);
				if (lineo[r - 1] == '\\') tempstr[templen++] = lineo[r - 1];
				tempstr[templen++] = lineo[r - 1];
				tempstr[templen++] = '\0';
			}

			else {
				if (!strcmp(checkSym(lineo[r - 1]), "QUOTE") && str == 0) {
					strcpy(tempstr, "\0");
					temp = isString("QUOTE");
					if (!strcmp(temp, "QUOTE")) {
						snprintf(stringval, sizeof(stringval), "\"%s\"", tempstr);
						strcpy(tempstr, "\0");
						return ("STRCON");
					}
					else return (temp);
				}

				else if (!strcmp(checkSym(lineo[r - 1]), "QUOTE") && str != 0) return ("QUOTE");

				else if (!strcmp(checkSym(lineo[r - 1]), "ASSIGN") && !strcmp(checkSym(lineo[r]), "ASSIGN")) {
					l = ++r;
					return ("EQL");
				}
				else if (!strcmp(checkSym(lineo[r - 1]), "GRE") && !strcmp(checkSym(lineo[r]), "ASSIGN")) {
					l = ++r;
					return ("GEQ");
				}
				else if (!strcmp(checkSym(lineo[r - 1]), "LSS") && !strcmp(checkSym(lineo[r]), "ASSIGN")) {
					l = ++r;
					return ("LEQ");
				}
				else if (!strcmp(checkSym(lineo[r - 1]), "EXCLAM") && !strcmp(checkSym(lineo[r]), "ASSIGN")) {
					l = ++r;
					return ("NEQ");
				}

				else if (!strcmp(checkSym(lineo[r - 1]), "APOSTROPHE") && isChar(lineo[r])) {
					if (!strcmp(checkSym(lineo[r + 1]), "APOSTROPHE")) {
						snprintf(countval, sizeof(countval), "%c", lineo[r]);
						strcpy(charval, toString(lineo[r]));
						r += 2;
					}
					else {
						errorOut(1);
						r++;
					}
					l = r;
					strcpy(curType, "CHARTK");
					return ("CHARCON");
				}

				else if (isspace(lineo[r - 1]) || lineo[r - 1] == '\0');

				else return (checkSym(lineo[r - 1]));
			}
		}

		else if ((isSymbol(lineo[r]) && l != r) || (r == len && l != r)) {
			subStr = subString(lineo, l, r - 1);

			l = r;

			if (str > 0) strcat(tempstr, subStr);

			else {
				if (!strcmp(checkWord(subStr), "OTHERS")) {
					if (isIden(subStr) && !isSymbol(lineo[r - 1])) {
						if (lineo[r] == '[' && assign) {
							char arrayname[50];
							int tempreg, tempid;

							strcpy(idenname, subStr);
							if ((tempid = findId()) < 0) {
								errorOut(3);
								temp = parseWord();
								assign = false;
								while (strcmp(temp, "RBRACK") && strcmp(temp, "SEMICN")) temp = parseWord();
								assign = true;
								strcpy(countval, "null");
							}
							else {
								if (!strcmp(valtab[tempid].identype, "INTTK")) intExp[iei] = 1;
								else intExp[iei] = 0;
								strcpy(arrayname, valtab[tempid].name);

								parseWord();
								iei++;
								tempreg = regnum++;
								if (regnum == 10) regnum = 0;
								checkExpression(parseWord());
								if (regnum == 9) regnum = 1;
								else regnum++;

								if (imm) {
									if (arr) {
										strcpy(curIndex, countval);
										storeCode("sll", curIndex, curIndex, "2");
										snprintf(curIndex, sizeof(curIndex), "%s(%s)", arrayname, countval);
									}
									else {
										getReg(countval, curType);
										snprintf(curIndex, sizeof(curIndex), "$t%d", getRegnumMin1());
										storeCode("sll", curIndex, curIndex, "2");
										snprintf(curIndex, sizeof(curIndex), "%s($t%d)", arrayname, getRegnumMin1());
									}
								}
								else {
									strcpy(curIndex, assignreg);
									storeCode("sll", curIndex, curIndex, "2");
									snprintf(curIndex, sizeof(curIndex), "%s(%s)", arrayname, assignreg);
								}
								snprintf(countval, sizeof(countval), "$t%d", tempreg);

								snprintf(tempstr, sizeof(tempstr), "$t%d", tempreg);
								if (!strcmp(valtab[tempid].identype, "CHARTK")) storeCode2("lb", tempstr, curIndex);
								else storeCode2("lw", tempstr, curIndex);
								regnum = tempreg;
								regnum++;
								if (regnum == 10) regnum = 0;
								strcpy(idenname, arrayname);
								arrId = findId();

								temp = expline;
								if (intExp[iei] == 0) errorOut(9);
								intExp[iei] = 0; iei--; iid--; arr = true;
							}
							if (strcmp(temp, "RBRACK")) {
								errorOut(13);
								return (temp);
							}
						}

						else if (lineo[r] == '(' && assign) {
							int tempreg;
							strcpy(funcname, subStr);
							if (findFunc() < 0) {
								errorOut(3);
								temp = parseWord();
								assign = false;
								while (strcmp(temp, "RPARENT")) temp = parseWord();
								assign = true;
							}
							else if (functab[findFunc()].valfunc) {
								if (funcdelay) {
									snprintf(s, sizeof(s), "%s", assignreg);
									storeCode2("sw", s, "0($sp)");
								}
								funcid[fid++] = findFunc();
								//iei++;
								if (!strcmp(functab[funcid[fid - 1]].functype, "INTTK")) intExp[iei] = 1;
								else intExp[iei] = 0;
								parseWord();
								iei++;
								tempreg = regnum;
								temp = checkFuncCall(parseWord());
								regnum = tempreg;

								snprintf(t, sizeof(t), "LABEL%d", functab[funcid[fid - 1]].labelnum);
								storeCode3("jal", t);
								strcpy(countval, "RET");

								intExp[iei] = 0; iei--;
								if (paramnum != functab[funcid[fid - 1]].paramnum) errorOut(4);
								paramnum = 0; stacknum = 0;
								fid--; //intExp[iei] = 0; iei--; 
								func = true;
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
							strcpy(countval, subStr);
							if (findId() < 0 && findParam(functab[layer - 1].paramnum, layer - 1) < 0) errorOut(3);
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

						strcpy(curType, "IDENFR");
						return ("IDENFR");
					}
					else if (isInt(subStr)) {
						strcpy(curType, "INTTK");
						if (assign) intExp[iei] = 1;
						strcpy(countval, subStr);
						intcon = atoi(subStr);
						return ("INTCON");
					}
				}
				else return (checkWord(subStr));
			}
		}
	}

	if (r > len&& fgets(lineo, 200, fi) != NULL) {
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
			line = parseWord();
			if (strcmp(line, "IDENFR") && strcmp(line, "MAINTK")) errorOut(1);
			checkFunc(line);
			newline = 0;
			line = parseWord();
		}
	}

	return;
}

void printError(char* code)
{
	//fprintf(fe, "%d %s\n", lc - newline, code);

	if (str == 0) newline = 0;

	return;
}

void printCode(char* code, char* d, char* s, char* t)
{
	fprintf(fo, "%s %s %s %s\n", code, d, s, t);

	return;
}

void printCode2(char* code, char* d, char* s)
{
	fprintf(fo, "%s %s %s\n", code, d, s);

	return;
}

int main()
{
	int i;

	if ((fi = fopen("testfile.txt", "r")) == NULL || (fo = fopen("mips.txt", "w")) == NULL ||
		(fm = fopen("76066002_medcode.txt", "w")) == NULL)
	{
		printf("Error opening file!");
		return(-1);
	}

	fgets(lineo, 200, fi);
	parse(parseWord());

	fprintf(fo, ".data\n");

	fprintf(fo, "\tvars: .space %d\n", vars);

	fprintf(fo, ".align 2\n");
	for (i = 0; i < datac4; i++) {
		if (mipsData4[i].datatype == 0)
			fprintf(fo, "\t%s: %s %s\n", mipsData4[i].name, dataType(mipsData4[i].type), mipsData4[i].content);
	}
	fprintf(fo, ".align 1\n");
	for (i = 0; i < datac4; i++) {
		if (mipsData4[i].datatype == 1)
			fprintf(fo, "\t%s: %s %s\n", mipsData4[i].name, dataType(mipsData4[i].type), mipsData4[i].content);
	}

	for (i = 0; i < datac3; i++) {
		fprintf(fo, "\t%s: %s %s\n", mipsData3[i].name, dataType(mipsData3[i].type), mipsData3[i].content);
	}

	for (i = 0; i < datac2; i++) {
		fprintf(fo, "\t%s: %s %s\n", mipsData2[i].name, dataType(mipsData2[i].type), mipsData2[i].content);
	}

	for (i = 0; i < datac; i++) {
		fprintf(fo, "\t%s: %s %s\n", mipsData[i].name, dataType(mipsData[i].type), mipsData[i].content);
	}

	fprintf(fo, ".text\n");

	for (i = 0; i < maincounter; i++) {
		fprintf(fo, "\t%s\n", mainCode[i]);
	}

	fprintf(fo, "\tj exit\n");

	for (i = 0; i < codecounter; i++) {
		fprintf(fo, "\t%s\n", mipsCode[i]);
	}

	fprintf(fo, "\texit:\n");

	fclose(fi);
	fclose(fo);
	fclose(fm);

	return 0;
}
