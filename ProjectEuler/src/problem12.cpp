// See: http://mathschallenge.net/index.php?section=faq&ref=number/number_of_divisors
// for more details.
int GetDividers(int number)
	{
	int count = 1;
	int result = 1;

	for(int i = 2; i <= number; ++i)
		{
		if(number % i == 0)
			{
			++count;
			number /= i;
			--i;
			}
		else
			{
			result *= count;
			count = 1;
			}
		}
	result *= count;

	return result;
	}

int GetTheValueOfTheFirstTriangleNumberToHaveOver500Divisors()
	{
	int number = 1;
	int n = 1;

	for(; (number = n * (n + 1) / 2); ++n)
		if(GetDividers(number) >= 500)
			break;

	return number;
	}
