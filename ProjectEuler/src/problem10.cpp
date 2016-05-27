#include <bitset>
#include <time.h>
#include <iostream>

#define GetSubscript(i)	(((i) - 3) >> 1)

long long int GetTheSumOfAllThePrimesBelow2000000()
	{
	const int maxsize = 2000000;
	std::bitset<maxsize / 2> sieve;
	sieve.flip();

	for(int i = 3; i < maxsize; i += 2)
		{
		if(sieve[GetSubscript(i)])
			for(int j = i * 3; j < maxsize; j += (2 * i))
				if(sieve[GetSubscript(j)])
					sieve[GetSubscript(j)].flip();
		}
	long long int result = 2;
	for(int i = 3; i < maxsize; i += 2)
		if(sieve[GetSubscript(i)])
			result += i;

	return result;
	}
