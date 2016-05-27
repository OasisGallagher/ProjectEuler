#include <algorithm>
#undef LOG

#define LENGTH	10
typedef char digit;
typedef digit array[LENGTH];
typedef __int64 number;
static number min_number;

#ifdef LOG
#include <iostream>
#include <fstream>
#include <set>
std::ofstream ofs("problem111.log");
std::set<number> myset;
#endif

static number numeric(const array arr)
{
	number result = 0;
	for(int i = 0; i < LENGTH; ++i)
		result = result * 10 + arr[i];
	return result;
}

static bool isprime(number i)
{
	if(i % 2 == 0) return false;
	for(__int64 j = 3; j * j <= i; j += 2)
		if(i % j == 0)
			return false;
	return true;
}

static number recurse(array arr, digit num, int pos, int cur, int depth)
{
	number result = 0;
	if(cur == depth)
	{
		number real = numeric(arr);
		result = -1;
		// real must be a LENGTH digits number.
		if(real >= min_number && isprime(real))
		{
#ifdef LOG
			ofs << real;
			ofs << "\n";
			if(!myset.insert(real).second)
				std::cout << "duplicated " << real << std::endl;
#endif
			result = real;
		}
		return result;
	}

	for(int p = pos; p < LENGTH; ++p)
	{	// prevent leading zero.
		for(digit d = (p == 0) ? 1 : 0; d < 10; ++d)
		{
			// couldn't be the same.
			if(d == num) continue;

			digit tmp = arr[p];
			arr[p] = d;
			number r = recurse(arr, num, p + 1, cur + 1, depth);
			if(r > 0)
			{
				result = std::max(result, number(0));
				result += r;
			}
			arr[p] = tmp;
		}
	}

	return result;
}

static number repeat_count(digit repeat)
{
	array arr;
	std::fill(arr, arr + LENGTH, repeat);
	// count: how many digits will be replaced.
	for(int count = 1; count < LENGTH; ++count)
	{
		// try to replace (LENGTH - 'count') digits, initial 'repeat'.
		number tmp = recurse(arr, repeat, 0, 0, count);
		if(tmp > 0)
			return tmp;
	}
	throw "fatal error, result not found";
	return -1;
}

static number i64pow(int base, int exp)
{
	return exp <= 0 ? 1i64 : base * i64pow(base, exp - 1);
}

number solve_111()
{
	number result = 0;
	// initialize min_number to make sure the prime we are testing is a LENGTH digit number.
	min_number = i64pow(10, LENGTH - 1);
	for(digit repeat = 0; repeat < 10; ++repeat)
	{
		result += repeat_count(repeat);
	}

	return result;
}
