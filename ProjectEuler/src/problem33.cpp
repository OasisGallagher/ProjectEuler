//将这样的数展开，写成：
// (10a + i) / 10i * d = a / d等四种形式，化简之后，可以发现，只有一种形式成立。

extern int GCD(int a, int b);

unsigned GetTheValueOfTheDenominator()
	{
	unsigned int x = 1, y = 1;

	for(int n = 1; n < 10; ++n)
		for(int i = 1; i < 10; ++i)
			for(int d = n + 1; d < 10; ++d)
				{
				if(10 * n * i == 9 * n * d + i * d)
					{
					x *= (10 * n + i);
					y *= (10 * i + d);
					}
				}
	return y / GCD(x, y);
	}
