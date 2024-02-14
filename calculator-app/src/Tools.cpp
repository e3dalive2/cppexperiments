#include "Tools.h"

bool IsMathSymbol(char c)
{
	std::string s;
	s += c;
	return std::find(kMathSymbols.begin(), kMathSymbols.end(), s) != kMathSymbols.end();
}

int ToInt(const std::string& st)
{
	if (st.length() == 1 && IsMathSymbol(st[0]))
	{
		throw std::exception("invalid int " + st[0]);
	}
	return atoi(st.c_str());
}

bool IsDigit(const std::string& st)
{
	return isdigit(st[0]);
}


ExpressionsVec TokenizeExpression(const std::string& text)
{
	ExpressionsVec actions;

	std::string curVal;

	for (auto& c : text)
	{
		if (c == ' ') continue;// Ignore space

		bool isDigit = isdigit(c);
		if (isDigit)
		{
			curVal += c;
		}
		else if (IsMathSymbol(c))
		{
			if (c == '-' && curVal.empty())
			{
				// handle cases for -number or +-number
				if ((actions.size() > 1 && IsMathSymbol(actions.back()[0])) || (actions.empty()))
				{
					curVal = "-" + curVal;
					continue;
				}
			}

			if (!curVal.empty())
			{
				actions.push_back(curVal);
				curVal = "";
			}


			std::string action;
			action += c;
			actions.push_back(action);
		}
		// ignore others

	}

	if (!curVal.empty()) // add remaining one
	{
		actions.push_back(curVal);
	}

	return actions;
}


void DisplayExprVec(const ExpressionsVec& actions, int start, int end)
{
	for (size_t i = start; i < end; i++)
	{
		std::cout << actions[i] << " ";
	}
	std::cout << "\n";
}

void DisplayExprVec(const ExpressionsVec& actions)
{
	DisplayExprVec(actions, 0, actions.size());
}

int FindStartOfSolvableSubexpression(const ExpressionsVec& actions, size_t start)
{
	for (int i = start; i >= 0; i--)
	{
		std::string st = actions[i];
		std::string prev = actions[i + 1];
		if (!IsDigit(st) && IsDigit(prev))
		{
			if (st == "(")
			{
				return i + 1;
			}
			else if (st == ")")
			{
				std::cout << "failed for ";
				DisplayExprVec(actions, i, start);
				return -1;
			}
		}
	}
	std::cout << "eof for ";
	DisplayExprVec(actions, 0, start);
	return -1;
}

int FindClosingParenthesisAfterDigit(const ExpressionsVec& actions, size_t start)
{
	if (start < 1) start = 1;

	for (size_t i = start; i < actions.size(); i++)
	{
		const auto& cur = actions[i];
		const auto& prev = actions[i - 1];
		if (cur == ")" && IsDigit(prev))
		{
			return i;
		}
	}
	return -1;
}

int FindClosingParenthesisAfterDigitRoll(const ExpressionsVec& actions, size_t start)
{
	bool wasNotRolled = start >= actions.size();
	if (start < 1 || wasNotRolled) start = 1;

	int pos = FindClosingParenthesisAfterDigit(actions, start);
	if (pos != -1) return pos;

	if (!wasNotRolled) return -1;

	return FindClosingParenthesisAfterDigit(actions, 1);
}
