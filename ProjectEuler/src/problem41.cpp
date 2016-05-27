extern int GetPrimeList(int len, int *buffer);

//用来判断一个数n位的数——number是不是由连续的1～n组成，且保证1～n各出现一次。
static
bool IsPandigitalEx(unsigned number)
	{
	int digits = 0, count = 0;
	for(; number > 0; ++count, number /= 10)
		{
		//预先保留digit的值。
		int tmp = digits;

		//，然后将digit”或“(int)((number % 10) - 1)。
		//这里相当于对一个32位数，从第0位开始，分别用来记录1，2，3……9。
		digits = digits | 1 << (int)((number % 10) - 1);

		//如果digit结果没变，表明(int)((number % 10) - 1)这个位已经为1了，所以直接返回false。
		if (tmp == digits)
			return false;
		}
	//表明各个位没有重复。
	//count记录的是这个数一共有多少位。
	//(1 << count) - 1时，(1 << count)得到1+0……0（count个0），然后减1，就得到1……1（count个）。
	//这行主要用来判断，如果number是13这样的数，各个位没有重复，但是会导致digit为101，
	//而此时的（1<<count）-1 为11，也就是说，用来判断一个n位的数，是不是1～n这样的n个数。
	return (digits == (1 << count) - 1);
	}

int GetTheLargestNDigitPanditalPrimeThatExists()
	{
	//9位的Pandital，各个位的和为1+2+3+4+5+6+7+8+9=45，表明这个数肯定能被3整除，所以肯定不是质数。
	//8位的Pandital，各个位的和为45-9=36，表明这个数肯定能被3整除，所以肯定不是质数。
	//7位的Pandital，各个位的和为36-8=28。7位数里才可能存在质数。
	const int limit = 10000000;
	int *buffer = new int[limit];
	int primeLen = GetPrimeList(10000000, buffer);
	int i = 0;
	
	for(i = (--primeLen); !IsPandigitalEx(buffer[i]); --i)
		;
	int result = buffer[i];
	delete buffer;

	return result;	
	}
