#include <iostream>

#define PRECENT	99

static bool isbouncy(unsigned number)
{	// number >= 100.
	char xbool = -1;
	char last = number % 10;
	for(number /= 10; number != 0; number /= 10)
	{
		char cur = (number % 10);
		if(cur != last)
		{
			if(xbool == -1)	// first time.
				xbool = (cur < last);
			else if(xbool != (cur < last))
				return true;
		}
		last = cur;
	}
	return false;
}

int solve_112()
{
	unsigned count = 0;
	for(unsigned i = 100; ; ++i)
	{
		if(isbouncy(i) && ++count * 100 == i * PRECENT)
			return i;
	}
	return -1;
}
