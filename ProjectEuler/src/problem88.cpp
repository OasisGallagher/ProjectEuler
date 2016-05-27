#include <cmath>
#include <set>
#include <numeric>
#include <ctime>

#define Sqrt(X)				(int)(sqrt((double)X))
// 换底公示求log2为底的对数。
#define Log2(X)				((int)(log((double)X) / log(2.0)))
#define LIMIT	12000

// 对于k,product-sum的最大值不会超过2k,因为对于任意的k,总是有一个product-sum为2k,
// 然后,再填充2k - k - 1个1,就可以成为真正意义上的product-sum了.
#define BOUND	LIMIT * 2

static int result[LIMIT + 1];

static void subGetProc(int curDepth, int targetDepth, int* sum, int* mul, int lastStat = 1)
	{
	if(curDepth > targetDepth)
		{
		int tmp = *mul - *sum + targetDepth;
		if(tmp <= LIMIT)
			result[tmp] = std::min(result[tmp], *mul);
		}
	else if(curDepth != -1)		//第一次调用时,curDepth为-1,以便进入for循环.
		{
		if(curDepth == 1)	//循环的第一层.
			*sum = 0, *mul = 1;
		for(int i = lastStat; i < BOUND; ++i)
			{
			int thisMul = *mul, thisSum = *sum;
			int tmp = thisMul * i;
			if(tmp > BOUND)
				break;
			thisMul = tmp;
			thisSum += i;
			subGetProc(1 + curDepth, targetDepth, &thisSum, &thisMul, i);
			}
		}
	else
		{
		for(int i = 2; i <= targetDepth; ++i)
			subGetProc(1, i, sum, mul);
		}
	}

int solve_88()
	{
	std::fill(result, result + LIMIT + 1, INT_MAX);
	int loopDepth = Log2(BOUND);	// 最多可以由多少个2相乘。
	int sum = 0, mul = 1;
	subGetProc(-1, loopDepth, &sum, &mul);
	std::set<int> tmp(result + 2, result + LIMIT + 1);
	return std::accumulate(tmp.begin(), tmp.end(), 0);
	}

