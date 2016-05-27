#if 0
#pragma region PseudoPrimeTest_10min
#include <iostream>
#include <cmath>
#include <ctime>
#include <limits>
typedef unsigned long long Number;
static Number NUM_MAX = std::numeric_limits<Number>::max();
static unsigned* sieve = NULL;
static const unsigned SieveUpper = 10000;
static unsigned sieve_size;

class PrimeTest {
public:
	static bool PseudoPrime(const Number& number) {
		return ModExp(2, number - 1, number) == 1;
	}

	static bool IsProbPrime(const Number& number) {
		if(sieve == NULL) {
			sieve = new unsigned[SieveUpper];
			sieve_size = GetPrimeList(SieveUpper, sieve);
		}

		for(unsigned i = 0; i < sieve_size && sieve[i] < number; ++i) {
			if(number % sieve[i] == 0) return false;
		}

		return PseudoPrime(number);
	}

	// get primes below len.
	static unsigned GetPrimeList(unsigned len, unsigned *buffer) {
		const unsigned* begin = buffer;
		bool *bptr = new bool[len];
		for(unsigned i = 2; i < len; ++i)
			bptr[i] = true;
		bptr[0] = bptr[1] = false;

		for(unsigned i = 2; i < len; ++i) {
			if(!bptr[i]) continue;
			for(unsigned j = 2; j * i < len; ++j)
				bptr[j * i] = false;
		}

		for(unsigned i = 0; i < len; ++i)
			if(bptr[i]) *buffer++ = i;

		// returns the count of primes.
		return buffer - begin;
	}
private:
	// eg: 7 = 1 + 2 + 4...
	// (x * y) % mod, taking into account that a * b might overflow.
	static Number MulMod(const Number& x, const Number& y, const Number& mod) {
		if(NUM_MAX / x >= y) return (x * y) % mod;

		Number tmpy = y;
		Number b = x % mod;
		Number result = 0;
		Number left = 0;
		while(tmpy != 0) {
			if((tmpy & 1) != 0) {
				result += b;
				result %= mod;
			}
			b <<= 1;
			b %= mod;
			tmpy >>= 1;
		}

		return result;
	}
	// (base ^ exp) % mod.
	static Number ModExp(const Number& base, const Number& exp, const Number& mod) {
		Number x = base;
		Number tmp_exp = exp;
		Number result = 1;
		for(; ; x = MulMod(x, x, mod)) {
			if((tmp_exp & 1) != 0)
				result = MulMod(result, x, mod);
			if(!(tmp_exp >>= 1))
				return result;
		}
		return 0;
	}
};
#pragma endregion PseudoPrimeTest_10min

// 10, 315410.
int main() {
	clock_t start = clock();
	unsigned result = 0;
	for(int i = 10; i < 160000000; i += 10) {
		//if(i == 315410) __asm int 3;
		if(i % 3 == 0 || (i + 4) % 7 > 1 || i % 13 == 0) continue;

		Number square = i * Number(i);
		if(square % 3 != 1) continue;

		unsigned rem7 = square % 7;
		if(rem7 != 2 && rem7 != 3) continue;

		if(!PrimeTest::IsProbPrime(square + 1)) continue;
		if(!PrimeTest::IsProbPrime(square + 3)) continue;
		if(!PrimeTest::IsProbPrime(square + 7)) continue;
		if(!PrimeTest::IsProbPrime(square + 9)) continue;
		if(!PrimeTest::IsProbPrime(square + 13)) continue;
		if(!PrimeTest::IsProbPrime(square + 27)) continue;
		if(PrimeTest::IsProbPrime(square + 19)) continue;
		if(PrimeTest::IsProbPrime(square + 21)) continue;
		result += i;
		std::cout << i << "\n";
	}
	std::cout << "result is " << result << std::endl;
	std::cout << (clock() - start) / float(CLOCKS_PER_SEC) << " second(s)." << std::endl;
}
#endif
#pragma region CheckPrimalityAtOnce_10s_From_Thread_Floor_11
#include <iostream>
#include <ctime>

typedef unsigned __int64 uint64_t;
bool isprime(uint64_t n, int sqrt_of_n) {
	if (n < 4) return (n > 1);
	if ((n % 2) == 0) return false;
	if ((n % 3) == 0) return false;
	for (int p = 5; ;) {
		if (p > sqrt_of_n) return true;
		if ((n % p) == 0) return false;
		p += 2;
 		if ((n % p) == 0) return false;
		// skip 9, 15, 21 ... 
 		p += 4;
	}
	return true;
}

int main(int argc, char *argv[]) {
	clock_t start = clock();
	unsigned limit = 150 * 1000000;
	uint64_t result = 0;
	
	for(unsigned n = 10; n < limit; n += 10) {
		uint64_t n2 = n; n2 *= n;

		if(n2 % 3 != 1) continue;
		unsigned tmp = n2 % 7;
		if(tmp != 2 && tmp != 3) continue;

		for (unsigned p = 11; ; ) {
			unsigned nd = n2 % p;

			// check for primality of all 6 numbers AT ONCE.
			if (((nd + 27) % p) <= 27) {
				if ((nd + 1) % p == 0) break;
				if ((nd + 3) % p == 0) break;
				if ((nd + 7) % p == 0) break;
				if ((nd + 9) % p == 0) break;
				if ((nd + 13) % p == 0) break;
				if ((nd + 27) % p == 0) break;
			}

			p += 2;
			if ((p % 3) == 0) p += 2;

			// n + 1 > sqrt(nd).
			if (p > n + 1) {
				// check for contiguity.
				if (isprime(n2 + 15, n + 1)) break;
				if (isprime(n2 + 19, n + 1)) break;
				if (isprime(n2 + 21, n + 1)) break;
				if (isprime(n2 + 25, n + 1)) break;
				std::cout << "found n = " << n << std::endl;
				result += n;
				break;
			}
		}
	}
	std::cout << "result is " << result << std::endl;
	std::cout << (clock() - start) / float(CLOCKS_PER_SEC) << " second(s)." << std::endl;
}
#pragma endregion CheckPrimalityAtOnce_10s_From_Thread_Floor_11
