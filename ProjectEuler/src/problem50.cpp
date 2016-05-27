static const int COUNT = 1000000;
extern int GetPrimeList(int len, int *buffer);
extern bool IsPrime(unsigned x);

int GetThePrimeBelow1000000CanBeWrittenAsTheSumOfTheMostConsecutivePrimes()
	{
	int* buffer = new int[COUNT];
	int realCount = GetPrimeList(COUNT, buffer);
	int result = 0, maxLen = 0;

	for(int i = 0; i < realCount - 1; ++i)
		{
		buffer[i + 1] += buffer[i];
		if(buffer[i + 1] >= COUNT)
			{
			realCount = i;
			break;
			}
		}
	for(int i = realCount; i >= 0; --i)
		{
		int temp = buffer[i];
		if(IsPrime(temp))
			{
			if(i > maxLen)
				{
				maxLen = i;
				result = temp;
				}
			}
		else
			for(int j = 0; j < realCount; ++j)
				{
				if(IsPrime(temp - buffer[j]))
					{
					if(i - j - 1 > maxLen)
						{
						maxLen = i - j - 1;
						result = temp - buffer[j];
						}
					}
				}
		}
	delete []buffer;
	return result;
	}
