
enum {
	filterMode_LP,
	filterMode_HP,
	filterMode_BP,
	filterMode_TOTAL
};

typedef struct {
	double c;  // cutoff, 0 to 0.99
	double q;  // resonance, 0 to 1
	double b0; // bank0, -1 to 1
	double b1; // bank1, -1 to 1
	int    mode;
} filterModule;

double filterSample(filterModule *f, double in);
filterModule newFilterModule(
	double c,
	double q,
	int    mode
);
void setResonance(filterModule *f, double q);
void setCutoff(filterModule *f, double c);
void logFilterModule(filterModule const f);
