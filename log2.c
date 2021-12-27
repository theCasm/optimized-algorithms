#include <stdio.h>
#include <stdlib.h>

float log2LIN(float n);
float log2QUA(float n);

int main(int argc, char *argv[])
{
	if (argc < 3) {
		char *file = argv[0];
		if (argc < 1) {
			file = "./log2";
		}

		fprintf(stderr, "Usage: %s <q(uadratic) | l(inear)> <number>\n", file);
		exit(1);
	}
	float input;
	float ans;
	if (sscanf(argv[2], "%f ", &input) < 1) {
		fputs("Invalid input\n", stderr);
		exit(1);
	}

	// lowercase compare first char
	if ((argv[1][0] | 0x20) == 'l') {
		ans = log2LIN(input);
	} else {
		// default to quadratic
		ans = log2QUA(input);
	}
	printf("log2(%f) ~ %f\n", input, ans);

	return 0;
}

float log2LIN(float n)
{
	long bits = *((long *)&n);
	long exp = ((bits >> 23) & 0xff) - 127;
	long fraction = bits & 0x7fffff;

	// convert to float, first give exponent of 0 (see IEEE-754)
	fraction |= (127 << 23);
	float ans = *((float*)&fraction);

	return exp + ans - 1;
}

/* 
 * this switches between 2 quadratic equations to get a more accurate answer
 * the first equation is (-sqrt(2)/4)(x + 1/(4sqrt(2) - 6))^2 + (9sqrt(2) + 8)/16
 * this can be gotten by a system of a(1-p)^2 + q = 0, a(sqrt(2)-p)^2 + q = 0.5, and a(2-p)^2 + q = 1
 * which is based off of values of log
 *
 * The second equation is (-1/3)(x-3)^2 + (4/3), which is based off of playing around with a system of
 * just two equations, for y = 0 and y = 1
 */
float log2QUA(float n)
{
	long bits = *((long *)&n);
	long exp = ((bits >> 23) & 0xff) - 127;
	long fraction = bits & 0x7fffff;

	// convert to float, first give exponent of 0 (see IEEE-754)
	fraction |= (127 << 23);
	float mant = *((float*)&fraction);

	// apply function depending on value
	if (mant < 1.478f) {
		mant -= 2.914213562f;
		mant = (mant*mant)*(-0.3535533906f) + (1.295495129f);
	} else {
		mant -= 3;
		mant = mant*mant*(-1.0f/3.0f) + (4.0f/3.0f);
	}
	return mant + exp;
}
