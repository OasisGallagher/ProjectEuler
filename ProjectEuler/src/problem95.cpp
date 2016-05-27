// 设置一个位置是否访问过,容易想到的类型就是bool,但是多次使用的话,需要每一次都进行清零.
// 这里的方法通过用int值代替bool值,并利用每次的int值都不同,通过指定的位置的值是否跟初始
// 值相同来检测改变,耗费了内存,但是提高了速度和简洁性.
// 方法1.	1s.
// 方法2很慢,大约要2分钟.之所以如此,可能就是因为用了map等复杂的数据结构.
// 之所以要用map与vector一一对应,是为了防止:
// a, b, x, y, x
// 这样的情况出现.
// 方法1用了一种更为巧妙的方法,见代码间的注释.
#include <vector>
#define Limit	1000000
// 索引i处表示i的真因子和.
static int gSieve[Limit];
// 表示这个数是否在查找链时索引过.
// 这个值用bool也可以标识,但是需要我们每次调用获取链长度时都把bool值全部清为false.
// 因此用整数表示,对于链中的起始值(n),如果索引为i处的值为n,表示被索引过,否则表示没有.
// 因为每次获取链长度时的起始值不一样,也就避免了重复清空bool值的操作.
static int gVisited[Limit];

static void init_div_sum()
{
	std::fill(gSieve, gSieve + Limit, 1);
	for(int i = 2; i < Limit; ++i)
		for(int j = 2; i * j < Limit; ++j)
			gSieve[i * j] += i;	// i * j contains divisor i.
}

// 如果gVisited[i] == from,表示i这个值被访问过.
static int chain_length(const int from)
{
	int result = 0;
	gVisited[from] = from;			// 置起始位置为访问过.
	for(int cur = gSieve[from]; cur < Limit; ++result)
	{
		if(gVisited[cur] == from)	// cur这个值,在环中出现过.
		{
			if(cur == from)			// 如果这个值就是起始值,表示找到了从头至尾的环.
				return result;
			else					// 链的中间存在环.
				return -1;
		}
		gVisited[cur] = from;		// 置cur位置为访问过.
		cur = gSieve[cur];
	}

	return -1;
}

int solve_95()
{
	init_div_sum();
	int maxLength = 0, result = 0;
	for(int i = 1; i < Limit; ++i)
	{
		int tmp = chain_length(i);
		if(tmp > maxLength)
			maxLength = tmp, result = i;
	}
	return result;
}
// 方法2.
#if 0
// Too slow, 200s.
#include <bitset>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

#define Sqrt(x)	(int)sqrt((double)x)
#define Limit	1000000
typedef std::vector<int>::iterator Iterator;
static std::map<int, std::vector<int> > sieve;
extern int GetPrimeList(int len, int *buffer);
extern int GetSumOfDivisors(int x, int* primeList);
int* gPrimeList = NULL;
int gPrimeCount = 0;
static int divisor_sum(int number)
{	// http://mathschallenge.net/library/number/sum_of_divisors
	return GetSumOfDivisors(number, gPrimeList);
	/*if(number == 1)
		return 1;
	int sq = Sqrt(number);
	int result = 1;
	for(int i = 2; i <= sq; ++i)
		if(number % i == 0)
			result += (i + number / i);
	if(sq * sq == number)
		result -= sq;
	return result;*/

}

static inline void combine(const int dest, const int src)
{
	Iterator ite = std::find(sieve[src].begin(), sieve[src].end(), dest);
	sieve[dest].insert(sieve[dest].end(), sieve[src].begin(), ite += (ite != sieve[src].end()));
}

static int search(const int src)
{
	int cur = src;
	const int& target = src;
	if((cur = divisor_sum(cur)) != src && cur < Limit)
	{
		sieve[src].push_back(cur);

		if(sieve[cur].empty())
			search(cur);

		combine(src, cur);
	}
	return cur;
}

int solve_95()
{
	gPrimeList = new int[Limit];
	gPrimeCount = GetPrimeList(Limit, gPrimeList);

	for(int i = 1; i < Limit; ++i)
	{
		if(sieve[i].empty())
			search(i);
	}

	size_t maxLength = 0;
	int result = 0;
	for(std::map<int, std::vector<int> >::iterator ite = sieve.begin(); ite != sieve.end(); ++ite)
	{
		size_t tmp = ite->second.size();
		if(tmp > 0 && ite->first == ite->second.back() && tmp > maxLength)
			maxLength = tmp, result = ite->first;
	}
	delete[] gPrimeList;
	return result;
}
#endif