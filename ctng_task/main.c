#include <stdio.h>

int main(void)
{
	int num1,num2,res;

	printf("Enter 1st Number: ");
	scanf("%d",&num1);
        printf("Enter 2nd Number: ");
	scanf("%d",&num2);

	res = num1 + num2;
	printf("%d + %d = %d \n",num1,num2,res);

	return 0;
}

