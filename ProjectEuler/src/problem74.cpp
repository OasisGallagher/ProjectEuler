//////////////////////////////////////////////////////////////////////////
//////////////////////// 47sec, HOW TO SPEED IT UP ? /////////////////////
//////////////////////////////////////////////////////////////////////////

static const unsigned Limit = 1000000;
static const unsigned Len = 60;
static unsigned buffer[Len];
static unsigned result = 0;
static const unsigned Pre[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

unsigned cache[Limit * 7];

static unsigned fact_sum(unsigned number)
	{
	unsigned result = 0;
	for(; number != 0; number /= 10)
		result += Pre[number % 10];
	return result;
	}

static int check(unsigned depth)
	{
	for(size_t i = 0; i <= depth; ++i)
		for(size_t j = i + 1; j <= depth; ++j)
			if(buffer[i] == buffer[j])
				return i;
	return -1;
	}
#include <iostream>
static void search(unsigned depth, unsigned number)
	{
	int overlap = -1;
	while(depth != Len)
		{
		buffer[depth] = fact_sum(number);
		if(-1 != (overlap = check(depth)))break;
		
		number = buffer[depth++];
		}
	for(int i = 0; i < overlap + 1; ++i)
		cache[buffer[i]] = depth - i;

	if(depth == Len)
		++result;
	}

unsigned __solve_74()
	{
	for(unsigned i = 4; i < Limit; ++i)
		{
		if(cache[i] == 0)
			{
			buffer[0] = i;
			search(1, i);
			}
		}
	return result;
	}

// http://projecteuler.net/thread=74, what does he mean?
unsigned solve_74()
	{
	unsigned count = 0;
	int factorial[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	static int chain_length[7 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9];
	for(int i = 1; i < Limit; ++i) 
		{
		if (chain_length[i] == 0) 
			{
			int fs = i, c;
			int seq[100];
			seq[0] = i;
			for (c = 1; ; ++c) 
				{
				int newfs = 0;
				do { newfs += factorial[fs % 10]; fs /= 10; } while (fs != 0);
				seq[c] = fs = newfs;
				int baselen = chain_length[newfs];
				if (baselen > 3) 
					{
					for (int s = 0; s < c; ++s) 
						{
						chain_length[seq[s]] = baselen + c - s;
						}
					c += baselen;
					break;
					}
				else if (fs == seq[c - 1]) 
					{
					for (int s = 0; s < c; ++s)
						chain_length[seq[s]] = c - s;
					break;
					} 
				else if (c > 1 && fs == seq[c - 2]) 
					{
					for (int s = 0; s < c - 1; ++s)
						chain_length[seq[s]] = c - s;				
						break;
					}
				else if (c > 2 && fs == seq[c - 3]) 
					{
					for (int s = 0; s < c - 2; ++s)
						chain_length[seq[s]] = c - s;
					break;
					}
				}
			if (c >= 60) 
				++count;
			}
		}
	return count;
	}