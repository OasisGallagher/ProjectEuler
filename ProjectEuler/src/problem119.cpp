// ֱ�ӱ����ķ����ǲ����е�,��ʱ̫��.
// ��Ҫע�����,��ȫN�η�����ʵ����.����2��˵,��ɵ���ȫN�η�������һ��64
// λ����˵,ֻ����64��,��2^n.
// ���,������Ƕȹ�����,�ٲ���Ӧ�û��ܶ�.
#include <list>
#include <algorithm>
#define UINT64_MAX	0xffffffffffffffffui64
typedef unsigned __int64 ui64_t;

static int digit_sum(ui64_t number)
{
	int result = 0;
	for(; number != 0; number /= 10)
		result += (number % 10);
	return result;
}

static bool mul_overflow(const ui64_t& x1, const ui64_t& x2)
{	// x1 �� x2�Ƿ����.
	return UINT64_MAX / x1 <= x2;
}

__int64 solve_119()
{
	std::list<ui64_t> xlist;
	for(int base = 2; base < 500; ++base)
	{
		// �˷��ķ�ʽ������,power��Ȼ����ȫN�η���,��Ҫ�����������DigitSum�Ƿ����N�η��Ļ������.
		for(ui64_t power = base * base; !mul_overflow(power, base); power *= base)
			if(digit_sum(power) == base)	// ��˳�����.
				xlist.insert(std::lower_bound(xlist.begin(), xlist.end(), power), power);
	}
	int i = 0;
	std::list<ui64_t>::const_iterator ite = xlist.begin();
	for(; ite != xlist.end() && ++i < 30; ++ite)
		;
	return ite != xlist.end() ? *ite : 0;
}