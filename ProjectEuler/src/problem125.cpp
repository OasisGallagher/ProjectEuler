#include <cmath>
#include <set>
#include <numeric>

#define LIMIT		100000000
static const unsigned SQRT_LIMIT = (unsigned)sqrt(float(LIMIT));

static bool ispandigital(unsigned number)
{	// �Ƿ�Ϊ������.
	const unsigned tmp = number;
	unsigned reverse = 0;
	for(; number != 0; number /= 10)
		reverse = reverse * 10 + number % 10;
	return reverse == tmp;
}

__int64 solve_125()
{
	unsigned* buffer = new unsigned[SQRT_LIMIT + 1];
	for(unsigned i = 1; i < SQRT_LIMIT; ++i)
		buffer[i] = i * i;

	std::set<unsigned> sqrtsum;

	// �����ۼ�2����,3����...Ϊһ��ĺ�.���ж��Ƿ��ǻ�����,�ǵĻ�����set��.
	for(unsigned len = 2; len <= SQRT_LIMIT; ++len)
	{	
		unsigned tmp = std::accumulate(buffer + 1, buffer + len + 1, 0u);
		
		if(tmp > LIMIT)
			break;
		
		if(ispandigital(tmp))
			sqrtsum.insert(tmp);

		for(unsigned j = 2; j <= SQRT_LIMIT; ++j)
		{	// ��������abcd, Sum(a, b, c) = x, ��ôSum(b, c, d) = Sum(a, b, c) - a + d = Sum(a, b, c) + (d - a).
			if((tmp += (buffer[j + len - 1] - buffer[j - 1])) > LIMIT)
				break;
			if(ispandigital(tmp))
				sqrtsum.insert(tmp);
		}
	}

	delete[] buffer;
	
	return std::accumulate(sqrtsum.begin(), sqrtsum.end(), 0u);
}
