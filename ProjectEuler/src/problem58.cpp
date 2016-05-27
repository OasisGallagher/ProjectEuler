#include <cmath>

static
bool isPrime(int x)
	{
	int sq = (int)std::sqrt((double)x);
	for(int i = 2; i <= sq; ++i)
		if(x % i == 0)
			return false;
	return true;
	}

static inline
int topLeft(int x) { return 4 * x * x - 8 * x + 5; }

static inline
int topRight(int x) { return 4 * x * x - 10 * x + 7; }

static inline
int bottomLeft(int x) { return 4 * x * x - 6 * x + 3; }

static inline
int bottomRight(int x) { return (2 * x - 1) * (2 * x - 1); }

static inline
int total(int x) { return 4 * (x - 1) + 1; }

int GetTheSideLengthOfSquareSpiralForWhichTheRatioOfPrimesAlongBothDiagonalsFirstFallsBelow10Percent()
	{
	int count = 0;
	for(int i = 2; ; ++i)
		{
		count += isPrime(topLeft(i));
		count += isPrime(topRight(i));
		count += isPrime(bottomLeft(i));
		count += isPrime(bottomRight(i));
		double t = (double)total(i);
		if(count / t < 0.1)
			return i * 2 - 1;
		}
	return -1;
	}
