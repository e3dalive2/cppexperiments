// This a calculator app, it solves basic equation +-/* with () with order. It also handles - cases for negative numbers
// I did the iterative version(more human with iteration pass with which the equation get's simplified more and more, since I didn't have much time
// So for developer who will read this, sorry if you eyes will bleed a little

#include <iostream>
#include <string>

#include "CBasicSolver.h"


class CCalcSolver
{
public:

	int solve(const std::string& text)
	{

		auto tokenized = TokenizeExpression(text);

		// first part is to solve ()
		// we need to find ) and closes to it ( with digits inside
		DisplayExprVec(tokenized);


		int offset = 1;

		int i = 0;
		while (i != -1)
		{
			i = FindClosingParenthesisAfterDigitRoll(tokenized, offset);
			if (i == -1) break;
			offset = i + 1;

			std::string cur = tokenized[i];
			std::string prev = tokenized[i - 1];

			auto solvable = FindStartOfSolvableSubexpression(tokenized, i - 1);
			if (solvable == -1) continue;

			CBasicSolver solver(tokenized, solvable, i);
			int res = solver.solveNew();

			int startPos = solvable - 1;
			int endPos = i;
			tokenized.erase(tokenized.begin() + startPos, tokenized.begin() + endPos);
			tokenized[startPos] = std::to_string(res);

			std::cout << "next ";
			DisplayExprVec(tokenized);

		}

		{
			CBasicSolver solver(tokenized);
			return solver.solveNew();
		}

	}


};

int main()
{
	std::string test = "(2+3) * (20-10)";

	//test = "(2+3) * (200-10*(15-7)+(72-6))";

	//test = "(7+6)*(72-4*(15-6))+10";

	//test = "5+4*3-2";

	//test = "12-9";

	//test = "19+2-2*6+7+42/2+4";

	//test = "6*7+2+7*4/2";

	//test = "-5+-5*4";

	CCalcSolver solver;
	int result = solver.solve(test);
	std::cout << "result " << result << "\n";

	return 0;
}