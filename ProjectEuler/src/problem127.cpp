#include <vector>

extern int GCD(int x, int y);
extern void GetRadical(int* cache, int len);
extern void SortNumberByRadical(int len, std::vector<int>* result, int* radical = NULL);

#define MaxN	(120000)
#define CoPrime(_X, _Y) (1 == GCD(_X, _Y))
// 24.4 seconds.
int solve_127()
{
	int* radical = new int[MaxN]();
	GetRadical(radical, MaxN);
 	int result = 0;
	// rad(a) * rad(b) * rad(c) = rad(abc).
	// Sort [1, MaxN) with their radical, if rad(ac) > c, we don't need to check
	// a + 1, a + 1 and so on.
	std::vector<int> sorted;
	SortNumberByRadical(MaxN - 1, &sorted, radical);

	// Iterate c.
	for(int c = 2; c < MaxN; ++c)
	{
		int half = c / 2;
		for(std::vector<int>::iterator ite = sorted.begin(); ite != sorted.end(); ++ite)
		{
			int& b = *ite;
			if(b >= c || b <= half)
				continue;

			__int64 part = 1i64 * radical[b] * radical[c];
			if(part >= c)	// 'Cause rad[b] is increasing.
				break;

			// (c - a) is b.
			int a = c - b;

			// If (a, b) is coprime, (a, a + b) must be coprime.
			if(CoPrime(radical[a], radical[b]) && (part * radical[a] < c))
				result += c;
		}
	}

	delete[]radical;
	return result;
}
