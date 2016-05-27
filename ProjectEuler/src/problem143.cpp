#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <bitset>
#include <cassert>
#include <ctime>

typedef std::pair<unsigned, unsigned> Term;
#define MakeTerm(U1, U2)	(std::make_pair(U1, U2))
#define Get1stPart(T)		(T.first)
#define Get2ndPart(T)		(T.second)
typedef std::vector<Term> TermContainer;
#define SumLimit	120000
#define Square(X)	((X) * (X))
typedef std::bitset<SumLimit> ContainChk;

struct Range { 
	Range(int l = 0, int h = 0) : low(l), high(h) {}
	int low; 
	int high; 
};
typedef std::map<int, Range> RangeHash;

static inline bool CmpTerm(Term& t1, Term& t2) {
	unsigned _1 = Get1stPart(t1), _2 = Get1stPart(t2);
	return (_1 == _2) ? Get2ndPart(t1) < Get2ndPart(t2) : (_1 < _2);
}

static int Gcd(unsigned x, unsigned y) {
	if(x < y) std::swap(x, y);
	while(y != 0)
		std::swap(x %= y, y);
	return x;
}

// http://www.geocities.ws/fredlb37/node9.html
// Finding parametric equations for 120 and 60 degree triples.
static void GetTerms(TermContainer* result, RangeHash& hash) {
	for(unsigned m = 1; m < 367; ++m) {
		for(unsigned n = 1; n < m; ++n) {
			if(Gcd(m, n) != 1 || (m - n) % 3 == 0) continue;

			unsigned n2 = Square(n);
			unsigned a = Square(m) - n2;
			unsigned b = 2 * m * n + n2;

			if(a + b > SumLimit) 
				break;

			if(a > b) std::swap(a, b);

			unsigned old_a = a, old_b = b;
			for(; (a + b) < SumLimit; a += old_a, b += old_b)
				result->push_back(MakeTerm(a, b));
		}
	}
	std::sort(result->begin(), result->end(), CmpTerm);

	int tmp = -1, first = 0, last = 0;
	for(TermContainer::iterator ite = result->begin(); ite != result->end(); ++ite) {
		Term& t = *ite;
		if(tmp == -1) {
			tmp = Get1stPart(t);
			first = std::distance(result->begin(), ite);
		}
		else if(Get1stPart(t) != tmp) {
			last = std::distance(result->begin(), ite);

			hash[tmp] = Range(first, last);

			tmp = Get1stPart(t);
			first = std::distance(result->begin(), ite);
		}
	}
	last = (int)result->size();
	hash[tmp] = Range(first, last);
}

int main() {
	clock_t start = clock();
	TermContainer cont;
	RangeHash hash;
	std::bitset<SumLimit> bs;
	unsigned result = 0;

	GetTerms(&cont, hash);

	std::cout << float(clock() - start) / CLOCKS_PER_SEC << " second(s) to prepare.\n";

	// example: 325	264	195.
	for(RangeHash::iterator ite = hash.begin(); ite != hash.end(); ++ite) {
		const RangeHash::value_type& val = *ite;
		for(int i = val.second.low; i < val.second.high; ++i) {
			for(int j = i + 1; j < val.second.high; ++j) {
				const Term& t1 = cont[i];
				const Term& t2 = cont[j];
				
				unsigned x = Get2ndPart(t1), y = Get2ndPart(t2);
				if(x > y) std::swap(x, y);
				Term term = MakeTerm(x, y);
				if(hash.find(x) != hash.end()) {
					const RangeHash::value_type::second_type& ran = hash[x];

					TermContainer::iterator first = cont.begin(), last = first;
					std::advance(first, ran.low);
					std::advance(last, ran.high);

					if(std::binary_search(first, last, term)) {
						unsigned sum = Get1stPart(term) + Get2ndPart(term) + val.first;
						if(sum < SumLimit && !bs.test(sum)) {
							result += sum;
							bs.set(sum);
						}
					}
				}
			}
		}
	}
	std::cout << result << std::endl;
	std::cout << float(clock() - start) / CLOCKS_PER_SEC << " second(s) in total.\n";
	return 0;
}