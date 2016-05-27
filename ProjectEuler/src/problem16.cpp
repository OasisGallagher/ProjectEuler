int GetTheSumOfTheDigitOfTheNumber2$1000()
{
	const int limit = 1000;
	int *arr = new int[limit];
	for(int i = 1; i < limit; ++i)
		arr[i] = 0;

	arr[0] = 1;

	for(int i = 0; i < limit; ++i)
	{
		int temp = 0;
		for(int j = 0; j < limit; ++j)
		{
			temp += arr[j] * 2; 
			arr[j] = temp % 10;
			temp /= 10;
		}
	}
	int result = 0;
	for(int i = 0; i < limit; ++i)
		result += arr[i];
	delete arr;
	return result;
}
