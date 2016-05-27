#include <bitset>
#include <cmath>
//See http://mathschallenge.net/library/number/sum_of_divisors or ./getsumofdivisors.docx
// for more details.

//static int power(int x, int n)
//	{
//	return n == 0 ? 1 : power(x, n - 1) * x;
//	}
#define power(x, n)	(int)pow((double)x, n)
static int *primeList;

int 
GetPrimeList(int len, int *buffer)
	{
	const int* begin = buffer;
	bool *bptr = new bool[len];
	for(int i = 2; i < len; ++i)
		bptr[i] = true;
	bptr[0] = bptr[1] = false;

	for(int i = 2; i < len; ++i)
		if(bptr[i])
			for(int j = 2; j * i < len; ++j)
				bptr[j * i] = false;

	for(int i = 0; i < len; ++i)
		if(bptr[i] == true)
			*buffer++ = i;
	return buffer - begin;
	}
/********************************************************\
 * Use prime list to factor is faster than usual method.*
\********************************************************/
int
GetSumOfDivisors(int x, int* primeList)
	{	
	const int X = x;
	
	int result = 1;
	
	for(int i = *primeList++; i * i <= x; i = *primeList++)
		{
		if(x % i == 0)
			{
			int j = i * i;
			x /= i;
			while(x != 0 && x % i == 0)
				j *= i, x /= i;
			result *= (j - 1) / (i - 1);
			}
		}
	
	if(x > 1)	//A prime factor larger than the square root remains.
		result *= (x + 1);	// result *= ((x ^ 2 - 1) / (x - 1)) = (x + 1).
	return result - X * (X != 1);
	}

bool
IsAmicableNumber(int x, std::bitset<10000>& bitset)
	{
	int divisors = GetSumOfDivisors(x, primeList);
	if(x != divisors && x == GetSumOfDivisors(divisors, primeList))
		return bitset[divisors] = true;
	return false;
	}

int 
GetTheSumOfAllTheAmicableNumbersUnder10000()
	{
	std::bitset<10000> bitset;
	primeList = new int[10000];
	GetPrimeList(10000, primeList);
	int result = 0;
	for(int i = 9999; i > 0; --i)
		{
		if(bitset[i] || IsAmicableNumber(i, bitset))
			{
			result += i;
			bitset[i] = true;
			}
		}
	delete primeList;
	return result;
	}
