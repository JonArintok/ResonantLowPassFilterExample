#include <stdio.h>
#include <float.h>
#include "filter.h"
#include "misc.h"

void setResonance(filterModule *f, double q) {f->q = clamp(0, 1.0, q);}
void setCutoff(filterModule *f, double c) {f->c = clamp(0, 0.99, c);}

filterModule newFilterModule(
	double c,
	double q,
	int    mode
) {
	filterModule f = {
		.c = clamp(0, 0.99, c),
		.q = clamp(0, 1.0, q),
		.b0 = 0,
		.b1 = 0,
		.mode = mode
	};
	return f;
}

double filterSample(filterModule *f, double in) {
	f->b0 += f->c*(in - f->b0 + (f->q + f->q/(1.0 - f->c))*(f->b0 - f->b1));
	f->b1 += f->c*(f->b0 - f->b1);
	switch (f->mode) {
		case filterMode_LP: return f->b1;
		case filterMode_HP: return in - f->b0;
		case filterMode_BP: return f->b0 - f->b1;
	}
	return 0.0;
}


void logFilterModule(filterModule const f) {
	printf(
		" c: %f\n"
		" q: %f\n"
		" b0: %f\n"
		" b1: %f\n"
		" mode: %i\n\n",
		f.c,
		f.q,
		f.b0,
		f.b1,
		f.mode
	);
}






