#include <iostream>
#include <ctime>
#include <fstream>
// 608720
static unsigned buffer[9] = { unsigned(-1) };
static unsigned len = 1;

static bool Check(unsigned n) {
	unsigned j = 0;
	buffer[j] += 2;
	for(; buffer[j] >= 10; ++buffer[++j])
		buffer[j] %= 10;

	if(j + 1 > len) ++len;

	if(buffer[0] == 0) return false;

	unsigned carry = 0;
	for(unsigned i = 0; i < len; ++i) {
		carry += buffer[i] + buffer[len - i - 1];
		if((carry & 1) == 0) return false;
		carry /= 10;
	}

	return true;
}

static unsigned BruteForce() {	// 29.6s
	unsigned count = 0;
	for(unsigned i = 1; i < 1000000000; i += 2) {
		// 首尾必须奇偶相异, 因此, 只迭代尾数为奇数的, 再乘2.
		if(Check(i)) {
			count += 2;
		}
	}
	return count;
}

unsigned Pow(unsigned x, unsigned y) {
	unsigned result = 1;
	for(; ; x *= x) {
		if((y & 1) != 0)
			result *= x;
		if((y >>= 1) == 0)
			return result;
	}
	return 0;
}

static unsigned ByHand() {
	// 根据奇偶性, 以及是否进位, 按数的位数逐个分析.
	unsigned result = 0;
	for(unsigned bitcount = 1; bitcount < 10; ++bitcount) {
		unsigned tmp = 0;
		switch(bitcount) {
		case 1:
			tmp = 0;
			break;
		case 2:
			tmp = 20;
			break;
		case 3:
			tmp = 100;
			break;
		case 4:
			tmp = 20 * Pow(30, 1);
			break;
		case 5:
			tmp = 0;
			break;
		case 6:
			tmp = 20 * Pow(30, 2);
			break;
		case 7:
			tmp = 20 * 25 * 20 * 5;
			break;
		case 8:
			tmp = 20 * Pow(30, 3);
			break;
		case 9:
			tmp = 0;
			break;
		default:
			tmp = 0;
			break;
		}
		result += tmp;
	}
	return result;
}

int main() {
	clock_t start = clock();
	std::cout << BruteForce() << std::endl;
	//std::cout << ByHand() << std::endl;
	std::cout << (clock() - start) / float(CLOCKS_PER_SEC) << " second(s).\n";
	return 0;
}