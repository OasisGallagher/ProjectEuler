// 直接遍历的方法是不可行的,耗时太久.
// 需要注意的是,完全N次方数其实很少.对于2来说,组成的完全N次方数对于一个64
// 位数来说,只存在64个,即2^n.
// 因此,从这个角度构造数,再测试应该会快很多.
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
{	// x1 × x2是否溢出.
	return UINT64_MAX / x1 <= x2;
}

__int64 solve_119()
{
	std::list<ui64_t> xlist;
	for(int base = 2; base < 500; ++base)
	{
		// 乘方的方式构造数,power必然是完全N次方数,需要检验的是它的DigitSum是否和它N次方的基数相等.
		for(ui64_t power = base * base; !mul_overflow(power, base); power *= base)
			if(digit_sum(power) == base)	// 按顺序插入.
				xlist.insert(std::lower_bound(xlist.begin(), xlist.end(), power), power);
	}
	int i = 0;
	std::list<ui64_t>::const_iterator ite = xlist.begin();
	for(; ite != xlist.end() && ++i < 30; ++ite)
		;
	return ite != xlist.end() ? *ite : 0;
}