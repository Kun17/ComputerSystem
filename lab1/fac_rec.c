#include <stdio.h>

     int
     fact_rec(int n){
	if(n == 1) return 1;
	return n * fact_rec(n-1);
     }


     int
     main(void)
     {
             int n = 5;

             printf("The factorial of %d is %d.\n",
                 n, fact_rec(n));
             return (0);
     }
