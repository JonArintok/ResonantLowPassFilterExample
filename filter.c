#include <stdio.h>
#include "filter.h"

void updateFeedbackAmount(filterModule *f) {
	f->feedbackAmount = f->resonance + f->resonance/(1.0 - f->cutoff);
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

double filterSample(filterModule *f, double inputValue) {
	f->b0 += f->cutoff * (inputValue - f->b0);
	f->b1 += f->cutoff * (f->b0 - f->b1);
	switch (f->mode) {
		case filterMode_LP:
			return f->b1;
		case filterMode_HP:
			return inputValue - f->b0;
		case filterMode_BP:
			return f->b0 - f->b1;
		default:
			return 0.0;
	}
}


void logFilterModule(filterModule const f) {
	printf(
		" cutoff: %f\n"
		" resonance: %f\n"
		" feedbackAmount: %f\n"
		" b0: %f\n"
		" b1: %f\n"
		" mode: %i\n\n",
		f.cutoff,
		f.resonance,
		f.feedbackAmount,
		f.b0,
		f.b1,
		f.mode
	);
}






