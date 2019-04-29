/*人民币兑换*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	int money, tens, fives, twos, ones;
	tens = 0;
	fives = 0;
	twos = 0;
	ones = 0;

	scanf("%d", &money);

	if (money > 100) {
		printf("Input Error\n");
	}

	else {

		while (money >= 10)
		{
			money -= 10;
			tens += 1;
			if (money < 0) {
				break;
			}
		}
	
		while (money >= 5) {
			money -= 5;
			fives += 1;
			if (money < 0) {
				break;
			}
		}

		while (money >= 2) {
			money -= 2;
			twos += 1;
			if (money < 0) {
				break;
			}
		}

		while (money >= 1) {
			money -= 1;
			ones += 1;
			if (money < 0) {
				break;
			}
		}
		printf("%d %d %d %d", tens, fives, twos, ones);
	}

	return 0;
}