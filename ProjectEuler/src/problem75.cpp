// Pythagorean triple
// http://www.mathblog.dk/project-euler-75-lengths-of-wire-right-angle-triangle/
const unsigned Lmt = 1500000;
#include <cmath>
// Overview:
// We can generate every primitive triplet by iterating over the integers m, n
// such that m > n, and m + n is odd and gcd(n,m) == 1.

extern unsigned gcd(unsigned, unsigned);
unsigned solve_75()
	{
	unsigned result = 0;
	// a = 2 * m * n;
	// b = m * m - n * n;
	// c = m * m + n * n;
	// Lmt >= a + b + c = 2mn + 2mm = 2(mn + mm)
	// mn + mm <= (Lmt / 2).
	// for n > 0, mm < mn + mm <= (Lmt / 2)
	// m < sqrt(Lmt / 2).
	unsigned upper = (unsigned)std::ceil(std::sqrt(Lmt / 2.0));

	// Use stack variable will cause stack overflow.
	size_t *buffer = new size_t[Lmt + 1];
	
	// Initialize buffer.
	for(size_t i = 0; i < Lmt + 1; ++i)
		buffer[i] = 0;
	
	for(size_t m = 2; m < upper; ++m)
		for(size_t n = 1; n < m; ++n)	// n < m.
			{
			// http://en.wikipedia.org/wiki/Pythagorean_triple
			// Definition: Primitive
			// A Pythagorean Triplet is called primitive if a, b and c are coprime. 
			// That means that the greatest common divisor (gcd) of the set {a,b,c} is one.
			// In order to generate a primitive primitive pythagorean, one of m and
			// n must be an odd, the other must be an even number, or, common divisor
			// of a, b, c will contain 2.
			// further more, gcd(m, n) must be 1, or d^2 will be an common divisor
			// of a, b, c.
			if((m + n) % 2 == 1 && gcd(n, m) == 1)
				{
				// Get a primitive pythagorean triple that multiply k with all
				// a, b, y will generate another.
				size_t a = 2 * m * n;
				size_t b = m * m - n * n;
				size_t c = m * m + n * n;
				size_t len = a + b + c;
				// Keep in mind that a, b and c are primitive triple, which may generate
				// lots of non-primitive triples.
				while(len <= Lmt)
					{ // If a, b, c is a pythagorean triple, ak, bk, ck must be too.
					++buffer[len];
					len += (a + b + c);
					}
				}
			}
	// Add only if exactly one integer sided right angle triangle be formed with a specific L.
	for(size_t i = 0; i <= Lmt; ++i)
		result += (buffer[i] == 1);

	//Clean up.
	delete[] buffer;
	return result;
	}
