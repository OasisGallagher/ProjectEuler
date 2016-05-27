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
	// See ��
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
/* ��:	����һ�����������,������ĳ�,��,����ͬ,����������ʲô˳���,����ʾ����
 *		һ������.����,(1,2,3)�ľ��κ�(3,1,2)�ľ�����һ����,ֻ�ǿ��ĽǶȲ�һ������.
 *		��������ö�ٵ��Ǿ��εĳ��Ϳ�͸ߵĳ����ܺ�,Ϊ�˱����ظ�����,����Ҫ������
 *		��һ��˳��.
 *		����,a+b+c=100,�ʹ��ж�����abc�����,����,��������ֵ��˳��.
 *		��Ϊ������ֵ��˳��,����Ϊ�˱����ظ�,���Ǿͱ���ָ��һ��˳����ͳ��,����a<=b<=c.
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
 *		���,CalcSolutions����,�Ͳ�����������˳��:
 *		length >= width >= height.	(1)
 *		length��֪,wh = width + height��֪,Ϊ��������1����,��Ҫ����wh��length��
 *		��ͬ��ѡ��.
 *		���1: length >= wh, ����, ֻ����width >= height�Ϳ�����.����floor(wh/2)��.
 *		���2: length < wh, ��ʱ, Ϊ����length >= width����, width���Ͻ���length(����).
 *		Ϊ��ʹwidth >= height����,width��ceil(wh/2)��ʼ,��Ҫע�����,����Ӧ��������ȡ��,
 *		��Ϊ,����wh��ż������,ceil�൱�ڿղ���; ����wh����������, (wh/2)��С��, ֻ��
 *		����ȡ��,���ܱ�֤width >= height.
 */
