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
// 找出质因子后,按照从小到大排列,并且从后向前替换质因子为比它小的合因子.
// 如果可以替换(满足约束并且比之前的值小),那么表示这个值可以缩小.

static double mainloop(int nvalue, Container& result)
{
	// 最终结果的因子个数必须要大于这个值,才能保证题目所述的丢番图方程的解大于nvalue个.
	const unsigned Target = nvalue * 2 - 1;

	// 每个质因子都是1次方,因为求的是nvalue^2的质因子,因此要*2,再+1就是总的互异质因子数.
	// count个质数相乘,结果满足题意,但是不是最小的值.
	int count = ceil_log3(Target);

	int xtry = 100;
	int* primes = new int[xtry]();

	// else, 目的是为了使primes里包含至少count个质数.
	if(get_prime_list(xtry, primes) < count) __asm int 3;

	Container exp, copy;
	for(int i = 0; i < count; ++i)
		exp[primes[i]] = 3;

	result = exp;
	// 题目中所需要的结果值,这里用double表示,因为double可以科学计数法保存,虽然转换为整数会有误差,
	// 但是用来比较大小还是很合适的.
	double min_exp_result = std::numeric_limits<double>::max();

	for(; --count >= 0; )
	{
		int i = 2;
		// 接下来要替换(primes[count]) ^ (exp[primes[count])为一个比它小的值.
		int upper = (int)pow(double(primes[count]), exp[primes[count]]);
		// 去掉这个质因子,后面替换它.
		exp.erase(primes[count]);
		copy = exp;

		// upper的值有时候会比较大,花费很多的时间在这个迭代中.
		for(; i < upper; ++i)
		{
			if(!is_prime(i, primes, count))
			{
				// 将这个数质因子分解,并且加到当前质数集合上.
				add_divisors(i, copy);

				// 当前的值.
				double current = to_number(copy);

				// 如果当前的值比当前最小值大,那么就可以退出了,因为i是单调递增的,后面的肯定也不满足.
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
		// 这次迭代中,没有缩小,表示已经无法再继续缩小,退出.
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
