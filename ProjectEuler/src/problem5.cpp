#define Swap(a, b) b = a - b; a = a - b; b = a + b
// We need a more effective method to get GCD.
int GCD(int a, int b)
{
	while(b != 0)
	{
		if(a < b)
		{
			Swap(a, b);
		}
		a %= b;
		Swap(a, b);
	}
	return a;
}

int GetSmallestPositiveNumEvenlyDivisibleByNumbersFrom1To20()
{
	int result = 1;
	for(int i = 2; i < 20; ++i)
	{
		result = (result * i) / GCD(result, i);
	}
	return result;
}