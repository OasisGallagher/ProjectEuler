//		1 / x + 1 / y = 1 / n
// =>	n(x + y) = xy
// =>	(x - n)(y - n) = n * n
// =>	(number_of_divisor_of(n * n) + 1) / 2.
// =>	divided by 2 cos' 2 * 3 is indentical to 3 * 2.
// =>	add 1 cos' n * n is counted only once.
#include <limits>
#include <map>

typedef std::map<int, int> Container;

extern int GetPrimeList(int len, int *buffer);
extern bool isPrime(int number, int* sieve, int count);
#define is_prime	isPrime
#define get_prime_list GetPrimeList

static inline unsigned ceil_log3(unsigned x)
{
	return (int)std::ceil(log10((double)x) / log10(3.0));
}

static void add_divisors(unsigned _value, Container& update)
{	// see problem12 for more details.
	
	for(unsigned i = 2; i <= _value; ++i)
	{
		unsigned tmp = 0;
		for(; _value % i == 0; _value /= i, ++tmp)
			;
		// n = p^n * q^m
		// n^2 = p^(2n) * q^(2m)
		if(tmp != 0)
			update[i] += (2 * tmp);
	}
}

static __int64 count_divisors(const Container& arg)
{
	__int64 result = 1;
	for(Container::const_iterator ite = arg.begin(); ite != arg.end(); ++ite)
		result *= ite->second;
	return result;
}

static void to_number(const Container& container, __int64& result)
{
	result = 1i64;
	for(Container::const_iterator ite = container.begin(); ite != container.end(); ++ite)
	{
		result *= (int)pow(double(ite->first), (ite->second - 1) / 2);
	}
}

static double to_number(const Container& container)
{
	double result = 1.0;
	for(Container::const_iterator ite = container.begin(); ite != container.end(); ++ite)
	{
		result *= pow(double(ite->first), (ite->second - 1) / 2);
	}
	return result;
}

static bool less_than(const Container& left, const Container& right)
{
	double tmp1 = to_number(left);
	double tmp2 = to_number(right);
	return tmp1 < tmp2;
}

// nvalue is identical to N in this problem.
//		(x + 1) / 2 >= N
//	=>	x >= 2N - 1
// �ҳ������Ӻ�,���մ�С��������,���ҴӺ���ǰ�滻������Ϊ����С�ĺ�����.
// ��������滻(����Լ�����ұ�֮ǰ��ֵС),��ô��ʾ���ֵ������С.

static double mainloop(int nvalue, Container& result)
{
	// ���ս�������Ӹ�������Ҫ�������ֵ,���ܱ�֤��Ŀ�����Ķ���ͼ���̵Ľ����nvalue��.
	const unsigned Target = nvalue * 2 - 1;

	// ÿ�������Ӷ���1�η�,��Ϊ�����nvalue^2��������,���Ҫ*2,��+1�����ܵĻ�����������.
	// count���������,�����������,���ǲ�����С��ֵ.
	int count = ceil_log3(Target);

	int xtry = 100;
	int* primes = new int[xtry]();

	// else, Ŀ����Ϊ��ʹprimes���������count������.
	if(get_prime_list(xtry, primes) < count) __asm int 3;

	Container exp, copy;
	for(int i = 0; i < count; ++i)
		exp[primes[i]] = 3;

	result = exp;
	// ��Ŀ������Ҫ�Ľ��ֵ,������double��ʾ,��Ϊdouble���Կ�ѧ����������,��Ȼת��Ϊ�����������,
	// ���������Ƚϴ�С���Ǻܺ��ʵ�.
	double min_exp_result = std::numeric_limits<double>::max();

	for(; --count >= 0; )
	{
		int i = 2;
		// ������Ҫ�滻(primes[count]) ^ (exp[primes[count])Ϊһ������С��ֵ.
		int upper = (int)pow(double(primes[count]), exp[primes[count]]);
		// ȥ�����������,�����滻��.
		exp.erase(primes[count]);
		copy = exp;

		// upper��ֵ��ʱ���Ƚϴ�,���Ѻܶ��ʱ�������������.
		for(; i < upper; ++i)
		{
			if(!is_prime(i, primes, count))
			{
				// ������������ӷֽ�,���Ҽӵ���ǰ����������.
				add_divisors(i, copy);

				// ��ǰ��ֵ.
				double current = to_number(copy);

				// �����ǰ��ֵ�ȵ�ǰ��Сֵ��,��ô�Ϳ����˳���,��Ϊi�ǵ���������,����Ŀ϶�Ҳ������.
				if(current > min_exp_result)
					break;

				if(count_divisors(copy) > Target && current < min_exp_result)
				{
					result = copy;
					min_exp_result = current;
					break;
				}

				copy = exp;
			}
		}
		// ��ε�����,û����С,��ʾ�Ѿ��޷��ټ�����С,�˳�.
		if(i == upper)
			break;
	}

	delete[] primes;
	return min_exp_result;
}

__int64 DiophantineReciprocals(int N)
{
	Container tmp;
	return (__int64)mainloop(N, tmp);
}

__int64 solve_108()
{
	return DiophantineReciprocals(1000);
}
