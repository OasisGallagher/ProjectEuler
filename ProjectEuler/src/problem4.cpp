// abccba = 
// 100000 * a + 10000 * b + 1000 * c + 100 * c + 10 * b + a = 
// 100001 * a + 10010 * b + 1100 * c = 
// 11 * (9091 * a + 910 * b + 100 * c)
#define MakeValue(a, b, c) (9091 * (a) + 910 * (b) + 100 * (c))
int GetTheLargestPalindromerMadeFromTheProductOfTwo3DigitNumbers()
{
	for(int a = 9; a > 0; --a)
		for(int b = 9; b >= 0; --b)
			for(int c = 9; c >= 0; --c)
			{
				int v = MakeValue(a, b, c);
				
				for(int d = 90; d > 10; --d)
				{
					if(v % d == 0)
					{
						if(v / d > 999)	// 不是三位数。
							break;
						else
							return v * 11;
					}
				}
			}
	return -1;
}
