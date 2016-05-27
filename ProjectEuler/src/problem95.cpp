// ����һ��λ���Ƿ���ʹ�,�����뵽�����;���bool,���Ƕ��ʹ�õĻ�,��Ҫÿһ�ζ���������.
// ����ķ���ͨ����intֵ����boolֵ,������ÿ�ε�intֵ����ͬ,ͨ��ָ����λ�õ�ֵ�Ƿ����ʼ
// ֵ��ͬ�����ı�,�ķ����ڴ�,����������ٶȺͼ����.
// ����1.	1s.
// ����2����,��ԼҪ2����.֮�������,���ܾ�����Ϊ����map�ȸ��ӵ����ݽṹ.
// ֮����Ҫ��map��vectorһһ��Ӧ,��Ϊ�˷�ֹ:
// a, b, x, y, x
// �������������.
// ����1����һ�ָ�Ϊ����ķ���,��������ע��.
#include <vector>
#define Limit	1000000
// ����i����ʾi�������Ӻ�.
static int gSieve[Limit];
// ��ʾ������Ƿ��ڲ�����ʱ������.
// ���ֵ��boolҲ���Ա�ʶ,������Ҫ����ÿ�ε��û�ȡ������ʱ����boolֵȫ����Ϊfalse.
// �����������ʾ,�������е���ʼֵ(n),�������Ϊi����ֵΪn,��ʾ��������,�����ʾû��.
// ��Ϊÿ�λ�ȡ������ʱ����ʼֵ��һ��,Ҳ�ͱ������ظ����boolֵ�Ĳ���.
static int gVisited[Limit];

static void init_div_sum()
{
	std::fill(gSieve, gSieve + Limit, 1);
	for(int i = 2; i < Limit; ++i)
		for(int j = 2; i * j < Limit; ++j)
			gSieve[i * j] += i;	// i * j contains divisor i.
}

// ���gVisited[i] == from,��ʾi���ֵ�����ʹ�.
static int chain_length(const int from)
{
	int result = 0;
	gVisited[from] = from;			// ����ʼλ��Ϊ���ʹ�.
	for(int cur = gSieve[from]; cur < Limit; ++result)
	{
		if(gVisited[cur] == from)	// cur���ֵ,�ڻ��г��ֹ�.
		{
			if(cur == from)			// ������ֵ������ʼֵ,��ʾ�ҵ��˴�ͷ��β�Ļ�.
				return result;
			else					// �����м���ڻ�.
				return -1;
		}
		gVisited[cur] = from;		// ��curλ��Ϊ���ʹ�.
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
// ����2.
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