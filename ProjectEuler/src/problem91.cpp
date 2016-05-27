#define PRO91_LMT		50
#define Min(x, y)	((x) < (y) ? (x) : (y))

extern int GCD(int x, int y);

static int count(int x, int y)
	{
	const int gcd = GCD(x, y);
	// 为了便于理解，将下面的步骤分开写。
	/*根据x和y的比例，沿着(0,0)到(x,y)的垂线移动。
	(PRO91_LMT - y) / yStep和(PRO91_LMT - x) / xStep分别是纵向和横向的最大值，超过
	它们，所求点的位置就会超过PRO91_LMT。
	const int xStep = y / gcd;
	const int yStep = x / gcd;
	int leftTopCount = Min(x / xStep, (PRO91_LMT - y) / yStep);
	int rightBottomCount = Min(y / yStep, (PRO91_LMT - x) / xStep);
	return (leftTopCount + rightBottomCount);
	*/
	/*return Min(x * gcd / y, (PRO91_LMT - y) * gcd / x)
		+ Min(y * gcd / x, (PRO91_LMT - x) * gcd / y);
	*/
	// 上面的做法还不是最优。
	// 可以注意到，对于一个50×50的表格，直角点坐标P1(12, 5)和直角点P2(5,12)形成的
	// 直角三角形时 一样多的。
	// 如果我们只计算P1的向下的形成三角形的个数，再×2，相当于计算了P1的向下三角形的个数和
	// P2的向上的三角形的个数的总和。
	// 同理，计算P2的向下三角形的个数×2，相当于计算了P2的向下三角形的个数+P1的向上三角形的个数。
	// 所说的向上向下是相对于(0,0)到P这条线的垂线而言的。
	// 因此：
	return Min(x * gcd / y, (PRO91_LMT - y) * gcd / x) * 2;
	}

int solve_91()
	{
	int result = 3 * PRO91_LMT * PRO91_LMT;
	for(int x = 1; x <= PRO91_LMT; ++x)
		{
		for(int y = 1; y <= PRO91_LMT; ++y)
			result += count(x, y);
		}
	return result;
	}
