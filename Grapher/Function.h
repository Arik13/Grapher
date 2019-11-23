#pragma once

#include <string>
#include <functional>
#include <map>
#include "Argument.h"

class FunctionMap;

class Function {
public:
	Function(std::string funcName);				// Variable Function Constructor
	Function(std::string func, float val);		// Constant Function Constructor
	Function(std::string func, Function* arg);	// Single Sub Function Constructor
	Function(std::string func, Function* arg1, Function* arg2);		// Double Sub Function Constructor
	Function(Function* func);
	~Function();
	float evaluate(char var, float val);
	float evaluate(char vars[], float vals[], int n);
	float evaluate(Argument* arg);
	bool isVariable(std::string var);
	Function* differentiate(std::string var);
	Function* tangentPlane(char* vars, float* values, int n);
	std::string name();

private:
	static FunctionMap* funcMap;
	std::string funcName;
	std::function<float(Argument*, Function**)> function;
	Function** subFuncs;
	int numSubFuncs;
};