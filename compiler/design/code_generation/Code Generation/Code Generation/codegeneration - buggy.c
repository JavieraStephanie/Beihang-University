#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

FILE *prr, *prd;
enum { stacksize = 1450, lineleng = 132 };
enum fct { lda, lod, ldi, dis, Fct, Int, jmp, jpc, swt, cas, f1u, f2u, f1d, f2d, mks, cal, idx, ixx, ldb,
			cpb, ldc, ldr, flt, red, wrs, wrw, wru, hlt, Exp, exf, ldt, not, mus, wrr, sto, eqr, ner, lsr,
			Ler, gtr, ger, eql, neq, lss, ler, grt, geq, orr, add, sub, adr, sur, and, mul, dip, mod, mur,
			dir, rdl, wrl};
int p, b, t; //program-, base-, topstack-registers
int ir, h1, h2, h3, h4; //{instruction register}
int lc = 0, l = 0, r = 0, ci = 0, ci0, ci1 = 0, ti = 1, ti0, di, level = 0, address = 0, pos, pos0 = 0, vali, num = 0, num2;
char lastsymbol[10], line[100], id[30] = "\0", vartyp[10] = "\0", valc[15] = "\0", op[10] = "PLUS", op2[10] = "\0", count[50];
int begin = 0, cond = 0, repeat = 0, forloop = 0, assign = 0, str = 0, con = 0, var = 0, relat = 0, neg = 0;
char cline[15] = "\0";
int cstart = 0;

/*bool stackdump;
int display[7], chrcount, lncount;
float rconst[20];
char *stab[600];

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
	char *inxtyp, *eltyp;
	int elref, low, high, elsize, size;
}atab[30];*/
struct table {
	char name[30];
	char *kind, *type;
	int link, ref, vali, level, adr;
	char val[15];
	bool normal;
}valtab[100];
struct opcode {
	int f;  // {fct}
	int l : 2;  // [0..3(levmax)]
	int a : 11; // [0..2047(amax)]
};
struct opcode code[];

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

char* fctString(int f)
{
	switch (f) {
	case lda: return ("LDA"); break;	case ldc: return ("LDC"); break;	case ger: return ("GER"); break;
	case lod: return ("LOD"); break;	case ldr: return ("LDR"); break;	case eql: return ("EQL"); break;
	case ldi: return ("LDI"); break;	case flt: return ("FLT"); break;	case neq: return ("NEQ"); break;
	case dis: return ("DIS"); break;	case red: return ("RED"); break;	case lss: return ("LSS"); break;
	case Fct: return ("FCT"); break;	case wrs: return ("WRS"); break;	case ler: return ("LER"); break;
	case Int: return ("INT"); break;	case wrw: return ("WRW"); break;	case grt: return ("GRT"); break;
	case jmp: return ("JMP"); break;	case wru: return ("WRU"); break;	case geq: return ("GEQ"); break;
	case jpc: return ("JPC"); break;	case hlt: return ("HLT"); break;	case orr: return ("ORR"); break;
	case swt: return ("SWT"); break;	case Exp: return ("EXP"); break;	case add: return ("ADD"); break;
	case cas: return ("CAS"); break;	case exf: return ("EXF"); break;	case sub: return ("SUB"); break;
	case f1u: return ("F1U"); break;	case ldt: return ("LDT"); break;	case adr: return ("ADR"); break;
	case f2u: return ("F2U"); break;	case not: return ("NOT"); break;	case sur: return ("SUR"); break;
	case f1d: return ("F1D"); break;	case mus: return ("MUS"); break;	case and: return ("AND"); break;
	case f2d: return ("F2D"); break;	case wrr: return ("WRR"); break;	case mul: return ("MUL"); break;
	case mks: return ("MKS"); break;	case sto: return ("STO"); break;	case dip: return ("DIV"); break;
	case cal: return ("CAL"); break;	case eqr: return ("EQR"); break;	case mod: return ("MOD"); break;
	case idx: return ("IDX"); break;	case ner: return ("NER"); break;	case mur: return ("MUR"); break;
	case ixx: return ("IXX"); break;	case lsr: return ("LSR"); break;	case dir: return ("DIR"); break;
	case ldb: return ("LDB"); break;	case Ler: return ("LER"); break;	case rdl: return ("RDL"); break;
	case cpb: return ("CPB"); break;	case gtr: return ("GTR"); break;	case wrl: return ("WRL"); break;
	default:  return ("NOP"); break;
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
		/*if (!strcmp(line, "BEQ")) storeCode(geq, 0, 11);
		else if (!strcmp(line, "EQL")) storeCode(eql, 0, 8);
		else if (!strcmp(line, "NEQ")) storeCode(neq, 0, 9);
		else if (!strcmp(line, "GTR")) storeCode(gtr, 0, 12);
		else if (!strcmp(line, "LEQ")) storeCode(ler, 0, 13);
		else if (!strcmp(line, "LSS")) storeCode(lss, 0, 10);*/
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
			;//storeCode(mus, 0, 1);
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
		/*pos = findId(id);
		if (pos == 0) {
			errorOut(11);
			return (false);
		}
		if (strcmp(valtab[pos].kind, "variable")) {
			errorOut(12);
			return (false);
		}*/
		return checkRead(parse());
	}

	else if (!strcmp(line, "COMMA"))
		return checkRead(parse());

	else if (!strcmp(line, "RPAREN")) {
		//storeCode(red, level - valtab[ti].level, valtab[ti].adr);
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
		/*pos = findId(id);
		if (pos == 0) {
			errorOut(11);
			return (false);
		}
		if (!strcmp(valtab[pos].kind, "constant"))
			storeCode(lda, 0, valtab[ti].vali);
		else if (!strcmp(valtab[pos].kind, "variable"))
			storeCode(lod, level - valtab[ti].level, valtab[ti].adr);
		else {
			errorOut(21);
			return (false);
		}*/
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
		// storeCode(wrl, 0, 0);
		return (true);
	}

	else return (false);
}

bool checkCondition(char* line)
{
	//pos = findId(id);
	if (isConstVal(line)) {
		if (!strcmp(line, "IDEN")) {
			/*if (!strcmp(valtab[pos].kind, "constant"))
				storeCode(lda, 0, atoi(valtab[ti].val));
			else if (!strcmp(valtab[pos].kind, "variable"))
				storeCode(lod, level - valtab[ti].level, valtab[ti].adr);
			else {
				errorOut(21);
				return (false);
			}*/
		}
		else if (!strcmp(line, "INT"))
		;// storeCode(lda, 0, vali);
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
				toreCode(lda, 0, valtab[pos].val);
			else if (!strcmp(valtab[pos].kind, "variable"))
				storeCode(lod, level - valtab[pos].level, valtab[pos].adr);
			else {
				errorOut(21);
				return (false);
			}*
			//vali = valtab[pos].vali;
		}
		else if (!strcmp(cline, "INT"))
			;// storeCode(lda, 0, vali);

		strcpy(cline, parse());

		if (!strcmp(op2, "TIMES")) {
			storeCode(mul, 0, 4);
			num2 *= vali;
		}
		else if (!strcmp(op2, "DIV")) {
			storeCode(div, 0, 5);
			num2 /= vali;
		}

		strcpy(op2, cline);
	}

	if (!strcmp(op, "PLUS")) {
		if (cstart == 0) cstart++;
		//else storeCode(add, 0, 2);
		num += num2;
	}

	else if (!strcmp(op, "MINUS")) {
		//storeCode(sub, 0, 3);
		num -= num2;
	}

	strcpy(op, op2);
	strcpy(cline, parse());
	if (!strcmp(cline, "IDEN")) {
		if (!strcmp(valtab[pos].kind, "constant"))
			;// storeCode(lda, 0, valtab[pos].val);
		else if (!strcmp(valtab[pos].kind, "variable"))
			;// storeCode(lod, level - valtab[pos].level, valtab[pos].adr);
		else {
			errorOut(21);
			return (false);
		}
		num2 = valtab[pos].vali;
	}
	else if (!strcmp(cline, "INT")) {
		//storeCode(lda, 0, vali);
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
	/*pos = findId(id);

	if (pos == 0) {
		errorOut(11);
		return;
	}

	else if (assign == 0)
		pos0 = pos;*/

	if (!strcmp(line, "LPAREN") && assign == 0) {
		return checkAssign(parse());
	}

	else if (!strcmp(line, "EQL") || !strcmp(line, "BECOMES")) {
		/*if (!strcmp(valtab[pos0].kind, "constant") || !strcmp(valtab[pos0].kind, "procedure")) {
			errorOut(12);
			return;
		}*/
		num = 0;
		assign++;
		return checkAssign(parse());
	}

	else if (isConstVal(line)) {
		/*if (!strcmp(line, "IDEN")) {
			if (!strcmp(valtab[pos].kind, "constant"))
				storeCode(lda, 0, valtab[pos].val);
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
			storeCode(lda, 0, vali);
			valtab[pos0].vali = vali;
			num2 = vali;
		}*/
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
			//valtab[pos0].vali = num;
			return checkAssign(line);
		}
		else if (!strcmp(line, "RPAREN") && assign == 0) {
			return checkAssign(parse());
		}
		else if (!strcmp(line, "SEMICOLON") && assign > 0) {
			// storeCode(sto, level - valtab[pos0].level, valtab[pos0].adr);
			assign = 0;
			return;
		}
	}

	else if (!strcmp(line, "SEMICOLON")) {
		if (assign == 0) {
			/*if (!strcmp(valtab[pos].kind, "procedure"))
				storeCode(cal, level - valtab[ti].level, valtab[ti].adr);*/
		}
		else {
			//storeCode(sto, level - valtab[ti].level, valtab[ti].adr);
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
			/*if (isConstVal(line)) {
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
			else printf("(L: %d, C : %d)Constant value expected\n", lc, r);*/
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
				//storeTable("variable");
			}
			else printf("(L: %d, C : %d)Type expected\n", lc, r);
		}
		else if (!strcmp(line, "COMMA")) {
			strcpy(valc, "\0");
			//storeTable("variable");
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

/*void storeCode(int f, int l, int a)
{
	code[ci].f = f;
	code[ci].l = l;
	code[ci].a = a;
	ci++;
}*/

/*void storeTable(char *type)
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
}*/

/*int findId(char *iden)
{
	int i = ti;
	while (strcmp(valtab[i].name, iden) && i > 0) {
		i--;
	}
	return i;
}*/

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
				//valtab[ti].adr = ci;
				level++;
				//storeCode(jmp, 0, 0);
				if (!strcmp(parse(), "IDEN")) {
					if (checkParHead(parse()))
						;// storeTable("procedure");
				}
				else errorOut(4);
				strcpy(lastsymbol, "\0");
			 }

			else if (!strcmp(lastsymbol, "FUNCTSYM")) {
				level++;
				//storeCode(jmp, 0, 0);
				if (!strcmp(parse(), "IDEN")) {
					if (checkParHead(parse()))
						;// storeTable("function");
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
				/*if (level) {
					code[valtab[ti0].adr].a = ci;
					valtab[ti0].adr = ci;
					ci0 = ci;
					//storeCode(Int, 0, di);
				}*/
				strcpy(lastsymbol, "\0");
			}

			else if (!strcmp(lastsymbol, "ENDSYM")) {
				if (begin) {
					begin--;
					if (begin == 0 && level > 0) {
						level--;
						//storeCode(exp, 0, 0);
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
					//storeCode(jpc, 0, 0);
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
								;// storeCode(lda, 0, vali);
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

/*void interpret()
{
	int fld[4];
	puts("Start pl/0");
	t = btab[2].vsize-1; b = 0; p = tab[s[4].i].adr;
	s[1].i = s[2].i = 0; s[3].i = -1; s[4].i = btab[1].last;
	display[0] = display[1] = 0;
	lncount = chrcount = 0;
	//ocnt := 0;
	do {
		printf("[%d]\n", p);
		struct opcode ir = code[p]; p = p + 1;
		switch (ir.f) {
		default:
		break; case lda: t = t + 1;  // load address
		{
			if (t > stacksize) fprintf(prr, "Storage overflow\n");
			else s[t].i = display[ir.l] + ir.a;
		}
		break; case lod: t = t + 1;  // load value
		{
			if (t > stacksize) fprintf(prr, "Storage overflow\n");
			else s[t] = s[display[ir.l] + ir.a];
		}
		break; case ldi: t = t + 1;  // load indirect
		{
			if (t > stacksize) fprintf(prr, "Storage overflow\n");
			else s[t] = s[s[display[ir.l] + ir.a].i];
		}
		break; case dis: h1 = ir.a; h2 = ir.l; h3 = b;// update display
		{
			while (h1 != h2) {
				display[h1] = h3; h1 = h1 - 1; h3 = s[h3 + 2].i;
			}
		}
		break; case Fct:
			switch (ir.a) {
			default:
			break; case 0: s[t].i = abs(s[t].i);
			break; case 1: s[t].r = abs(s[t].r);
			break; case 2: s[t].i = sqrt(s[t].i);
			break; case 3: s[t].r = sqrt(s[t].r);
			break; case 4: s[t].b = (s[t].i % 2 == 0); // odd num
			break; case 5: s[t].c = s[t].i;
			break; case 6: s[t].i = s[t].c;
			break; case 7: s[t].c = s[t].c+1;
			break; case 8: s[t].c = s[t].c-1;
			break; case 9: s[t].i = round(s[t].r);
			break; case 10: s[t].i = trunc(s[t].r);
			break; case 11: s[t].r = sin(s[t].r);
			break; case 12: s[t].r = cos(s[t].r);
			break; case 13: s[t].r = exp(s[t].r);
			break; case 14: s[t].r = log(s[t].r);
			break; case 15: s[t].r = sqrtf(s[t].r);
			break; case 16: s[t].r = atan(s[t].r);
			break; case 17: t = t + 1; 
			{
				if (t > stacksize) fprintf(prr, "Storage overflow\n");
				else s[t].b = (feof(prd));
			}
			break; case 18: t = t + 1;
			{
				//if (t > stacksize) fprintf(prr, "Storage overflow\n", text);
				//else s[t].b = (eoln(prd));
			}
			}
		break; case 9: s[t].i = s[t].i + ir.a; // offset
		break; case 10: p = ir.a; // jump
		break; case 11: p = ir.a; // conditional jump
		{
			if (!s[t].b) p = ir.a;
			t = t - 1;
		}
		break; case 12: h1 = s[t].i; t = t - 1; h2 = ir.a; h3 = 0;// switch
		{
			while (h3 == 0) {
				if (code[h2].f != 13) { h3 = 1; fprintf(prr, "undefined case"); }
				else if (code[h2].a == h1) { h3 = 1; p = code[h2 + 1].a; }
				else h2 = h2 + 2;
			}
		}
		break; case 14: h1 = s[t - 1].i; // for1up
		{
			if (h1 <= s[t].i) s[s[t - 2].i].i = h1;
			else { t = t - 3; p = ir.a; }
		}
		break; case 15: h2 = s[t - 2].i; h1 = s[h2].i + 1; // for2up
		{
			if (h1 <= s[t].i) { s[h2].i = h1; p = ir.a; }
			else t = t - 3;
		}
		break; case 16: h1 = s[t - 1].i; // for1down
		{
			if (h1 >= s[t].i) s[s[t - 2].i].i = h1;
			else { p = ir.a; t = t - 3; }
		}
		break; case 17: h2 = s[t - 2].i; h1 = s[h2].i - 1; // for2down
		{
			if (h1 >= s[t].i) { s[h2].i = h1; p = ir.a; }
			else t = t - 3;
		}
		break; case 18: h1 = btab[valtab[ir.a].ref].vsize; // mark stack
		{
			if (t + h1 > stacksize) fprintf(prr, "Storage overflow\n");
			else { t = t + 5; s[t - 1].i = h1 - 1; s[t].i = ir.a; }
		}
		break; case 19: h1 = t - ir.a; h2 = s[h1 + 4].i; h3 = valtab[h2].level; display[h3 + 1] = h1;// call
		{
			h4 = s[h1 + 3].i + h1; s[h1 + 1].i = p; s[h1 + 2].i = display[h3]; s[h1 + 3].i = b;
			for (h3 = t + 1; h3 < h4; h3++) s[h3].i = 0;
			b = h1; t = h4; p = valtab[h2].adr;
			//if (stackdump) dump;
		}
		break; case 20: h1 = ir.a; h2 = atab[h1].low; h3 = s[t].i; // index1
		{
			if ((h3 < h2) || (h3 > atab[h1].high)) fprintf(prr, "invalid index");
			else { t = t - 1; s[t].i = s[t].i + (h3 - h2); }
		}
		break; case 21: h1 = ir.a; h2 = atab[h1].low; h3 = s[t].i; // index
		{
			if ((h3 < h2) || (h3 > atab[h1].high)) fprintf(prr, "invalid index");
			else { t = t - 1; s[t].i = s[t].i + (h3 - h2)*atab[h1].elsize; }
		}
		break; case 22: h1 = s[t].i; t = t - 1; h2 = ir.a + t; // load block
		{
			if (h2 > stacksize) fprintf(prr, "Storage overflow\n");
			else { 
				while (t < h2) { t = t + 1; s[t] = s[h1]; h1 = h1 + 1; }
			}
		}
		break; case 23: h1 = s[t - 1].i; h2 = s[t].i; h3 = h1 + ir.a; // copy block
		{
			while (h1 < h3) { s[h1] = s[h2]; h1 = h1 + 1; h2 = h2 + 1; }
			t = t - 2;
		}
		break; case 24: t = t + 1; // literal
		{
			if (t > stacksize) fprintf(prr, "Storage overflow\n");
			else s[t].i = ir.a;
		}
		break; case 25: t = t + 1; // load real
		{
			if (t > stacksize) fprintf(prr, "Storage overflow\n");
			else s[t].r = rconst[ir.a];
		}
		break; case 26: h1 = t - ir.a; s[h1].r = s[h1].i; // float
		break; case 27: // read
		{
			if (feof(prd)) fprintf(prr, "reading past end or file");
			else switch (ir.a) {
			default:
			//break; case 1: read(prd, s[s[t].i].i);
			//break; case 2: read(prd, s[s[t].i].r);
			//break; case 4: read(prd, s[s[t].i].c);
			}
			t = t - 1;
		}
		break; case 28: h1 = s[t].i; h2 = ir.a; t = t - 1; chrcount = chrcount + h1; // write string
		{
			if (chrcount > lineleng) fprintf(prr, "line too long\n");
			while (h1 != 0) { fprintf(prr, stab[h2]); h1 = h1 - 1; h2 = h2 + 1; }
		}
		break; case 29: chrcount = chrcount + fld[ir.a]; // write1
		{
			if (chrcount > lineleng) fprintf(prr, "line too long\n");
			else switch (ir.a) {
			default:
				break; case 1: fprintf(prr, "%*d", fld[1], s[t].i);
				break; case 2: fprintf(prr, "%*d", fld[2], s[t].r);
				break; case 3: if (s[t].b) printf("true"); else printf("false");
				break; case 4: fprintf(prr, s[t].i);
			}
			t = t - 1;
		}
		break; case 30: chrcount = chrcount + s[t].i; // write2
		{
			if (chrcount > lineleng) fprintf(prr, "line too long\n");
			else switch (ir.a) {
			default:
			break; case 1: fprintf(prr, "%*d", s[t].i, s[t - 1].i);
			break; case 2: fprintf(prr, "%*d", s[t].i, s[t - 1].r);
			break; case 3: if (s[t - 1].b) printf("true"); else printf("false");
			}
			t = t - 2;
		}
		//break; case 31: ps = fin;
		break; case 32: t = b - 1; p = s[b + 1].i; b = s[b + 3].i; // exit procedure
		break; case 33: t = b; p = s[b + 1].i; b = s[b + 3].i; // exit function
		break; case 34: s[t] = s[s[t].i];
		break; case 35: s[t].b = !s[t].b;
		break; case 36: s[t].i = -s[t].i;
		break; case 37: chrcount = chrcount + s[t - 1].i;
		{
			if (chrcount > lineleng) fprintf(prr, "line too long\n");
			else fprintf(prr, "%**d", s[t].i, s[t - 1].i, s[t - 2].r);
			t = t - 3;
		}
		break; case 38: s[s[t - 1].i] = s[t]; t = t - 2; // store
		break; case 39: t = t - 1; s[t].b = (s[t].r == s[t + 1].r);
		break; case 40: t = t - 1; s[t].b = (s[t].r != s[t + 1].r);
		break; case 41: t = t - 1; s[t].b = (s[t].r < s[t + 1].r);
		break; case 42: t = t - 1; s[t].b = (s[t].r <= s[t + 1].r);
		break; case 43: t = t - 1; s[t].b = (s[t].r > s[t + 1].r);
		break; case 44: t = t - 1; s[t].b = (s[t].r >= s[t + 1].r);
		break; case 45: t = t - 1; s[t].b = (s[t].i == s[t + 1].i);
		break; case 46: t = t - 1; s[t].b = (s[t].i != s[t + 1].i);
		break; case 47: t = t - 1; s[t].b = (s[t].i < s[t + 1].i);
		break; case 48: t = t - 1; s[t].b = (s[t].i <= s[t + 1].i);
		break; case 49: t = t - 1; s[t].b = (s[t].i > s[t + 1].i);
		break; case 50: t = t - 1; s[t].b = (s[t].i >= s[t + 1].i);
		break; case 51: t = t - 1; s[t].b = (s[t].i | s[t + 1].i);
		break; case 52: t = t - 1; s[t].i = s[t].i + s[t + 1].i;
		break; case 53: t = t - 1; s[t].i = s[t].i - s[t + 1].i;
		break; case 54: t = t - 1; s[t].r = s[t].r + s[t + 1].r;
		break; case 55: t = t - 1; s[t].r = s[t].r - s[t + 1].r;
		break; case 56: t = t - 1; s[t].b = (s[t].b & s[t + 1].b);
		break; case 57: t = t - 1; s[t].i = s[t].i*s[t + 1].i;
		break; case 58: t = t - 1;
		{
			if (s[t + 1].i == 0) fprintf(prr, "division by 0");
			else s[t].i = s[t].i / s[t + 1].i;
		}
		break; case 59: t = t - 1;
		{
			if (s[t + 1].i == 0) fprintf(prr, "division by 0");
			else s[t].i = s[t].i % s[t + 1].i;
		}
		break; case 60: t = t - 1; s[t].r = s[t].r*s[t + 1].r;
		break; case 61: t = t - 1; s[t].r = s[t].r / s[t + 1].r;
		break; case 62:
		{
			if (feof(prd)) fprintf(prr, "reading past end or file");
			//else readln;
		}
		break; case 63:
		{
			fprintf(prr, "\n");
			lncount = lncount + 1;
			chrcount = 0;
			if (lncount > 200) fprintf(prr, "too much output");
		}
	} while (p != 1); //< (sizeof(code)/sizeof(struct opcode)) );
	puts(" end pl/0");
}*/

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

	/*for (k = 1; k < ti; k++) {
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
	}*/

	fclose(fo);

	system("pause");
	return 0;
}
