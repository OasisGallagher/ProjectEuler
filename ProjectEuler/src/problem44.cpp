// http://www.divye.in/2012/07/how-do-you-determine-if-number-n-is.html
#include <cmath>

bool IsPentagonalNumber(int number)
	{
	double temp = (1 + std::sqrt(1 + 24.0 * number)) / 6;
	return temp == (int)temp;
	}

static inline
int GetPentagonalNumber(int generater)
	{
	return generater * (3 * generater - 1) / 2;
	}

int GetValueOfD()
	{
	for(int i = 1; ; ++i)
		{
		int first = GetPentagonalNumber(i);
		for(int j = i - 1; j > 0; --j)
			{
			int second = GetPentagonalNumber(j);
			if(IsPentagonalNumber(first + second) && IsPentagonalNumber(first - second))
				return first - second;
			}
		}
	}