#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define sqrt(n) ksqrt(n, 4)
#define GUESS1 (1.2071067811865475244);
#define GUESS2 (1.7071067811865475244);


// hell hell hell hell trick c into letting me treat n as bits
// god I shouldve used bit fields this sucks
#define BITS(n) (*((uint64_t*)&n))

double ksqrt(double n, int k);

int main(int argc, char *argv[])
{
	double input;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <num>\n", argv[0]);
		exit(1);
	}
	sscanf(argv[1], "%lf", &input);

	if (input < 0) {
		fputs("no\n", stderr);
		exit(1);
	}
	printf("sqrt(%.17g) ~ %.17g\n", input, sqrt(input));
}

double ksqrt(double n, int k)
{
	uint64_t temp;
	int magicalFlag = 0;
	double est = GUESS1;
	unsigned int newExp;

	if (n == 0) return 0;

	int exp = ((BITS(n) >> 52) & 0x7ff);
	if ((exp & 1) == 0) {
		exp--;
		magicalFlag = 1;
		est = GUESS2;
	}
	newExp = (exp - 0x3ff) / 2 + 0x3ff;

	// set exponent to 0
	temp = (BITS(n) & 0x800fffffffffffff) | ((uint64_t)0x3ff << 52);
	memcpy(&n, &temp, 8);
	
	// has to be after to not be put back into exponent
	if (magicalFlag) {
		n *= 2;
	}

	// funny -- thing
	while (k --> 0) {
		est = (est + (n / est)) / 2;
	}

	// re-add exponent
	temp = (BITS(est) & 0x800fffffffffffff) | ((uint64_t)(newExp) << 52);
	memcpy(&est, &temp, 8);
	return est;
}
