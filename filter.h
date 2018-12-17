
enum {
	filterMode_LP,
	filterMode_HP,
	filterMode_BP,
	filterMode_TOTAL
};

typedef struct {
	double cutoff;    // 0 to 1
	double resonance; // 0 to 1
	double feedback;  // 0 to 1
	double b0;        // -1 to 1
	double b1;        // -1 to 1
	int    mode;
} filterModule;

double filterSample(filterModule *f, double in);
filterModule newFilterModule(
	double cutoff,
	double resonance,
	int    mode
);
void setResonance(filterModule *f, double resonance);
void setCutoff(filterModule *f, double cutoff);
void logFilterModule(filterModule const f);
