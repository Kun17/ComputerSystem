#include <stdio.h>

     /* Put your functions here. */
     int
     fact_for(int n){
	int i;
	int total = 1;
	for(i = 1; i <= n; ++i){
	    total *= i;
	}
	return total;
     }     
     
     int
     fact_while(int n){
     	int total = 1;
	int i = 1;
	while(i <= n){
	    total *= i;
	    ++i;
	}
	return total;
     }

     int
     main(void)
     {
             int n = 5;

             printf("Factorial of %d is %d = %d.\n",
                 n, fact_for(n), fact_while(n));
             return (0);
     }
