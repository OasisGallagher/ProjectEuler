#include <fstream>

int solve_99()
{
	double curMax = 0.0;
	int lineNumber = 0;
	int line = 1;
	for(std::ifstream ifs("base_exp.txt"); ifs; ++line)
	{
		int base;
		double exp;
		ifs >> base;
		ifs.ignore();
		ifs >> exp;
		ifs.ignore();

		if((exp *= (log10((double)base))) > curMax)
		{
			curMax = exp;
			lineNumber = line;
		}
	}
	return lineNumber;
}