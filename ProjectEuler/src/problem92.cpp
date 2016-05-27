// ��ֱ�ӵķ���Ҳ���Խ��, ����, ��Ϊ����һ������, �Լ������κ�һ���ֵ���, ���ĸ�λ
// ƽ���Ͷ���һ����.
// ���, ����ö��һ�����ֵĸ���λ, �������4λ��, abcd, ����a >= b >= c >= d, Ȼ��
// �ټ������Ĳ��ظ����ֵ�������ֵĸ���.

#define LIMIT			10000000

static int square_digits(int number)
	{
	int result = 0;
	for(; number > 0; number /= 10)
		{
		int tmp = (number % 10);
		result += (tmp * tmp);
		}
	return result;
	}

static bool arrive89(int start)
	{
	for(; start != 0 && start != 89 && start != 1; start = square_digits(start))
		;
	return (start == 89);
	}

static int inner_product(int from, int to)
	{	// from * from - 1 * ... * (to - 2) * (to - 1).
	int total = 1;
	for(; from < to; ++from)
		total *= from;
	return total;
	}

static int fact(int number)
	{	// number !
	return inner_product(2, number + 1);
	}
static int count_permutation(int number)
	{	// ����ABCCDDEEF�������γɵ�����������ϸ���, ����0�������ֵĿ�ͷ.
	unsigned char buffer[10] = { 0 };
	int digitCount = 0;
	for(; number != 0; number /= 10)
		{
		++buffer[number % 10];
		++digitCount;
		}
	int total = 0;
	
	if(buffer[0] == 0)
		total = fact(digitCount);
	else
		{
		total = inner_product(digitCount - buffer[0], digitCount);
		total *= fact(digitCount - buffer[0]);
		}
	int div = 1;
	for(int i = 0; i < 10; ++i)
		div *= fact(buffer[i]);
	return total / div;
	}

static int simuloop(int curDepth, int depth, int digitBase, int number)
	{
	int total = 0;
	if(curDepth == depth)
		{
		if(arrive89(number))
			total += count_permutation(number);
		}
	else
		{
		for(int curDigit = digitBase; curDigit >= 0; --curDigit)
			total += simuloop(curDepth + 1, depth, curDigit, number * 10 + curDigit);
		}
	return total;
	}

int solve_92()
	{
	int sum = 0;
	const int MAX_DIGIT_COUNT = 8;	// LIMIT����9λ, ������ȡ����ֵ��9999999(7��9), ����, ���ֵΪ8.
	for(int depth = 1; depth < MAX_DIGIT_COUNT; ++depth)
		sum += simuloop(0, depth, 9, 0);
	return sum;
	}
