extern __int64 dp_count(int len, int min_red);
int solve_115()
{
	int i = 51;
	for(; dp_count(i, 50) <= 1000000; ++i)
		;
	return i;
}