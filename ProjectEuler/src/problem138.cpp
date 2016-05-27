#include <stdio.h>

static inline __int64 Square(__int64 number) { return number * number; }
// h = b + 1, (0, 1)
static void Term1(int& xn, int& yn)
{
	int x_tmp = 17 * xn + 4 * yn;
	yn = 4 * xn + yn;
	xn = x_tmp;
}

// h = b - 1, (1, 0)
static void Term2(int& xn, int& yn) { Term1(xn, yn); }

template <class ValueType>	// Insertion sort.
static void SortRange(ValueType* first, int count)
{
	for(int i = 1; i < count; ++i)
	{
		int j = i - 1;
		ValueType key = first[i];
		for(; j >= 0 && first[j] > key; --j)
			first[j + 1] = first[j];
		
		first[j + 1] = key;
	}
}

int main() 
{
	__int64 container[20] = { 0 };
	int x0 = 0, y0 = 1;
	int m0 = 1, n0 = 0;
	int i1 = 0, i2 = 10;
	do
	{
		Term1(x0, y0);
		Term2(m0, n0);
		container[i1++] = Square(x0) + Square(y0);
		container[i2++] = Square(m0) + Square(n0);
	}while(i1 < 10);
	
	SortRange(container, 20);

	__int64 sum = 0;
	for(int i = 0; i < 12; ++i)
		sum += container[i];
	// don't know how to print int64 with printf.
	// printf("%llu\n", sum);
	return 0;
}
