//Quote: http://projecteuler.net/thread=28
//First I noted that for an n by n grid, and n being odd, the number in the top right corner is n^2.
//A little mathematical analysis told me that the other corners are given by: n^2-n+1, n^2-2n+2, and n^2-3n+3. 
//Adding these together gives the quadratic, 4n^2-6n+6. 
//Then all I had to do was create a loop from 3 to 1001 in steps of 2 and find the running total (starting from 1)
//of the quadratic.
int
GetTheSumOfTheNumbersOnTheDiagonalsInA1001By1001SpiralFormedInTheWayDescribedAsThisProblem()
{
	//四个角的值都与它所处的自内向外的圈数成二次关系。
	int result = 1;
	for(int n = 3; n <= 1001; n += 2)
		result += (4 * n * n - 6 * n + 6);
	return result;
}

/*static inline int
GetRowLen(int row)
{
	return row * 2 + 1;
}

int 
GetTheSumOfTheNumbersOnTheDiagonalsInA1001By1001SpiralFormedInTheWayDescribedAsThisProblem()
{
	const int limit = 1001;
	int result = 1;
	int cur = 2;
	for(int i = 0; i < limit / 2; ++i)
	{
		int len = GetRowLen(i);
		result += (cur += len++);

		for(int j = 0; j < 3; ++j)
			result += (cur += len);

		++cur;
	}
	return result;
}
*/