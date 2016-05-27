#include <vector>
#include <queue>
#include <cassert>
#include <bitset>
#include <numeric>

#include <fstream>

typedef std::vector<size_t> container;

#define Count	(200)
typedef std::bitset<Count> bs_type;

static bool set_value(container* cont, size_t pos, size_t val, bs_type& sieve)
{
	cont->at(pos) = val;
	sieve.set(pos);
	return !sieve.all();
}

// bfs.
// 用dfs也可以解决,键枝的依据在于,结果的长度不会高于一直平方的长度.比如,1-2-4-8-16...
// 这个问题是经典的NPC问题.wiki上有上述的论述.
// en.m.wikipedia.org/wiki/Addition-chain_exponentiation
// http://www.mathblog.dk/project-euler-122-efficient-exponentiation/
int solve_122()
{
	std::queue<container> que;
	
	container cont(Count);
	cont[0] = 1;

	bs_type sieve;
	sieve.set(0);
	
	que.push(container(1, 1));

	size_t deep = 0;
	
	while(!que.empty())
	{	
		container coins = que.front();
		que.pop();

		container::value_type last = coins.back();
		deep = coins.size();

		for(size_t i = 0; i < deep; ++i)
		{
			size_t tmp = last + coins[i];
			if(tmp > Count)
				break;

			// [1], see below.
			// already set and need more steps.
			if(sieve.test(tmp - 1) && cont[tmp - 1] < deep)
				continue;

			if(!set_value(&cont, tmp - 1, deep, sieve))
				return std::accumulate(cont.begin(), cont.end(), 0) - 1;// (zero step to get 1)

			coins.push_back(tmp);
			que.push(coins);
			coins.pop_back();
		}
	}
	throw std::runtime_error("runtime error: unable to get the answer!");
	return deep;
}

// [1]
