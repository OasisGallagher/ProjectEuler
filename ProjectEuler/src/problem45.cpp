extern bool IsPentagonalNumber(int);

// T(n) = n(n + 1) / 2.			(1)
// when n is odd, say n is 2m - 1, combine it with (1):
// => T(2m - 1) = (2m - 1)(2m - 1 + 1) / 2
// => T(2m - 1) = (2m - 1)m
// => T(2m - 1) = m(2m - 1).
// so, T(n) is equivalent to H(n) when n is odd.
// In other word, H(n) is a subset of T(n).
// So, checking H(n) and P(n) is enough.

int GetTheNextTriangleNumberThatIsAlsoPentagonalAndHexagonal()
	{
	for(int n = 143 + 1; ; ++n)
		{
		int temp = n * (2 * n - 1);
		if(IsPentagonalNumber(temp))
			return temp;
		}
	}
