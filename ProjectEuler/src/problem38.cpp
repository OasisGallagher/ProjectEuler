#include <math.h>
//因为需要最大值，所以首先假设这个值是9开始的。
//如果开始的数（等同于例子中的192）n，是3位数，那么2×n是4位数，3×n是4位数，不能满足9位数的需求。
//如果n是2位数，那么2×n是3位数，3×n是3位数，此时已经占用了8位数，所以也不可能。
//如果n是1位数，也就是9，那么结果为918273645。
//对于4位数而言，为9xyz，如果x大于4，那么2×n就会是19ijk，会与开始的四位数中的9冲突。所以，
//这个4位数的上界应该减少到9487。
//再来考虑下界，因为要9开头，所以9123。但是，对于2×n，一定是1hijk（上面解释了为什么确切是19xxx），
//所以，开始的数字中不能再有1。所以下界紧确到9234。
extern bool IsPandigital(unsigned number);

static inline
unsigned ConcatentNumbers(unsigned number1, unsigned number2)
	{
	return number1 * ((int)pow(10.0, 1 + (int)log10((double)number2))) + number2;
	}

unsigned GetTheLargest1To9Pandigital9DigitNumberThatCanBeFormedAsTheConcatenatedProductOfAnIntegerWith1ToNWhereNIsGreaterThan1()
	{
	for(unsigned i = 9487; i >= 9234; --i)
		{
		unsigned temp = ConcatentNumbers(i, 2 * i);
		if(IsPandigital(temp))
			return temp > 918273645 ? temp : 918273645;
		}
	return -1;
	}
