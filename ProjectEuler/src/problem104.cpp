#define Sieve	1000000000		// Sieves the last 9 digits of a number.
#include <cmath>

struct Pair
{
	typedef unsigned __int64 Number;
	Pair(Number h, Number l):high(h), low(l){}
	Number high;
	Number low;
};

static bool PanHelper(Pair::Number number)
{
	int sieve = 0;
	for(; number != 0; number /= 10)
	{
		int tmp = sieve;
		sieve |= (1u << (number % 10));
		if(tmp == sieve)
			return false;
	}
	return sieve == ((1 << 10) - 2);
}

static Pair::Number HighNineDigits(Pair::Number number)
{
	for(; number >= Sieve; number /= 10)
		;
	return number;
}

static inline bool Pandigital(const Pair& number)
{
	return PanHelper(number.low) && PanHelper(HighNineDigits(number.high));
}

int solve_104()
{
	Pair num0(1, 1), num1(1, 1);
	int result = 2;

#ifdef ApproachOne
	const Pair::Number Max = (~((Pair::Number)0)) / 10;	// UINT64_MAX / 10
	for(; !Pandigital(num1); ++result)
	{
		// It's easy to handle the low-9 digits.
		Pair::Number t_low = num1.low;
		num1.low = (num1.low + num0.low) % Sieve;
		num0.low = t_low;

		Pair::Number t_high = num1.high + num0.high;

		// dig_count(x) + dig_count(y) <= 1 + max(dig_count(x), dig_count(y)).
		if(t_high > Max)
		{
			// num1.high is a little too big, shrink it.
			t_high /= 10;
			num1.high /= 10;
		}

		num0.high = num1.high;
		num1.high = t_high;
	}
#else	// Another approach, amazing.
	for(; ; )
	{
		++result;
		// It's easy to handle the low-9 digits.
		Pair::Number t_low = num1.low;
		num1.low = (num1.low + num0.low) % Sieve;
		num0.low = t_low;

		if(PanHelper(num1.low))
		{
			// F(n) = ((phi ^ n) / sqrt(5.0)).
			// phi = (1 + sqrt(5)) / 2, 黄金分割.
			// 设 l_10 = log10(F(n))
			// 然后计算
			// pow(10, 8.0 + (l_10的小数部分)).
			// 因为是10的乘方,所以非000项都是由10的小数次方产生的.
			// 当n足够大时,这个值非常接近F(n).
			// log(pi) = 0.20898764024997873.
			// log(sqrt(5)) = 0.3494850021680094.
			const double t = (result * 0.20898764024997873 - 0.3494850021680094);
			num1.high = (Pair::Number)pow(10, t - (Pair::Number)t + 8.0);
			if(PanHelper(num1.high))
				break;
		}
	}
#endif
	return result;
}

/*#include <string>
#define MaxDigits	1024 * 1024

class integer
{
public:
	integer(int number = 0): dig_count_(0)
	{
		__from_int(number);
	}
	integer operator + (const integer& other)
	{
		integer result;
		__plus_helper(other, &result);
		return result;
	}
	integer& operator += (const integer& other)
	{
		__plus_helper(other, this);
		return *this;
	}
	operator bool()
	{
		return __valid();
	}
private:
	bool __valid()
	{
		return __dig_count() >= 9 
		? (__pandigital(data_.substr(__dig_count() - 9, 9)) && __pandigital(data_.substr(0, 9)))
		: false;
	}
	void __plus_helper(const integer& other, integer* dest)
	{
		integer result;
		int carry = 0;
		const int digs = 1 + std::max(__dig_count(), other.__dig_count());
		if(digs >= MaxDigits)
			throw "overflow";

		for(int i = 0; i < digs; ++i)
		{
			int tmp = other.data_[i] + data_[i];
			dest->data_[i] = (tmp + carry) % 10;
			carry = (tmp + carry) / 10;
		}
		dest->__set_dig_count(digs);
	}
	bool __pandigital(const std::string& str)
	{
		int sieve = 0;
		for(std::string::const_iterator ite = str.begin(); ite != str.end(); ++ite)
		{
			int tmp = sieve;
			sieve |= (1u << *ite);
			if(tmp == sieve)
				return false;
		}
		return sieve == ((1 << 10) - 2);
	}
	void __set_dig_count(int upper_bound)
	{
		dig_count_ = upper_bound;
		for(int i = upper_bound - 1; i >= 0 && data_[i] == 0; --i, --dig_count_)
			;
	}
	int __dig_count()const
	{
		return dig_count_;
	}
	void __from_int(int number)
	{
		for(; number != 0; number /= 10, ++dig_count_)
			data_.push_back(number % 10);
		std::reverse(data_.begin(), data_.end());
		data_.resize(MaxDigits);
	}
	int dig_count_;
	std::string data_;
};

int solve_104()
{
	integer i(1), j(1);
	int k = 3;
	for(; !j; ++k)
	{
		integer tmp = i;
		i = j;
		j += tmp;
	}
	return k;
}
*/