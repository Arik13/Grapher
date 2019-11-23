#pragma once

#include "Function.h"
#include <boost/lexical_cast.hpp>
#include <string>

bool isFloat(const std::string& someString);
Function* parseFunction(std::string funcStr);
Function* parseFunction(std::string funcStr, int lo, int hi);