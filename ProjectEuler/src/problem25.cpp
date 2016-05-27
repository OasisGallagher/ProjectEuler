#include <iostream>

static const int len = 1000;
struct number{
	unsigned char buffer[len];
};
static void
InitNumber(number* num, int val = 0)
{
	for(int i = 0; i < len; ++i)
		num->buffer[i] = 0;
	num->buffer[0] = val;
}

static void
AddNumber(const number& num1, const number& num2, number* result)
{
	int remain = 0;
	for(int i = 0; i < len; ++i)
	{
		unsigned char val = num1.buffer[i] + num2.buffer[i] + remain;
		result->buffer[i] = val % 10;
		remain = val / 10;
	}
}

static void
CopyNumber(const number& src, number* dest)
{
	for(int i = 0; i < len; ++i)
		dest->buffer[i] = src.buffer[i];
}

static void
PrintNumber(const number& num)
{
	for(int i = len - 1; i >= 0; --i)
		std::cout << (int)num.buffer[i];
}

int GetTheFirstTermInTheFibonacciSequenceToContain1000Digits()
{
	number num1, num2, result;
	int count = 2;
	InitNumber(&num1, 1);
	InitNumber(&num2, 1);
	InitNumber(&result);

	while(result.buffer[len - 1] == 0)
	{
		AddNumber(num1, num2, &result);
		CopyNumber(num2, &num1);
		CopyNumber(result, &num2);
		++count;
	}

	return count;
}
