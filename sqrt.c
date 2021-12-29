#include <stdio.h>
#include <stdlib.h>

#define sqrt(n) ksqrt(n, 5)

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
	printf("sqrt(%lf) ~ %lf\n", input, sqrt(input));
}

double ksqrt(double n, int k)
{
	if (n == 0) return 0;
	double est = n;

	int exp = ((*((long long int*)&n) >> 52) & 0x7ff) - 0x3ff;
	
	if (exp == 0) {
		est = 1;
	} else {
		est /= (2 << (((exp + 1) >> 1) - 1));
	}

	while (k-- > 0) {
		est = (est + (n / est)) / 2;
	}
	return est;
}
