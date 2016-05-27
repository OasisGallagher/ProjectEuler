#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

// �������Ϊn, ������d, ����q, ������r.
// ����, ��Ŀ��˵, ����, ��, ���������ǵȲ�����, ���ǲ���һ��������˳��, ��Ҫ����ȷ��˳��.
// ��Ȼ, d > r, ���Լ���d > q > r(�����������֤���ǲ����ܵ�, ֻ��q > d > r����, ���ǽ���q��d��λ��,
// Ҳ���Եõ�ǰ��Ĺ�ʽ)
//
// <TODO>
// ��һ������, ���ǵ�q > d > rʱ, ����q, d��λ��, ����q | n, ʹ��rΪ0. ������û�������������, 
// ���ǻ�����Ҫ��Ϊ�ϸ��֤��.
// </TODO>
//
// �蹫��Ϊa, ��ôq = ar, d = aar, ��a > 1. ��Ϊa�����Ƿ���, ���Խ�aд�� b / c����ʽ, ��gcd(b,c) = 1.
// ��Ϊd, q, r����������, br / c��brr / c����������.
// ����gcd(b, c) = 1, ����, c�б�Ȼ��������rr, ��������������е�rԼ��.
// ��r = ecc, ����r, e��һ��������, cΪa�ķ�ĸ.
// ���ݳ������������, n = dq + r = dar * arr + r = d(r^2)(a^3) + r = (e^2)(c^4)(a^3) + e(c^2) = (e^2)((ac)^3)c + e(c^2)
// ��Ϊc��a�ķ�ĸ, ����ac����a�ķ���, ��Ϊb.
// ��(e^2)(b^3)c + e(c^2) = n.
// ��ʱ, ��ʽ�е��κα�������������, b��a�ķ���, c��a�ķ�ĸ, ��Ϊa > 1, ����b > c.
// ������, ö��������ֵ.
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