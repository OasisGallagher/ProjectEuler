#include <bitset>

//******* Better sulotion ******
//I did not use a computer to solve this problem.
//The formula n^2-79n+1601 is nothing more than (n-40)^2+n-40+41 
//so that all the forty primes of n^2+n+41 are met twice that's why 80 primes are found, but only 40 different one's.
//So what I did was:
//take (n-p)^2+n-p+41, working out this formula gives:
//n^2-(2p-1)n+p^2-p+41.
//Now |2p-1|<1000 and |p^2-p+41|<1000.
//The second condition gives -30<=p<=31
//The value p=31 gives the most primes.
//So the numbers are -(2*31-1)=-61 and 31^2-31+41=971.
//See also: http://mathworld.wolfram.com/Prime-GeneratingPolynomial.html 
////

static void
GetPrimeBelow1000(std::bitset<1000>* bitset)
{
	bitset->flip();
	bitset->at(0).flip();
	bitset->at(1).flip();
	for(int i = 2; i < 1000; ++i)
	{
		if(bitset->at(i))
			for(int j = i * 2; j < 1000; j += i)
				if(bitset->at(j))
					bitset->at(j).flip();
	}
}

static bool
IsPrime(int number, int* primeArray, int len)
{
	for(int i = 0; i < len; ++i)
		if(primeArray[i] == number)
			return true;
	return false;
}

int GetTheProductOfTheCoefficientsABForTheQuadraticExpressionProcudesTheMaxNumOfPrimesForConsecutiveValueOfNStartingWith0()
{
	std::bitset<1000> bitset;
	GetPrimeBelow1000(&bitset);
	int count = 0;
	int primeArray[168];
	int* ptr = primeArray;
	for(int i = 2; i < 1000; ++i)
	{
		if(bitset[i])
			*ptr++ = i;
	}

	int maxA = 0, maxB = 0, maxLen = 0;

	for(int a = -999; a < 1000; a += 2)
	{
		for(int b = 0; b < 168; ++b)
		{
			int n = 0;
			for(; n < 1000; ++n)
			{
				if(!IsPrime(n * n + a * n + primeArray[b], primeArray, 168))
					break;
			}
			if(n > maxLen)
			{
				maxLen = n;
				maxA = a;
				maxB = primeArray[b];
			}
		}
	}
	return maxA * maxB;
}

