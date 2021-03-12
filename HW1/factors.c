/*
 * COMP 321 Project 1: Factors
 *
 * This program computes the number of prime factors, and optionally the number
 * of distinct prime factors, for an unsigned integer input.
 * 
 * <kun peng and kp30>
 */

#include <assert.h>
#include <math.h>     // Included in case you use the standard math library.
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

static unsigned int	count_distinct_factors(unsigned int n);
static unsigned int	count_factors(unsigned int n);
static unsigned int	count_factors_recursive(unsigned int n);
static unsigned int find_next_prime(unsigned int n, unsigned int s);
static bool 		is_prime(unsigned int n);
static bool 		is_prime_recursive(unsigned int n, unsigned int s);
static void			test_factors(void);

// Replace this comment with any global variable declarations.

// Replace this comment with any helper functions.
static unsigned int
find_next_prime(unsigned int n, unsigned int s)
{
	if (!is_prime_recursive(s, 2) && s < n)
		return find_next_prime(n, s+1);
	if (n%s == 0)
		return s;
	return find_next_prime(n, s+1);
}

static bool
is_prime(unsigned int n)
{
	unsigned int i;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for(i = 5; i*i < n; i += 6){
		if (n % i == 0 || n % (i+2) == 0)
			return false;
	}
	return true;
}

static bool
is_prime_recursive(unsigned int n, unsigned int s)
{
	if (n == s)
		return true;
	if (n % s == 0)
		return false;
	return is_prime_recursive(n, s+1);
}
  
/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of factors of the input "n".
 */
static unsigned int
count_factors_recursive(unsigned int n)
{
	int nextPrime;

	assert(n > 1);
	nextPrime = find_next_prime(n, 2);
	if (n/nextPrime == 1)
		return 2;
	return 1 + count_factors_recursive(n/nextPrime);
}

/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of factors of the input "n".
 */
static unsigned int
count_factors(unsigned int n)
{
    int d = 2, cur = n, cnt = 1;
	bool is_p_flg = false;

	assert(n > 1);
	while (cur > 1){
		if(d*d > cur){
			++cnt;
			break;
		}
		if (!is_p_flg)
			is_p_flg = is_prime(d);
		if (is_p_flg && cur % d == 0){
			cur /= d;
			++cnt;
		} else {
			++d;
			is_p_flg = false;
		}
	}
	return cnt;
}

/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of distinct factors of the input "n".
 */
static unsigned int
count_distinct_factors(unsigned int n)
{
	int d = 2, cur = n, cnt = 1, pre = 1;
	bool is_p_flg = false;

	assert(n > 1);
	while (cur > 1){
		if(d*d > cur){
			if (pre != cur)
				++cnt;
			break;
		}
		if (!is_p_flg)
			is_p_flg = is_prime(d);
		if (is_p_flg && cur % d == 0){
			if (d != pre){
				++cnt;
				pre = d;
			}
			cur /= d;
		} else {
			++d;
			is_p_flg = false;
		}
	}
	return cnt;
}

/* 
 * Requires:
 *   Nothing.
 *
 * Effects:
 *   Runs testing procedures.  Currently only prints a message.
 */
static void
test_factors(void)
{
	int test_int;
	clock_t start, end;
	printf("Enter an integer for computing its factor: ");
	scanf("%d", &test_int);
	printf("Calling count_factors_recursive. Number of factor of %d is %d\n", test_int, count_factors_recursive(test_int));
	start = clock();
	printf("Calling count_factors. Number of factor of %d is %d\n", test_int, count_factors(test_int));
	end = clock();
	printf("Time used for executing count_factors of input %d is %fs\n", test_int, (double)(end - start)/CLOCKS_PER_SEC);
	printf("Calling count_distinct_factors. Number of distinct factor of %d is %d\n", test_int, count_distinct_factors(test_int));
}

/* 
 * Requires:
 *   Nothing.
 *
 * Effects:
 *   If the "-t" option is specified on the command line, then test code is
 *   executed and the program exits.
 *   
 *   Otherwise, requests a number from standard input.  If the "-r" option is
 *   specified on the command line, then prints the number of prime factors
 *   that the input number has, calculated using a recursive function.
 *   Otherwise, prints the number of prime factors that the input number has
 *   and the number of those factors that are distinct using iterative
 *   functions.
 *
 *   Upon completion, the program always returns 0.
 *
 *   If the number that is input is not between 2 and the largest unsigned
 *   integer, the output of the program is undefined, but it will not crash.
 */
int
main(int argc, char **argv)
{
	unsigned int n;
	int c;
	bool recursive = false;
	bool runtests = false;

	// Parse the command line.
	while ((c = getopt(argc, argv, "rt")) != -1) {
		switch (c) {
		case 'r':             // Use recursive version.
			recursive = true;
			break;
		case 't':             // Run test procedure and exit.
			runtests = true;
			break;
		default:
			break;
		}
	}

	// If "-t" is specified, run test procedure and exit program.
	if (runtests) {
		test_factors();
		return (0);
	}

	// Get input.
	printf("Enter number:\n");
	if (scanf("%u", &n) != 1) {
		fprintf(stderr, "Input error\n");
		return (1);
	}

	// Validate the input.
	if (n < 2) {
		fprintf(stderr, "Invalid input: %u\n", n);
		return (1);
	}

	// Print results.
	if (recursive) {
		// Use recursive version.
		printf("%u has %u prime factors.\n",
		    n, count_factors_recursive(n));
	} else {
		// Use iterative versions.
		printf("%u has %u prime factors, %u of them distinct.\n",
		    n, count_factors(n), count_distinct_factors(n));
	}

	// Report no errors.
	return (0);
}
