// See ./euler-partition.pdf for more details.
#include <vector>

inline int pentagon(int x)
	{ return x * (3 * x - 1) / 2; }

static std::vector<unsigned> cache;

static int limited_cached_euler_partition(unsigned n)
	{	// Use loop instead of recursion.
	for(unsigned cur = cache.size(); cur <= n; ++cur)
		{
		// What wastes me lots of time is tmp may be negative sometimes.
		// DO NOT USE unsigned tmp.
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
		// What we are interested in is the last 6 digits.
		cache.push_back(tmp % 1000000);
		}
	return cache[n];
	}

int solve_78()
	{
	// P(55374) = 36325300925435785930832331577396761646715836173633893227071086460709268608053489541731404543537668438991170680745272159154493740615385823202158167635276250554555342115855424598920159035413044811245082197335097953570911884252410730174907784762924663654000000L
	cache.push_back(1);	// cache[0] = 1.
	for(int i = 1; i < 0x7FFFFFFF; ++i)
		if(0 == limited_cached_euler_partition(i))
			return i;
	return -1;
	}
