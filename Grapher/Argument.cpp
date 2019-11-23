#include "Argument.h"

Argument::Argument(char varName, float value) {
	emplace(varName, value);
}

Argument::Argument(char varNames[], float values[], int n) {
	for (int i = 0; i < n; i++) {
		emplace(varNames[i], values[i]);
	}
}