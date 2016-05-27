#include <cstdlib>
extern bool IsPrime(unsigned x);

bool hasSameDigits(int number1, int number2)
	{
	int temp1 = 0, temp2 = 0;
	while(number1 != 0)
		{
		temp1 |= (1 << (number1 % 10));
		number1 /= 10;
		}
	while(number2 != 0)
		{
		temp2 |= (1 << (number2 % 10));
		number2 /= 10;
		}
	return temp1 == temp2;
	}

bool isAPrimeWithSameDistinctDigit(int number, int oldOne = -1)
	{
	return IsPrime(number) && (oldOne == -1 || hasSameDigits(number, oldOne));
	}

char* GetThe12DigitNumberFormedByConcatenatingThe3TermsInTheSequence()
	{
	static char buffer[13] = { 0 };
	for(int i = 1234; i < 3216; ++i)
		{
		if(i != 1487 && isAPrimeWithSameDistinctDigit(i) && isAPrimeWithSameDistinctDigit(i + 3330, i)
			&& isAPrimeWithSameDistinctDigit(i + 6660, i))
			{
			itoa(i, buffer, 10);
			itoa(i + 3330, buffer + 4, 10);
			itoa(i + 6660, buffer + 8, 10);
			return buffer;
			}
		}
	return 0;
	}