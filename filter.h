
enum {
	filterMode_LP,
	filterMode_HP,
	filterMode_BP,
	filterMode_TOTAL
};

typedef struct {
	double cutoff;
	double resonance;
	double feedbackAmount;
	double b0;
	double b1;
	int    mode;
} filterModule;

double filterSample(filterModule *f, double inputValue);
filterModule newFilterModule(
	double cutoff,
	double resonance,
	int    mode
);
void setResonance(filterModule *f, double resonance);
void setCutoff(filterModule *f, double cutoff);
void logFilterModule(filterModule const f);
