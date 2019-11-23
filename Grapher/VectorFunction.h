#pragma once

#include <vector>
#include "Function.h"
#include "Argument.h"

class VectorFunction {
public:
	VectorFunction(Function* f1, Function* f2);
	VectorFunction(Function* f1, Function* f2, Function* f3);
	VectorFunction(Function** functions, int n);
	float* evaluate(char var, float val);
	float* evaluate(char vars[], float vals[], int n);
	float* evaluate(Argument* arg);
private:
	std::vector<Function*> functions;
};