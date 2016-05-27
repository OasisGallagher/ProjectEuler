#include <vector>
#include <sstream>
#include <numeric>

// 与公式计算出来的集合估计的差值(扩大这个差值可能让结果更加可信,但是会极大的增加时间).
static const int Offset = 3;
// 当前最小的集合和.
static int min_sum = INT_MAX;

static int count(std::vector<int>&arr, int mask, int max_pos, size_t& bit_count)
{
	bit_count = 0;
	int result = 0;
	for(int i = 0; i < max_pos; ++i)
	{
		if(1 << i & mask)
		{
			result += arr[i];
			++bit_count;
		}
	}
	return result;
}
// 如果最小的大集合的和依然大于小集合的和, 那么一定成立. 取前n / 2 + 1个值和其余的值的和,
// 前n/2+1个值的和就是大集合的最小值,其余的就是小集合的最大值.
static bool bigset_bigsum(std::vector<int>& arr)
{
	int sum = 0;
	int head = 0, tail = arr.size() - 1;
	for(; head < tail; ++head, --tail)
		sum += arr[head] - arr[tail];

	return sum + arr[head] > 0;
}

bool special_set(std::vector<int>& arr)
{
	if(!bigset_bigsum(arr))
		return false;
	const int SieveSize = arr[arr.size() - 1] * arr.size();
	std::auto_ptr<bool> sieve(new bool[SieveSize]());
	const int Limit = 1 << arr.size();

	for(int mask = 1; mask < Limit; ++mask)
	{
		size_t bit_count = 0;
		int sum = count(arr, mask, arr.size(), bit_count);

		if(*(sieve.get() + sum))
			return false;
		*(sieve.get() + sum) = true;
	}

	return true;
}

static void format(std::vector<int>& result, std::string& str)
{
	std::stringstream ss;

	for(size_t i = 0; i < result.size(); ++i)
		ss << result[i];
	str.assign(ss.str());
}

static bool findproc(const int* Limit, int size, int min, int depth, std::vector<int>& result, std::string& str)
{
	if(depth == size)
	{
		return special_set(result);
	}
	else
	{
		for(int i = min; i <= Limit[depth]; ++i)
		{
			result[depth] = i;
			if(findproc(Limit, size, i + 1, depth + 1, result, str))
			{
				int tmp = std::accumulate(result.begin(), result.end(), 0);
				if(tmp < min_sum)
				{
					min_sum = tmp;
					format(result, str);
				}
			}
		}
	}
	return false;
}

std::string solve_103()
{
	int limit[] = { 20, 31, 38, 39, 40, 42, 45 }, size = _countof(limit);
	const int FirstMin = limit[0];
	for(int i = 0; i < size; ++i)
		limit[i] += Offset;
	std::vector<int> result(size, 0);
	std::string str = "not found.";
	findproc(limit, size, FirstMin, 0, result, str);
	
	return str;
}
