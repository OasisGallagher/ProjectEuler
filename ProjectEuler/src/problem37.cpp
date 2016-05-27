#include <math.h>
#include <algorithm>

static const int limit = 1000000;
static int primeList[1000000];
static int primeCount;
extern int GetPrimeList(int len, int *buffer);
static const int InvalidRotatedNumber = -1;

static 
int ShiftLeft(int number)
	{
	if(number < 10)
		return 0;
	int mysieve = (int)pow(10.0, (int)log10((double)number));
	return number % mysieve;
	}

static inline
int ShiftRight(int number)
	{
	return number / 10;	
	}

static inline
bool IsPrime(int number)
	{
	return std::binary_search(primeList, primeList + primeCount, number);
	}

static 
bool IsBindPrime(int number)
	{
	int next = number;
	
	while((next = ShiftLeft(next)) != 0 && next != InvalidRotatedNumber)
		{
		if(!IsPrime(next))
			return false;
		}
	if(next != 0)
		return false;

	next = number;
	while((next = ShiftRight(next)) != 0 && next != InvalidRotatedNumber)
		{
		if(!IsPrime(next))
			return false;
		}

	return (next == 0);
	}

int GetTheSumOfOnlyElevenPrimesThatAreBothTruncatableFromLeftToRightAndRightToLeft()
	{
	primeCount = GetPrimeList(limit, primeList);

	int result = 0;
	int count = 0;
	for(int i = 4; i < primeCount; ++i)
		if(IsBindPrime(primeList[i]))
			{
			++count;
			result += primeList[i];
			if(count >= 11)
				break;
			}

	if(count < 11)
		return -1;

	return result;
	}
