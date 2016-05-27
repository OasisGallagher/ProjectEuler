unsigned long long reverseNumber(unsigned long long number)
	{
	unsigned long long result = 0;
	for(; number != 0; number /= 10)
		result = 10 * result + number % 10;
	return result;
	}

int GetTheCountOfLychrelNumbersBelow10000()
	{
	int result = 0;
	for(int i = 1; i < 10000; ++i)
		{
		int iterCount = 1;
		unsigned long long number = i;
		unsigned long long re = reverseNumber(number);
		number += re;

		for(; iterCount < 50; ++iterCount)
			{
			unsigned long long re = reverseNumber(number);
			if(re == number)
				break;
			number += re;
			}

		result += (iterCount == 50);
		}
	return result;
	}
