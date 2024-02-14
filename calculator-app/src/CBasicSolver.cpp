#include "CBasicSolver.h"

CBasicSolver::CBasicSolver(const std::string& text)
{
	_actions = TokenizeExpression(text);
}

CBasicSolver::CBasicSolver(const ExpressionsVec& text)
{
	_actions = text;
}

CBasicSolver::CBasicSolver(const ExpressionsVec& source, int start, int end)
{
	for (int a = start; a < end; a++)
	{
		addAction(source[a]);
	}
}

void CBasicSolver::addAction(const std::string& action)
{
	_actions.push_back(action);
}

int CBasicSolver::solveNew()
{
	for (int i = kMinMathSym; i < kMathSymbols.size(); i++)
	{
		std::string operand = kMathSymbols[i];

		auto it = std::find(_actions.begin(), _actions.end(), operand);
		while (it != _actions.end()) {

			int pos = it - _actions.begin();
			if (pos == 0 || pos == _actions.size() - 1) throw std::exception("bad data pos " + pos); // Something is bad

			auto val1 = ToInt(_actions[pos - 1]);
			auto val2 = ToInt(_actions[pos + 1]);
			auto oper = (*it)[0];// This is safe since it always have len of 1
			auto res = ::Solve(val1, val2, oper);

			it = _actions.erase(it - 1, it + 1);
			*it = std::to_string(res);

			it = std::find(_actions.begin(), _actions.end(), operand);
		}
	}

	if (_actions.size() == 1)
	{
		std::string fst = *_actions.begin();
		return atoi(fst.c_str());
	}

	return -1;
}

