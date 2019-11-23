#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "FunctionMap.h"

 FunctionMap::FunctionMap(){
	 std::function<float(Argument*, Function**)> eFunc		= [](Argument* t, Function** subFuncs) {return M_E; };
	 std::function<float(Argument*, Function**)> piFunc		= [](Argument* t, Function** subFuncs) {return M_PI; };
	 std::function<float(Argument*, Function**)> absFunc	= [](Argument* t, Function** subFuncs) {return abs(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> sinFunc	= [](Argument* t, Function** subFuncs) {return sin(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> cosFunc	= [](Argument* t, Function** subFuncs) {return cos(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> tanFunc	= [](Argument* t, Function** subFuncs) {return tan(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> asinFunc	= [](Argument* t, Function** subFuncs) {return asin(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> acosFunc	= [](Argument* t, Function** subFuncs) {return acos(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> atanFunc	= [](Argument* t, Function** subFuncs) {return atan(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> lnFunc		= [](Argument* t, Function** subFuncs) {return log(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> logFunc	= [](Argument* t, Function** subFuncs) {return log10(subFuncs[0]->evaluate(t)); };
	 std::function<float(Argument*, Function**)> sumFunc	= [](Argument* t, Function** subFuncs) {return subFuncs[0]->evaluate(t) + subFuncs[1]->evaluate(t); };
	 std::function<float(Argument*, Function**)> difFunc	= [](Argument* t, Function** subFuncs) {return subFuncs[0]->evaluate(t) - subFuncs[1]->evaluate(t); };
	 std::function<float(Argument*, Function**)> prodFunc	= [](Argument* t, Function** subFuncs) {return subFuncs[0]->evaluate(t) * subFuncs[1]->evaluate(t); };
	 std::function<float(Argument*, Function**)> divFunc	= [](Argument* t, Function** subFuncs) {return subFuncs[0]->evaluate(t) / subFuncs[1]->evaluate(t); };
	 std::function<float(Argument*, Function**)> powFunc	= [](Argument* t, Function** subFuncs) {return pow(subFuncs[0]->evaluate(t), subFuncs[1]->evaluate(t)); };
	 
	 for (int i = 'a'; i < 'z'; i++) {
		 if (i == 'e') i++;
		 if (i == 'i') i++;
		 std::function<float(Argument*, Function**)> varFunc = [i](Argument* arg, Function** subFuncs) { return (*arg)[i]; };
		 emplace(std::string(1, i), varFunc);
	 }
	 emplace("e", eFunc);
	 emplace("PI", piFunc);
	 emplace("abs", absFunc);
	 emplace("sin", sinFunc);
	 emplace("cos", cosFunc);
	 emplace("tan", tanFunc);
	 emplace("arcsin", asinFunc);
	 emplace("arccos", acosFunc);
	 emplace("arctan", atanFunc);
	 emplace("ln", lnFunc);
	 emplace("log", logFunc);
	 emplace("+", sumFunc);
	 emplace("-", difFunc);
	 emplace("*", prodFunc);
	 emplace("/", divFunc);
	 emplace("^", powFunc);
	 
}