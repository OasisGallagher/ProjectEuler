#include <math.h>
#include <algorithm>
//At first I thought circular primes were any permutation of the prime, but then 
//791 would be in the example as well, so I realised that it is primes that you 
//can rotate such that any rotation is also a prime.

static const int limit = 1000000;
static int primeList[1000000];
static int primeCount;
extern int GetPrimeList(int len, int *buffer);
static const int InvalidRotatedNumber = -1;

static const int sieve[] = {10, 100, 1000, 10000, 100000, 1000000};

static
bool CheckContains2Or5(int number)
	{
	for(; number != 0; number /= 10)
		{
		int temp = number % 10;
		if(temp % 2 == 0 || temp % 5 == 0)
			return false;
		}
	return true;
	}

static
int ShiftLeft(int number)
	{
	if(!CheckContains2Or5(number))
		return InvalidRotatedNumber;
	
	int temp = (int)pow((double)10, (int)log10((double)number));
	return int(10 * (number % temp) + number / temp);
	}

static 
bool IsPrime(int number)
	{
	return std::binary_search(primeList, primeList + primeCount, number);
	}

static 
bool IsRotatePrime(int number)
	{
	int next = number;

	while((next = ShiftLeft(next)) != number && next != InvalidRotatedNumber)
		{
		if(!IsPrime(next))
			return false;
		}

	return (next == number);
	}

int GetTheCountOfCircularPrimesBelow1000000()
	{
	primeCount = GetPrimeList(limit, primeList);

	int result = 4;
	for(int i = 4; i < primeCount; ++i)
		if(IsRotatePrime(primeList[i]))
			++result;

	return result;
	}
