int GetTheDifferenceBetweenTheSumOfTheSuaresOfTheFirst100NaturalNumbersAndTheSquareOfTheSum()
{
	const int limit = 100;
	int result = 0;
	for(int i = 1; i <= limit; ++i)
		for(int j = i + 1; j <= limit; ++j)
		{
			result += (i * j);
		}
	return result * 2;
}