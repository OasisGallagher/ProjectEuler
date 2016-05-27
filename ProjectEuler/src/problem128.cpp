// see ../problem128.gif for more info.

static __int64 FirstNumber(int ring)
{
	__int64 result = 2;
	for(; --ring >= 1;)
		result += 6 * ring;
	return result;
}

static __int64 LastNumber(int ring)
{
	return FirstNumber(ring + 1) - 1;
}

extern bool IsPrime(unsigned x);

static bool TestFirst(int ring)
{
	return IsPrime(6 * ring - 1) && IsPrime(12 * ring + 5) && IsPrime(6 * ring + 1);
}

static bool TestLast(int ring)
{
	return IsPrime(6 * ring - 1) && IsPrime(12 * ring - 7) && IsPrime(6 * ring + 5);
}

#define Limit	(2000)
__int64 solve_128()
{
	int count = 2;
	for(int ring = 2; ; ++ring)
	{
		if(TestFirst(ring) && ++count == Limit)
			return FirstNumber(ring);
		if(TestLast(ring) && ++count == Limit)
			return LastNumber(ring);
	}
	return 0;
}