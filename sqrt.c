#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sqrt(n) ksqrt(n, 5)

// hell hell hell hell trick c into letting me treat n as bits
#define BITS(n) (*((unsigned long long int*)&n))

double ksqrt(double n, int k);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <num>\n", argv[0]);
		exit(1);
	}
	double input;
	sscanf(argv[1], "%lf", &input);
	if (input < 0) {
		fputs("no\n", stderr);
		exit(1);
	}
	printf("sqrt(%.17g) ~ %.17g\n", input, sqrt(input));
}

double ksqrt(double n, int k)
{
	if (n == 0) return 0;
	double est = 1.5;

	unsigned long long int temp;

	int magicalFlag = 0;

	int exp = ((BITS(n) >> 52) & 0x7ff);
	if ((exp & 1) == 0) {
		exp--;
		magicalFlag = 1;
		est = 3;
	}
	unsigned int newExp = (exp - 0x3ff) / 2 + 0x3ff;

	// set exponent to 0
	temp = (BITS(n) & 0x800fffffffffffff) | ((unsigned long long int)0x3ff << 52);
	memcpy(&n, &temp, 8);
	
	printf("%lf\n", n);

	// magical stuff
	if (magicalFlag) {
		n *= 2;
	}

	printf("%lf\n", n);

	while (k --> 0) {
		est = (est + (n / est)) / 2;
	}
	printf("%lf\n", est);

	// re-add exponent
	printf("%d\n", newExp);
	temp = (BITS(est) & 0x800fffffffffffff) | ((unsigned long long int)(newExp) << 52);
	memcpy(&est, &temp, 8);
	printf("%lf\n", est);
	return est;
}
