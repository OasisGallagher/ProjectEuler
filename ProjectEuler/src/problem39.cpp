//通过下面的两个等式，可以将b用p和a表示，从而避免了对b的轮询。
// a^2 + b^2 = c^2	(1)
// a + b + c = p	(2)
// c = (p - (a + b)) => 
// c^2 = p^2 + (a + b)^2 - 2pa - 2pb =>
// c^2 = p^2 + a^2 + b^2 + 2ab - 2pa - 2pb =>
// cos' a ^ 2 + b ^ 2 = c ^ 2 =>
// 0 = p^2 + 2ab - 2pa - 2pb =>
// b(2a - 2p) = 2pa - p^2 => b = (2pa-p^2) / (2a - 2p)
// so:
#define GetAnotherFromOneAndTotal(A, P) (2 * A * P - P * P) / (2 * A - 2 * P)

int GetTheValueOfPLessEqualTo1000IsTheNumberOfSolutionsMaximised()
	{
	int result = 0;
	int prevMax = 0;
	int max = 1000;
	for(int total = 1000; total >= 3; --total)
		{
		result = 0;
		for(int i = 1; i <= total - 2; ++i)
			{
			int j = GetAnotherFromOneAndTotal(i, total);
			int k = total - i - j;
			if(i * i + j * j == k * k)
				++result;
			}

		if(result > prevMax)
			{
			prevMax = result;
			max = total;
			}
		}
	return max;
	}
