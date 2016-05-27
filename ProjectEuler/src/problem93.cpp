#include <vector>
#include <algorithm>
#include <bitset>
#include <numeric>
#define OpLoop1(x)			for(Operator x = Plus; x < OpCount; ++x)
#define OpLoop3(x, y, z)	OpLoop1(x)\
							OpLoop1(y)\
							OpLoop1(z)
#define MAX		(6 * 7 * 8 * 9 + 1)
typedef int Operator;
typedef std::vector<int> Numbers;
typedef std::vector<Numbers> Selection;
enum { Plus, Subtract, Multiply, Divide, OpCount };
typedef void (*Case)(const Numbers& numbers, std::bitset<MAX>* result, Operator op1, Operator op2, Operator op3);

extern unsigned one_count(unsigned number);

static int combine(const Numbers& numbers)
	{
	int result = 0;
	for(Numbers::const_iterator ite = numbers.begin(); ite != numbers.end(); ++ite)
		result = result * 10 + *ite;
	return result;
	}

static inline double operate(double x, double y, Operator op)
	{
	switch(op)
		{
	case Plus:
		return x + y;
	case Subtract:
		return x - y;
	case Multiply:
		return x * y;
	case Divide:
		if(y == 0)
			return -1;
		return x / y;
		}
	throw "invalid operator";
	return 0;
	}

static void get_numbers(const int mask, Numbers* result)
	{
	for(int i = 0; i < 10; ++i)
		if(mask & (1 << i))
			result->push_back(i);
	}

static void gen_selection(Selection* selection)
	{
	const unsigned limit = (1 << 10);
	for(unsigned i = 0; i < limit; ++i)
		{
		if(one_count(i) == 4)
			{
			Numbers tmp;
			tmp.reserve(4);
			get_numbers(i, &tmp);
			selection->push_back(tmp);
			}
		}
	}

static int revise(double cur)
	{
	if(cur < 0) return -1;
	double c = ceil(cur);
	return c - cur < 0.000001 ? int(c) : -1;
	}

static void case1(const Numbers& numbers, std::bitset<MAX>* result, Operator op1, Operator op2, Operator op3)
	{
	// a + b + c + d.
	const int tmp = revise(operate(operate(operate(numbers[0], numbers[1], op1), numbers[2], op2), numbers[3], op3));

	if(tmp != -1)
		result->set(tmp);
	}

static void case2(const Numbers& numbers, std::bitset<MAX>* result, Operator op1, Operator op2, Operator op3)
	{
	// (a + b) + (c + d).
	const int tmp = revise(operate(operate(numbers[0], numbers[1], op1), operate(numbers[2], numbers[3], op3), op3));
	if(tmp != -1)
		result->set(tmp);
	}

static void case3(const Numbers& numbers, std::bitset<MAX>* result, Operator op1, Operator op2, Operator op3)
	{
	// a + b + (c + d).
	// the same as case2, ignore.
	}

static void case4(const Numbers& numbers, std::bitset<MAX>* result, Operator op1, Operator op2, Operator op3)
	{
	// a + (b + c + d).
	const int tmp = revise(operate(numbers[0], operate(operate(numbers[1], numbers[2], op2), numbers[3], op3), op1));
	if(tmp != -1)
		result->set(tmp);
	}

static void case5(const Numbers& numbers, std::bitset<MAX>* result, Operator op1, Operator op2, Operator op3)
	{
	// a + (b + c) + d.
	const int tmp = revise(operate(operate(numbers[0], operate(numbers[1], numbers[2], op2), op1), numbers[3], op3));
	if(tmp != -1)
		result->set(tmp);
	}

static void calc(const Numbers& numbers, std::bitset<MAX>* result)
	{
	Case arr[] = { case1, case2, case3, case4, case5 };
	OpLoop3(op1, op2, op3)
		{
		for(int i = 0; i < _countof(arr); ++i)
			{
			arr[i](numbers, result, op1, op2, op3);
			}
		}
	}

static int count(Numbers& numbers)
	{
	std::bitset<MAX> sieve;
	do{
		calc(numbers, &sieve);
	} while(std::next_permutation(numbers.begin(), numbers.end()));
	
	int result = 1;
	for(; result < MAX && sieve[result]; ++result)
		;

	return result - 1;
	}

int solve_93()
	{
	int result = 0, sofar = 0;
	Selection sel;
	gen_selection(&sel);

	for(Selection::iterator ite = sel.begin(); ite != sel.end(); ++ite)
		{
		int tmp = count(*ite);
		if(tmp > sofar)
			{
			sofar = tmp;
			result = combine(*ite);
			}
		}
	return result;
	}