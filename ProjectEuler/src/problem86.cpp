#include <cmath>
#define Square(x)	((x) * (x))
#define IsDoubleEqualToZero(x)	((x) < 0.000001)

static inline bool IsIntegralPythagoreanTriple(int x, int y)
	{
	double other = sqrt(double(Square(x) + Square(y)));
	return IsDoubleEqualToZero(other - (int)other);
	}

static inline int CalcSolutions(int len, int wAndH)
	{
	// Remove duplicated solutions.
	// ((wAndH + 1) / 2) equals to ceil(wAndH / 2).
	// See ①
	return (wAndH <= len)
			? (wAndH / 2)
			: (1 + (len - (wAndH + 1) / 2));
	}

int solve_86()
	{
	const int LIMIT = 1000000;
	int len = 1;
	for(int count = 0; count <= LIMIT; ++len)
		{	// Enumerate length.
		for(int wAndH = 1; wAndH <= 2 * len; ++wAndH)
			{	// Enumerate the sum of width and height.
			// The shortest route is integer.
			if(IsIntegralPythagoreanTriple(len, wAndH))
				{	// Accumulate the count of solutions from 1 to len.
				count += CalcSolutions(len, wAndH);
				}
			}
		}
	// Cos' count has already exceeded LIMIT twice.
	return (len - 1);
	}
//______________________________________________________________________________
/* ①:	对于一个长方体而言,如果它的长,宽,高相同,无论他们是什么顺序的,都表示的是
 *		一个矩形.比如,(1,2,3)的矩形和(3,1,2)的矩形是一样的,只是看的角度不一样而已.
 *		由于这里枚举的是矩形的长和宽和高的长度总和,为了避免重复计算,就需要让三者
 *		有一个顺序.
 *		就像,a+b+c=100,问共有多少种abc的组合,并且,不管他们值的顺序.
 *		因为不考虑值的顺序,所以为了避免重复,我们就必须指定一个顺序来统计,比如a<=b<=c.
 *
 *		int count(int sum)
 *			{
 *			int total = 0;
 *			for(int a = 1; a < sum; ++a)
 *				{
 *				for(int b = a; b < sum; ++b)
 *					total += ((sum - a - b) >= b);
 *				}
 *			return total;
 *			}
 *
 *		因此,CalcSolutions方法,就采用了这样的顺序:
 *		length >= width >= height.	(1)
 *		length已知,wh = width + height已知,为了让条件1成立,就要依赖wh和length做
 *		不同的选择.
 *		情况1: length >= wh, 所以, 只需让width >= height就可以了.共有floor(wh/2)种.
 *		情况2: length < wh, 此时, 为了让length >= width成立, width的上界是length(包括).
 *		为了使width >= height成立,width从ceil(wh/2)开始,需要注意的是,这里应该是向上取整,
 *		因为,对于wh是偶数而言,ceil相当于空操作; 对于wh是奇数而言, (wh/2)是小数, 只有
 *		向上取整,才能保证width >= height.
 */
