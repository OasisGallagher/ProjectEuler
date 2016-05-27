extern int Factorial(int n);
static int buffer[10];

static 
void InitFactorialBuffer()
	{
	for(int i = 0; i < 10; ++i)
		buffer[i] = Factorial(i);
	}

static
bool IsEqualToTheSumOfTheFactorialOfItsDigits(int number)
	{
	const int temp = number;
	int result = 0;
	for(; number != 0; )
		{
		int remain = number % 10;
		result += buffer[remain];
		number /= 10;
		}

	return (result == temp);
	}

int GetTheSumOfAllNumbersWhichAreEqualToTheSumOfTheFactorialOfTheirDigits()
	{
	InitFactorialBuffer();
	int result = 0;
	
	for(int i = 10; i < 362880 * 7; ++i)
		if(IsEqualToTheSumOfTheFactorialOfItsDigits(i))
			result += i;

	return result;
	}