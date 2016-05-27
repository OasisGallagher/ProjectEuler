// Make the upper bound more tight.

//Also, for numbers under 1000000, palindromes are of one of these forms:
//
//a
//aa
//aba
//abba
//abcba
//abccba
//
//A can be either 1, 3, 5, 7, or 9, while b and c can 0, 1, 2...8, 9.  So the amount of numbers in each form are:
//
//a      - 5
//aa     - 5
//aba    - 50
//abba   - 50
//abcba  - 500
//abccba - 500
//
//This adds up to a total of 1110 possibilities for base 10 palindromes, instead of 999999.

static bool
IsStringPalindromic(const char* buffer, int len)
	{
	for(int i = 0; i <= len / 2; ++i)
		if(buffer[i] != buffer[len - i - 1])
			return false;
	return true;
	}
static bool
IsPalindromic(int number)
	{
	const int numberOld = number;
	int rotateResult = 0;
	for(; number != 0; )
		{
		rotateResult *= 10;
		rotateResult += number % 10;
		number /= 10;
		}
	return (numberOld == rotateResult);
	}

static int
DecimalToBinary(int number, char* buffer)
	{
	const char* const ptr = buffer;
	for(; number != 0; number /= 2)
		*buffer++ = number % 2;
	return (buffer - ptr);
	}

static void
BZero(char* buf, int len)
	{
	const char* ptr = buf;
	for(int i = 0; i < len; ++i)
		*buf++ = 0;
	}

int GetTheSumOfAllNumbersLessThan1000000WhichArePalindromicInBase10AndBase2()
	{
	int result = 0;
	char *buffer = new char[24];

	// If i(binary format) is palindromic, i MUST be odd.
	// Because the leading charactor of i must be 1, so the last one is 1 too.
	for(int i = 1; i < 1000000; i += 2)
		{
		if(IsPalindromic(i))
			{
			BZero(buffer, 24);
			int len = DecimalToBinary(i, buffer);
			if(IsStringPalindromic(buffer, len))
				result += i;
			}
		}
	delete buffer;
	return result;
	}
