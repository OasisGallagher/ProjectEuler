// http://www.mathblog.dk/project-euler-69-find-the-value-of-n-%E2%89%A4-1000000-for-which-n%CF%86n-is-a-maximum/
// The man pointed above is so clever !!!
//通过观察pi的求法，发现，n越小，使得n/pi(n)的一个因子越大。所以，找出从2开始所有质数的乘积
//同时保证这个积不大于LIMIT，这个积就是结果。
static const int LIMIT = 1000000;
extern int GetPrimeList(int len, int *buffer);

unsigned solve_69()
	{
	int buffer[20];
	GetPrimeList(20, buffer);

	unsigned result = 1;

	size_t i = 0;
	for(; (result *= buffer[i]) < LIMIT; ++i)
		;

	return result / buffer[i];
	}
//////////////////////////////////////////////////////////////////////////
/////////////////////// (6 mins)My ugly and slow solution :( /////////////////////
/*
static const int LIMIT = 1000000;
static int getPrimeDivisor(int& number)
	{
	for(int i = 2; i <= number; )
		{
		if(number % i == 0)
			{
			while((number /= i) % i == 0)
				;
			return i;
			}
		else
			++i;
		}
	return -1;
	}

unsigned solve_69()
	{
	double tmp = 0.0;
	int result = 0;
	for(int i = 1; i <= LIMIT; ++i)
		{
		double radius = 1.0;
		int cur = i;
		while(cur != 1)
			radius *= (1.0 - 1.0 / getPrimeDivisor(cur));
		
		if(1.0 / radius > tmp)
			{
			tmp = 1.0 / radius;
			result = i;
			}
		}

	return result;
	}
*/