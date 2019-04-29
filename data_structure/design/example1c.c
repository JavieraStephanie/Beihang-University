#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
#include <string.h>  

int main()
{
	int num = 0, num2, num3;
	char op = '+', op2, op3;

	//From the problem it is known that '=' would be the end sign of the expression so when there's '=', the expression would end
	//So while there's no '=', keep inputing things
	while (op != '=')
	{
		//Input one integer and one operation in every input, because no matter how long your input is, this will always be the input form
		scanf("%d %c", &num2, &op2);

		//It can also be seen from the example in the problem page that * and / would be calculated first, just like in real calculation
		//So if the operator is either * or /, calculate it first
		while (op2 == '*' || op2 == '/')
		{
			//Since we want to calculate it first, we need to input the next integer and operation (remember the input format) to be calculated with the current integer
			scanf("%d %c", &num3, &op3);
			
			//If the operator was *, times it, if /, divide it
			if (op2 == '*')
				num2 *= num3;
			else if (op2 == '/')
				num2 /= num3;

			//After that, the new operator would change the previous operator so for example your input now is
			//num2 = 5, op2 = *, num3 = 3, op3 = -, -> 5*3-
			//After we calculate 5*3 we'll get 15 after that we'll change the expression to 15- and prepare for the next operations
			//Mind that this could happen in a loop so for example 5*1/3 ... etc so it's a while expression
			op2 = op3;
		}

		//Otherwise if the operator is + or - just do the calculation accordingly
		if (op == '+')
			num += num2;
		else if (op == '-')
			num -= num2;

		//Now the real operator sign is the op2, then we now see again if it's '=' or not, if not then continue the loop
		op = op2;
	}

	//Print out the result
	printf("%d", num);

	return 0;
}