#include <math.h>
// See also: http://en.wikipedia.org/wiki/Champernowne_constant
// 9 * 1, 90 * 2, 900 * 3, 9000 * 4, 90000 * 5 ...
static const int sieve[] = {9 * 1, 90 * 2, 900 * 3, 9000 * 4, 90000 * 5, 900000 * 6};
static 
int GetDigitByPos(int number, int pos)
	{
	char buffer[16] = {0};
	char* ptr = buffer;
	for(; number != 0;)
		{
		*ptr++ = number % 10;
		number /= 10;
		}

	if(pos == 0)
		return buffer[0];
	return *(ptr - pos);
	}
static
int GetValueByPos(int pos)throw (int)
	{
	int cur = 0;
	for(size_t i = 0; i < sizeof(sieve) / sizeof(sieve[0]); ++i)
		{
		cur += sieve[i];
		if(cur > pos)
			{
			pos -= (cur - sieve[i]);
			cur = (i == 0) ? (1) : ((int)pow(10.0, (int)i));
			cur += (pos - 1) / (i + 1);
			return GetDigitByPos(cur, pos % (i + 1));
			}
		}
	throw int(-1);
	}

// 1, 10, 100, 1000, 10000, 100000, 1000000
int GetTheValueOfTheExpressionDescribedAsTheProblem()
	{
	return GetValueByPos(1) * GetValueByPos(10) * GetValueByPos(100) * GetValueByPos(1000) * GetValueByPos(10000)
		* GetValueByPos(100000) * GetValueByPos(1000000);
	}
