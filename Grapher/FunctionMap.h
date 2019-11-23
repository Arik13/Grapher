#pragma once

#include <functional>
#include <map>
#include <vector>
#include "Function.h"

class FunctionMap : public std::map<std::string, std::function<float(Argument*, Function**)> > {
public:
	FunctionMap();
};
