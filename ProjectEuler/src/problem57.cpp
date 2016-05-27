#include <string.h>

const int BUF_LEN = 400;
#define Init(buffer)	memset(buffer, 0, BUF_LEN)

static
void Plus(const char* number1, char* number2)
	{
	int carry = 0;
	for(int i = 0; i < BUF_LEN; ++i)
		{
		number2[i] += (number1[i] + carry);
		carry = number2[i] / 10;
		number2[i] %= 10;
		}
	}

static inline
int GetNumberLength(char* number)
	{
	int i = BUF_LEN;
	for(; (--i) >= 0; )
		{
		if(number[i] != 0)
			break;
		}
	return i + 1;
	}

int GetTheCountOfFactionsContainANumberatorWithMoreDigitsThanDeminatorInTheFirst1000ExpansionsOfSqrt2()
	{
	char* x = new char[BUF_LEN];
	Init(x);
	x[0] = 3;
	char* y = new char[BUF_LEN];
	Init(y);
	y[0] = 2;
	int result = 0;
	char* temp = new char[BUF_LEN];
	for(int i = 0; i < 999; ++i)
		{
		Init(temp);

		memcpy(temp, y, BUF_LEN);

		Plus(x, y);

		//X += 2 * TEMP.
		int carry = 0;
		for(int i = 0; i < BUF_LEN; ++i)
			{
			temp[i] = 2 * temp[i] + carry;
			carry = temp[i] / 10;
			temp[i] %= 10;
			}

		Plus(temp, x);

		if(GetNumberLength(x) > GetNumberLength(y))
			++result;
		}

	delete[] x;
	delete[] y;
	delete[] temp;
	return result;
	}
