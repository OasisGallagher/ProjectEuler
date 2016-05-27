extern int GetPrimeList(int len, int *buffer);
static const int TOTAL = 4096 * 2;
#include <algorithm>
#include <cmath>

bool isPrime(int number, int* sieve, int count)
	{
	return std::binary_search(sieve, sieve + count, number);
	}

static
bool isSquare(int number)
	{
	double temp = std::sqrt((double)number);
	return temp == (int)temp;
	}

int GetTheSmallestOddCompositeThatCannotBeWrittenAsTheSumOfAPrimeAndTwiceASquare()
	{
	int *primes = new int[TOTAL];
	int count = GetPrimeList(TOTAL, primes);
	for(int i = 9; ; i += 2)
		{
		if(!isPrime(i, primes, count))
			{
			for(int j = 0; j < count; ++j)
				{
				if(primes[j] < i && isSquare((i - primes[j]) / 2))
					break;
				else if(primes[j] >= i)
					{
					delete []primes;
					return i;
					}
				}
			}
		}
	delete []primes;
	return -1;
	}