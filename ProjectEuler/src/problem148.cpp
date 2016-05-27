#include <iostream>
#include <ctime>

typedef unsigned __int64 Number;
// pascal三角的行, 从0开始记.
// 对于n!中含有多少个7,  例如, 对于35, 可以知道35!中, 含有5个7因子.
// 然而对于49, 则是7 + 1 = 8个7因子, 因为49中含有2个.
// 因此, 可以这样计算:
/*
unsigned Count7InNumberFact(unsigned n) {
	unsigned result = 0;
	for(; n != 0; n /= 7)
		result += (n / 7);
	return result;
}
*/
// 由此可知, 对于7的倍数的行, 必然只有不能被7整除的数, 即两个1.
// 可以推测出, 在[0, 7)行中, 有28个不能被7整除的数.
// 在第7行, 有2个不能被7整除的数, 因此, 可以推测出, 第14行, 有三个.
// 第49行依然有两个, 因此, [0, 49)行, 有28 * 28个.
// 而且他们组成的图形, 类似sierpinski三角形, 中空的部分是可以被7整除的.
// 从第49行开始, 之后组成的图形依然与[0, 49)行的相似, 只是三角形高度最高
// 的角是[0, 49)行..
// 以此类推...

int main() {
	clock_t beg = clock();
	unsigned crows = 1000000000;
	Number result = 0;
	unsigned width = 1;
	unsigned product = 1;
	Number cell = 1;

	do {
		unsigned height = 1;

		cell = 1;
		for(; height * 7 < crows; height *= 7) cell *= 28;

		if(cell == 1) {
			crows = (1 + crows) * crows / 2;
			result += crows * product;
		}
		else {
			unsigned count = crows / height;

			unsigned sum = (1 + count) * count / 2;

			crows = crows % height;

			result += product * sum * cell;

			product *= (count + 1);
		}
	}while(cell != 1);

	std::cout << result << std::endl;
	std::cout << float(clock() - beg) / CLOCKS_PER_SEC << " second(s)." << std::endl;
	return 0;
}
