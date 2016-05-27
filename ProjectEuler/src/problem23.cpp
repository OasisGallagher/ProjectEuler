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
	// ֻ������޵�limit - 13������Abundant number�Ϳ��ԡ���Ϊ��Ҫ��֤����Abundant number�ĺͲ�����limit��
	for(int i = 12; i < limit - 13; ++i)
		if(IsAbundantNumber(i))
			*ptr++ = i;
	//�������ÿ�����ֵĸ�����ӵ���ϣ������罫һ����Χ�ڵķ���������ֵ���оٳ�����
	for(int i = 0; i < limit; ++i)
		for(int j = i; j < limit; ++j)			
			if(abundant[i] + abundant[j] <= limit)
				canBeWritten[abundant[i] + abundant[j]] = true;
			else	//abundant�ǵ��������У����Կ�������ѭ����
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
