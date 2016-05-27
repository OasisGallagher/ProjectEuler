// http://blog.csdn.net/sdj222555/article/details/8155072

#include <iostream>
#include <cmath>

#ifdef DETAIL
#include <set>
#include <iterator>
#endif

static
void makePrimeTable(int count, bool* buffer)
	{
	std::fill(buffer, buffer + count, true);
	for(int i = 2; i < count; ++i)
		{
		if(buffer[i])
			{
			for(int j = i * 2; j < count; j += i)
				buffer[j] = false;
			}
		}
	}

static
bool CheckNumber(int x, bool* primes)
	{
	const int len = 6;/*(int)log10((double)x) + 1;*/
	const int boundary = (1 << len);

	for(int i = 2; i < boundary; i += 2)
		{
		int digits[6];
		int* ptr = digits;
		int temp = x;
		int count = 1;

		for(int sub = 0; sub < len; ++sub, temp /= 10)
			*ptr++ = (temp % 10);

		// Check x.
		temp = -1;
		int k;
		for(k = 0; k < len && count != 0; ++k)
			{
			if(((1 << k) & i) != 0)
				{
				if(digits[k] > 2)
					count = 0;
				else if(temp == -1)
					temp = digits[k];
				else if(digits[k] != temp)
					count = 0;
				}	
			}

		if(count == 0)
			continue;
#ifdef DETAIL
		std::set<int> mySet;
		mySet.insert(x);
#endif
		
		for(int j = 1; j < 10; ++j)
			{
			for(k = 0; k < len; ++k)
				if(((1 << k) & i) != 0)
					digits[k] = j;

			int newNumber = 0;
			for(int i = len - 1; i >= 0; --i)
				newNumber = newNumber * 10 + digits[i];

			if(primes[newNumber] && newNumber != x)
				{
#ifdef DETAIL
				mySet.insert(newNumber), 
#endif
				++count;
				}
			}

		if(count == 8)
			{
#ifdef DETAIL
			std::copy(mySet.begin(), mySet.end(), std::ostream_iterator<int>(std::cout, " "));
#endif
			return true;
			}
		}
	return false;
	}

int GetTheSmallestPrimeWhichByReplacingPartOfTheNumberWithTheSameDigitIsPartOfAn8PrimeValueFamily()
	{
	bool* primes = new bool[1000000];
	makePrimeTable(1000000, primes);
	
	for(int i = 100001; i < 1000000; i += 2)
		if(primes[i] && CheckNumber(i, primes))
			{
			delete []primes;
			return i;
			}

	delete []primes;
	return -1;
	}
