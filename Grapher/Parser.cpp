#include <iostream>
#include "Parser.h"

bool isFloat(const std::string& str) {
	using boost::lexical_cast;
	using boost::bad_lexical_cast;
	try {
		boost::lexical_cast<float>(str);
		return true;
	}
	catch (bad_lexical_cast&) { return false; };
}

Function* parseFunction(std::string funcStr) {
	std::string trimmedFuncStr = "";
	for (int i = 0; i < funcStr.length(); i++) {
		if (funcStr[i] != ' ') {
			trimmedFuncStr += funcStr[i];
		}
	}
	return parseFunction(trimmedFuncStr, 0, trimmedFuncStr.length() - 1);
}

Function* parseFunction(std::string funcStr, int lo, int hi) {
	std::string subStr = funcStr.substr(lo, ((hi - lo) + 1));

	// Base Case: Function is a variable
	if (lo == hi && funcStr[lo] >= 'a' && funcStr[lo] <= 'z') {
		//std::cout << "Got here second" << std::endl;
		return new Function(std::string(1, funcStr[lo]));
	}

	// Base Case: Function is a constant
	if (isFloat(subStr)) {
		return new Function("const", boost::lexical_cast<float>(subStr));
	}

	// Split into sum or difference of sub functions
	int bracketLayer = 0;
	for (int i = lo; i < hi; i++) {
		if (funcStr[i] == '(') bracketLayer++;
		if (funcStr[i] == ')') bracketLayer--;
		if (bracketLayer == 0 && funcStr[i] == '+') {
			return new Function("+", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
		}
		else if (bracketLayer == 0 && funcStr[i] == '-') {
			return new Function("-", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
		}
	}

	// Split into product or quotient of sub functions
	bracketLayer = 0;
	for (int i = lo; i < hi; i++) {
		if (funcStr[i] == '(') bracketLayer++;
		if (funcStr[i] == ')') bracketLayer--;
		if (bracketLayer == 0 && funcStr[i] == '*') {
			return new Function("*", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
		}
		else if (bracketLayer == 0 && funcStr[i] == '/') {
			return new Function("/", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
		}
	}

	// Split into an exponential operation between a base sub function and an exponent sub function
	bracketLayer = 0;
	for (int i = lo; i < hi; i++) {
		if (funcStr[i] == '(') bracketLayer++;
		if (funcStr[i] == ')') bracketLayer--;
		if (bracketLayer == 0 && funcStr[i] == '^') {
			return new Function("^", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
		}
	}

	// Parse the statement between two brackets
	if (funcStr[lo] == '(') {
		return parseFunction(funcStr, lo + 1, hi - 1);
	}
	// Parse an elementary function and its argument
	else if (funcStr.find("abs", lo) == lo) {
		return new Function("abs", parseFunction(funcStr, lo + 4, hi - 1));
	}
	else if (funcStr.find("sin", lo) == lo) {
		return new Function("sin", parseFunction(funcStr, lo + 4, hi - 1));
	}
	else if (funcStr.find("cos", lo) == lo) {
		return new Function("cos", parseFunction(funcStr, lo + 4, hi - 1));
	}
	else if (funcStr.find("tan", lo) == lo) {
		return new Function("tan", parseFunction(funcStr, lo + 4, hi - 1));
	}
	else if (funcStr.find("arcsin", lo) == lo) {
		return new Function("arcsin", parseFunction(funcStr, lo + 7, hi - 1));
	}
	else if (funcStr.find("arccos", lo) == lo) {
		return new Function("arccos", parseFunction(funcStr, lo + 7, hi - 1));
	}
	else if (funcStr.find("arctan", lo) == lo) {
		return new Function("arctan", parseFunction(funcStr, lo + 7, hi - 1));
	}
	else if (funcStr.find("ln", lo) == lo) {
		//std::cout << "Got here first" << std::endl;
		return new Function("ln", parseFunction(funcStr, lo + 3, hi - 1));
	}
	else if (funcStr.find("log", lo) == lo) {
		return new Function("log", parseFunction(funcStr, lo + 4, hi - 1));
	}
	else if (funcStr.find("PI", lo) == lo) {
		return new Function("PI", nullptr);
	}
	return nullptr;
}