#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool isType(char* line);
bool checkParHead(char* line);
bool checkParam(char* line);
bool checkRead(char* line);
bool checkWrite(char* line2);
bool checkCondition();
void checkAssign(char* line2);
void checkConstant(char* line);
void checkVar(char* line);
void storeCode(int f, int l, int a);
void storeTable(char kind[]);
void storeBlock();
void storeArray(int l, int h);
void storeReal(float x);
int findId(char *iden);
char* parse();

FILE *fo, *prr, *prd;
enum { 
	stacksize = 500, 
	lineleng = 132,
	kmax = 15,
	nmax = 32767,
	xmax = 32767,
	amax = 30,
	bmax = 20,
	cmax = 800,
	c2max = 20,
	lmax = 7,
	tmax = 100
};
enum fct { 
	lda, lod, ldi, dis, Int, jmp, jpc, f1u, f2u, f1d, f2d, mks, cal, idx, ixx, ldb,
	cpb, ldc, ldr, flt, red, wrs, wrw, hlt, Exp, exf, ldt, mus, sto, eqr, ner, lsr, 
	ler, gtr, ger, eql, neq, lss, leq, grt, geq, add, sub, adr, sur, mul, Div, mur, 
	dir};
int p, b, t; //program-, base-, topstack-registers
int ir, h1, h2, h3, h4; //{instruction register}
int lc = 0, l = 0, r = 0, ai = 0, bi = 1, ci = 0, ci0, ci1 = 0, ci2 = 0, c1 = 0, c2 = 0, ti = 28, ti0, level = 1, address = 5, pos, pos0 = 0, vali, num = 0, num2;
char lastsymbol[10], line[100], id[30] = "\0", vartyp[10] = "\0", valc[15] = "\0", op[10] = "PLUS", op2[10] = "\0", count[50];
int begin = 0, cond = 0, repeat = 0, forloop = 0, assign = 0, str = 0, con = 0, var = 0, relat = 0, neg = 0;
char cline[15] = "\0", ctype[10] = "NOTYPE", tp[10] = "\0", tp2[10] = "\0", restyp[10] = "\0", relop[5] = "\0";
int cstart = 0, varstart = 0, forstart = 0, aref;
float valf = 0.0;

bool stackdump, negative = false, cntop = false, valpar = false, parcheck = false, isfun = false;
int display[7], chrcount, lncount, ocnt, prb, prt, strcount = 0, sx = 0;
float rconst[20];
char *stab[600], expres[10] = "\0";

struct stacktab {
	int i; // in case cn is an integer
	float r; // in case cn is a real
	bool b; // in case cn is a boolean
	char c; // in case cn is a char
}s[stacksize];
struct blocktab {
	int last, lastpar, psize, vsize;
} btab[20];
struct arraytab {
	char inxtyp[10], eltyp[10];
	int elref, low, high, elsize, size;
}atab[30];

struct table {
	char name[30];
	char kind[10];
	char type[10];
	bool normal;
	int link, ref, vali;
	float valf;
	char val[15];
	int level;
	int adr;
}valtab[200];

struct opcode {
	int f;  // {fct}
	int l : 3;
	int a : 16;
};

struct opcode code[cmax] = {
	{ jmp, 1,  1 },
};

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
	case 3: printf("Identifier expected"); break;
	case 4: printf("Program should started with 'program'"); break;
	case 5: printf("')' expected"); break;
	case 6: printf("':' expected when defining a variable type"); break;
	case 7: printf("Invalid symbol, some symbols will be skipped"); break;
	case 8: printf("Parameters should start with an identifier or 'var'"); break;
	case 9: printf("'of' expected"); break;
	case 10: printf("'(' expected"); break;
	case 11: printf("Type should start with identifier, array, or record"); break;
	case 12: printf("'[' expected"); break;
	case 13: printf("']' expected"); break;
	case 14: printf("'..' expected"); break;
	case 15: printf("';' expected"); break;
	case 16: printf("Function return type should be integer, real, boolean, or char"); break;
	case 17: printf("'=' expected, ':=' should only be used in assignment statements not declarations"); break;
	case 18: printf("Expression following 'if', 'while', or 'until' should be boolean type"); break;
	case 19: printf("The initial value or result value of expression in 'for' statement should be the same as loop variable type"); break;
	case 20: printf("Arguement 'output' or 'input' expected in the program head"); break;
	case 21: printf("Number out of range (Maximum of 14 integers)"); break;
	case 22: printf("The end of program is '.', check the corresponding 'begin' and 'end'"); break;
	case 23: printf("Expression after 'case' should be integer, char or boolean type"); break;
	case 24: printf("Invalid character"); break;
	case 25: printf("Constant value or identifier expected after '=' in constant declaration"); break;
	case 26: printf("The subscript expression type must be the same as the subscript type in the array description"); break;
	case 27: printf("In the array description, the lower bound cannot exceed the upper bound, and their types must be the same"); break;
	case 28: printf("No such array"); break;
	case 29: printf("Type identifier expected"); break;
	case 30: printf("Type undefined"); break;
	case 31: printf("No such record"); break;
	case 32: printf("The operand of 'not', 'and', or 'or' should be of boolean type"); break;
	case 33: printf("The type of this arithmetic expression is invalid"); break;
	case 34: printf("The operand of 'div' and 'mod' should be of integer type"); break;
	case 35: printf("The object types to be compared must be the same, unless one is an integer and the other is a real"); break;
	case 36: printf("The actual parameter and the corresponding formal parameter type should be the same, unless the formal parameter is a real value parameter and the actual parameter is an integer."); break;
	case 37: printf("Variable expected"); break;
	case 38: printf("String should at least have a character"); break;
	case 39: printf("The number of actual parameters is different with the number of formal parameters"); break;
	case 40: printf("No number found after '.'"); break;
	case 41: printf("Wrong arguments in 'write' or 'read'"); break;
	case 42: printf("The expression should be a real type"); break;
	case 43: printf("The domain width of the write statement should be an integer"); break;
	case 44: printf("Type or procedure identifier cannot appear in an expression"); break;
	case 45: printf("Should be a variable or procedure/function identifier"); break;
	case 46: printf("The assigned variable in the assignment statement should be the same as the expression type, unless the former is a real type and the latter is an integer type."); break;
	case 47: printf("The label in the case statement must be the same type as the case clause expression"); break;
	case 48: printf("The argument expression type of the standard function is incorrect"); break;
	case 49: printf("Memory overflow"); break;
	case 50: printf("Constant expected"); break;
	case 51: printf("':=' expected"); break;
	case 52: printf("'then' expected"); break;
	case 53: printf("'until' expected"); break;
	case 54: printf("'do' expected"); break;
	case 55: printf("'to' or 'downto' expected"); break;
	case 56: printf("'begin' expected"); break;
	case 57: printf("'end' expected"); break;
	case 58: printf("Factor should start with identifier, constant, not, or '('"); break;
	}
	printf("\n");
	return;
}

void fatal(int n)
{
	switch (n) {
	case 1: printf("Compiler table for identifier is too small\n"); break;
	case 2: printf("Compiler table for procedures is too small\n"); break;
	case 3: printf("Compiler table for reals is too small\n"); break;
	case 4: printf("Compiler table for arrays is too small\n"); break;
	case 5: printf("Compiler table for levels is too small\n"); break;
	case 6: printf("Compiler table for code is too small\n"); break;
	case 7: printf("Compiler table for strings is too small\n"); break;
	}
	return (-1);
}

char* fctString(int f)
{
	switch (f) {
	case lda: return ("LDA"); break;
	case lod: return ("LOD"); break;
	case ldi: return ("LDI"); break;
	case dis: return ("DIS"); break;
	case Int: return ("INT"); break;
	case jmp: return ("JMP"); break;
	case jpc: return ("JPC"); break;
	case f1u: return ("F1U"); break;
	case f2u: return ("F2U"); break;
	case f1d: return ("F1D"); break;
	case f2d: return ("F2D"); break;
	case mks: return ("MKS"); break;
	case cal: return ("CAL"); break;
	case idx: return ("IDX"); break;
	case ixx: return ("IXX"); break;
	case ldb: return ("LDB"); break;

	case cpb: return ("CPB"); break;
	case ldc: return ("LDC"); break;
	case ldr: return ("LDR"); break;
	case flt: return ("FLT"); break;
	case red: return ("RED"); break;
	case wrs: return ("WRS"); break;
	case wrw: return ("WRW"); break;
	case hlt: return ("HLT"); break;
	case Exp: return ("EXP"); break;
	case exf: return ("EXF"); break;
	case ldt: return ("F2D"); break;
	case mus: return ("MUS"); break;
	case sto: return ("STO"); break;
	case eqr: return ("EQR"); break;
	case ner: return ("NER"); break;
	case lsr: return ("LSR"); break;

	case ler: return ("LER"); break;
	case gtr: return ("GTR"); break;
	case ger: return ("GER"); break;
	case eql: return ("EQL"); break;
	case neq: return ("NEQ"); break;
	case lss: return ("LSS"); break;
	case leq: return ("LEQ"); break;
	case grt: return ("GRT"); break;
	case geq: return ("GEQ"); break;
	case add: return ("ADD"); break;
	case sub: return ("SUB"); break;
	case adr: return ("ADR"); break;
	case sur: return ("SUR"); break;
	case mul: return ("MUL"); break;
	case Div: return ("DIV"); break;
	case mur: return ("MUR"); break;

	case dir: return ("DIR"); break;
	default:  return ("NOP"); break;
	}
}

bool isSymbol(char ch)
{
	if (isspace(ch) || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == ';' || ch == ':' || ch == '[' || ch == ']' ||
		ch == '\'' || ch == '"' || ch == '\n' || ch == '\0')
		return (true);

	if (ch == '$' || ch == '@' || ch == '?' ||
		ch == '&' || ch == '^' || ch == '!')
		errorOut(24);
	return (false);
}

char* checkSym(char ch) {
	switch (ch) {
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
	else if (!strcmp(line, "downto"))		return ("DOWNTOSYM");

	else if (!strcmp(line, "program"))		return ("PROGSYM");
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

int checkType(char* line)
{
	if (!strcmp(line, "INT") || !strcmp(line, "INTTYPE")) return 1;
	else if (!strcmp(line, "REAL") || !strcmp(line, "REALTYPE")) return 2;
	else if (!strcmp(line, "BOOLEAN")) return 3;
	else if (!strcmp(line, "CHAR") || !strcmp(line, "CHARTYPE") ||
			 !strcmp(line, "STRING") || !strcmp(line, "STRTYPE")) return 4;
	else if (!strcmp(line, "ARRAY") || !strcmp(line, "ARRTYPE")) return 5;
	return 0;
}

int checkKind(char* line)
{
	if (!strcmp(line, "variable")) return 1;
	else if (!strcmp(line, "constant")) return 0;
	else if (!strcmp(line, "procedure")) return 3;
	else if (!strcmp(line, "function")) return 4;
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
		strcpy(relop, line);
		return (true);
	}
	return (false);
}

bool isConstVal(char* line)
{
	if (!strcmp(line, "INT")	|| !strcmp(line, "REAL") || !strcmp(line, "STRING") || 
		!strcmp(line, "IDEN")	|| !strcmp(line, "ARRAY"))
		return (true);
	return (false);
}

bool isArray(char* line)
{
	if (!strcmp(line, "ARRTYPE")) {
		if (!strcmp(parse(), "LBRACKETS")) {
			if (!strcmp(parse(), "INT")) {
				storeArray(0, vali);
				aref = ai;
				if (!strcmp(parse(), "RBRACKETS")) {
					if (!strcmp(parse(), "OFSYM")) {
						line = parse();
						if (isType(line)) {
							//atab[aref].size = (atab[aref].high - atab[aref].low + 1) * atab[aref].elsize;
							atab[aref].size = (atab[aref].high - atab[aref].low + 1);
							strcpy(atab[aref].eltyp, line);
							atab[aref].elref = 0;
							atab[aref].elsize = 0;
							return (true);
						}
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

	if (len == 0 || len > kmax) {
		errorOut(21);
		return false;
	}

	for (i = 0; i < len; i++) {
		if (line[i] < '0' || line[i] > '9' || (line[i] == '-' && i > 0))
			return false;
	}
	if (negative)
		storeCode(mus, 0, 0);
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
	if (negative)
		storeCode(mus, 0, 0);
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
		varstart = ti + 1;
		parcheck = true;
		if (checkParam(parse())) {
			varstart = 0;
			return checkParHead(parse());
		}
	}

	else if (!strcmp(line, "SEMICOLON"))
		return (true);
	
	else if (!strcmp(line, "COLON") && isfun) {
		isfun = false;
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
		valpar = true;
		storeTable("variable");
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

	else if (!strcmp(line, "VARSYM")) {
		valpar = false;
		if (!strcmp(parse(), "IDEN")) {
			storeTable("variable");
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
	}

	if (!strcmp(line, "SEMICOLON") || !strcmp(line, "RPAREN")) {
		parcheck = false;
		for (; varstart < ti + 1; varstart++) {
			if (!strcmp(line, "INTTYPE")) strcpy(valtab[varstart].type, "INT");
			else if (!strcmp(line, "REALTYPE")) strcpy(valtab[varstart].type, "REAL");
			else if (!strcmp(line, "STRTYPE")) strcpy(valtab[varstart].type, "STRING");
			else if (!strcmp(line, "ARRTYPE")) strcpy(valtab[varstart].type, "ARRAY");
			valtab[varstart].adr = address;
			valtab[varstart].level = level;
			valtab[varstart].normal = valpar;
			address++;
		}
		if (!strcmp(line, "SEMICOLON")) return checkParam(parse());
		else if (!strcmp(line, "RPAREN")) return (true);
	}

	return (false);
}

bool checkRead(char* line)
{
	if (!strcmp(line, "LPAREN"))
		return checkRead(parse());

	else if (!strcmp(line, "IDEN")) {
		pos = findId(id);
		if (pos == 0) {
			errorOut(1);
			return (false);
		}
		if (strcmp(valtab[pos].kind, "variable")) {
			errorOut(12);
			return (false);
		}
		if (valtab[pos].normal) storeCode(lda, valtab[pos].level, valtab[pos].adr);
		else storeCode(lod, valtab[pos].level, valtab[pos].adr);
		storeCode(red, 0, checkType(valtab[pos].type));
		strcpy(id, "\0");
		return checkRead(parse());
	}

	else if (!strcmp(line, "COMMA"))
		return checkRead(parse());

	else if (!strcmp(line, "RPAREN")) {
		return (true);
	}

	else return (false);
}

bool checkWrite(char* line2)
{
	if (!strcmp(line2, "LPAREN")) {
		if (line[r] == '\'' || line[r + 1] == '\'' || line[r] == '"' || line[r + 1] == '"') {
			if (!strcmp(parse(), "STRING")) {
				int i = 0, k = 1;
				for (; i < strlen(valc) - 1; i++, k++)
					stab[sx + i] = valc[k];
				i--;
				storeCode(ldc, 0, i);
				storeCode(wrs, 0, sx);
				sx += i;
				strcpy(valc, "\0");
				line2 = parse();
				if (!strcmp(line2, "COMMA")) {
					strcpy(id, "\0");
					cstart++;
					expression();
					line2 = parse();
				}
				if (!strcmp(line2, "RPAREN")) {
					storeCode(wrw, 0, checkType(restyp));
					return (true);
				}
			}
		}
		else {
			cntop = true;
			cstart++;
			expression();
			if (!strcmp(parse(), "RPAREN")) {
				//storeCode(wrw, 0, checkType(valtab[pos].type));
				storeCode(wrw, 0, checkType(restyp));
				return (true);
			}
		}
		return (false);
	}

	else return (false);
}

bool checkCondition()
{
	expression(); r--;
	if (isRelatType(parse())) {
		expression();
		if (!strcmp(tp, tp2)) {
			if (!strcmp(relop, "BEQ")) storeCode(geq, 0, 0);
			else if (!strcmp(relop, "EQL")) storeCode(eql, 0, 0);
			else if (!strcmp(relop, "NEQ")) storeCode(neq, 0, 0);
			else if (!strcmp(relop, "GTR")) storeCode(grt, 0, 0);
			else if (!strcmp(relop, "LEQ")) storeCode(leq, 0, 0);
			else if (!strcmp(relop, "LSS")) storeCode(lss, 0, 0);
		}
		else if (!strcmp(tp, "INT")) {
			strcpy(tp, "REAL");
			storeCode(flt, 1, 0);
		}
		else if (tp2 == "INT") {
			strcpy(tp2, "REAL");
			storeCode(flt, 0, 0);
		}
		else if (!strcmp(tp, "REAL") && !strcmp(tp2, "REAL")) {
			if (!strcmp(relop, "BEQ")) storeCode(ger, 0, 0);
			else if (!strcmp(relop, "EQL")) storeCode(eqr, 0, 0);
			else if (!strcmp(relop, "NEQ")) storeCode(ner, 0, 0);
			else if (!strcmp(relop, "GTR")) storeCode(gtr, 0, 0);
			else if (!strcmp(relop, "LEQ")) storeCode(ler, 0, 0);
			else if (!strcmp(relop, "LSS")) storeCode(lsr, 0, 0);
		}
		else
			errorOut(35);
		return (true);
	}

	return (false);
}

char* resultType()
{
	if ((strcmp(tp, "INT") && strcmp(tp, "REAL")) && (strcmp(tp2, "INT") && strcmp(tp2, "REAL")))
		errorOut(33);

	else if (!strcmp(tp, "INT") && !strcmp(tp2, "INT"))
		return ("INT");

	else if (!strcmp(tp, "INT") && !strcmp(tp2, "REAL"))
	{
		storeCode(flt, 1, 0);
		return ("REAL");
	}
	else {
		if (!strcmp(tp2, "INT"))
			storeCode(flt, 0, 0);
		return ("REAL");
	}
	return ("NULL");
}

int factor()
{
	strcpy(cline, parse());
	cntop = false;
	if (!strcmp(cline, "IDEN")) {
		pos = findId(id);
		if (!strcmp(valtab[pos].kind, "constant")) {
			if (!strcmp(valtab[pos].type, "REAL"))
				storeCode(ldr, 0, valtab[pos].adr);
			else storeCode(ldc, 0, valtab[pos].adr);
		}
		else if (!strcmp(valtab[pos].kind, "variable")) {
			if (!strcmp(valtab[pos].type, "ARRAY")) {
				expression();
				if (valtab[pos].normal) storeCode(lda, valtab[pos].level, valtab[pos].adr);
				else storeCode(lod, valtab[pos].level, valtab[pos].adr);
				int a = valtab[pos].ref;
				if (strcmp(atab[a].inxtyp, valtab[pos].type)) errorOut(26);
				else if (atab[a].elsize == 1) storeCode(idx, 0, a);
				else storeCode(ixx, 0, a);
				strcpy(valtab[pos].type, atab[a].eltyp);
				valtab[pos].ref = atab[a].elref;
				storeCode(ldt, 0, 0);
			}
			else if (isConstVal(valtab[pos].type)) {
				if (valtab[pos].normal) storeCode(lod, valtab[pos].level, valtab[pos].adr);
				else storeCode(ldi, valtab[pos].level, valtab[pos].adr);
			}
			else if (valtab[pos].normal) storeCode(lda, valtab[pos].level, valtab[pos].adr);
			else storeCode(lod, valtab[pos].level, valtab[pos].adr);
		}
		else if (!strcmp(valtab[pos].kind, "function")) {
			if (level != 0) {
				checkAssign(parse());
			}
		}
		else {
			errorOut(21);
			strcpy(id, "\0");
			return (false);
		}
		strcpy(id, "\0");
		strcpy(restyp, valtab[pos].type);
		if (!strcmp(valtab[pos].type, "INT")) {
			if (!strcmp(tp, "\0")) strcpy(tp, "INT");
			else strcpy(tp2, "INT");
			return valtab[pos].vali;
		}
		else {
			if (!strcmp(tp, "\0")) strcpy(tp, "REAL");
			else strcpy(tp2, "REAL");
			return valtab[pos].valf;
		}
	}
	else if (!strcmp(cline, "INT")) {
		storeCode(ldc, 0, vali);
		strcpy(restyp, "INT");
		strcpy(id, "\0");
		if (!strcmp(tp, "\0")) strcpy(tp, "INT");
		else strcpy(tp2, "INT");
		return vali;
	}

	else if (!strcmp(cline, "REAL")) {
		storeReal(valf);
		storeCode(ldr, 0, c1);
		strcpy(restyp, "REAL");
		strcpy(id, "\0");
		if (!strcmp(tp, "\0")) strcpy(tp, "REAL");
		else strcpy(tp2, "REAL");
		return valf;
	}

	else if (!strcmp(cline, "LPAREN"))
	{
		// '('
		int result = expression();
		parse(); // ')'
		return result;
	}
	return 0; // error
}

int term()
{
	int result = factor();
	while (isspace(line[r])) r++;
	while (line[r] == '*' || line[r] == '/') {
		cntop = true;
		char *temp = parse();
		if (!strcmp(temp, "TIMES")) {
			result *= factor();
			strcpy(restyp, resultType());
			if (!strcmp(restyp, "INT")) storeCode(mul, 0, 0);
			else if (!strcmp(restyp, "REAL")) storeCode(mur, 0, 0);
		}
		else {
			float temp = (float) result;
			int fact = factor();
			//temp = result / factor();
			if (ceilf(result) != result) { //if the result is not a whole number
				if (!strcmp(tp, "INT")) {
					storeCode(flt, 1, 0);
					strcpy(tp, "REAL");
				}
				if (!strcmp(tp2, "INT")) {
					storeCode(flt, 0, 0);
					strcpy(tp2, "REAL");
				}
			}
			strcpy(restyp, resultType());
			if (!strcmp(restyp, "INT")) storeCode(Div, 0, 0);
			else if (!strcmp(restyp, "REAL")) storeCode(dir, 0, 0);
		}
	}
	return result;
}

int expression()
{
	int result = term();
	while (isspace(line[r])) r++;
	while (line[r] == '+' || line[r] == '-') {
		char *temp = parse();
		cntop = true;
		if (!strcmp(temp, "PLUS")) {
			result += term();
			strcpy(restyp, resultType());
			if (!strcmp(restyp, "INT")) storeCode(add, 0, 0);
			else if (!strcmp(restyp, "REAL")) storeCode(adr, 0, 0);
		}
		else {
			result -= term();
			strcpy(restyp, resultType());
			if (!strcmp(restyp, "INT")) storeCode(sub, 0, 0);
			else if (!strcmp(restyp, "REAL")) storeCode(sur, 0, 0);
		}
	}
	cstart = 0;
	return result;
}

void checkAssign(char* line2)
{
	pos = findId(id);

	if (pos == 0) {
		errorOut(1);
		return;
	}

	else if (assign == 0)
		pos0 = pos;

	if (!strcmp(line2, "LPAREN") && assign == 0) {
		storeCode(mks, 0, 0);
		strcpy(id, "\0");
		expression();
		if (!strcmp(cline, "RPAREN") || !strcmp(parse(), "RPAREN")) {
			if (assign == 0) {
				if (!strcmp(valtab[pos].kind, "procedure"))
					storeCode(cal, 0, btab[valtab[pos].ref].psize - 1);
				if (valtab[pos].level < level)
					storeCode(dis, valtab[pos].level, level);
			}
			assign = 0;
			if (ci2 != 0) {
				code[ci2].a = ci;
				ci2 = 0;
			}
			strcpy(op, "\0");
			return;
		}
			//return checkAssign(parse());
	}

	else if (!strcmp(line2, "BECOMES")) {
		if (valtab[pos0].normal) storeCode(lda, valtab[pos0].level, valtab[pos0].adr);
		else storeCode(lod, valtab[pos0].level, valtab[pos0].adr);
		strcpy(id, "\0");
		if (!strcmp(valtab[pos0].kind, "constant") || !strcmp(valtab[pos0].kind, "procedure")) {
			errorOut(12);
			return;
		}
		assign++; cstart++;
		valtab[pos0].vali = expression();
		if (!strcmp(valtab[pos0].type, restyp)) {
			if (isConstVal(restyp)) {
				if (!strcmp(valtab[pos0].type, "ARRAY"))
					storeCode(cpb, 0, atab[valtab[pos0].ref].size);
				else
					storeCode(sto, 0, 0);
					//storeBlock(cpb, 0, btab[valtab[pos0].ref].vsize);
			}
		}
		else if (!strcmp(valtab[pos0].type, "REAL") && !strcmp(restyp, "INT")) {
			storeCode(flt, 0, 0);
			storeCode(sto, 0, 0);
		}
		//return checkAssign(parse());
		if (assign == 0) {
			if (!strcmp(valtab[pos].kind, "procedure"))
				storeCode(cal, 0, btab[valtab[pos].ref].psize - 1);
			if (valtab[pos].level < level)
				storeCode(dis, valtab[pos].level, level);
		}
		assign = 0;
		if (ci2 != 0) {
			code[ci2].a = ci;
			ci2 = 0;
		}
		strcpy(op, "\0");
		return;
	}

	/*else if (!strcmp(line2, "SEMICOLON")) {
		if (assign == 0) {
			if (!strcmp(valtab[pos].kind, "procedure"))
				storeCode(cal, 0, btab[valtab[pos].ref].psize - 1);
			if (valtab[pos].level < level)
				storeCode(dis, valtab[pos].level, level);
		}
		assign = 0;
		if (ci2 != 0) {
			code[ci2].a = ci;
			ci2 = 0;
		}
		strcpy(op, "\0");
		return;
	}*/

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
				if (!strcmp(line, "SEMICOLON")) {
					strcpy(valtab[ti+1].type, ctype);
					storeTable("constant");
					strcpy(ctype, "NOTYPE");
					strcpy(lastsymbol, "\0");
				}
				else if (!strcmp(line, "COMMA")) {
					strcpy(valtab[ti + 1].type, ctype);
					storeTable("constant");
					strcpy(ctype, "NOTYPE");
					checkConstant(parse());
				}
			}
			/*else if (!strcmp(line, "MINUS")) {
				if (!strcmp(parse(), "INT")) {
					line = parse();
					if (!strcmp(line, "SEMICOLON")) {
						strcpy(valtab[ti + 1].type, ctype);
						storeTable("constant");
						strcpy(ctype, "NOTYPE");
						strcpy(lastsymbol, "\0");
					}
					else if (!strcmp(line, "COMMA")) {
						strcpy(valtab[ti + 1].type, ctype);
						storeTable("constant");
						strcpy(ctype, "NOTYPE");
						checkConstant(parse());
					}
				}
			}*/
			else printf("(L: %d, C : %d)Constant value expected\n", lc, r);
			con = 0;
		}
	}
	else errorOut(3);
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
				for (; varstart < ti+1; varstart++) {
					if (!strcmp(line, "INTTYPE")) strcpy(valtab[varstart].type, "INT");
					else if (!strcmp(line, "REALTYPE")) strcpy(valtab[varstart].type, "REAL");
					else if (!strcmp(line, "STRTYPE")) strcpy(valtab[varstart].type, "STRING");
					else if (!strcmp(line, "CHARTYPE")) strcpy(valtab[varstart].type, "CHAR");
					else if (!strcmp(line, "ARRTYPE")) strcpy(valtab[varstart].type, "ARRAY");
				}
				varstart = 0;
				strcpy(ctype, "NOTYPE");
				if (!strcmp(parse(), "SEMICOLON")) {
					//strcpy(lastsymbol, "\0");
					btab[prb].vsize = address;
				}
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

void storeCode(int f, int l, int a)
{
	if (ci == cmax) fatal(6);
	code[ci].f = f;
	code[ci].l = l;
	code[ci].a = a;
	ci++;
}

void storeTable(char kind[])
{
	if (ti == tmax) fatal(1);
	else
	{
		int j, l;
		strcpy(valtab[0].name, id);
		j = btab[display[level]].last;
		l = j;
		while (strcmp(valtab[j].name, id))
			j = valtab[j].link;
		if (j != 0) errorOut(2);
		else {
			ti++;
			strcpy(valtab[ti].name, id);
			strcpy(valtab[ti].kind, kind);
			valtab[ti].link = ti - 1;
			if ((ti == 29) || (valtab[ti - 1].level == level && (!strcmp(valtab[ti - 1].kind, "procedure") || !strcmp(valtab[ti - 1].kind, "function")))) {
				if (strcmp(kind, "procedure") && strcmp(kind, "function"))
					valtab[ti].link = 0;
			}
			valtab[ti].normal = true;
			valtab[ti].level = level;
			valtab[ti].ref = 0;
			if (!strcmp(kind, "variable")) {
				valtab[ti].adr = address;
				address++;
			}
			else if (!strcmp(kind, "constant")) {
				if (!strcmp(valtab[ti].type, "STRING")) {
					valtab[ti].adr = strlen(valc) - 2;
					strcpy(valtab[ti].val, valc);
				}
				else if (!strcmp(valtab[ti].type, "REAL")) {
					valtab[ti].valf = valf;
					storeReal(valf);
					valtab[ti].adr = c1;
				}
				else {
					valtab[ti].vali = vali;
					valtab[ti].adr = vali;
				}
			}
			else if (!strcmp(kind, "procedure") || !strcmp(kind, "function"))
				strcpy(valtab[ti].val, "(NULL)");
			btab[display[level]].last = ti;
			resetData();
		}
	}
	return;
}

void storeBlock()
{
	if (bi == bmax) fatal(2);
	else
	{
		bi++;
		btab[bi].last = 0;
		btab[bi].lastpar = 0;
	}
}

void storeArray(int l, int h)
{
	if (l > h) errorOut(27);
	if (abs(l) > xmax || abs(h) > xmax) {
		errorOut(27);
		l = h = 0;
	}
	if (ai == amax) fatal(4);
	else {
		ai++;
		strcpy(atab[ai].inxtyp, "INT");
		atab[ai].low = l;
		atab[ai].high = h;
	}
}

void storeReal(float x)
{
	if (c2 == c2max - 1) fatal(3);
	else {
		rconst[c2 + 1] = x;
		c1 = 1;
		while (rconst[c1] != x)
			c1++;
		if (c1 > c2) c2 = c1;
	}
}

int findId(char *iden)
{
	int i = ti;
	while (strcmp(valtab[i].name, iden) && i > 0) {
		i--;
	}
	return i;
	/*int i, j;
	i = level;
	strcpy(valtab[0].name, id);
	while (i >= 0 || j == 0) {
		j = btab[display[i]].last;
		while (strcmp(valtab[j].name, id))
			j = valtab[j].link;
		i--;
	}
	if (j == 0) errorOut(0);
	return j;*/
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
		if (!isSymbol(line[r]))
			r++;

		if (isSymbol(line[r]) && l == r) {
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

			else if (isspace(line[r - 1]));

			else if (!strcmp(checkSym(line[r - 1]), "MINUS")) {
				if (line[r] > '0' && line[r] < '9' && (cstart == 0 || cntop)) {
					negative = true;
					return (parse());
				}
				else
					return (checkSym(line[r - 1]));
			}

			else if (!strcmp(checkSym(line[r - 1]), "PLUS")) {
				if (line[r] > '0' && line[r] < '9' && (cstart == 0 || cntop)) {
					negative = false;
					return (parse());
				}
				else
					return (checkSym(line[r - 1]));
			}

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
		else if (isSymbol(line[r]) && l != r || (r == len && l != r)) {
			char* subStr = subString(line, l, r - 1);
			if (str > 0) {
				strcat(valc, subStr);
			}
			l = r;

			if (!strcmp(checkWord(subStr), "OTHERS")) {
				if (isIden(subStr) && !isSymbol(line[r - 1])) {
					char* temp = "IDEN";
					if (line[r] == '[') {
						r++;
						cstart++;
						expression();
						if (line[r] == ']') {
							r++; temp = "ARRAY";
							int a = valtab[pos].ref;
							if (strcmp(atab[a].inxtyp, valtab[pos].type)) errorOut(26);
							else if (atab[a].elsize == 1) storeCode(idx, 0, a);
							else storeCode(ixx, 0, a);
							strcpy(valtab[pos].type, atab[a].eltyp);
							valtab[pos].ref = atab[a].elref;
						}
					}
					if (!strcmp(id, "\0") || !strcmp(lastsymbol, "\0")) {
						strcpy(id, subStr);
					}

					if (!strcmp(lastsymbol, "\0")) {
						if (cstart > 0) return (temp);
						if (assign == 0) checkAssign(parse());
						else checkAssign(temp);
					}

					else if (!strcmp(lastsymbol, "CONSTSYM") && con == 0) {
						con++;
						checkConstant("IDEN");
					}

					else if (!strcmp(lastsymbol, "VARSYM") && var == 0 && !parcheck) 
						checkVar("IDEN");

					else return (temp);
				}
				else if (isInt(subStr)) {
					if (str == 0) {
						if (negative)
							vali = -atoi(subStr);
						else
							vali = atoi(subStr);
						negative = false;
					}
					if (vali > nmax)
						errorOut(21);
					else
						strcpy(ctype, "INT");
					return ("INT");
				}
				else if (isReal(subStr)) {
					if (str == 0) {
						if (negative)
							valf = -atof(subStr);
						else
							valf = atof(subStr);
						negative = false;
					}
					strcpy(ctype, "REAL");
					return ("REAL");
				}
				else if (!isIden(subStr) && !isSymbol(line[r - 1]))
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
				else errorOut(3);
				strcpy(lastsymbol, "\0");
				strcpy(id, "\0");
			}

			else if (!strcmp(lastsymbol, "CONSTSYM") || !strcmp(lastsymbol, "VARSYM")) {
				if (!strcmp(lastsymbol, "VARSYM"))
				{
					if (varstart == 0) varstart = ti + 1;
					else if (parcheck) return ("VARSYM");
				}
				parse();
			}

			else if (!strcmp(lastsymbol, "PROCSYM")) {
				level++;
				if (level > lmax) fatal(5);
				storeBlock();
				prb = bi;
				display[level] = bi;
				valtab[ti].ref = prb;
				if (!strcmp(parse(), "IDEN")) {
					storeTable("procedure");
					strcpy(valtab[ti].type, "NOTYPE");
					strcpy(id, "\0");
					if (checkParHead(parse())) {
						btab[prb].lastpar = ti;
						btab[prb].psize = address;
					}
				}
				else errorOut(3);
				strcpy(lastsymbol, "\0");
			 }

			else if (!strcmp(lastsymbol, "FUNCTSYM")) {
				isfun = true;
				level++;
				if (level > lmax) fatal(5);
				storeBlock();
				prb = bi;
				display[level] = bi;
				valtab[ti].ref = prb;
				if (!strcmp(parse(), "IDEN")) {
					storeTable("function");
					strcpy(valtab[ti].type, "NOTYPE");
					strcpy(id, "\0");
					if (checkParHead(parse())) {
						btab[prb].lastpar = ti;
						btab[prb].psize = address;
					}
				}
				else errorOut(3);
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

			else if (!strcmp(lastsymbol, "IFSYM")) {
				cond++;
				if (checkCondition()) {
					ci1 = ci;
					storeCode(jpc, 0, 0);
				}
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "THENSYM")) {
				if (cond);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "ELSESYM")) {
				if (cond) {
					cond--;
					ci2 = ci;
					storeCode(jmp, 0, 0);
					code[ci1].a = ci;
					ci1 = 0;
				}
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "FORSYM")) {
				if (!strcmp(parse(), "IDEN")) {
					forstart++;
					pos = findId(id);
					strcpy(id, "\0");
					if (strcmp(valtab[pos].kind, "variable")) {
						if (!valtab[pos].normal) errorOut(37);
						else storeCode(lda, valtab[pos].level, valtab[pos].adr);
						return (false);
					}
					if (!strcmp(parse(), "BECOMES")) {
						expression(); r--;
						parse(); parse();
						if (!strcmp(lastsymbol, "TOSYM")) {
							expression();
							storeCode(f1u, 0, 0);
							/*if (forstart == 1) storeCode(f1u, 0, 0);
							else { storeCode(f2u, 0, 0); forstart = 0; }*/
						}
						else if (!strcmp(lastsymbol, "DOWNTOSYM")) {
							expression(); forstart++;
							storeCode(f1d, 0, 0);
							/*if (forstart == 1) storeCode(f1d, 0, 0);
							else { storeCode(f2d, 0, 0); forstart = 0; }*/
						}
						else printf("(L: %d, C: %d)'to' expression expected\n", lc, r);
					}
					else errorOut(13);
				}
				else errorOut(3);
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "DOSYM")) {
				////////////////NEEDED FOR THE f2u and f2d commands//////////////////
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "REPEATSYM")) {
				repeat++;
				ci1 = ci;
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "UNTILSYM")) {
				if (repeat) {
					if (checkCondition()) {
						repeat--;
						storeCode(jpc, 0, ci1);
					}
				}
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "BEGINSYM")) {
				begin++;
				if (level > 1) {
					code[valtab[ti0].adr].a = ci;
					valtab[ti0].adr = ci;
					ci0 = ci;
					storeCode(Int, 0, address);
				}
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "ENDSYM")) {
				if (feof(fo) && line[r] != '.') {
					errorOut(22);
				}
				else {
					if (begin) {
						begin--;
						level--;
						/*it doesn't always mean that when there's a begin,
						the level should decrement*/
					}
					else printf("Unexpected 'end'\n");
				}
				if (ci2 != 0) {
					code[ci2].a = ci;
					ci2 = 0;
				}
				strcpy(lastsymbol, "\0");
			}
		}
	}
	return ("\0");
}

void interpret()
{
	int fld[4], pc;
	enum ps { run, fin, divchk, inxchk, stkchk, lngchk };
	puts("Start pl/0");
	pc = run;
	t = btab[2].vsize - 1; b = 0; p = valtab[s[4].i].adr;
	s[1].i = s[2].i = 0; s[3].i = -1; s[4].i = btab[1].last;
	display[0] = display[1] = 0;
	lncount = chrcount = 0;
	ocnt = 0;
	do {
		struct opcode ir = code[p]; p = p + 1;
		ocnt = ocnt + 1;
		switch (ir.f) {
		default:
		break; case lda: t = t + 1;  // load address
		{
			if (t > stacksize) { pc = stkchk; }
			else s[t].i = display[ir.l] + ir.a;
		}
		break; case lod: t = t + 1;  // load value
		{
			if (t > stacksize) { pc = stkchk; }
			else s[t] = s[display[ir.l] + ir.a];
		}
		break; case ldi: t = t + 1;  // load indirect
		{
			if (t > stacksize) { pc = stkchk; }
			else s[t] = s[s[display[ir.l] + ir.a].i];
		}
		break; case dis: h1 = ir.a; h2 = ir.l; h3 = b;// update display
		{
			while (h1 != h2) {
				display[h1] = h3; h1 = h1 - 1; h3 = s[h3 + 2].i;
			}
		}
		break; case Int: s[t].i = s[t].i + ir.a; // offset
		break; case jmp: p = ir.a; printf("%d", ir.a);// jump
		break; case jpc: p = ir.a; // conditional jump
		{
			if (!s[t].b) p = ir.a;
			t = t - 1;
		}
		break; case f1u: h1 = s[t - 1].i; // for1up
		{
			if (h1 <= s[t].i) s[s[t - 2].i].i = h1;
			else { t = t - 3; p = ir.a; }
		}
		break; case f2u: h2 = s[t - 2].i; h1 = s[h2].i + 1; // for2up
		{
			if (h1 <= s[t].i) { s[h2].i = h1; p = ir.a; }
			else t = t - 3;
		}
		break; case f1d: h1 = s[t - 1].i; // for1down
		{
			if (h1 >= s[t].i) s[s[t - 2].i].i = h1;
			else { p = ir.a; t = t - 3; }
		}
		break; case f2d: h2 = s[t - 2].i; h1 = s[h2].i - 1; // for2down
		{
			if (h1 >= s[t].i) { s[h2].i = h1; p = ir.a; }
			else t = t - 3;
		}
		break; case mks: h1 = btab[valtab[ir.a].ref].vsize; // mark stack
		{
			if (t + h1 > stacksize) { pc = stkchk; }
			else { t = t + 5; s[t - 1].i = h1 - 1; s[t].i = ir.a; }
		}
		break; case cal: h1 = t - ir.a; h2 = s[h1 + 4].i; h3 = valtab[h2].level; display[h3 + 1] = h1;// call
		{
			h4 = s[h1 + 3].i + h1; s[h1 + 1].i = p; s[h1 + 2].i = display[h3]; s[h1 + 3].i = b;
			for (h3 = t + 1; h3 < h4; h3++) s[h3].i = 0;
			b = h1; t = h4; p = valtab[h2].adr;
			//if (stackdump) dump;
		}
		break; case idx: h1 = ir.a; h2 = atab[h1].low; h3 = s[t].i; // index1
		{
			if ((h3 < h2) || (h3 > atab[h1].high)) { pc = inxchk; }
			else { t = t - 1; s[t].i = s[t].i + (h3 - h2); }
		}
		break; case ixx: h1 = ir.a; h2 = atab[h1].low; h3 = s[t].i; // index
		{
			if ((h3 < h2) || (h3 > atab[h1].high)) { pc = inxchk; }
			else { t = t - 1; s[t].i = s[t].i + (h3 - h2)*atab[h1].elsize; }
		}
		break; case ldb: h1 = s[t].i; t = t - 1; h2 = ir.a + t; // load block
		{
			if (h2 > stacksize) { pc = stkchk; }
			else {
				while (t < h2) { t = t + 1; s[t] = s[h1]; h1 = h1 + 1; }
			}
		}
		break; case cpb: h1 = s[t - 1].i; h2 = s[t].i; h3 = h1 + ir.a; // copy block
		{
			while (h1 < h3) { s[h1] = s[h2]; h1 = h1 + 1; h2 = h2 + 1; }
			t = t - 2;
		}
		break; case ldc: t = t + 1; // literal
		{
			if (t > stacksize) { pc = stkchk; }
			else s[t].i = ir.a;
		}
		break; case ldr: t = t + 1; // load real
		{
			if (t > stacksize) { pc = stkchk; }
			else s[t].r = rconst[ir.a];
		}
		break; case flt: h1 = t - ir.a; s[h1].r = s[h1].i; // float
		break; case red: // read
		{
			switch (ir.a) {
			default:
				break; case 1: scanf("%d", &s[s[t].i].i);
				break; case 2: scanf("%f", &s[s[t].i].r);
				break; case 4: scanf("%c", &s[s[t].i].c);
			}
			t = t - 1;
		}
		break; case wrs: h1 = s[t].i; h2 = ir.a; t = t - 1; chrcount = chrcount + h1; // write string
		{
			if (chrcount > lineleng) { pc = lngchk; }
			while (h1 != 0) { printf("%c", stab[h2]); h1 = h1 - 1; h2 = h2 + 1; }
			chrcount = 0;
		}
		break; case wrw: chrcount = chrcount + fld[ir.a]; // write1
		{
			if (chrcount > lineleng) { pc = lngchk; }
			else switch (ir.a) {
			default:
			break; case 1: printf("%d", s[t].i);
			break; case 2: printf("%.2f", s[t].r);
			break; case 3: if (s[t].b) printf("true"); else printf("false");
			break; case 4: printf("%c", s[t].i);
			}
			t = t - 1;
			chrcount = 0;
		}
		break; case hlt: pc = fin;
		break; case Exp: t = b - 1; p = s[b + 1].i; b = s[b + 3].i; // exit procedure
		break; case exf: t = b; p = s[b + 1].i; b = s[b + 3].i; // exit function
		break; case ldt: s[t] = s[s[t].i];
		break; case mus: s[t].i = -s[t].i;
		break; case sto: s[s[t - 1].i] = s[t]; t = t - 2; // store
		break; case eqr: t = t - 1; s[t].b = (s[t].r == s[t + 1].r);
		break; case ner: t = t - 1; s[t].b = (s[t].r != s[t + 1].r);
		break; case lsr: t = t - 1; s[t].b = (s[t].r < s[t + 1].r);
		break; case ler: t = t - 1; s[t].b = (s[t].r <= s[t + 1].r);
		break; case gtr: t = t - 1; s[t].b = (s[t].r > s[t + 1].r);
		break; case ger: t = t - 1; s[t].b = (s[t].r >= s[t + 1].r);
		break; case eql: t = t - 1; s[t].b = (s[t].i == s[t + 1].i);
		break; case neq: t = t - 1; s[t].b = (s[t].i != s[t + 1].i);
		break; case lss: t = t - 1; s[t].b = (s[t].i < s[t + 1].i);
		break; case leq: t = t - 1; s[t].b = (s[t].i <= s[t + 1].i);
		break; case grt: t = t - 1; s[t].b = (s[t].i > s[t + 1].i);
		break; case geq: t = t - 1; s[t].b = (s[t].i >= s[t + 1].i);
		break; case add: t = t - 1; s[t].i = s[t].i + s[t + 1].i;
		break; case sub: t = t - 1; s[t].i = s[t].i - s[t + 1].i;
		break; case adr: t = t - 1; s[t].r = s[t].r + s[t + 1].r;
		break; case sur: t = t - 1; s[t].r = s[t].r - s[t + 1].r;
		break; case mul: t = t - 1; s[t].i = s[t].i*s[t + 1].i;
		break; case Div: t = t - 1;
		{
			if (s[t + 1].i == 0) { pc = divchk; }
			else s[t].i = s[t].i / s[t + 1].i;
		}
		break; case mur: t = t - 1; s[t].r = s[t].r*s[t + 1].r;
		break; case dir: t = t - 1; s[t].r = s[t].r / s[t + 1].r;
		}
	} while (pc == run); //< (sizeof(code)/sizeof(struct opcode)) );
	puts("\n end pl/0");

	if (pc != fin) {
		printf("halt at %d because of ", p);
		switch (pc) {
			default:
			break; case divchk: printf("division by 0\n");
			break; case inxchk: printf("invalid index\n");
			break; case stkchk: printf("storage overflow\n");
			break; case lngchk: printf("line too long\n");
		}
	}
}

int main() {
	int k;
	char filename[50];

	printf("Please type in your file name: \n");
	scanf("%s", filename);

	if ((fo = fopen(filename, "r")) == NULL)
	{
		printf("Error opening file!");
		return(-1);
	}
	btab[1].last = ti;
	btab[1].lastpar = 1;
	btab[1].psize = 0;
	btab[1].vsize = 0;

	storeBlock();

	valtab[ti].link = ti - 1;
	strcpy(valtab[ti].kind, "procedure");
	strcpy(valtab[ti].type, "null");
	valtab[ti].normal = 1;
	valtab[ti].level = 0;
	valtab[ti].ref = 2;

	prb = bi;
	display[level] = bi;
	valtab[ti].ref = prb;
	btab[prb].lastpar = ti;
	btab[prb].psize = address;

	display[level] = bi;

	while (fgets(line, 100, fo) != NULL) {
		resetData();
		l = r = 0;
		lc++;
		parse();
	}

	storeCode(hlt, 0, 0);

	printf("\tname\t\tlink\tobj\ttyp\tref\tnrm\tlev\tadr\n");
	for (k = 28; k < ti+1; k++) {
		printf("%d\t%s\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", k, valtab[k].name, valtab[k].link, checkKind(valtab[k].kind), checkType(valtab[k].type), valtab[k].ref, valtab[k].normal, valtab[k].level, valtab[k].adr);
	}

	printf("\n");

	printf("blocks\tlast\tlpar\tpsze\tvsze\n");
	for (k = 1; k < bi; k++) {
		printf("%d\t%d\t%d\t%d\t%d\n", k, btab[k].last, btab[k].lastpar, btab[k].psize, btab[k].vsize);
	}

	printf("\n");

	printf("arrays\txtyp\tetyp\teref\tlow\thigh\tsize\n");
	for (k = 1; k < ai+1; k++) {
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n", k, atab[k].inxtyp, checkType(atab[k].eltyp), atab[k].elref, atab[k].low, atab[k].high, atab[k].size);
	}

	printf("\n");

	for (k = 0; k < ci; k++) {
		if (code[k].f < 0)
			continue;
		printf("%d\t%s\t%d\t%d\t%d\n", k, fctString(code[k].f), code[k].f, code[k].l, code[k].a);
	}

	interpret();

	printf("Starting address is %d\n", valtab[btab[1].last].adr);
	fclose(fo);

	system("pause");
	return 0;
}
