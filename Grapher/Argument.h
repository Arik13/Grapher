#pragma once

#include <map>

class Argument : public std::map<char, float> {
public:
	Argument(char varName, float value);
	Argument(char varNames[], float values[], int n);
private:
};