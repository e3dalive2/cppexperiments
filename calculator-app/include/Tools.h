#pragma once

#include <vector>
#include <string>
#include <iostream>

// Operands and priorities
const std::vector<std::string> kMathSymbols = { {"("},{")"}, {"*"},{"/"},{"+"},{"-"} };
constexpr auto kMinMathSym = 2;

using ExpressionsVec = std::vector <std::string >;


template<class Any>
inline Any Solve(Any val, Any val2, char oper)
{
	auto res = 0;
	if (oper == '*') res = val * val2;
	else if (oper == '/') res = val / val2;
	else if (oper == '+') res = val + val2;
	else if (oper == '-') res = val - val2;
	else throw std::exception("invalid operator " + oper);
	std::cout << val << oper << val2 << "=" << res << "\n";
	return res;
}

bool IsMathSymbol(char c);
int ToInt(const std::string& st);
bool IsDigit(const std::string& st);
ExpressionsVec TokenizeExpression(const std::string& text);
void DisplayExprVec(const ExpressionsVec& actions, int start, int end);
void DisplayExprVec(const ExpressionsVec& actions);


int FindStartOfSolvableSubexpression(const ExpressionsVec& actions, size_t start);

int FindClosingParenthesisAfterDigit(const ExpressionsVec& actions, size_t start);

// Rollable version added for simplicity in order not to create the same code many times
int FindClosingParenthesisAfterDigitRoll(const ExpressionsVec& actions, size_t start);