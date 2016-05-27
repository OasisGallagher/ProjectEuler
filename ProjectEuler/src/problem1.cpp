int SumArithmeticSequence(int a1, int d, int n)
	{
	return a1 * n + n * (n - 1) * d / 2;
	}
int GetSumBelow1000()
	{
	return SumArithmeticSequence(3, 3, 999 / 3) + SumArithmeticSequence(5, 5, 999 / 5) - SumArithmeticSequence(15, 15, 999 / 15);
	}