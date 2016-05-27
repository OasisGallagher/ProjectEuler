static int RepunitLength(int number)
{
	int result = 0;
	for(int rem = 1; rem != 0; rem = (rem * 10 + 1) % number, ++result)
		;
	return result;
}

static bool CoPrimeTo10(int number)
{
	return number % 2 != 0 && number % 5 != 0;
}

#define LIMIT	1000000

int solve_129()
{
	int i = LIMIT + 1;
	for(int tmp = 0; (tmp = RepunitLength(i)) <= LIMIT;)
	{
		while(!CoPrimeTo10(++i))
			;
	}
	return i;
}
