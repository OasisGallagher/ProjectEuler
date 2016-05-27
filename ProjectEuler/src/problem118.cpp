#include "../include/next-permutation.hpp"

#define Length	9
typedef char* string;
extern bool IsPrime(unsigned x);

static unsigned gen_number(string str, int len)
{
	unsigned result = 0;
	for(int i = 0; i < len; ++i)
		result = result * 10 + str[i];
	return result;
}

// last_number is used to keep order.
static int solve(string str, int from = 0, unsigned last_number = 0)
{
	if(from == Length)
		return 1;
	int result = 0;
	for(int len = 1; len <= Length - from; ++len)
	{
		unsigned new_number = gen_number(str + from, len);
		if(IsPrime(new_number) && new_number > last_number)
			result += solve(str, from + len, new_number);
	}
	return result;
}

int solve_118()
{
	string str = new char[Length]();

	for(int i = 0; i < Length; ++i)
		str[i] = (i + 1);
	int count = 0;
	
	do 
	{
		if(str[Length - 1] % 2 != 0 && str[Length - 1] % 5 != 0)
			count += solve(str);
	}while(NextPermutation(str, str + Length));

	delete []str;
	return count;
}