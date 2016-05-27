// http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
// See ./PE64.pdf corollary 3.3 tells us how to terminate the iteration.
#include <cmath>

#define NextM(d, a, m)	(d * a - m)
#define NextD(S, m, d)	((S - m * m) / d)
#define NextA(a0, m, d)	((a0 + m) / d)

int GetTheCountOfContinuedFractionsForNLessEqualTo100HaveAnOddPeriod()
	{
	int result = 0;
	for(int S = 2; S <= 10000; ++S)
		{
		int a = (int)sqrt((double)S);
		if(a * a == S) continue;	// Skip perfect square.

		int m = 0, d = 1, a0 = a, count = 0;
		while(a != 2 * a0)
			{
			++count;
			m = NextM(d, a, m);
			d = NextD(S, m, d);
			a = NextA(a0, m, d);
			}
		result += (count & 1);
		}
	return result;
	}
