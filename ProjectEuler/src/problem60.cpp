#include <map>
#include <iostream>
#include <limits>
#include "../include/visitmatrix.hpp"

extern bool IsPrime(unsigned x);

static int* primes;
static const int COUNT = 1100;
static int ans = std::numeric_limits<int>::max();
static int list[5];

//vm(i, j), both i and j is the index of the prime table.
static VisitMatrix vm(COUNT);

static
void initPrimes(int count)
	{
	int cur = 0;
	for(int i = 2; cur < count; ++i)
		if(IsPrime(i))
			primes[cur++] = i;
	}

static
bool checkPrev(int depth)
	{
	for(int i = 0; i < depth; ++i)
		if(!vm(list[i], list[depth]))
			return false;
	return true;
	}

static
int catNumbers(int first, int second)
	{
	int tmp1 = first;
	for(int tmp2 = second; tmp2 != 0; tmp2 /= 10)
		tmp1 *= 10;
	return tmp1 + second;
	}

static
void buildTable()
	{
	for(int i = 0; i < COUNT; ++i)
		for(int j = i + 1; j < COUNT; ++j)
			{
			vm.set(i, j);
			if(!IsPrime(catNumbers(primes[i], primes[j])) || !IsPrime(catNumbers(primes[j], primes[i])))
				vm.clear(i, j);
			}
	}

// Great algorithm.
static
void dfs(int cur, int depth)
	{
	if(depth == 5)
		{
		int sum = 0;
		for(int i = 0; i < 5; ++i)
			sum += primes[list[i]];
		if(sum < ans)
			ans = sum;
		}
	else
		{
		for(int i = cur; i < COUNT; ++i)
			{
			list[depth] = i;
			if(checkPrev(depth))	// Get an available result.
				dfs(i + 1, depth + 1);
			// then, ++i, check i with the same depth.
			}
		}
	}

int GetTheLowestSumForASetOfFivePrimesForWhichAnyTwoPrimesConcatenateToProduceAnotherPrime()
	{
	primes = new int[COUNT];
	initPrimes(COUNT);
	buildTable();
	dfs(0, 0);
	delete[] primes;
	return ans;
	}

/////////////////////// Ugly and slow solution by myself :( ////////////////////////
#if 0	
#define BUF_LEN	4096 * 4

std::map<int, bool> table;
extern int GetPrimeList(int len, int *buffer);
extern bool IsPrime(unsigned x);
static int* buffer;
static int count;

static
int catNumber(int first, int last)
	{
	int temp1 = first;
	int temp2 = last;
	for(; temp2 != 0; temp2 /= 10)
		temp1 *= 10;
	return temp1 + last;
	}

void buildTable()
	{
	clock_t beg = clock();
	for(int i = 0; i < count; ++i)
		for(int j = 0; j < count; ++j)
		{
		if(i == j)
			{
			table[makeKey(buffer[i], buffer[j])] = false;
			continue;
			}

		int number = catNumber(buffer[i], buffer[j]);
		table[makeKey(buffer[i], buffer[j])] = IsPrime(number);
		number = catNumber(buffer[j], buffer[i]);
		table[makeKey(buffer[j], buffer[i])] = IsPrime(number);
		}
	std::cout << __FUNCTION__ << ": " << (clock() - beg) << " milliseconds in total.\n";
	}

int GetTheLowestSumForASetOfFivePrimesForWhichAnyTwoPrimesConcatenateToProduceAnotherPrime()
	{
	buffer = new int[BUF_LEN];
	count  = GetPrimeList(BUF_LEN, buffer);
	buildTable();
	clock_t beg = clock();
	int result = 0;
	for(int i = 0; i < count; ++i)
		for(int j = i + 1; j < count; ++j)
			{
			if(!table[makeKey(buffer[i], buffer[j])] || !table[makeKey(buffer[j], buffer[i])])
				continue;
			for(int k = j + 1; k < count; ++k)
				{
				if(!table[makeKey(buffer[j], buffer[k])] || !table[makeKey(buffer[i], buffer[k])]
				|| !table[makeKey(buffer[k], buffer[j])] || !table[makeKey(buffer[k], buffer[i])])
					continue;
				for(int l = k + 1; l < count; ++l)
					{
					if(!table[makeKey(buffer[i], buffer[l])] || !table[makeKey(buffer[j], buffer[l])] || !table[makeKey(buffer[k], buffer[l])]
					|| !table[makeKey(buffer[l], buffer[i])] || !table[makeKey(buffer[l], buffer[j])] || !table[makeKey(buffer[l], buffer[k])])
						continue;
					for(int m = l + 1; m < count; ++m)
						{
						if(!table[makeKey(buffer[i], buffer[m])] || !table[makeKey(buffer[j], buffer[m])] || !table[makeKey(buffer[k], buffer[m])] || !table[makeKey(buffer[l], buffer[m])]
						|| !table[makeKey(buffer[m], buffer[i])] || !table[makeKey(buffer[m], buffer[j])] || !table[makeKey(buffer[m], buffer[k])] || !table[makeKey(buffer[m], buffer[l])])
							continue;
						else
							{
							std::cout << buffer[i] << " " << buffer[j] << " " << buffer[k] << " "<< buffer[l] << " "<< buffer[m] << std::endl;
							result = buffer[i] + buffer[j] + buffer[k] + buffer[l] + buffer[m];
							delete[] buffer;
							std::cout << __FUNCTION__ << ": " << (clock() - beg) << " milliseconds in total.\n";
							return result;
							}
						}
					}
				}
			}
	delete[]buffer;
	return 0;	
	}
#endif