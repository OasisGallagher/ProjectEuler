#define LIMIT	100000
#define DESIRE	10000
#include <algorithm>
#include <numeric>
#include <vector>

void GetRadical(int* cache, int len)
{	// Method used in problem72.
	std::fill(cache, cache + len, 1);

	for(int i = 2; i < len; ++i)
	{
		if(cache[i] == 1)
		{	// i must be prime.
			for(int j = i; j < len; j += i)
				cache[j] *= i;
		}
	}
}

class sortby : public std::binary_function<int, int, bool>
{
public:
	sortby(int* buffer) : buffer_(buffer){}
	bool operator()(int x, int y) const
	{
		return buffer_[x] == buffer_[y] ? (x < y) : buffer_[x] < buffer_[y];
	}
private:
	int* buffer_;
};

void SortNumberByRadical(int len, std::vector<int>* result, int* radical = NULL)
{	// sort [1, len] by radical.
	bool del = false;
	if(radical == NULL)
	{
		radical = new int[len];
		del = true;
	}
	GetRadical(radical, len);
	result->resize(len, 1);
	std::partial_sum(result->begin(), result->end(), result->begin());
	std::sort(result->begin(), result->end(), sortby(radical));
	
	if(del)
		delete[] radical;
}

int solve_124()
{
	std::vector<int> vec;
	SortNumberByRadical(LIMIT + 1, &vec);
	return vec[DESIRE];
}
