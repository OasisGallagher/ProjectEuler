#include <algorithm>

static 
long long MakeLongLong(int arr[10])
	{
	long long result = 0;
	for(int i = 0; i < 10; ++i)
		{
		result *= 10;
		result += arr[i];
		}
	return result;
	}

static
bool IsNumberWithThatProperty(long long number)
	{
	int sieve[] = { 17, 13, 11, 7, 5, 3, 2 };
	const int filter = 1000;
	const size_t sz = sizeof(sieve) / sizeof(sieve[0]);

	for(int i = 0; i < sz; ++i)
		{
		if((number % filter) % sieve[i] != 0)
			return false;
		number /= 10;
		}
	return true;
	}

long long GetTheSumOfAll0To9PandigitalNumberWithThisProperty()
	{
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	long long result = 0;
	do	{
		if(arr[0] != 0 && (arr[5] == 0 || arr[5] == 5))
			{
			long long temp = MakeLongLong(arr);
			
			if(IsNumberWithThatProperty(temp))
				result += temp;
			}
		}while(std::next_permutation(arr, arr + 10));
	return result;
	}