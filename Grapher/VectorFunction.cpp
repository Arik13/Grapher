#include "VectorFunction.h"

VectorFunction::VectorFunction(Function* f1, Function* f2) {
	functions.push_back(f1);
	functions.push_back(f2);
}

VectorFunction::VectorFunction(Function* f1, Function* f2, Function* f3) {
	functions.push_back(f1);
	functions.push_back(f2);
	functions.push_back(f3);
}

VectorFunction::VectorFunction(Function** functions, int n) {
	for (int i = 0; i < n; i++) {
		this->functions.push_back(functions[i]);
	}
}

float* VectorFunction::evaluate(char var, float val) {
	Argument* arg = new Argument(var, val);
	float* evaluation = evaluate(arg);
	delete arg;
	return evaluation;
}

float* VectorFunction::evaluate(char vars[], float vals[], int n) {
	Argument* arg = new Argument(vars, vals, n);
	float* evaluation = evaluate(arg);
	delete arg;
	return evaluation;
}

float* VectorFunction::evaluate(Argument* arg) {
	float* values = new float[functions.size()];
	for (int i = 0; i < functions.size(); i++) {
		values[i] = functions[i]->evaluate(arg);
	}
	return values;
}
