#include <stdio.h>

int
sum_upto(int n)
{
	if(n == 0)
		return (0);
	else
		return (n + sum_upto(n - 1));
}

int
main(void)
{
	int n1 = 3;
	int n2 = 5;
	printf("The sum of 0..%d = %d.\nThe sum of 0..%d = %d.\n",
		n1, sum_upto(n1),n2, sum_upto(n2));
	return (0);
}
