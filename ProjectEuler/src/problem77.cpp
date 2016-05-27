#include <vector>
extern bool IsPrime(unsigned x);

unsigned solve_77()
	{
	const unsigned Lmt = 5000;

	for(size_t upperBound = 1; ; upperBound *= 2)
		{
		std::vector<unsigned> vec;
		vec.push_back(1);
		vec.resize(upperBound);

		for(size_t i = 2; i < upperBound; ++i)
			{
			if(!IsPrime(i)) continue;

			for(size_t j = i; j < upperBound; ++j)
				{
				if((vec[j] += vec[j - i]) > Lmt && i == j)
					return j;
				}
			}
		}

	return 0;
	}