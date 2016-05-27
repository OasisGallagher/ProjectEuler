#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

// 设检测的数为n, 除数是d, 商是q, 余数是r.
// 首先, 题目中说, 除数, 商, 余数三者是等差数列, 但是并不一定是哪种顺序, 需要首先确定顺序.
// 显然, d > r, 可以假设d > q > r(其他情况可以证明是不可能的, 只有q > d > r可能, 但是交换q和d的位置,
// 也可以得到前面的公式)
//
// <TODO>
// 有一种意外, 就是当q > d > r时, 交换q, d的位置, 可能q | n, 使得r为0. 本题中没有遇到这个问题, 
// 但是还是需要更为严格的证明.
// </TODO>
//
// 设公比为a, 那么q = ar, d = aar, 且a > 1. 因为a可能是分数, 所以讲a写成 b / c的形式, 且gcd(b,c) = 1.
// 因为d, q, r都是正整数, br / c与brr / c都是正整数.
// 由于gcd(b, c) = 1, 所以, c中必然还有因子rr, 这样才能与分子中的r约掉.
// 设r = ecc, 其中r, e是一个正整数, c为a的分母.
// 根据除法运算的性质, n = dq + r = dar * arr + r = d(r^2)(a^3) + r = (e^2)(c^4)(a^3) + e(c^2) = (e^2)((ac)^3)c + e(c^2)
// 因为c是a的分母, 所以ac就是a的分子, 设为b.
// 即(e^2)(b^3)c + e(c^2) = n.
// 此时, 上式中的任何变量都是正整数, b是a的分子, c是a的分母, 因为a > 1, 所以b > c.
// 接下来, 枚举这三个值.
//
// <TODO>
// 26s on i3 cpu.
// </TODO>

typedef __int64 Number;

static bool FareySequence(unsigned& a, unsigned& b, unsigned& c, unsigned& d, const unsigned n)
{
	unsigned tmp = (n + b) / d;
	unsigned c1 = c, d1 = d;
	c = tmp * c - a;
	d = tmp * d - b;
	a = c1;
	b = d1;

	return c != d;
}
#define Square(rt)	(Number(rt) * (rt))
#define Cube(rt)	(Square(rt) * (rt))

#define MaxValue    1000000000000i64
static const unsigned MaxNumerator = (unsigned)ceil(pow(double(MaxValue), 1.0 / 3)) - 1;

class PSChecker {
public:
	PSChecker() { 
		pscount = (unsigned)ceil(sqrt((double)MaxValue));
		maxsquare = Square(pscount - 1);
		buffer = new Number[pscount]; 
		pos = 0;
		for(unsigned i = 0; i < pscount; ++i) {
			buffer[i] = Square(i);
			if(pos == 0 && buffer[i] > UINT_MAX)
				pos = i;
		}
	}
	~PSChecker() { delete[] buffer; }
	bool ChkNumber(const Number& number) const {
		if(number <= UINT_MAX) {
			return Square((unsigned)(sqrt((double)number))) == number;
		}

		return std::binary_search(buffer + pos, buffer + pscount, number);
	}

	Number MaxSquare() const {
		return maxsquare;
	}
private:
	unsigned pscount;
	Number maxsquare;
	unsigned pos;
	Number* buffer;
};

int main() { 
	clock_t start = clock();
	Number result = 0; 

	PSChecker chkps;
	Number MaxSq = chkps.MaxSquare();

	std::cout << ((float)clock() - start) / CLOCKS_PER_SEC << " second(s) to prepare.\n";
	for(unsigned a = 0, b = 1, c = 1, d = MaxNumerator; FareySequence(a, b, c, d, MaxNumerator); ) {
		Number b3 = Cube(b), a2 = Square(a), ab3 = a * b3;
		Number first = 0, second = 0;
		for(unsigned e = 1; ; ++e) {
			first += ab3 * (2 * e - 1);
			if(first > MaxSq) break;

			// if first < MaxSquare, second must be less than MaxSquare too.
			second += a2;

			Number tmp = first + second; 
			if(tmp > MaxSq) break;

			if(chkps.ChkNumber(tmp))
				result += tmp;
		}
	}

	std::cout << ">> " << result << std::endl;
	std::cout << (float)(clock() - start) / CLOCKS_PER_SEC << " second(s) to finish.\n";
	return 0; 
} 