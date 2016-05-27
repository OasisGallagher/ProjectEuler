#include <math.h>
bool IsPrime(unsigned x)
{
	if(x == 1) return false;
	for(unsigned i = 2; i * i <= x; ++i)
		if(x % i == 0)
			return false;
	return true;
}

int GetThe10001stPrimeNumber()
{
	unsigned count = 1;	// 2 is prime.
	for(unsigned i = 3; ; i += 2)	// test only odd numbers..
	{
		if(IsPrime(i))
		{
			++count;
			if(count == 10001)
				return i;
		}
	}
}
