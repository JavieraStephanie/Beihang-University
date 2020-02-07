#define _CRT_SECURE_NO_WARNINGS
enum fct {
	lit, opr, lod, sto, cal, Int, jmp, jpc, red, wrt
};

struct opcode {
	int f;  // {fct}
	int l : 2;  // [0..3(levmax)]
	int a : 11; // [0..2047(amax)]
};

enum { stacksize = 500 };
int p, b, t; //{program-, base-, topstack-registers}
int i; //{instruction register}
int s[stacksize]; //[1..stacksize];

int base(int l) {
	int b1 = b; // {find base l levels down}
	while (l > 0) {
		b1 = s[b1];
		l--;
	}
	return b1;
}

#include <stdio.h>

int main() {
	struct opcode code[] = {
		//f  l   a
	  { jmp, 0,  1 },
	  { red, 1,  0 },
	  { opr, 0,  0 }
	};
	puts(" start pl/0");
	t = 0; b = 1; p = 0;
	s[1] = s[2] = s[3] = 0;
	do {
		printf("[%d]\n", p);
		struct opcode i = code[p]; p = p + 1;
		switch (i.f) {
		default:
		break; case lit: { t++; s[t] = i.a; }
		break; case opr:
			switch (i.a) {
			default:
			break; case 0:
			{ // {return}
				t = b - 1; p = s[t + 3]; b = s[t + 2];
			}
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
		break; case lod: t++; s[t] = s[base(i.l) + i.a];
		break; case sto: s[base(i.l) + i.a] = s[t]; printf("%d\n", s[t]); t--;
		break; case cal:
		{ //{generate new block mark}
			s[t + 1] = base(i.l); s[t + 2] = b; s[t + 3] = p;
			b = t + 1; p = i.a;
		}
		break; case Int: t = t + i.a;
		break; case jmp: p = i.a;
		break; case jpc: if (s[t] == 0) { p = i.a; t = t - 1; }
		break; case red: printf("??:"); scanf("%d", &s[base(i.l) + i.a]);
		break; case wrt: printf("%d", s[t]); t++;
		}
	} while (p != 0); //< (sizeof(code)/sizeof(struct opcode)) );
	puts(" end pl/0");
	system("pause");

	return 0;
}