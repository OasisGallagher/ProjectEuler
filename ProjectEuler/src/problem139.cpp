#include <iostream>
#include <ctime>

#define MAX_PERIMETER	(100000000)

static inline bool even(int n){ return (n & 1) == 0; }
static inline bool farey_sequence(int n, int& a, int& b, int& c, int& d)
{
	int k = (n + b) / d;
	int tmpc = c;
	int tmpd = d;
	c = k * c - a;
	d = k * d - b;
	a = tmpc;
	b = tmpd;
	return a != b;
}

static int gcd(int a, int b)
{
	if(a < b) std::swap(a, b);
	while(b != 0)
	{
		a = a % b;
		std::swap(a, b);
	}
	return a;
}

static int solve_139()
{
	int result = 0;
	int upper = (unsigned)ceil(sqrt(MAX_PERIMETER / 2.f));

	int a = 0, b = 1, c = 1, d = upper;
	for(; farey_sequence(upper, a, b, c, d); )
	{
		if(even(b - a)) continue; 
		int x = b * b - a * a;
		int y = 2 * a * b;
		int z = a * a + b * b;
		int perimeter = x + y + z;

		if(perimeter >= MAX_PERIMETER) continue;

		if(x < y) std::swap(x, y);

		if(z % (x - y) == 0)
			result += MAX_PERIMETER / perimeter;
	}

	return result;
}

int main()
{
	clock_t start = clock();
	std::cout << solve_139() << std::endl;
	std::cout << (clock() - start) / float(CLOCKS_PER_SEC) << "second(s)." << std::endl;
}
