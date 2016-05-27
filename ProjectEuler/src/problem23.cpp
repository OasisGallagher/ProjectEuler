#include <cmath>
#include <bitset>

static const int limit = 28123;
extern int GetSumOfDivisors(int x, int* primeList);
extern int GetPrimeList(int len, int *buffer);
static int* primeList;

int abundant[limit];

#define IsAbundantNumber(number)	(GetSumOfDivisors(number, primeList) > (number))

static void 
GetNumbersWhichCanBeWrittenAsTheSumOfTwoAbundantNumbers(bool* canBeWritten)
	{
	int *ptr = abundant;
	// 只算出上限到limit - 13的所有Abundant number就可以。因为需要保证两个Abundant number的和不大于limit。
	for(int i = 12; i < limit - 13; ++i)
		if(IsAbundantNumber(i))
			*ptr++ = i;
	//与其测试每个数字的各种相加的组合，倒不如将一定范围内的符合条件的值都列举出来。
	for(int i = 0; i < limit; ++i)
		for(int j = i; j < limit; ++j)			
			if(abundant[i] + abundant[j] <= limit)
				canBeWritten[abundant[i] + abundant[j]] = true;
			else	//abundant是递增的序列，所以可以跳出循环。
				break;
	}

int
GetTheSumOfAllThePositiveIntegersWhichCannotBeWrittenAsTheSumOfTwoAbundantNumbers()
	{
	int result = 0;
	
	primeList = new int[10000];
	int len = GetPrimeList(10000, primeList);
	
	bool* canBeWritten = new bool[limit + 1];
	for(int i = 0; i <= limit; ++i)
		canBeWritten[i] = false;

	GetNumbersWhichCanBeWrittenAsTheSumOfTwoAbundantNumbers(canBeWritten);

	for(int i = 1; i <= limit; ++i)
		if(!canBeWritten[i])
			result += i;

	delete []primeList;
	delete []canBeWritten;
	return result;
	}
