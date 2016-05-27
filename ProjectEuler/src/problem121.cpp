#define SolutionOne
typedef __int64 number;

// 计算概率,计算方法为枚举蓝色比红色多的各种情况,累加概率.

static number _Sel(int* from, int len, int index, int cur, int total, number memory)
{
	if(cur > total)
		return memory;

	number result = 0;
	for(int i = index; i < len; ++i)
		result += _Sel(from, len, i + 1, cur + 1, total, memory * from[i]);

	return result;
}

static number select(int len)
{
	number tmp = 0;
	int* from = new int[len];

	for(int i = 0; i < len; ++i)
		from[i] = i + 1;

	int bound = (len & 1) ? len / 2 + 1 : len / 2;

	for(int i = 0; i < bound; ++i)
	{
		number memory = 1;
		tmp += _Sel(from, len, 0, 1, i, memory);
	}

	delete []from;
	return tmp;
}

static number fact(int n)
{
	return n <= 1 ? 1 : n * fact(n - 1);
}

template <int TurnCount>
number totalselect();

number solve_121()
{
	const int len = 15;
	number tmp = 0;
	number f = fact(len + 1);
#ifdef SolutionOne	// 3 ms
	tmp = select(len);
#else				// 22 ms
	tmp = totalselect<len>();
#endif
	return (f % tmp == 0) ? 1 + f / tmp : f / tmp;
}

#include <bitset>
template <int TurnCount>
bool increase(std::bitset<TurnCount>& bs);

template <int TurnCount>
number totalselect()
{
	std::bitset<TurnCount> bs;
	size_t bound = (TurnCount & 1) ? TurnCount / 2 + 1 : TurnCount / 2;
	number result = 0;
	do 
	{
		// 置为1的位表示这次取到的是红色,即失败.
		if(bs.count() < bound)
		{
			number tmp = 1;
			for(int i = 0; i < TurnCount; ++i)
			{
				if(bs.test(i))
					tmp *= (i + 1);
			}
			result += tmp;
		}
	} while (increase(bs));

	return result;
}

template <int TurnCount>
bool increase(std::bitset<TurnCount>& bs)
{
	int i = 0;
	for(; i < TurnCount && bs.test(i); ++i)
		bs.set(i, false);

	return i < TurnCount ? bs.set(i), true : false;
}
