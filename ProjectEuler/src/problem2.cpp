int GetSumFibonacciBellow4Million()
{
	const int limit = 4000000;
	int x = 1, y = 2;
	int total = 0;
	while(y <= limit)
	{
		total += y;
		x += 2 * y;
		y = 2 * x - y;
	}
	return total;
}
