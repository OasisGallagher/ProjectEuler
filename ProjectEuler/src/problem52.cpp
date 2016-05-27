// http://projecteuler.net/thread=52
//For this problem I didn't even use a computer. 
//I just remembered that the repeating sequence of digits in the decimal representation of 1/7 has the desired property.
//
//1/7 = 0.142857 142857 142857 ...
//
//2 * 142857 = 285714
//3 * 142857 = 428571
//4 * 142857 = 571428
//5 * 142857 = 714285
//6 * 142857 = 857142
//but
//7 * 142857 = 999999

enum { OK, LoopTerminated = -2, CanNotRepresent };
#define IsOK(x)	((x) > OK)

static
int RepresentDigit(int x)
	{
	int result = 0;
	for(; x != 0; x /= 10)
		{
		int temp = result;
		result |= (1 << x % 10);
		if(result == temp)
			return CanNotRepresent;
		}
	return result;
	}

int GetTheSmallestPositiveIntegerXSuchThat2x3x4x5x6xContainTheSameDigit()
	{
	for(int i = 2; ; ++i)
		{
		int result1 = RepresentDigit(i);
		for(int product = 2; IsOK(result1) && product < 7; ++product)
			{
			int result2 = RepresentDigit(product * i);

			if(result1 != result2)
				result1 = LoopTerminated;
			else
				result1 = result2;
			}
		if(IsOK(result1))
			return i;
		}
	return -1;
	}
