int GetTheSumOfDigitsInTheNumberOfFactorial100()
{
	const int limit = 100;
	const int memsize = 512;
	int *arr = new int[memsize];
	for(int i = 1; i < memsize; ++i)
		arr[i] = 0;

	arr[0] = 1;

	for(int i = 0; i < limit; ++i)
	{
		int temp = 0;
		for(int j = 0; j < memsize; ++j)
		{
			temp += arr[j] * (i + 1);
			arr[j] = temp % 10;
			temp /= 10;
		}
	}
	int result = 0;
	for(int i = 0; i < memsize; ++i)
		result += arr[i];
	delete arr;
	return result;
}
