extern int GetPrimeList(int len, int *buffer);
static const double Limit = 10000000.0;
#define DBL_MAX 1.7976931348623158e+308 

#include <vector>
#include <algorithm>
#include <cmath>
#define xpow(x, n)	(unsigned)pow((double)x, (int)n)
#define dgtGet(ull, pos)	(ull / xpow(10, pos) % 10)
#define dgtAdd(ull, pos)	(ull += xpow(10, pos))
#define dgtSub(ull, pos)	(ull -= xpow(10, pos))

bool isPermutation(unsigned x, unsigned y)
	{
	unsigned long long sieve = 0;
	for(; x != 0; x /= 10)
		dgtAdd(sieve, x % 10);

	for(; y != 0; y /= 10)
		{
		if(dgtGet(sieve, y % 10) <= 0)
			return false;
		dgtSub(sieve, y % 10);
		}
	return (sieve == 0);
	}
unsigned solve_70()
	{
	int bufLen = (int)/*Limit*/5000;	// Why 5000 is big enough ?
	int* primes = new int[bufLen];
	unsigned result = 0;
	double least = DBL_MAX;

	const int PrimeCount = GetPrimeList(bufLen, primes);
	const int Lower = 0;
//345 497
	for(int i = PrimeCount - 1; i >= Lower; --i)
		for(int j = i - 1; j >= Lower; --j)
		{
		unsigned cur = primes[i] * primes[j];
		
		if(cur > (unsigned)Limit)
			continue;

		unsigned pi = (primes[i] - 1) * (primes[j] - 1);
		double test = (double)pi / cur;

		if(test >= 10.0)
			continue;
		if(test <= 0.1)
			break;
		if(isPermutation(pi, cur))
			{
			double curRatio = (double)cur / pi;
			if(curRatio < least)
				result = cur, least = curRatio;
			}
		}
	delete []primes;
	return result;
	}