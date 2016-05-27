#include <utility>
typedef std::pair<int, int> Sequence;
static const unsigned LMT = 12000;
// See farey-sequences.png and http://en.wikipedia.org/wiki/Farey_sequence for more details.
// 100 ms, with farey sequence.
static void next_fraction(unsigned& x, unsigned& y)
	{
	for(unsigned i = LMT; i >= 2; --i)
		{
		unsigned tmp;
		if((tmp = i * x + 1) % y == 0)
			{
			x = tmp / y;
			y = i;
			break;
			}
		}
	}

bool NextSequence(Sequence& sq1, Sequence& sq2, const int N)
{	// Get next term of farey-sequence.
	std::swap(sq1, sq2);
	const int tmp = (N + sq2.second) / sq1.second;
	sq2 = std::make_pair(tmp * sq1.first - sq2.first, tmp * sq1.second - sq2.second);
	return (sq2.first != sq2.second);
}

unsigned solve_73()
	{
	unsigned result = 0;
	unsigned a = 1;
	unsigned b = 3;
	unsigned c = a;
	unsigned d = b;
	next_fraction(c, d);

	while(c != 1 || d != 2)
		{
		unsigned tmp = (LMT + b) / d;
		unsigned e = tmp * c - a;
		unsigned f = tmp * d - b;
		// Update.
		a = c;
		b = d;
		c = e;
		d = f;

		++result;
		}
	return result;
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////// 5 sec, Brute force /////////////////////////////////
//////////////////////////////////////////////////////////////////////////

unsigned gcd(unsigned, unsigned);
unsigned __solve_73()
	{
	unsigned result = 0;
	for(unsigned denominator = 4; denominator <= LMT; ++denominator)
		{
		// If 2 | denominator, numerator must be less than (denominator / 2)
		// or, numerator must be less than ceil(denominator / 2).
		// For 3, 1 + denominator / 3 is OK.
		unsigned boundary = (denominator % 2 == 0) ? (denominator / 2) 
			: (denominator / 2) + 1;
		for(unsigned numerator = 1 + denominator / 3; 
			numerator < boundary; ++numerator)
			result += (gcd(denominator, numerator) == 1);
		}
	return result;
	}

#include <algorithm>
unsigned gcd(unsigned x, unsigned y)
	{
	while(y != 0)
		{
		if(x < y)
			std::swap(x, y);

		x %= y;
		std::swap(x, y);
		}
	return x;
	}
