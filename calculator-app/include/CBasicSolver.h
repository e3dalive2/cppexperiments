#pragma once

#include "Tools.h"

class CBasicSolver
{
public:

	CBasicSolver(const std::string& text);

	CBasicSolver(const ExpressionsVec& text);

	CBasicSolver(const ExpressionsVec& source, int start, int end);

	void addAction(const std::string& action);

	int solveNew();

protected:
	ExpressionsVec _actions;
};
