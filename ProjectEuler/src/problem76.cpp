// See ./euler-partition.pdf for more details.
#include <vector>	// For cache.

// Euler partition //
inline int pentagon(int x)
	{ return x * (3 * x - 1) / 2; }
unsigned cached_euler_partition(unsigned n)
	{	// Use loop instead of recursion.
	std::vector<unsigned> cache;
	cache.push_back(1);	// cache[0] = 1.
	cache.reserve(n);	// reserve space.

	for(unsigned cur = 1; cur <= n; ++cur)
		{
		int tmp = 0;
		char sign = 1;
		for(int i = 1; ; ++i, sign = -sign)
			{
			int pen = cur - pentagon(i);
			if(pen < 0) break;
			tmp += sign * cache[pen];
			if((pen = cur - pentagon(-i)) < 0) break;
			tmp += sign * cache[pen];
			}

		cache.push_back(tmp);
		}
	return cache[n];
	}

unsigned solve_76()
	{
	return cached_euler_partition(100) - 1;
	}

static unsigned pure_euler_partition(int n)
	{
	if(n < 0) return 0;
	if(n == 0) return 1;
	unsigned result = 0;
	char sign = 1;
	for(int i = 1; ; ++i, sign = -sign)
		{	// Break only if euler_partition's argument is less than 0.
		int tmp = n - pentagon(i);
		if(tmp < 0) break;
		result += sign * pure_euler_partition(tmp);

		if((tmp = n - pentagon(-i)) < 0) break;
		result += sign * pure_euler_partition(tmp);
		}
	return result;
	}

unsigned __pure_solve_76()
	{	// Use euler partition without any cache.
	return pure_euler_partition(20);
	}

// Dynamic programming //
unsigned __solve_76()
	{
	const unsigned Lmt = 101;
	unsigned* buffer = new unsigned[Lmt];
	for(size_t i = 0; i < Lmt; ++i)
		buffer[i]= 0;
	buffer[0] = 1;
	for(size_t i = 1; i < Lmt; ++i)
		for(size_t j = i; j < Lmt; ++j)
			buffer[j] += buffer[j - i];
	
	unsigned result = buffer[Lmt - 1];
	delete []buffer;
	return result - 1;
	}
