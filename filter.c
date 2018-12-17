#include <stdio.h>
#include <float.h>
#include "filter.h"

void updateFeedbackAmount(filterModule *f) {
	if (f->cutoff == 1.0) {
		f->feedback = f->resonance + f->resonance/(DBL_MIN);
	}
	else {
		f->feedback = f->resonance + f->resonance/(1.0 - f->cutoff);
	}
}
void setResonance(filterModule *f, double resonance) {
	f->resonance = resonance;
	updateFeedbackAmount(f);
}
void setCutoff(filterModule *f, double cutoff) {
	f->cutoff = cutoff;
	updateFeedbackAmount(f);
}

filterModule newFilterModule(
	double cutoff,
	double resonance,
	int    mode
) {
	filterModule f = {
		.cutoff = cutoff,
		.resonance = resonance,
		.b0 = 0,
		.b1 = 0,
		.mode = mode
	};
	updateFeedbackAmount(&f);
	return f;
}

double filterSample(filterModule *f, double in) {
	f->b0 += f->cutoff * (in - f->b0 + f->feedback*(f->b0 - f->b1));
	f->b1 += f->cutoff * (f->b0 - f->b1);
	switch (f->mode) {
		case filterMode_LP: return f->b1;
		case filterMode_HP: return in - f->b0;
		case filterMode_BP: return f->b0 - f->b1;
	}
	return 0.0;
}


void logFilterModule(filterModule const f) {
	printf(
		" cutoff: %f\n"
		" resonance: %f\n"
		" feedback: %f\n"
		" b0: %f\n"
		" b1: %f\n"
		" mode: %i\n\n",
		f.cutoff,
		f.resonance,
		f.feedback,
		f.b0,
		f.b1,
		f.mode
	);
}






