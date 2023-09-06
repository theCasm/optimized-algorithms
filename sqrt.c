#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define sqrt(n) ksqrt(n, 4)
#define GUESS1 (1.2071067811865475244)
#define GUESS2 (1.7071067811865475244)

double ksqrt(double n, int k);

union DBits {
	double val;
	struct {
		uint64_t mantissa : 52;
		unsigned int exponent : 11;
		unsigned int sign : 1;
	};
};

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
	union DBits num, est;
	int magicalFlag = 0;
	unsigned int newExp;

	if (n == 0) return 0;
	num.val = n;
	est.val = GUESS1;
	
	if ((num.exponent & 1) == 0) {
		// will be odd after subtracting 1023
		num.exponent--;
		magicalFlag = 1;
		est.val = GUESS2;
	}
	newExp = (num.exponent - 0x3ff) / 2 + 0x3ff;

	// set exponent to 0
	num.exponent = 0x3ff;
	
	// has to be after to not be put back into exponent
	if (magicalFlag) {
		num.val *= 2;
	}

	while (k --> 0) {
		est.val = (est.val + (num.val / est.val)) / 2;
	}

	// re-add exponent
	est.exponent = newExp;
	return est.val;
}
