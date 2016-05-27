static inline __int64 last10digits(__int64 number)
	{
	return number % 10000000000;
	}
__int64 solve_97()
	{
	__int64 result = 1;
	for(int i = 0; i < 7830457; ++i)
		result = last10digits(result * 2);
	result = last10digits(result * 28433 + 1);
	return result;
	}