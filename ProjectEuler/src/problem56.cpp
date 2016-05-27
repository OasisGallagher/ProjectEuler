#include <string.h>

#define  BUF_LEN		200

static
char* xPowY(int x, int y, char* result)
	{
	int temp = x;

	char* tmpRange = new char[BUF_LEN];
	memset(tmpRange, 0, BUF_LEN);
	int cur = BUF_LEN;

	for(; temp != 0; temp /= 10)
		{
		result[--cur] = temp % 10;
		}

	for(int i = 1; i < y; ++i)
		{
		temp = x;
		for(int k = 0; temp != 0; temp /= 10, ++k)
			{
			int carry = 0;
			for(int j = BUF_LEN - 1; j >= 0; --j)
				{
				int res = ((temp % 10) * result[j]) + carry + tmpRange[j - k];
				carry = res / 10;
				tmpRange[j - k] = res % 10;
				}
			}
		memcpy(result, tmpRange, BUF_LEN);
		memset(tmpRange, 0, BUF_LEN);
		}
	delete[] tmpRange;
	return result;
	}

int GetTheMaxDigitSumOfXPowYWhereBothAAndBAreLessThan100()
	{
	char* result = new char[BUF_LEN];

	int max = 0;
	int first = 0, second = 0;
	for(int i = 90; i < 100; ++i)
		for(int j = 90; j < 100; ++j)
			{
			memset(result, 0, BUF_LEN);
			xPowY(i, j, result);

			int sum = 0;
			for(int k = 0; k < BUF_LEN; ++k)
				sum += result[k];

			if(sum > max)
				{
				first = i;
				second = j;
				max = sum;
				}
			}
	delete result;
	return max;
	}
