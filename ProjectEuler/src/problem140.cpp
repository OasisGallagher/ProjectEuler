#include <iostream>
#include <set>
#include <numeric>

// see problem137 for more details.
typedef __int64 i64_t;
typedef std::set<i64_t> container_t;
static void next(i64_t& xn, i64_t& yn)
{
	i64_t tmp = -9i64 * xn + 20i64 * yn + 28i64;
	yn = 4i64 * xn - 9i64 * yn - 14i64;
	xn = tmp;
}

static void count(int firstx, int firsty, container_t* container)
{
	container_t::value_type x = firstx, y = firsty;
	int count = 0;
	for(; count < 30; )
	{
		if(y > 0)
		{
			++count;
			container->insert(y);
		}
		next(x, y);
	}
}

int main()
{
	// http://www.alpertron.com.ar/QUAD.HTM gives lots of solutions.
	// check them one by one.
	// any methods better than this one?
	container_t cont;
	count(-1, 0, &cont);
	count(1, 0, &cont);
	count(-7, 2, &cont);
	count(7, 2, &cont);
	count(-2, -3, &cont);
	count(2, -3, &cont);
	count(-5, -4, &cont);
	count(5, -4, &cont);
	count(14, 5, &cont);
	container_t::iterator ite = cont.begin();
	std::advance(ite, 30);
	std::cout << std::accumulate(cont.begin(), ite, 0i64) << std::endl;
}