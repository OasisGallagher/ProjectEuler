static 
int getDistinctPrimeDivisorsCount(int number)
	{
	int count = 0;
	for(; number != 0 && number % 2 == 0; number /= 2)
		count = 1;
	
	for(int i = 3; i <= number; i += 2)	
		{
		for(bool used = false; number != 0 && number % i == 0; number /= i)
			if(!used) ++count, used = true;
		}
	return count;
	}

int GetTheFirstFourConsecutiveIntegersToHaveFourDistinctPrimesFactorsJustTellTheFirstOneOfThem()
	{
	int okCount = 0;
	for(int i = 647; ; i++)
		{
		if(getDistinctPrimeDivisorsCount(i) == 4)
			++okCount;
		else
			okCount = 0;
		if(okCount == 4)
			return i - 3;
		}
	return -1;
	}
