extern int GetPrimeList(int len, int *buffer);

static __int64 calc(int x, int y)
{
	__int64 result = y, inc = y;
	for(int step = 10; step / 10 < x;)
	{
		result += inc;
		while(result % step == x % step)
		{
			inc *= 10;
			step *= 10;
		}
	}
	return result;
}

__int64 solve_134()
{
	const int BOUND = 1000004;
	int* primes = new int[BOUND]();
	int count = GetPrimeList(BOUND, primes);
	int p = 5;
	__int64 result = 0;
	for(int i = 3; i < count; ++i)
	{
		result += calc(p, primes[i]);
		p = primes[i];
	}
	delete[] primes;
	return result;
}