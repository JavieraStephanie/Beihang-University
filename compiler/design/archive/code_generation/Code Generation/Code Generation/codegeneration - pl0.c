#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isArray(char* line);
bool isType(char* line);
bool checkParHead(char* line);
bool checkParam(char* line);
bool checkRead(char* line);
bool checkWrite(char* line);
bool checkCondition(char* line);
void checkAssign(char* line);
int findId(char *iden);
void storeCode(int f, int l, int a);
void storeTable(char *type);
char* parse();

enum { stacksize = 500 };
enum fct { lit, opr, lod, sto, cal, Int, jmp, jpc, red, wrt };
int p, b, t; //program-, base-, topstack-registers
int ir; //{instruction register}
int s[stacksize]; //[1..stacksize];
int lc = 0, l = 0, r = 0, ci = 0, ci0, ci1 = 0, ti = 1, ti0, di, level = 0, adr = 3, pos, pos0 = 0, vali, num = 0, num2;
char lastsymbol[10], line[100], id[30] = "\0", vartyp[10] = "\0", valc[15] = "\0", op[10] = "PLUS", op2[10] = "\0", count[50];
int begin = 0, cond = 0, repeat = 0, forloop = 0, assign = 0, str = 0, con = 0, var = 0, relat = 0, neg = 0;
char cline[15] = "\0";
int cstart = 0;

struct table {
	char name[30];
	char *kind;
	int vali;
	char val[15];
	int level;
	int adr;
}valtab[200];

struct opcode {
	int f;  // {fct}
	int l : 2;  // [0..3(levmax)]
	int a : 11; // [0..2047(amax)]
};

struct opcode code[] = {
	//f  l   a
  { jmp, 1,  1 },
  { Int, 1,  5 },
  { lit, 1,  0 },
  { sto, 1,  3 },
  { lit, 1,  1 },
  { sto, 1,  4 },
  { lod, 1,  3 },
  { lit, 1, 16 },
  { opr, 1,  9 },
  { jpc, 1, 19 },
  { lod, 1,  3 },
  { lit, 1,  1 },
  { opr, 1,  2 },
  { sto, 1,  3 },
  { lod, 1,  4 },
  { lod, 1,  3 },
  { opr, 1,  4 },
  { sto, 1,  4 },
  { jmp, 1,  6 },
  { opr, 1,  0 },
};

int base(int l) {
	int b1 = b; // {find base l levels down}
	while (l > 0) {
		b1 = s[b1];
		l--;
	}
	return b1;
}

void resetData()
{
	strcpy(id, "\0");
	strcpy(valc, "\0");
	strcpy(vartyp, "\0");
	pos = 0;
}

void errorOut(int errnum)
{
	printf("(L: %d C: %d)", lc, r);
	switch (errnum) {
	case 1: printf("Identifier not defined"); break;
	case 2: printf("Identifier redefinition"); break;
	case 3: printf("= expected after identifier"); break;
	case 4: printf("Identifier expected after const, var, procedure, program"); break;
	case 5: printf(", or ; expected"); break;
	case 6: printf("Wrong symbol after procedure declaration"); break;
	case 7: printf("Statement expected"); break;
	case 8: printf("Wrong symbol after statement"); break;
	case 9: printf(". expected"); break;
	case 10: printf("; expected between statements"); break;
	case 11: printf("Identifier not defined"); break;
	case 12: printf("Can't assign value to constant or procedure"); break;
	case 13: printf(":= expected"); break;
	case 14: printf("Identifier expected after call"); break;
	case 15: printf("Can't call a constant or variable"); break;
	case 16: printf("'then' expected"); break;
	case 17: printf("; or 'end' expected"); break;
	case 18: printf("'do' expected"); break;
	case 19: printf("Wrong symbol after statement"); break;
	case 20: printf("Relational operator expected"); break;
	case 21: printf("Procedure identifier shouldn't be in the expression"); break;
	case 22: printf(") expected"); break;
	case 23: printf("Wrong symbol"); break;
	case 24: printf("Expression shouldn't start with this symbol"); break;
	case 25: printf("Expression shouldn't start with this symbol"); break;
	case 26: printf("Expression shouldn't start with this symbol"); break;
	case 27: printf("Expression shouldn't start with this symbol"); break;
	case 28: printf("Expression shouldn't start with this symbol"); break;
	case 29: printf("Expression shouldn't start with this symbol"); break;
	case 30: printf("Number out of range"); break;
	case 31: printf("Expression shouldn't start with this symbol"); break;
	case 32: printf("Expression shouldn't start with this symbol"); break;
	case 33: printf("Expression shouldn't start with this symbol"); break;
	case 34: printf("Expression shouldn't start with this symbol"); break;
	case 35: printf("Expression shouldn't start with this symbol"); break;
	case 36: printf("Expression shouldn't start with this symbol"); break;
	case 37: printf("Expression shouldn't start with this symbol"); break;
	case 38: printf("Expression shouldn't start with this symbol"); break;
	case 39: printf("Expression shouldn't start with this symbol"); break;
	case 40: printf("( expected"); break;
	case 41: printf("Expression shouldn't start with this symbol"); break;
	case 42: printf("Expression shouldn't start with this symbol"); break;
	case 43: printf("Expression shouldn't start with this symbol"); break;
	case 44: printf("Expression shouldn't start with this symbol"); break;
	case 45: printf("Expression shouldn't start with this symbol"); break;
	case 46: printf("Expression shouldn't start with this symbol"); break;
	case 47: printf("Expression shouldn't start with this symbol"); break;
	case 48: printf("Expression shouldn't start with this symbol"); break;
	case 49: printf("Expression shouldn't start with this symbol"); break;
	case 50: printf("Expression shouldn't start with this symbol"); break;
	case 51: printf("Expression shouldn't start with this symbol"); break;
	case 52: printf("Expression shouldn't start with this symbol"); break;
	case 53: printf("Expression shouldn't start with this symbol"); break;
	case 54: printf("Expression shouldn't start with this symbol"); break;
	case 55: printf("Expression shouldn't start with this symbol"); break;
	case 56: printf("Expression shouldn't start with this symbol"); break;
	}
	printf("\n");
	return;
}

char* fctString(int f)
{
	switch (f) {
	case lit: return ("LIT"); break;
	case opr: return ("OPR"); break;
	case lod: return ("LOD"); break;
	case sto: return ("STO"); break;
	case cal: return ("CAL"); break;
	case Int: return ("INT"); break;
	case jmp: return ("JMP"); break;
	case jpc: return ("JPC"); break;
	case red: return ("RED"); break;
	case wrt: return ("WRT"); break;
	}
}

bool isSymbol(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == ';' || ch == ':' || ch == '[' || ch == ']' ||
		ch == '\'' || ch == '\n' || ch == '\0' || ch == '\t')
		return (true);
	return (false);
}

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
	case '\t': return ("TAB"); break;
	}
	return ("\0");
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
		!strcmp(line, "GTR") || !strcmp(line, "LEQ") || !strcmp(line, "LSS")) {
		if (!strcmp(line, "BEQ")) storeCode(opr, 0, 11);
		else if (!strcmp(line, "EQL")) storeCode(opr, 0, 8);
		else if (!strcmp(line, "NEQ")) storeCode(opr, 0, 9);
		else if (!strcmp(line, "GTR")) storeCode(opr, 0, 12);
		else if (!strcmp(line, "LEQ")) storeCode(opr, 0, 13);
		else if (!strcmp(line, "LSS")) storeCode(opr, 0, 10);
		return (true);
	}
	return (false);
}

bool isConstVal(char* line)
{
	if (!strcmp(line, "INT") || !strcmp(line, "REAL") || !strcmp(line, "STRING") || !strcmp(line, "IDEN"))
		return (true);
	return (false);
}

bool isArray(char* line)
{
	if (!strcmp(line, "ARRTYPE")) {
		if (!strcmp(parse(), "LBRACKETS")) {
			if (!strcmp(parse(), "INT")) {
				if (!strcmp(parse(), "RBRACKETS")) {
					if (!strcmp(parse(), "OFSYM")) {
						if (isType(parse()))
							return (true);
					}
				}
			}
		}
	}
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
		if (line[0] == '-')
			storeCode(opr, 0, 1);
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

bool isString(char* line)
{
	if (!strcmp(line, "QUOTE") && str == 0) {
		strcat(valc, "\'");
		str++;
		return isString(parse());
	}

	else if (!strcmp(line, "QUOTE") && str != 0) {
		strcat(valc, "\'");
		str = 0;
		return (true);
	}

	else if (strcmp(line, "QUOTE")) {
		return isString(parse());
	}

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

bool checkRead(char* line)
{
	if (!strcmp(line, "LPAREN"))
		return checkRead(parse());

	else if (!strcmp(line, "IDEN")) {
		pos = findId(id);
		if (pos == 0) {
			errorOut(11);
			return (false);
		}
		if (strcmp(valtab[pos].kind, "variable")) {
			errorOut(12);
			return (false);
		}
		return checkRead(parse());
	}

	else if (!strcmp(line, "COMMA"))
		return checkRead(parse());

	else if (!strcmp(line, "RPAREN")) {
		storeCode(red, level - valtab[ti].level, valtab[ti].adr);
		return (true);
	}

	else return (false);
}

bool checkWrite(char* line)
{
	if (!strcmp(line, "LPAREN"))
		return checkWrite(parse());

	if (!strcmp(line, "STRING"))
		return checkWrite(parse());

	else if (!strcmp(line, "IDEN") && str == 0) {
		pos = findId(id);
		if (pos == 0) {
			errorOut(11);
			return (false);
		}
		if (!strcmp(valtab[pos].kind, "constant"))
			storeCode(lit, 0, valtab[ti].vali);
		else if (!strcmp(valtab[pos].kind, "variable"))
			storeCode(lod, level - valtab[ti].level, valtab[ti].adr);
		else {
			errorOut(21);
			return (false);
		}
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
		else return checkWrite(line);
	}

	else if (!strcmp(line, "COMMA")) {
		strcpy(id, "\0");
		return checkWrite(parse());
	}

	else if (!strcmp(line, "RPAREN")) {
		storeCode(wrt, 0, 0);
		return (true);
	}

	else return (false);
}

bool checkCondition(char* line)
{
	pos = findId(id);
	if (isConstVal(line)) {
		if (!strcmp(line, "IDEN")) {
			if (!strcmp(valtab[pos].kind, "constant"))
				storeCode(lit, 0, atoi(valtab[ti].val));
			else if (!strcmp(valtab[pos].kind, "variable"))
				storeCode(lod, level - valtab[ti].level, valtab[ti].adr);
			else {
				errorOut(21);
				return (false);
			}
		}
		else if (!strcmp(line, "INT"));
			storeCode(lit, 0, vali);
		line = parse();
		if (!strcmp(line, "LBRACKETS")) {
			return checkCondition(parse());
		}
		else if (!strcmp(line, "RBRACKETS")) {
			return checkCondition(parse());
		}
		else if (isOp(line)) {
			return checkCondition(parse());
		}
		else if (isRelatType(line) && relat == 0) {
			relat++;
			return checkCondition(parse());
		}
		else if (relat > 0) {
			relat = 0;
			return (true);
		}
	}

	else if (isRelatType(line) && relat == 0) {
		relat++;
		return checkCondition(parse());
	}

	return (false);
}

char* checkCount()
{
	while (!strcmp(op2, "TIMES") || !strcmp(op2, "DIV"))
	{
		strcpy(cline, parse());
		if (!strcmp(cline, "IDEN")) {
			if (!strcmp(valtab[pos].kind, "constant"))
				storeCode(lit, 0, valtab[pos].val);
			else if (!strcmp(valtab[pos].kind, "variable"))
				storeCode(lod, level - valtab[pos].level, valtab[pos].adr);
			else {
				errorOut(21);
				return (false);
			}
			vali = valtab[pos].vali;
		}
		else if (!strcmp(cline, "INT"))
			storeCode(lit, 0, vali);

		strcpy(cline, parse());

		if (!strcmp(op2, "TIMES")) {
			storeCode(opr, 0, 4);
			num2 *= vali;
		}
		else if (!strcmp(op2, "DIV")) {
			storeCode(opr, 0, 5);
			num2 /= vali;
		}

		strcpy(op2, cline);
	}

	if (!strcmp(op, "PLUS")) {
		if (cstart == 0) cstart++;
		else storeCode(opr, 0, 2);
		num += num2;
	}

	else if (!strcmp(op, "MINUS")) {
		storeCode(opr, 0, 3);
		num -= num2;
	}

	strcpy(op, op2);
	strcpy(cline, parse());
	if (!strcmp(cline, "IDEN")) {
		if (!strcmp(valtab[pos].kind, "constant"))
			storeCode(lit, 0, valtab[pos].val);
		else if (!strcmp(valtab[pos].kind, "variable"))
			storeCode(lod, level - valtab[pos].level, valtab[pos].adr);
		else {
			errorOut(21);
			return (false);
		}
		num2 = valtab[pos].vali;
	}
	else if (!strcmp(cline, "INT")) {
		storeCode(lit, 0, vali);
		num2 = vali;
	}
	strcpy(cline, parse());
	if (!strcmp(cline, "PLUS") || !strcmp(cline, "MINUS") || !strcmp(cline, "TIMES") || !strcmp(cline, "DIV")) {
		strcpy(op2, cline);
		return checkCount();
	}
	else if (!strcmp(cline, "SEMICOLON"))
		return checkCount();

	cstart = 0;
	return (cline);
}

void checkAssign(char* line)
{
	pos = findId(id);

	if (pos == 0) {
		errorOut(11);
		return;
	}

	else if (assign == 0)
		pos0 = pos;

	if (!strcmp(line, "LPAREN") && assign == 0) {
		return checkAssign(parse());
	}

	else if (!strcmp(line, "EQL") || !strcmp(line, "BECOMES")) {
		if (!strcmp(valtab[pos0].kind, "constant") || !strcmp(valtab[pos0].kind, "procedure")) {
			errorOut(12);
			return;
		}
		num = 0;
		assign++;
		return checkAssign(parse());
	}

	else if (isConstVal(line)) {
		if (!strcmp(line, "IDEN")) {
			if (!strcmp(valtab[pos].kind, "constant"))
				storeCode(lit, 0, valtab[pos].val);
			else if (!strcmp(valtab[pos].kind, "variable"))
				storeCode(lod, level - valtab[pos].level, valtab[pos].adr);
			else {
				errorOut(21);
				return;
			}
			valtab[pos0].vali = valtab[pos].vali;
			num2 = valtab[pos].vali;
		}
		else if (!strcmp(line, "INT")) {
			storeCode(lit, 0, vali);
			valtab[pos0].vali = vali;
			num2 = vali;
		}
		line = parse();
		if (!strcmp(line, "LBRACKETS")) {
			return checkAssign(parse());
		}
		else if (!strcmp(line, "RBRACKETS")) {
			return checkAssign(parse());
		}
		else if (isOp(line)) {
			strcpy(op2, line);
			checkCount();
			valtab[pos0].vali = num;
			return checkAssign(line);
		}
		else if (!strcmp(line, "RPAREN") && assign == 0) {
			return checkAssign(parse());
		}
		else if (!strcmp(line, "SEMICOLON") && assign > 0) {
			storeCode(sto, level - valtab[pos0].level, valtab[pos0].adr);
			assign = 0;
			return;
		}
	}

	else if (!strcmp(line, "SEMICOLON")) {
		if (assign == 0) {
			if (!strcmp(valtab[pos].kind, "procedure"))
				storeCode(cal, level - valtab[ti].level, valtab[ti].adr);
		}
		else {
			storeCode(sto, level - valtab[ti].level, valtab[ti].adr);
			assign = 0;
		}
		strcpy(op, "\0");
		return;
	}

	return;
}

void checkConstant(char* line)
{
	if (!strcmp(line, "IDEN")) {
		con++;
		if (!strcmp(parse(), "EQL")) {
			line = parse();
			if (isConstVal(line)) {
				line = parse();
				if (!strcmp(line, "SEMICOLON"))
					storeTable("constant");
				else if (!strcmp(line, "COMMA")) {
					storeTable("constant");
					checkConstant(parse());
				}
			}
			else if (!strcmp(line, "MINUS")) {
				if (!strcmp(parse(), "INT")) {
					line = parse();
					if (!strcmp(line, "SEMICOLON"))
						storeTable("constant");
					else if (!strcmp(line, "COMMA")) {
						storeTable("constant");
						checkConstant(parse());
					}
				}
			}
			else printf("(L: %d, C : %d)Constant value expected\n", lc, r);
			con = 0;
		}
		else errorOut(3);
	}
	else errorOut(4);
	return;
}

void checkVar(char* line)
{
	if (!strcmp(line, "IDEN")) {
		line = parse();
		if (!strcmp(line, "COLON")) {
			var++;
			line = parse();
			if (isType(line) || isArray(line)) {
				var = 0;
				strcpy(valc, "\0");
				storeTable("variable");
			}
			else printf("(L: %d, C : %d)Type expected\n", lc, r);
		}
		else if (!strcmp(line, "COMMA")) {
			strcpy(valc, "\0");
			storeTable("variable");
			checkVar(parse());
		}
		else printf("(L: %d, C : %d)':' or ',' expected\n", lc, r);
	}

	return;
}

void checkType(char* line)
{
	if (!strcmp(line, "IDEN")) {
		if (!strcmp(parse(), "EQL")) {
			if (isType(parse()))
				printf("(L: %d)This is a type declaration\n", lc);
			else printf("(L: %d, C: %d)Type expected\n", lc, r);
		}
		else errorOut(3);
	}

	return;
}

void storeCode(int f, int l, int a)
{
	code[ci].f = f;
	code[ci].l = l;
	code[ci].a = a;
	ci++;
}

void storeTable(char *type)
{
	strcpy(valtab[ti].name, id);
	valtab[ti].kind = type;
	if (!strcmp(type, "constant")) {
		if (strcmp(valc, "\0"))
			strcpy(valtab[ti].val, valc);
		else
			valtab[ti].vali = vali;
	}
	else if (!strcmp(type, "procedure") || !strcmp(type, "function"))
		strcpy(valtab[ti].val, "(NULL)");
	valtab[ti].level = level;
	if (!strcmp(type, "variable"))
		valtab[ti].adr = adr;
	ti++;
	resetData();
	return;
}

int findId(char *iden)
{
	int i = ti;
	while (strcmp(valtab[i].name, iden) && i > 0) {
		i--;
	}
	return i;
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
			if (str > 0) {
				strcat(valc, subStr);
			}
			l = r;

			if (!strcmp(checkWord(subStr), "OTHERS")) {
				if (isIden(subStr) == true && isSymbol(line[r - 1]) == false) {
					if (!strcmp(id, "\0") || !strcmp(lastsymbol, "\0")) {
						strcpy(id, subStr);
					}

					if (!strcmp(lastsymbol, "\0")) {
						if (cstart > 0) return ("IDEN");
						if (assign == 0) checkAssign(parse());
						else checkAssign("IDEN");
					}

					else if (!strcmp(lastsymbol, "CONSTSYM") && con == 0) {
						con++;
						checkConstant("IDEN");
					}

					else if (!strcmp(lastsymbol, "VARSYM") && var == 0) 
						checkVar("IDEN");

					else if (!strcmp(lastsymbol, "TYPESYM"))
						checkType("IDEN");

					else return ("IDEN");
				}
				else if (isInt(subStr) == true) {
					if (str == 0)
						vali = atoi(subStr);
					return ("INT");
				}
				else if (isReal(subStr) == true) {
					if (str == 0)
						strcpy(valc, subStr);
					return ("REAL");
				}
				else if (isIden(subStr) == false && isSymbol(line[r - 1]) == false)
					return ("UNKNOWN");
			}

			else if (isType(checkWord(subStr)))
				return (checkWord(subStr));

			else if (!strcmp(checkWord(subStr), "ARRTYPE") || !strcmp(checkWord(subStr), "OFSYM"))
				return checkWord(subStr);

			else strcpy(lastsymbol, checkWord(subStr));

			if (!strcmp(lastsymbol, "PROGSYM")) {
				if (!strcmp(parse(), "IDEN")) {
					if (!strcmp(parse(), "SEMICOLON"))
						printf("Start of the program\n");
					else errorOut(5);
				}
				else errorOut(4);
				strcpy(lastsymbol, "\0");
				strcpy(id, "\0");
			}

			else if (!strcmp(lastsymbol, "CONSTSYM") || !strcmp(lastsymbol, "VARSYM") ||
				!strcmp(lastsymbol, "TYPESYM"))
				parse();

			else if (!strcmp(lastsymbol, "PROCSYM")) {
				di = 3;
				ti0 = ti;
				valtab[ti].adr = ci;
				level++;
				storeCode(jmp, 0, 0);
				if (!strcmp(parse(), "IDEN")) {
					if (checkParHead(parse()))
						storeTable("procedure");
				}
				else errorOut(4);
				strcpy(lastsymbol, "\0");
			 }

			else if (!strcmp(lastsymbol, "FUNCTSYM")) {
				level++;
				storeCode(jmp, 0, 0);
				if (!strcmp(parse(), "IDEN")) {
					if (checkParHead(parse()))
						storeTable("function");
				}
				else errorOut(4);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "READSYM")) {
				if (checkRead(parse()));
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "WRITESYM")) {
				if (checkWrite(parse()));
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "BEGINSYM")) {
				begin++;
				if (level) {
					code[valtab[ti0].adr].a = ci;
					valtab[ti0].adr = ci;
					ci0 = ci;
					storeCode(Int, 0, di);
				}
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "ENDSYM")) {
				if (begin) {
					begin--;
					if (begin == 0 && level > 0) {
						level--;
						storeCode(opr, 0, 0);
					}
				}
				else printf("Unexpected 'end'\n");
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "IFSYM")) {
				cond++;
				if (checkCondition(parse()));
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "THENSYM")) {
				if (cond) {
					ci1 = ci; 
					storeCode(jpc, 0, 0);
					code[ci1].a = ci; //After statement(fsys);
				}
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "ELSESYM")) {
				if (cond) cond--;
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "FORSYM")) {
				if (!strcmp(parse(), "IDEN")) {
					if (!strcmp(parse(), "BECOMES")) {
						char *temp = parse();
						if (isConstVal(temp)) {
							if (!strcmp(temp, "INT"))
								storeCode(lit, 0, vali);
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
					else errorOut(13);
				}
				else printf("(L: %d, C: %d)Identifier expected\n", lc, r);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "REPEATSYM")) {
				repeat++;
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "UNTILSYM")) {
				if (repeat) {
					if (checkCondition(parse())) repeat--;
				}
				strcpy(lastsymbol, "\0");
			}
		}
	}
	return ("\0");
}

void interpret()
{
	puts("Start pl/0");
	t = 0; b = 1; p = 0;
	s[1] = s[2] = s[3] = 0;
	do {
		printf("[%d]\n", p);
		struct opcode ir = code[p]; p = p + 1;
		switch (ir.f) {
		default:
		break; case lit: { t++; s[t] = ir.a; }
		break; case opr:
			switch (ir.a) {
			default:
			break; case 0: t = b - 1; p = s[t + 3]; b = s[t + 2];
			break; case 1: s[t] = -s[t];
			break; case 2: t--; s[t] = s[t] + s[t + 1];
			break; case 3: t--; s[t] = s[t] - s[t + 1];
			break; case 4: t--; s[t] = s[t] * s[t + 1];
			break; case 5: t--; s[t] = s[t] / s[t + 1];
			break; case 6: s[t] = (s[t] & 1); //ord(odd(s[t]));
			break; case 8: t--; s[t] = (s[t] == s[t + 1]);
			break; case 9: t--; s[t] = (s[t] != s[t + 1]);
			break; case 10: t--; s[t] = (s[t] < s[t + 1]);
			break; case 11: t--; s[t] = (s[t] >= s[t + 1]);
			break; case 12: t--; s[t] = (s[t] > s[t + 1]);
			break; case 13: t--; s[t] = (s[t] <= s[t + 1]);
			}
		break; case lod: t++; s[t] = s[base(ir.l) + ir.a];
		break; case sto: s[base(ir.l) + ir.a] = s[t]; printf("%d\n", s[t]); t--;
		break; case cal:
		{ //{generate new block mark}
			s[t + 1] = base(ir.l); s[t + 2] = b; s[t + 3] = p;
			b = t + 1; p = ir.a;
		}
		break; case Int: t = t + ir.a;
		break; case jmp: p = ir.a;
		break; case jpc: if (s[t] == 0) { p = ir.a; t = t - 1; }
		//break; case red: printf("??:\n"); readln(s[base(ir.l) + ir.a]);
		break; case wrt: printf("%d\n", s[t]); t = t + 1;
		}
	} while (p != 1); //< (sizeof(code)/sizeof(struct opcode)) );
	puts(" end pl/0");
}

int main() {
	FILE *fo;
	int k;
	char filename[50];

	printf("Please type in your file name: \n");
	scanf("%s", filename);

	if ((fo = fopen(filename, "r")) == NULL)
	{
		printf("Error opening file!");
		return(-1);
	}

	while (fgets(line, 100, fo) != NULL) {
		resetData();
		l = r = 0;
		lc++;
		parse();
	}

	printf("name\t\tkind\t\tval\t\tlevel\t\tadr\n");

	for (k = 1; k < ti; k++) {
		if (!strcmp(valtab[k].val, "\0"))
			printf("%s\t\t%s\t%d\t\t%d\n", valtab[k].name, valtab[k].kind, valtab[k].vali, valtab[k].level);
		else
			printf("%s\t\t%s\t%s\t\t%d\n", valtab[k].name, valtab[k].kind, valtab[k].val, valtab[k].level);
	}

	printf("\n");

	for (k = 0; k < ci; k++) {
		if (code[k].f < 0)
			continue;
		printf("%s\t%d\t%d\n", fctString(code[k].f), code[k].l, code[k].a);
	}

	fclose(fo);

	system("pause");
	return 0;
}
