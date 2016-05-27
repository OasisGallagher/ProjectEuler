// http://www.mathblog.dk/project-euler-63-n-digit-nth-power/
#include <cmath>
/* For an integer x:
 10^(n-1) <= x^n < 10^n	-> x < 10.
-> 10^(n-1) <= x^n
-> n - 1 <= log(x^n)
-> n - 1 <= log(x) * n
-> (n - 1) / n <= log(x)
-> x >= 10^((n - 1) / n).
-> x in range [ceil(10^((n - 1) / n)), 10) is OK.
-> let lower = ceil(10^((n - 1) / n)), lower must be less than 10.
-> lim{n->infinite} ((n - 1) / n) = 1, so, lower -> 10, as a result,
-> the loop will be terminated.
*/
unsigned GetTheCountOfNDigitPositiveIntegersExistWhichAreAlsoAnNthPower()
	{
	unsigned result = 0;
	double n = 1.0;
	for(unsigned lower = 0; lower < 10; ++n)
		{
		lower = (int)ceil(pow(10.0, (n - 1.0) / n));
		result += (10 -lower);
		}
	return result;
	}
