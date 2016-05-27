static inline
unsigned long long getLast10Digit(unsigned long long number)
	{
	return number % 10000000000ul;
	}

unsigned long long GetTheLastTenDigitsOfTheSeries()
	{
	unsigned long long result = 0;
	for(unsigned int i = 1; i <= 999; ++i)
		{
		unsigned long long temp = 1;
		for(unsigned j = 0; j < i; ++j)
			{
			temp *= i;
			temp = getLast10Digit(temp);
			}
		result += temp;
		}
	return getLast10Digit(result);
	}
