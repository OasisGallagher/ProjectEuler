#include <cmath>
/**
 * 侧边长为a,底边为a+1的话,h为高,根据勾股定理:
 * h^2 = a^2 - ((a + 1) / 2)^2.
 * 展开,并两边×4去掉分母:
 * 3a^2 - 4h^2 + 2a = 1.
 * 两边×3:
 * 9a^2 - 12h^2 + 6a + 1 = 4.
 * (3a - 1)^2 - 12h^2 = 4.
 * 两边/4:
 * ((3a - 1) / 2) ^ 2 - 3h^2 = 1.
 * 设x = (3a - 1) / 2, y = h:
 * x^2 - 3y^2 = 1.
 * 即,D=3的佩尔方程.
 * 满足这个方程之后,就可以组成"接近等边三角形",然后再判断边和面积是否是整数.
**/
#define NextM(d, a, m)	(d * a - m)
#define NextD(S, m, d)	((S - m * m) / d)
#define NextA(SqrtS, m, d) ((SqrtS + m) / d)
struct pair{ pair(__int64 _x, __int64 _y) : x(_x), y(_y){} __int64 x; __int64 y; };

//#ifdef _DEBUG
//#define DbgTrace(x)	std::cout << (x) << std::endl
//#else
#define DbgTrace(x) x
//#endif

pair solve_pell(int S)
	{
	const int sq = (int)sqrt(double(S));
	if(sq * sq == S)
		throw "S can not be a perfect square number";

	int numerator = sq, denominator = 1;

	for(int m = 0, d = 1, a = sq, numerator_1 = 1, denominator_1 = 0; 
		numerator * numerator - S * denominator * denominator != 1; 
		)
		{
		m = NextM(d, a, m);
		d = NextD(S, m, d);
		a = NextA(sq, m, d);
		// shift.
		int numerator_2 = numerator_1;
		numerator_1 = numerator;

		int denominator_2 = denominator_1;
		denominator_1 = denominator;

		numerator = a * numerator_1 + numerator_2;
		denominator = a * denominator_1 + denominator_2;
		}
	return pair(numerator, denominator);
	};

pair next_solution(__int64 x1, __int64 xk, __int64 y1, __int64 yk, int S)
	{
	return pair(x1 * xk + S * y1 * yk, x1 * yk + y1 * xk);
	}

__int64 solve_94()
	{
	const int S = 3;
	pair cur = solve_pell(S);
	const pair init = cur;
	const int Limit = 1000000000;
	__int64 result = 0;
	// x^2 - 3y^2 = 1.
	for(; ; )
		{
		// 通过计算出的佩尔方程值,计算周长和面积.
		// aX3表示a边长度的三倍,areaX3同理.
		__int64 aX3 = cur.x * 2 - 1;

		if(aX3 > Limit)
			break;

		__int64 areaX3 = (cur.x - 2) * __int64(cur.y);

		if(aX3 > 0 && areaX3 > 0 && aX3 % 3 == 0 && areaX3 % 3 == 0)
			DbgTrace(result += (aX3 - 1));

		aX3 = cur.x * 2 + 1, areaX3 = (cur.x + 2) * cur.y;

		if(aX3 > 0 && areaX3 > 0 && aX3 % 3 == 0 && areaX3 % 3 == 0)
			DbgTrace(result += (aX3 + 1));

		cur = next_solution(init.x, cur.x, init.y, cur.y, S);
		}
	return result;
	}