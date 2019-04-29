/*前驱、后继字符*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	char a;
	
	scanf("%c", &a);
	
	printf("\n%c %c %c\n", a - 1, a, a + 1); // Display inputted character
	
	printf("%d %d %d\n\n", a - 1, a, a + 1); // Display ASCII Code

	return 0;

}
